#include <sourcemeta/core/gzip.h>

#include "bit_reader.h"
#include "deflate.h"

#include <sourcemeta/core/crypto.h>

#include <array>       // std::array
#include <cstddef>     // std::size_t, std::ptrdiff_t
#include <cstdint>     // std::uint8_t, std::uint16_t, std::uint32_t
#include <istream>     // std::istream
#include <string_view> // std::string_view
#include <vector>      // std::vector

namespace sourcemeta::core {

static constexpr std::size_t GZIP_BUFFER_SIZE{16384};

struct GZIPStreamBuffer::Internal {
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
  std::istream &stream;
  BitReader reader;
  DeflateDecoder deflate;
  bool stream_ended{false};
  bool any_member_completed{false};
  bool member_started{false};
  std::uint32_t member_crc32{0};
  std::uint32_t member_isize{0};
  std::array<std::uint8_t, GZIP_BUFFER_SIZE> decompressed_buffer{};

  Internal(std::istream &source)
      : stream{source}, reader{source}, deflate{reader} {}
};

namespace {

auto try_read_first_byte(BitReader &reader, std::uint8_t &first_byte) -> bool {
  try {
    first_byte = reader.read_byte();
    return true;
  } catch (const GZIPError &) {
    return false;
  }
}

auto parse_member_header(BitReader &reader, const std::uint8_t first_byte,
                         std::vector<std::uint8_t> &header_bytes) -> void {
  // Caller already consumed the ID1 byte and verified it is 0x1f
  header_bytes.push_back(first_byte);
  const auto id2{reader.read_byte()};
  header_bytes.push_back(id2);
  if (id2 != 0x8b) {
    throw GZIPError{"Invalid gzip magic bytes"};
  }
  const auto compression_method{reader.read_byte()};
  header_bytes.push_back(compression_method);
  if (compression_method != 8) {
    throw GZIPError{"Unsupported gzip compression method"};
  }
  const auto flag_byte{reader.read_byte()};
  header_bytes.push_back(flag_byte);
  if ((flag_byte & 0xe0) != 0) {
    throw GZIPError{"Reserved gzip FLG bits must be zero"};
  }

  // MTIME (4 bytes) + XFL (1 byte) + OS (1 byte) are informational
  for (std::size_t index = 0; index < 6; ++index) {
    header_bytes.push_back(reader.read_byte());
  }

  if ((flag_byte & 0x04) != 0) {
    // FEXTRA
    const auto xlen_lo{reader.read_byte()};
    const auto xlen_hi{reader.read_byte()};
    header_bytes.push_back(xlen_lo);
    header_bytes.push_back(xlen_hi);
    const auto xlen{static_cast<std::size_t>(xlen_lo) |
                    (static_cast<std::size_t>(xlen_hi) << 8)};
    for (std::size_t index = 0; index < xlen; ++index) {
      header_bytes.push_back(reader.read_byte());
    }
  }

  if ((flag_byte & 0x08) != 0) {
    // FNAME (null-terminated)
    while (true) {
      const auto byte{reader.read_byte()};
      header_bytes.push_back(byte);
      if (byte == 0) {
        break;
      }
    }
  }

  if ((flag_byte & 0x10) != 0) {
    // FCOMMENT (null-terminated)
    while (true) {
      const auto byte{reader.read_byte()};
      header_bytes.push_back(byte);
      if (byte == 0) {
        break;
      }
    }
  }

  if ((flag_byte & 0x02) != 0) {
    // FHCRC: low 16 bits of CRC-32 over all preceding header bytes
    const auto stored_lo{reader.read_byte()};
    const auto stored_hi{reader.read_byte()};
    const std::uint16_t stored{static_cast<std::uint16_t>(
        static_cast<std::uint16_t>(stored_lo) |
        static_cast<std::uint16_t>(static_cast<std::uint16_t>(stored_hi)
                                   << 8))};
    const auto checksum{crc32(
        std::string_view{reinterpret_cast<const char *>(header_bytes.data()),
                         header_bytes.size()})};
    const std::uint16_t computed{
        static_cast<std::uint16_t>(checksum & 0xffffu)};
    if (stored != computed) {
      throw GZIPError{"FHCRC mismatch"};
    }
  }
}

} // namespace

GZIPStreamBuffer::GZIPStreamBuffer(std::istream &compressed_stream)
    : internal{new Internal{compressed_stream}} {}

GZIPStreamBuffer::~GZIPStreamBuffer() = default;

auto GZIPStreamBuffer::underflow() -> int_type {
  if (this->gptr() && this->gptr() < this->egptr()) {
    return traits_type::to_int_type(*this->gptr());
  }
  if (this->internal->stream_ended) {
    return traits_type::eof();
  }

  while (true) {
    if (!this->internal->member_started) {
      std::uint8_t first_byte{0};
      if (!try_read_first_byte(this->internal->reader, first_byte)) {
        if (!this->internal->any_member_completed) {
          throw GZIPError{"Empty source stream"};
        }
        this->internal->stream_ended = true;
        return traits_type::eof();
      }
      if (first_byte != 0x1f) {
        if (!this->internal->any_member_completed) {
          throw GZIPError{"Invalid gzip magic bytes"};
        }
        // Trailing garbage after a complete member is silently ignored
        this->internal->stream_ended = true;
        return traits_type::eof();
      }
      std::vector<std::uint8_t> header_bytes;
      parse_member_header(this->internal->reader, first_byte, header_bytes);

      this->internal->deflate.reset();
      this->internal->member_started = true;
      this->internal->member_crc32 = 0;
      this->internal->member_isize = 0;
    }

    const auto produced{this->internal->deflate.decompress(
        this->internal->decompressed_buffer.data(),
        this->internal->decompressed_buffer.size())};

    if (produced > 0) {
      this->internal->member_crc32 = crc32_update(
          this->internal->member_crc32,
          std::string_view{reinterpret_cast<const char *>(
                               this->internal->decompressed_buffer.data()),
                           produced});
      this->internal->member_isize += static_cast<std::uint32_t>(produced);

      auto *buffer_start{
          reinterpret_cast<char *>(this->internal->decompressed_buffer.data())};
      this->setg(buffer_start, buffer_start,
                 buffer_start + static_cast<std::ptrdiff_t>(produced));
      return traits_type::to_int_type(*this->gptr());
    }

    if (!this->internal->deflate.stream_ended()) {
      throw GZIPError{"Deflate stream ended unexpectedly"};
    }

    std::array<std::uint8_t, 8> trailer{};
    this->internal->reader.read_bytes(trailer.data(), trailer.size());
    const auto stored_crc32{static_cast<std::uint32_t>(trailer[0]) |
                            (static_cast<std::uint32_t>(trailer[1]) << 8) |
                            (static_cast<std::uint32_t>(trailer[2]) << 16) |
                            (static_cast<std::uint32_t>(trailer[3]) << 24)};
    const auto stored_isize{static_cast<std::uint32_t>(trailer[4]) |
                            (static_cast<std::uint32_t>(trailer[5]) << 8) |
                            (static_cast<std::uint32_t>(trailer[6]) << 16) |
                            (static_cast<std::uint32_t>(trailer[7]) << 24)};
    if (stored_crc32 != this->internal->member_crc32) {
      throw GZIPError{"Gzip member CRC32 mismatch"};
    }
    if (stored_isize != this->internal->member_isize) {
      throw GZIPError{"Gzip member ISIZE mismatch"};
    }

    this->internal->any_member_completed = true;
    this->internal->member_started = false;
  }
}

} // namespace sourcemeta::core
