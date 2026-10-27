#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/html.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/text.h>
#include <sourcemeta/core/unicode.h>

#include <algorithm>   // std::any_of, std::all_of, std::find_if
#include <array>       // std::array
#include <cctype>      // std::toupper
#include <cmath>       // std::floor, std::fabs, std::isfinite
#include <cstddef>     // std::size_t
#include <cstdint>     // std::uint32_t, std::int64_t
#include <cstdio>      // std::snprintf
#include <deque>       // std::deque
#include <iterator>    // std::prev
#include <map>         // std::map
#include <optional>    // std::optional
#include <set>         // std::set
#include <sstream>     // std::ostringstream
#include <string>      // std::string
#include <string_view> // std::string_view
#include <utility>     // std::move, std::pair
#include <vector>      // std::vector

// The table format into a page. This renderer reads the table format and
// nothing else, so it draws a page for a schema of any language that was
// converted into it. It writes bare markup with no stylesheet, so whoever shows
// the page styles it through the class names on it. It holds:
//
// - the shapes everything else is built on, before the things built on them
// - one row per property, with limits drawn rather than written
// - a thing inside a thing is a table inside that row
// - inherited properties behind one strip, opened in place
// - a shape pointed at is a link to where it is written out once
//
// No scripting, no JSON on the page.

namespace {

using sourcemeta::core::JSON;

auto at(const JSON *value, const std::string &key) -> const JSON * {
  if (value == nullptr || !value->is_object() || !value->defines(key)) {
    return nullptr;
  }

  return &value->at(key);
}

auto truthy(const JSON *value) -> bool {
  if (value == nullptr || value->is_null()) {
    return false;
  }

  if (value->is_boolean()) {
    return value->to_boolean();
  }

  if (value->is_integer()) {
    return value->to_integer() != 0;
  }

  if (value->is_real()) {
    return value->to_real() != 0 && !std::isnan(value->to_real());
  }

  if (value->is_string()) {
    return !value->to_string().empty();
  }

  if (value->is_decimal()) {
    return !(*value == JSON{static_cast<std::int64_t>(0)});
  }

  return true;
}

// Present and not null.
auto given(const JSON *value) -> bool {
  return value != nullptr && !value->is_null();
}

auto list(const JSON *value, const std::string &key)
    -> std::vector<const JSON *> {
  std::vector<const JSON *> result;
  const auto *entries{at(value, key)};
  if (entries != nullptr && entries->is_array()) {
    for (const auto &entry : entries->as_array()) {
      result.push_back(&entry);
    }
  }

  return result;
}

auto count(const JSON *value, const std::string &key) -> std::size_t {
  const auto *entries{at(value, key)};
  return entries != nullptr && entries->is_array() ? entries->array_size() : 0;
}

auto kind(const JSON *value) -> std::string {
  const auto *entry{at(value, "kind")};
  return entry != nullptr && entry->is_string() ? entry->to_string() : "";
}

auto is_one(const JSON *value) -> bool {
  return value != nullptr && value->is_number() &&
         !(*value < JSON{static_cast<std::int64_t>(1)}) &&
         !(JSON{static_cast<std::int64_t>(1)} < *value);
}

// A value written the way the reference renderer writes it.
auto text(const JSON *value) -> std::string;

auto number_text(const JSON &value) -> std::string {
  if (value.is_integer()) {
    return std::to_string(value.to_integer());
  }

  if (value.is_real()) {
    const auto real{value.to_real()};
    if (std::isfinite(real) && std::floor(real) == real &&
        std::fabs(real) < 1e21) {
      std::array<char, 32> buffer{};
      std::snprintf(buffer.data(), buffer.size(), "%.0f", real);
      const std::string result{buffer.data()};
      return result == "-0" ? "0" : result;
    }
  }

  // The shortest form that reads back as the same number.
  std::ostringstream stream;
  sourcemeta::core::stringify(value, stream);
  return stream.str();
}

auto text(const JSON *value) -> std::string {
  if (value == nullptr) {
    return "undefined";
  }

  if (value->is_string()) {
    return value->to_string();
  }

  if (value->is_number()) {
    return number_text(*value);
  }

  if (value->is_boolean()) {
    return value->to_boolean() ? "true" : "false";
  }

  if (value->is_null()) {
    return "null";
  }

  if (value->is_array()) {
    std::string result;
    auto first{true};
    for (const auto &entry : value->as_array()) {
      if (!first) {
        result += ',';
      }

      first = false;
      if (!entry.is_null()) {
        result += text(&entry);
      }
    }

    return result;
  }

  return "[object Object]";
}

auto text(const JSON *value, const std::string &key) -> std::string {
  return text(at(value, key));
}

// Values a reader sees, never JSON.
auto plain(const JSON *value) -> std::string {
  if (value == nullptr) {
    return "undefined";
  }

  if (value->is_boolean()) {
    return value->to_boolean() ? "yes" : "no";
  }

  if (value->is_null()) {
    return "nothing";
  }

  if (value->is_array()) {
    if (value->empty()) {
      return "an empty list";
    }

    std::vector<std::string> parts;
    for (const auto &entry : value->as_array()) {
      parts.push_back(plain(&entry));
    }

    return sourcemeta::core::join(parts, ", ");
  }

  if (value->is_object()) {
    return "a group of details";
  }

  return text(value);
}

auto plain_all(const JSON *values, const std::string_view glue) -> std::string {
  std::vector<std::string> parts;
  if (values != nullptr && values->is_array()) {
    for (const auto &entry : values->as_array()) {
      parts.push_back(plain(&entry));
    }
  }

  return sourcemeta::core::join(parts, glue);
}

// Whether a value is the same as another by the strict equality of the
// reference renderer: scalars by value, anything with parts never.
auto strictly_equal(const JSON *left, const JSON *right) -> bool {
  if (left == nullptr || right == nullptr) {
    return left == right;
  }

  if (left->is_array() || left->is_object() || right->is_array() ||
      right->is_object()) {
    return false;
  }

  if (left->is_number() && right->is_number()) {
    return !(*left < *right) && !(*right < *left);
  }

  return *left == *right;
}

// A shape's identifier is opaque, so two that read alike must still get two
// anchors. The readable part is the identifier with anything an anchor cannot
// hold turned into a dash, and when that loses something, a short mark of the
// identifier itself is added.

auto tidy(const std::string_view identifier) -> std::string {
  std::string result;
  auto dash{false};
  for (const auto character : identifier) {
    const auto keep{(character >= 'a' && character <= 'z') ||
                    (character >= 'A' && character <= 'Z') ||
                    (character >= '0' && character <= '9')};
    if (keep) {
      if (dash && !result.empty()) {
        result += '-';
      }

      dash = false;
      result += character;
    } else {
      dash = true;
    }
  }

  return result;
}

auto mark(const std::string_view identifier) -> std::string {
  std::uint32_t hash{0x811c9dc5};
  for (const auto point :
       sourcemeta::core::utf8_to_utf32(identifier).value_or(std::u32string{})) {
    hash ^= static_cast<std::uint32_t>(point);
    hash *= 0x01000193;
  }

  if (hash == 0) {
    return "0";
  }

  std::string result;
  while (hash > 0) {
    const auto digit{hash % 36};
    result.insert(
        result.begin(),
        static_cast<char>(digit < 10 ? '0' + digit : 'a' + digit - 10));
    hash /= 36;
  }

  return result;
}

auto anchor(const std::string_view identifier) -> std::string {
  if (identifier.empty()) {
    return "root";
  }

  const auto readable{tidy(identifier)};
  if (readable == identifier) {
    return "shape-" + readable;
  }

  return "shape-" + readable + "-" + mark(identifier);
}

// An address from a schema is shown as a link only when following it is safe.
// A browser throws away tabs, newlines and control characters before it reads
// an address, so they are thrown away here too.
auto linkable(const std::string_view address) -> bool {
  std::string bare;
  for (const auto point :
       sourcemeta::core::utf8_to_utf32(address).value_or(std::u32string{})) {
    if (point > 32 && point != 127) {
      // Only the start matters, which is ASCII when it is a scheme at all.
      bare += point < 128 ? static_cast<char>(point) : '?';
    }
  }

  std::size_t position{0};
  if (!bare.empty() && sourcemeta::core::is_alpha(bare[0])) {
    position = 1;
    while (position < bare.size() &&
           (sourcemeta::core::is_alphanum(bare[position]) ||
            bare[position] == '+' || bare[position] == '.' ||
            bare[position] == '-')) {
      position += 1;
    }

    if (position < bare.size() && bare[position] == ':') {
      std::string scheme{bare.substr(0, position)};
      sourcemeta::core::to_lowercase(scheme);
      return scheme == "http" || scheme == "https" || scheme == "mailto";
    }
  }

  return !bare.starts_with("//");
}

auto type_words(const std::string &name) -> std::string {
  static const std::map<std::string, std::string> WORDS{
      {"string", "text"},
      {"integer", "a whole number"},
      {"number", "a number"},
      {"boolean", "yes or no"},
      {"object", "a group of properties"},
      {"array", "a list"},
      {"null", "nothing"}};
  const auto match{WORDS.find(name)};
  return match == WORDS.cend() ? "undefined" : match->second;
}

// A declared format is a stronger statement than the type underneath it, so
// when one is present it is what the reader is told.
auto format_words(const JSON *format) -> std::optional<std::string> {
  static const std::map<std::string, std::string> WORDS{
      {"date-time", "a date and time"},
      {"date", "a date"},
      {"time", "a time"},
      {"uri", "a web address"},
      {"uri-reference", "a web address"},
      {"url", "a web address"},
      {"email", "an email address"},
      {"hostname", "a computer name"},
      {"ipv4", "an IP address"},
      {"ipv6", "an IP address"},
      {"uuid", "a unique id"},
      {"regex", "a search pattern"}};
  if (format == nullptr) {
    return std::nullopt;
  }

  const auto match{WORDS.find(text(format))};
  if (match == WORDS.cend()) {
    return std::nullopt;
  }

  return match->second;
}

// What a length counts, by the kind it is on.
auto count_words(const std::string &name) -> std::string {
  if (name == "string") {
    return " characters";
  }

  if (name == "array") {
    return " entries";
  }

  if (name == "object") {
    return " properties";
  }

  return "";
}

// A value with nothing on it beyond its kind, which a short phrase says fully.
auto is_simple(const JSON *value) -> bool {
  if (value == nullptr) {
    return false;
  }

  if (!value->is_object()) {
    return true;
  }

  return std::all_of(value->as_object().cbegin(), value->as_object().cend(),
                     [](const auto &entry) {
                       return entry.first == "kind" ||
                              entry.first == "format" ||
                              entry.first == "title" ||
                              entry.first == "description";
                     });
}

auto only_keys(const JSON *value, const std::set<std::string> &allowed)
    -> bool {
  return value != nullptr && value->is_object() &&
         std::all_of(value->as_object().cbegin(), value->as_object().cend(),
                     [&allowed](const auto &entry) {
                       return allowed.contains(entry.first);
                     });
}

struct Draw {
  std::map<std::string, const JSON *> shapes;
  std::map<std::string, std::size_t> stats;
  std::set<std::string> inlining;
  // Values put together while drawing, which the page points into.
  std::deque<JSON> kept;

  auto keep(JSON value) -> const JSON * {
    this->kept.push_back(std::move(value));
    return &this->kept.back();
  }

  [[nodiscard]] auto shape(const std::string &identifier) const
      -> const JSON * {
    const auto match{this->shapes.find(identifier)};
    return match == this->shapes.cend() ? nullptr : match->second;
  }

  [[nodiscard]] auto name_of(const std::string &identifier) const
      -> std::string;
};

// What to call a shape: the author's title, or the name it is declared under.
auto shape_name(const JSON *shape) -> std::string {
  const auto *title{at(at(shape, "value"), "title")};
  if (truthy(title)) {
    return text(title);
  }

  return text(shape, "name");
}

auto Draw::name_of(const std::string &identifier) const -> std::string {
  if (identifier.empty()) {
    return "this whole document";
  }

  const auto *found{this->shape(identifier)};
  if (found != nullptr) {
    return shape_name(found);
  }

  const auto slash{identifier.rfind('/')};
  return slash == std::string::npos ? identifier : identifier.substr(slash + 1);
}

// The short phrase for a value, worked out from its facts alone.
auto label(const JSON *value, const Draw &draw) -> std::string {
  if (value == nullptr) {
    return "no rule beyond being there";
  }

  const auto name{kind(value)};
  if (name == "any") {
    return "anything";
  }

  if (name == "never") {
    return "nothing is allowed here";
  }

  if (name == "external") {
    return "follows rules kept in another file";
  }

  if (name == "ref") {
    return draw.name_of(text(value, "ref"));
  }

  if (name == "choice") {
    const auto options{list(value, "options")};
    if (!options.empty() &&
        std::all_of(options.cbegin(), options.cend(),
                    [](const auto *option) { return kind(option) == "ref"; })) {
      std::vector<std::string> names;
      names.reserve(options.size());
      for (const auto *option : options) {
        names.push_back(draw.name_of(text(option, "ref")));
      }

      return "either " + sourcemeta::core::join(names, " or ");
    }

    if (!options.empty() &&
        std::all_of(options.cbegin(), options.cend(), is_simple) &&
        !truthy(at(value, "overlap"))) {
      std::vector<std::string> phrases;
      phrases.reserve(options.size());
      for (const auto *option : options) {
        phrases.push_back(label(option, draw));
      }

      return sourcemeta::core::join(phrases, " or ");
    }

    return "one of " + std::to_string(options.size()) + " forms";
  }

  if (name == "enum") {
    return count(value, "values") == 1 ? "a fixed value" : "one of these";
  }

  if (name == "array") {
    return "a list";
  }

  if (name == "object") {
    return "a group of properties";
  }

  if (name == "boolean") {
    return "yes or no";
  }

  if (name == "null") {
    return "nothing (null)";
  }

  if (name == "string" || name == "number" || name == "integer") {
    const auto *format{at(value, "format")};
    const auto words{format_words(format)};
    if (name == "string" && truthy(format) && words.has_value()) {
      return words.value();
    }

    return type_words(name) +
           (truthy(format) && !(name == "string" && words.has_value())
                ? " (" + text(format) + ")"
                : "");
  }

  return "a value";
}

// The first example a reader can take in at a glance.
auto first_example(const JSON *value) -> const JSON * {
  for (const auto *example : list(value, "examples")) {
    if (!example->is_array() && !example->is_object()) {
      return example;
    }
  }

  return nullptr;
}

// How a pattern is presented: exactly as written, with an example if there is
// one.
auto pattern_note(const JSON *pattern, const JSON *example)
    -> std::optional<std::string> {
  if (!truthy(pattern)) {
    return std::nullopt;
  }

  auto shown{"matching " + text(pattern)};
  if (example != nullptr) {
    shown += ", for example " + plain(example);
  }

  return shown;
}

auto pattern_note(const JSON *value) -> std::optional<std::string> {
  return pattern_note(at(value, "pattern"), first_example(value));
}

auto range_word(const JSON *bounds, const std::string &edge) -> std::string {
  if (edge == "min") {
    return truthy(at(bounds, "minExclusive")) ? "above" : "from";
  }

  return truthy(at(bounds, "maxExclusive")) ? "below" : "up to";
}

// The facts a value carries beyond its kind, in a few words.
auto facts_of(const JSON *value) -> std::string {
  if (value == nullptr || !value->is_object()) {
    return "";
  }

  std::vector<std::string> said;
  const auto pattern{pattern_note(value)};
  if (pattern.has_value()) {
    said.push_back(pattern.value());
  }

  if (truthy(at(value, "format"))) {
    said.push_back("written as " + text(value, "format"));
  }

  if (const auto *range{at(value, "range")}; truthy(range)) {
    if (given(at(range, "min"))) {
      said.push_back(range_word(range, "min") + " " + plain(at(range, "min")));
    }

    if (given(at(range, "max"))) {
      said.push_back(range_word(range, "max") + " " + plain(at(range, "max")));
    }
  }

  const auto bounded = [&said](const JSON *bounds, const std::string &unit) {
    const auto *minimum{at(bounds, "min")};
    const auto *maximum{at(bounds, "max")};
    if (given(minimum) && given(maximum)) {
      said.push_back(plain(minimum) + " to " + plain(maximum) + " " + unit);
    } else if (given(minimum)) {
      said.push_back("at least " + plain(minimum) + " " + unit);
    } else if (given(maximum)) {
      said.push_back("at most " + plain(maximum) + " " + unit);
    }
  };

  if (const auto *length{at(value, "length")}; truthy(length)) {
    bounded(length, kind(value) == "array" ? "entries" : "characters");
  }

  if (given(at(value, "multipleOf"))) {
    said.push_back("in steps of " + plain(at(value, "multipleOf")));
  }

  if (const auto *amount{at(value, "propertyCount")}; truthy(amount)) {
    bounded(amount, "properties");
  }

  if (truthy(at(value, "unique"))) {
    said.emplace_back("no two entries the same");
  }

  if (truthy(at(value, "closed"))) {
    said.emplace_back("no other properties");
  }

  if (const auto *keys{at(value, "keys")};
      truthy(keys) && truthy(at(keys, "pattern"))) {
    said.push_back("names matching " + text(keys, "pattern"));
  }

  if (truthy(at(value, "nullable"))) {
    said.emplace_back("or nothing");
  }

  if (truthy(at(value, "deprecated"))) {
    said.emplace_back("no longer used");
  }

  if (truthy(at(value, "otherTypesAllowed"))) {
    said.emplace_back("other kinds pass these rules");
  }

  if (const auto more{count(value, "also")}; more > 0) {
    said.push_back("and " + (more == 1 ? std::string{"one more rule"}
                                       : std::to_string(more) + " more rules"));
  }

  if (count(value, "conditions") > 0) {
    said.emplace_back("with rules for some cases");
  }

  return sourcemeta::core::join(said, ", ");
}

// What a condition turns on, read from the value it tests.
auto condition_text(const JSON *condition) -> std::string {
  const auto *when{at(condition, "when")};
  const auto properties{kind(when) == "object" ? list(when, "properties")
                                               : std::vector<const JSON *>{}};
  if (properties.size() == 1) {
    const auto *first{properties.front()};
    const auto *value{at(first, "value")};
    if (truthy(value) && kind(value) == "enum" && count(value, "values") == 1) {
      // A test on a property's value also passes when it is not there.
      // Only text is quoted, so the number 1 does not read as the text "1".
      const auto name{text(first, "name")};
      const auto &fixed{at(value, "values")->at(0)};
      return "when " + name + " is " +
             (fixed.is_string() ? "\"" + fixed.to_string() + "\""
                                : text(&fixed)) +
             (truthy(at(first, "required")) ? ""
                                            : ", or " + name + " is left out");
    }
  }

  if (!properties.empty() &&
      std::all_of(properties.cbegin(), properties.cend(),
                  [](const auto *property) {
                    return !truthy(at(property, "value")) &&
                           truthy(at(property, "required"));
                  })) {
    std::vector<std::string> names;
    names.reserve(properties.size());
    for (const auto *property : properties) {
      names.push_back(text(property, "name"));
    }

    return "when " + sourcemeta::core::join(names, " and ") + " " +
           (names.size() > 1 ? "are" : "is") + " filled in";
  }

  if (!properties.empty()) {
    std::vector<std::string> names;
    names.reserve(properties.size());
    for (const auto *property : properties) {
      names.push_back(text(property, "name"));
    }

    return "depending on " + sourcemeta::core::join(names, " and ");
  }

  return "in one case";
}

// The property a condition turns on when it only asks whether that one
// property is there, as in "when shippingMethod is filled in".
auto presence_of(const JSON *condition) -> std::optional<std::string> {
  const auto *when{at(condition, "when")};
  if (kind(when) != "object" || count(when, "properties") != 1 ||
      !only_keys(when, {"kind", "properties"})) {
    return std::nullopt;
  }

  const auto *first{list(when, "properties").front()};
  if (truthy(at(first, "required")) && !truthy(at(first, "value"))) {
    return text(first, "name");
  }

  return std::nullopt;
}

// What a value must not be, as phrases.
auto not_phrases(const JSON *value, const Draw &draw)
    -> std::vector<std::string> {
  if (!truthy(value)) {
    return {};
  }

  if (kind(value) == "choice" && truthy(at(value, "overlap"))) {
    std::vector<std::string> result;
    for (const auto *option : list(value, "options")) {
      for (auto &phrase : not_phrases(option, draw)) {
        result.push_back(std::move(phrase));
      }
    }

    return result;
  }

  if (kind(value) == "enum") {
    return {"must not be " + plain_all(at(value, "values"), " or ")};
  }

  const auto properties{list(value, "properties")};
  const auto filled{kind(value) == "object" && !properties.empty() &&
                    std::all_of(properties.cbegin(), properties.cend(),
                                [](const auto *property) {
                                  return truthy(at(property, "required")) &&
                                         !truthy(at(property, "value"));
                                }) &&
                    only_keys(value, {"kind", "properties", "otherTypesAllowed",
                                      "title", "description"})};
  const auto why{truthy(at(value, "description"))
                     ? " (" + text(value, "description") + ")"
                     : std::string{}};
  if (filled) {
    std::vector<std::string> names;
    names.reserve(properties.size());
    for (const auto *property : properties) {
      names.push_back(text(property, "name"));
    }

    return {(names.size() > 1
                 ? "you cannot use " + sourcemeta::core::join(names, " and ") +
                       " together"
                 : names.front() + " may not be used") +
            why};
  }

  const auto facts{facts_of(value)};
  return {"must not be " + label(value, draw) +
          (facts.empty() ? "" : " " + facts) + why};
}

auto pattern_name(const std::string &pattern) -> std::string {
  return "any name matching " + pattern;
}

constexpr std::string_view OTHER_NAME{"any name you choose"};

// Words that take no article: "each one text", not "each one a text".
auto with_article(const std::string &words) -> std::string {
  static const std::vector<std::string> BARE{
      "a",       "an",       "the",     "this", "one",      "either",
      "exactly", "anything", "nothing", "text", "yes or no"};
  std::string lower{words};
  sourcemeta::core::to_lowercase(lower);

  for (const auto &bare : BARE) {
    if (!lower.starts_with(bare)) {
      continue;
    }

    if (lower.size() == bare.size()) {
      return words;
    }

    const auto next{lower[bare.size()]};
    const auto word{sourcemeta::core::is_alphanum(next) || next == '_'};
    if (!word) {
      return words;
    }
  }

  const auto vowel{!lower.empty() &&
                   std::string_view{"aeiou"}.find(lower.front()) !=
                       std::string_view::npos};
  return (vowel ? "an " : "a ") + words;
}

auto capitalised(const std::string &sentence) -> std::string {
  if (sentence.empty()) {
    return sentence;
  }

  auto result{sentence};
  result[0] =
      static_cast<char>(std::toupper(static_cast<unsigned char>(result[0])));
  return result;
}

// A value said briefly, naming a fixed value outright.
auto brief(const JSON *value, const Draw &draw) -> std::string {
  if (truthy(value) && kind(value) == "enum") {
    const auto *values{at(value, "values")};
    if (count(value, "values") == 1) {
      return "the value " + plain(&values->at(0));
    }

    return "one of " + plain_all(values, ", ");
  }

  return with_article(label(value, draw));
}

enum class NameKind : std::uint8_t { Named, Pattern, Other };

struct Row {
  bool condition{false};
  const JSON *about{nullptr};
  // A row for a property. A property may be named with empty text, so whether
  // the row has a name is kept apart from the name itself.
  std::string name;
  bool has_name{false};
  const JSON *value{nullptr};
  bool required{false};
  NameKind name_kind{NameKind::Named};
  std::string pattern;
  const JSON *fallback{nullptr};
  std::vector<const JSON *> brings;
};

struct Inherited {
  std::string from;
  std::vector<Row> rows;
};

struct Rows {
  std::vector<Row> own;
  std::vector<Inherited> inherited;
};

auto row_count(const Rows &rows) -> std::size_t {
  auto result{rows.own.size()};
  for (const auto &group : rows.inherited) {
    result += group.rows.size();
  }

  return result;
}

const JSON &never_value() {
  static const JSON NEVER{sourcemeta::core::parse_json(R"({"kind":"never"})")};
  return NEVER;
}

// The rows a group of properties is drawn as: its named properties, the
// properties named by a pattern, the properties not otherwise named, and its
// conditions, in that order. Properties it inherits from a shape come
// separately, grouped by shape.
auto rows_of(const JSON *value, const Draw &draw,
             const std::set<std::string> &seen = {}) -> Rows {
  Rows result;
  if (value == nullptr) {
    return result;
  }

  if (kind(value) != "object") {
    for (const auto *entry : list(value, "conditions")) {
      Row row;
      row.condition = true;
      row.about = entry;
      result.own.push_back(std::move(row));
    }

    return result;
  }

  std::vector<Inherited> inherited;
  for (const auto *also : list(value, "also")) {
    const auto reference{text(also, "ref")};
    if (kind(also) != "ref" || seen.contains(reference)) {
      continue;
    }

    const auto *found{draw.shape(reference)};
    if (found == nullptr || !truthy(at(found, "value")) ||
        kind(at(found, "value")) != "object") {
      continue;
    }

    auto deeper{seen};
    deeper.insert(reference);
    auto inner{rows_of(at(found, "value"), draw, deeper)};
    for (auto &group : inner.inherited) {
      inherited.push_back(std::move(group));
    }

    inherited.push_back({.from = reference, .rows = std::move(inner.own)});
  }

  std::map<std::string, std::pair<std::size_t, std::size_t>> by_name;
  for (std::size_t group = 0; group < inherited.size(); group++) {
    for (std::size_t index = 0; index < inherited[group].rows.size(); index++) {
      const auto &row{inherited[group].rows[index]};
      if (!row.condition && row.name_kind == NameKind::Named && row.has_name) {
        by_name.insert_or_assign(row.name, std::pair{group, index});
      }
    }
  }

  const auto *other{at(value, "otherProperties")};
  const auto *fallback{truthy(other)                 ? other
                       : truthy(at(value, "closed")) ? &never_value()
                                                     : nullptr};
  for (const auto *property : list(value, "properties")) {
    const auto name{text(property, "name")};
    // A property only named as required here, and described by a shape it
    // inherits from, is that inherited property made required.
    const auto match{by_name.find(name)};
    if (!truthy(at(property, "value")) && match != by_name.cend()) {
      auto &row{inherited[match->second.first].rows[match->second.second]};
      row.required = row.required || truthy(at(property, "required"));
      continue;
    }

    Row row;
    row.has_name = at(property, "name") != nullptr;
    if (row.has_name) {
      row.name = name;
    }
    row.value = truthy(at(property, "value")) ? at(property, "value") : nullptr;
    row.required = truthy(at(property, "required"));
    row.fallback = fallback;
    result.own.push_back(std::move(row));
  }

  // A condition that only asks whether one of these properties is there is
  // drawn under that property: "filling in X makes Y required".
  std::vector<const JSON *> conditions;
  for (const auto *entry : list(value, "conditions")) {
    const auto name{presence_of(entry)};
    Row *owner{nullptr};
    if (name.has_value() && !name.value().empty() &&
        !truthy(at(entry, "otherwise"))) {
      for (auto &row : result.own) {
        if (!row.condition && row.has_name && row.name == name.value() &&
            row.name_kind == NameKind::Named) {
          owner = &row;
          break;
        }
      }
    }

    if (owner != nullptr) {
      owner->brings.push_back(at(entry, "then"));
    } else {
      conditions.push_back(entry);
    }
  }

  for (const auto *entry : list(value, "patternProperties")) {
    Row row;
    row.value = truthy(at(entry, "value")) ? at(entry, "value") : nullptr;
    row.name_kind = NameKind::Pattern;
    row.pattern = text(entry, "pattern");
    result.own.push_back(std::move(row));
  }

  if (truthy(other)) {
    Row row;
    row.value = other;
    row.name_kind = NameKind::Other;
    result.own.push_back(std::move(row));
  }

  for (const auto *entry : conditions) {
    Row row;
    row.condition = true;
    row.about = entry;
    result.own.push_back(std::move(row));
  }

  for (auto &group : inherited) {
    if (!group.rows.empty()) {
      result.inherited.push_back(std::move(group));
    }
  }

  return result;
}

struct Group {
  const JSON *group;
  std::vector<const JSON *> alternatives;
};

// A choice between one group of properties and a few plain values, such as a
// schema that may be an object or a boolean, is drawn as the group with the
// other types noted beside it.
auto as_group(const JSON *value, Draw &draw) -> std::optional<Group> {
  if (value == nullptr) {
    return std::nullopt;
  }

  if (kind(value) == "object") {
    return Group{.group = value, .alternatives = {}};
  }

  if (kind(value) != "choice") {
    return std::nullopt;
  }

  std::vector<const JSON *> objects;
  std::vector<const JSON *> rest;
  for (const auto *option : list(value, "options")) {
    if (option == nullptr || option->is_null()) {
      continue;
    }

    (kind(option) == "object" ? objects : rest).push_back(option);
  }

  if (objects.size() != 1 ||
      !std::all_of(rest.cbegin(), rest.cend(), [](const auto *option) {
        return is_simple(option) && !truthy(at(option, "description"));
      })) {
    return std::nullopt;
  }

  // What the choice itself also says applies to the group too.
  auto group{*objects.front()};
  for (const std::string key : {"also", "conditions"}) {
    const auto *more{at(value, key)};
    if (!truthy(more)) {
      continue;
    }

    auto merged{JSON::make_array()};
    for (const auto *entry : list(&group, key)) {
      merged.push_back(*entry);
    }

    if (more->is_array()) {
      for (const auto &entry : more->as_array()) {
        merged.push_back(entry);
      }
    }

    group.assign(key, std::move(merged));
  }

  if (const auto *forbidden{at(value, "not")}; truthy(forbidden)) {
    if (truthy(at(&group, "not"))) {
      auto options{JSON::make_array()};
      options.push_back(group.at("not"));
      options.push_back(*forbidden);
      auto choice{JSON::make_object()};
      choice.assign("kind", JSON{std::string{"choice"}});
      choice.assign("options", std::move(options));
      choice.assign("overlap", JSON{true});
      group.assign("not", std::move(choice));
    } else {
      group.assign("not", *forbidden);
    }
  }

  return Group{.group = draw.keep(std::move(group)), .alternatives = rest};
}

// What a branch of a condition, or anything pointed at, holds.
auto content_of(const JSON *value, const Draw &draw) -> const JSON * {
  if (kind(value) == "ref") {
    const auto *found{draw.shape(text(value, "ref"))};
    if (found != nullptr) {
      return at(found, "value");
    }
  }

  return value;
}

// Whether any form of a choice carries the author's words.
auto forms_say(const JSON *value) -> bool {
  const auto options{list(value, "options")};
  return std::any_of(options.cbegin(), options.cend(), [](const auto *option) {
    return truthy(option) &&
           (truthy(at(option, "description")) ||
            (kind(option) == "choice" && forms_say(option)) ||
            (kind(option) == "array" && truthy(at(option, "item")) &&
             truthy(at(at(option, "item"), "description"))));
  });
}

// How one form of a choice is named.
auto form_text(const JSON *option, const Draw &draw) -> std::string {
  const auto *item{at(option, "item")};
  std::string inner;
  if (kind(option) == "array" && truthy(item)) {
    if (truthy(at(item, "description"))) {
      inner = text(item, "description");
    } else if (truthy(at(item, "title"))) {
      inner = text(item, "title");
    }
  }

  const auto each{inner.empty() ? std::string{} : ", each entry: " + inner};
  if (truthy(at(option, "description"))) {
    return text(option, "description") + each;
  }

  if (kind(option) == "choice") {
    std::vector<std::string> parts;
    for (const auto *entry : list(option, "options")) {
      parts.push_back(form_text(entry, draw));
    }

    return sourcemeta::core::join(parts, " or ");
  }

  const auto facts{facts_of(option)};
  return label(option, draw) + (facts.empty() ? "" : ", " + facts) + each;
}

// Drawing. Every element goes through the core HTML writer. A part whose
// emptiness decides what wraps it is drawn on its own writer first and then
// placed, as it is already markup.

using Writer = sourcemeta::core::HTMLWriter;

template <typename Drawing> auto piece(const Drawing &drawing) -> std::string {
  Writer writer;
  drawing(writer);
  return writer.take();
}

auto bar(Writer &out, const JSON *bounds, const std::string &counts) -> void {
  const auto *minimum{at(bounds, "min")};
  const auto *maximum{at(bounds, "max")};
  const auto low{!given(minimum)
                     ? std::string{"any"}
                     : plain(minimum) + (truthy(at(bounds, "minExclusive"))
                                             ? " (not included)"
                                             : "")};
  const auto high{!given(maximum)
                      ? std::string{"any number of"}
                      : plain(maximum) + (truthy(at(bounds, "maxExclusive"))
                                              ? " (not included)"
                                              : "")};
  out.span()
      .attribute("class", "bar")
      .attribute("title", "from " + low + " to " + high);
  out.span().attribute("class", "bend").text(low).close();
  out.span().attribute("class", "btrack").close();
  out.span().attribute("class", "bend").text(high + counts).close();
  out.close();
}

auto bool_control(Writer &out) -> void {
  out.span()
      .attribute("class", "boolctl")
      .attribute("title", "a yes or no answer");
  out.span().attribute("class", "bo").text("yes").close();
  out.span().attribute("class", "bo").text("no").close();
  out.close();
}

auto chips(Writer &out, const JSON *values, const JSON *fallback) -> void {
  const auto all{piece([&](Writer &inner) {
    inner.span().attribute("class", "chips");
    if (values != nullptr && values->is_array()) {
      for (const auto &value : values->as_array()) {
        const auto chosen{strictly_equal(&value, fallback)};
        inner.span().attribute("class", chosen ? "chip def" : "chip");
        inner.text(plain(&value));
        if (chosen) {
          inner.em("default");
        }

        inner.close();
      }
    }

    inner.close();
  })};

  const auto total{
      values != nullptr && values->is_array() ? values->array_size() : 0};
  if (total <= 6) {
    out.raw(all);
    return;
  }

  out.details().attribute("class", "pick");
  out.summary("one of " + std::to_string(total));
  out.raw(all);
  out.close();
}

auto row_name(const Row &row) -> std::string {
  if (row.condition) {
    return condition_text(row.about);
  }

  if (row.name_kind == NameKind::Pattern) {
    return pattern_name(row.pattern);
  }

  if (row.name_kind == NameKind::Other) {
    return std::string{OTHER_NAME};
  }

  return row.has_name ? row.name : "undefined";
}

auto name_cell(Writer &out, const Row &row) -> void {
  if (row.condition) {
    out.span().attribute("class", "nm cond");
  } else if (row.name_kind != NameKind::Named) {
    out.span().attribute("class", "nm ghost");
  } else {
    out.span().attribute("class", "nm");
  }

  out.text(row_name(row)).close();
}

auto starts_with_word(const std::string &sentence,
                      const std::vector<std::string> &words) -> bool {
  for (const auto &word : words) {
    if (!sentence.starts_with(word)) {
      continue;
    }

    if (sentence.size() == word.size()) {
      return true;
    }

    const auto next{sentence[word.size()]};
    if (!((next >= 'a' && next <= 'z') || (next >= 'A' && next <= 'Z') ||
          (next >= '0' && next <= '9') || next == '_')) {
      return true;
    }
  }

  return false;
}

auto required_cell(Writer &out, const Row &row,
                   const std::optional<std::string> &under) -> void {
  if (row.condition) {
    out.span().attribute("class", "rq cond").text("Only in certain cases");
  } else if (row.required && under.has_value() && !under.value().empty()) {
    out.span()
        .attribute("class", "rq cond")
        .text("Yes, " +
              (starts_with_word(under.value(), {"when", "depending",
                                                "otherwise", "in one case"})
                   ? under.value()
                   : "once you fill in " + under.value()));
  } else if (row.required) {
    out.span().attribute("class", "rq req").text("Yes, always");
  } else {
    out.span().attribute("class", "rq opt").text("No, you can leave it out");
  }

  out.close();
}

auto link(Writer &out, const std::string &reference, const Draw &draw,
          const std::string &variant = "ty link") -> void {
  const auto *target{at(draw.shape(reference), "value")};
  const std::string extra{variant == "ty link" && truthy(target) &&
                                  kind(target) == "array"
                              ? ", and that shape is itself a list"
                              : ""};
  out.a()
      .attribute("class", variant)
      .attribute("href", "#" + anchor(reference))
      .text((variant == "ty link" ? with_article(draw.name_of(reference))
                                  : draw.name_of(reference)) +
            extra)
      .close();
}

auto either(Writer &out, const std::vector<const JSON *> &options,
            const Draw &draw) -> void {
  for (std::size_t index = 0; index < options.size(); index++) {
    if (index > 0) {
      // A string rather than one of two literals, which GCC would otherwise
      // hold to the bounds of the shorter one when escaping it.
      const std::string separator{index + 1 == options.size() ? " or " : ", "};
      out.text(separator);
    }

    link(out, text(options[index], "ref"), draw);
  }
}

auto forms_of(Writer &out, const std::vector<const JSON *> &options,
              const Draw &draw) -> void {
  out.div().attribute("class", "forms");
  for (const auto *option : options) {
    if (!truthy(option)) {
      continue;
    }

    out.span().attribute("class", "form");
    const auto *item{at(option, "item")};
    if (kind(option) == "ref") {
      link(out, text(option, "ref"), draw);
      if (truthy(at(option, "description"))) {
        out.text(" ").i(text(option, "description"));
      }
    } else if (kind(option) == "array" && truthy(item) && kind(item) == "ref") {
      out.text("a list, each one ");
      link(out, text(item, "ref"), draw);
    } else {
      out.text(form_text(option, draw));
      const auto *example{first_example(option)};
      if (example != nullptr && !truthy(at(option, "pattern"))) {
        out.text(" ").b(plain(example));
      }

      for (const auto &phrase : not_phrases(at(option, "not"), draw)) {
        out.text(" ").i(phrase);
      }
    }

    out.close();
  }

  out.close();
}

template <typename Inside>
auto notes(Writer &out, const Inside &inside) -> void {
  out.div().attribute("class", "notes");
  out.span();
  inside(out);
  out.close();
  out.close();
}

auto external_link(Writer &out, const JSON *value) -> void {
  const auto address{text(value, "href")};
  if (linkable(address)) {
    out.a()
        .attribute("class", "extlink")
        .attribute("href", address)
        .attribute("rel", "noopener noreferrer")
        .text(address)
        .close();
  } else {
    out.span().attribute("class", "extlink").text(address).close();
  }
}

auto value_cell(Writer &out, const JSON *value, Draw &draw) -> void {
  if (!truthy(value)) {
    out.span().attribute("class", "ty").text("no rule beyond being there");
    out.close();
    return;
  }

  const auto typed = [&out](const std::string &words) {
    out.span().attribute("class", "ty").text(words).close();
  };

  const auto name{kind(value)};
  if (name == "ref") {
    link(out, text(value, "ref"), draw);
  } else if (name == "external") {
    typed("follows rules kept in another file");
    external_link(out, value);
  } else if (name == "array") {
    const auto *item{at(value, "item")};
    const auto slots{count(value, "slots")};
    const auto options{list(item, "options")};
    if (slots > 0) {
      typed("a list with " + std::to_string(slots) + " fixed " +
            (slots == 1 ? "slot" : "slots"));
    } else if (truthy(item) && kind(item) == "ref") {
      out.span().attribute("class", "ty").text("a list, each one ");
      link(out, text(item, "ref"), draw);
      out.close();
    } else if (truthy(item) && kind(item) == "choice" && !options.empty() &&
               std::all_of(options.cbegin(), options.cend(),
                           [](const auto *option) {
                             return truthy(option) && kind(option) == "ref";
                           })) {
      out.span().attribute("class", "ty").text("a list, each entry either ");
      either(out, options, draw);
      out.close();
    } else if (truthy(item) && kind(item) == "choice" && !options.empty() &&
               (label(item, draw).starts_with("one of") || forms_say(item))) {
      typed("a list, each entry one of " + std::to_string(options.size()) +
            " forms");
      forms_of(out, options, draw);
    } else {
      std::string said{"a list"};
      if (truthy(item)) {
        std::vector<std::string> parts;
        const auto own{facts_of(item)};
        if (!own.empty()) {
          parts.push_back(own);
        }

        const auto forbidden{
            sourcemeta::core::join(not_phrases(at(item, "not"), draw), "; ")};
        if (!forbidden.empty()) {
          parts.push_back(forbidden);
        }

        said += ", each one " + with_article(label(item, draw));
        if (!parts.empty()) {
          said += ", " + sourcemeta::core::join(parts, ", ");
        }
      }

      typed(said);
    }
  } else if (name == "boolean") {
    bool_control(out);
  } else if (name == "enum") {
    typed(count(value, "values") == 1 ? "a fixed value" : "one of these");
    chips(out, at(value, "values"), at(value, "default"));
  } else if (name == "choice") {
    const auto options{list(value, "options")};
    const auto said{label(value, draw)};
    const auto group{as_group(value, draw)};
    if (!options.empty() &&
        std::all_of(options.cbegin(), options.cend(),
                    [](const auto *option) {
                      return truthy(option) && kind(option) == "ref";
                    }) &&
        !forms_say(value)) {
      out.span().attribute("class", "ty").text("either ");
      either(out, options, draw);
      out.close();
    } else if (!said.starts_with("one of") && !said.starts_with("either") &&
               !forms_say(value)) {
      typed(said);
    } else if (group.has_value()) {
      std::vector<std::string> others;
      for (const auto *alternative : group->alternatives) {
        others.push_back(label(alternative, draw));
      }

      typed(label(group->group, draw));
      notes(out, [&](Writer &inner) {
        inner.text("or " + sourcemeta::core::join(others, " or "));
      });
    } else {
      typed(std::string{truthy(at(value, "overlap")) ? "one or more" : "one"} +
            " of " + std::to_string(options.size()) + " forms");
      forms_of(out, options, draw);
    }
  } else if (name == "object") {
    // A group whose only content is a name the writer picks is a map, and
    // said on the row itself it is one sentence.
    const auto *other{at(value, "otherProperties")};
    const auto patterns{count(value, "patternProperties")};
    const auto only_other{count(value, "properties") == 0 &&
                          count(value, "conditions") == 0 &&
                          ((truthy(other) && patterns == 0) ||
                           (!truthy(other) && patterns == 1))};
    if (only_other) {
      const auto *first{patterns > 0 ? list(value, "patternProperties").front()
                                     : nullptr};
      typed("a group where you choose the names, each one");
      value_cell(out, truthy(other) ? other : at(first, "value"), draw);
      if (!truthy(other)) {
        notes(out, [&](Writer &inner) {
          inner.text(pattern_name(text(first, "pattern")));
        });
      }
    } else {
      typed(label(value, draw));
    }
  } else {
    typed(label(value, draw));
  }

  for (const auto *also : list(value, "also")) {
    const auto also_kind{kind(also)};
    if (also_kind == "ref") {
      const auto *found{draw.shape(text(also, "ref"))};
      // Properties inherited from a group of properties are drawn with the
      // properties.
      if (name == "object" && found != nullptr && truthy(at(found, "value")) &&
          kind(at(found, "value")) == "object") {
        continue;
      }

      notes(out, [&](Writer &inner) {
        inner.text("and follows ");
        inner.a()
            .attribute("class", "link")
            .attribute("href", "#" + anchor(text(also, "ref")))
            .text(with_article(draw.name_of(text(also, "ref"))))
            .close();
        inner.text(" as well");
      });
    } else if (also_kind == "external") {
      notes(out, [](Writer &inner) {
        inner.text("and follows rules kept in another file as well");
      });
      external_link(out, also);
    } else if (also_kind == "choice" && count(also, "options") > 0) {
      const auto options{list(also, "options")};
      if (label(also, draw).starts_with("one of") &&
          std::any_of(options.cbegin(), options.cend(), [](const auto *option) {
            return truthy(option) && kind(option) == "object";
          })) {
        continue;
      }

      std::vector<std::string> parts;
      parts.reserve(options.size());
      for (const auto *option : options) {
        parts.push_back(truthy(at(option, "description"))
                            ? text(option, "description")
                            : form_text(option, draw));
      }

      notes(out, [&](Writer &inner) {
        inner.text(
            std::string{"and "} +
            (truthy(at(also, "overlap")) ? "at least one" : "exactly one") +
            " of these: " + sourcemeta::core::join(parts, "; "));
      });
    } else if (!(also_kind == "object" && name == "object")) {
      std::vector<std::string> extra;
      if (also_kind == "enum" && at(also, "values") != nullptr &&
          at(also, "values")->is_array()) {
        extra.push_back(plain_all(at(also, "values"), ", "));
      }

      if (const auto *range{at(also, "range")}; truthy(range)) {
        if (given(at(range, "min"))) {
          extra.push_back(range_word(range, "min") + " " +
                          plain(at(range, "min")));
        }

        if (given(at(range, "max"))) {
          extra.push_back(range_word(range, "max") + " " +
                          plain(at(range, "max")));
        }
      }

      if (const auto *length{at(also, "length")}; truthy(length)) {
        if (given(at(length, "min"))) {
          extra.push_back("at least " + plain(at(length, "min")) + " long");
        }

        if (given(at(length, "max"))) {
          extra.push_back("at most " + plain(at(length, "max")) + " long");
        }
      }

      const auto said{pattern_note(also)};
      if (said.has_value()) {
        extra.push_back(said.value());
      }

      notes(out, [&](Writer &inner) {
        inner.text(
            "and must also be " + with_article(label(also, draw)) +
            (extra.empty() ? "" : ", " + sourcemeta::core::join(extra, ", ")));
      });
    }
  }

  const auto *bounds{truthy(at(value, "range")) ? at(value, "range")
                                                : at(value, "length")};
  if (truthy(bounds) && name != "object") {
    bar(out, bounds, count_words(name));
  }

  std::vector<std::string> said;
  const auto *example{first_example(value)};
  if (example == nullptr && (name == "ref" || name == "choice")) {
    std::vector<std::string> targets;
    if (name == "ref") {
      targets.push_back(text(value, "ref"));
    } else {
      for (const auto *option : list(value, "options")) {
        if (truthy(option) && kind(option) == "ref") {
          targets.push_back(text(option, "ref"));
        }
      }
    }

    for (const auto &target : targets) {
      const auto *found{draw.shape(target)};
      const auto *other{found == nullptr ? nullptr
                                         : first_example(at(found, "value"))};
      if (other != nullptr) {
        example = other;
        break;
      }
    }
  }

  const auto pattern{pattern_note(at(value, "pattern"), example)};
  if (pattern.has_value()) {
    said.push_back(pattern.value());
  }

  if (given(at(value, "multipleOf"))) {
    said.push_back("in steps of " + plain(at(value, "multipleOf")));
  }

  const auto *item{at(value, "item")};
  const auto item_pattern{pattern_note(item)};
  if (item_pattern.has_value()) {
    said.push_back("each entry " + item_pattern.value());
  }

  if (!pattern.has_value() && !item_pattern.has_value() && example != nullptr &&
      name != "enum") {
    said.push_back("for example " + plain(example));
  }

  // What the author wrote about a single entry, when a list is drawn on one
  // row.
  if (truthy(item)) {
    if (truthy(at(item, "description"))) {
      said.push_back("each entry: " + text(item, "description"));
    } else if (truthy(at(item, "title"))) {
      said.push_back("each entry: " + text(item, "title"));
    }
  }

  for (auto &phrase : not_phrases(at(value, "not"), draw)) {
    said.push_back(std::move(phrase));
  }

  if (const auto *amount{at(value, "propertyCount")}; truthy(amount)) {
    const auto *minimum{at(amount, "min")};
    const auto *maximum{at(amount, "max")};
    if (given(minimum) && given(maximum)) {
      said.push_back("between " + text(minimum) + " and " + text(maximum) +
                     " properties");
    } else if (given(minimum)) {
      said.push_back("at least " + text(minimum) + " " +
                     (is_one(minimum) ? "property" : "properties"));
    } else {
      said.push_back("at most " + text(maximum) + " " +
                     (is_one(maximum) ? "property" : "properties"));
    }
  }

  if (const auto *keys{at(value, "keys")}; truthy(keys)) {
    if (truthy(at(keys, "format"))) {
      said.push_back("every name must be " + text(keys, "format"));
    }

    if (truthy(at(keys, "pattern"))) {
      said.push_back("every name must match " + text(keys, "pattern"));
    } else if (kind(keys) == "enum") {
      said.push_back("names can only be " +
                     plain_all(at(keys, "values"), ", "));
    } else if (kind(keys) != "string") {
      said.push_back("every name must be " + with_article(label(keys, draw)));
    }

    if (const auto *length{at(keys, "length")}; truthy(length)) {
      said.push_back("names from " +
                     (given(at(length, "min")) ? text(at(length, "min"))
                                               : std::string{"any"}) +
                     " to " +
                     (given(at(length, "max")) ? text(at(length, "max"))
                                               : std::string{"any number of"}) +
                     " characters");
    }
  }

  if (const auto *contains{at(value, "contains")}; truthy(contains)) {
    const auto *minimum{at(contains, "min")};
    const auto *maximum{at(contains, "max")};
    const auto how{given(maximum)
                       ? "between " + text(minimum) + " and " + text(maximum)
                       : "at least " + text(minimum)};
    const auto facts{facts_of(at(contains, "value"))};
    said.push_back(how + " " +
                   (is_one(minimum) && !given(maximum) ? "entry" : "entries") +
                   " must be " + brief(at(contains, "value"), draw) +
                   (facts.empty() ? "" : ", " + facts));
  }

  if (const auto *access{at(value, "access")}; access != nullptr) {
    if (text(access) == "read") {
      said.emplace_back("you do not fill this in, it is sent back to you");
    } else if (text(access) == "write") {
      said.emplace_back("you fill this in, it is never sent back");
    }
  }

  if (const auto *content{at(value, "content")}; truthy(content)) {
    said.push_back("the text inside is " +
                   (truthy(at(content, "mediaType"))
                        ? text(content, "mediaType")
                        : std::string{"in a set format"}) +
                   (truthy(at(content, "encoding"))
                        ? ", written as " + text(content, "encoding")
                        : ""));
  }

  if (truthy(at(value, "unique"))) {
    said.emplace_back("no two entries the same");
  }

  if (truthy(at(value, "closed"))) {
    said.emplace_back("nothing else may be added here");
  }

  if (truthy(item) && truthy(at(item, "closed"))) {
    said.emplace_back("nothing else may be added to an entry");
  }

  if (truthy(at(value, "nullable"))) {
    said.emplace_back("it may also be null");
  }

  if (truthy(at(value, "otherTypesAllowed"))) {
    said.emplace_back(count(value, "also") > 0 || truthy(at(value, "not")) ||
                              count(value, "conditions") > 0
                          ? "another kind of value passes the rules above, "
                            "and still has to match the rest"
                          : "any other kind of value is also accepted");
  }

  if (at(value, "default") != nullptr && name != "enum") {
    said.push_back("left out means " + plain(at(value, "default")));
  }

  std::erase_if(said, [](const auto &note) { return note.empty(); });
  if (!said.empty()) {
    out.div().attribute("class", "notes");
    for (const auto &note : said) {
      out.span(note);
    }

    out.close();
  }
}

// A table of rows, or nothing when there are no rows.
auto table(Writer &out, const std::string &rows, const bool sub = false)
    -> void {
  if (rows.empty()) {
    return;
  }

  out.table().attribute("class", sub ? "doc sub" : "doc");
  if (!sub) {
    out.tr();
    out.th("Property");
    out.th("What goes in it");
    out.th("Required?");
    out.th("What it means");
    out.close();
  }

  out.raw(rows);
  out.close();
}

auto sub_table(const std::string &rows) -> std::string {
  return piece([&](Writer &out) { table(out, rows, true); });
}

// A strip that opens to show what a row holds.
template <typename Title>
auto nest(Writer &out, const Title &title, const std::string &amount,
          const std::string &inner, const std::string &variant = "") -> void {
  out.tr().attribute("class", variant.empty() ? "nest" : "nest " + variant);
  out.td().attribute("colspan", "4");
  out.details().attribute(
      "class", variant.empty() ? "nestbox" : "nestbox " + variant + "box");
  if (variant != "dep") {
    out.attribute("open");
  }

  out.summary();
  title(out);
  if (!amount.empty()) {
    out.text(" ").span().attribute("class", "cnt").text(amount).close();
  }

  out.close();
  out.raw(inner);
  out.close();
  out.close();
  out.close();
}

// A title made of words with one name in bold.
auto bold_in(const std::string &before, const std::string &name,
             const std::string &after = "") {
  return [before, name, after](Writer &out) {
    out.text(before).b(name).text(after);
  };
}

auto words(const std::string &sentence) {
  return [sentence](Writer &out) { out.text(sentence); };
}

auto leaf(const JSON *value, Draw &draw, const std::string &after = "")
    -> std::string {
  return piece([&](Writer &out) {
           out.div().attribute("class", "leafval");
           value_cell(out, value, draw);
           out.close();
         }) +
         after;
}

// The word for one or many, and with `counted` the number before it too.
auto plural(const std::size_t amount, const std::string &one,
            const std::string &many, const bool counted = false)
    -> std::string {
  return (counted ? std::to_string(amount) + " " : std::string{}) +
         (amount == 1 ? one : many);
}

auto render_row(Writer &out, const Row &row, Draw &draw,
                const std::optional<std::string> &under) -> void;
auto nested_of(Writer &out, const JSON *value, Draw &draw,
               const std::string &name, const std::optional<std::string> &under)
    -> void;

auto has_inside(const JSON *value, const Draw &draw,
                const std::size_t depth = 0) -> bool {
  if (!truthy(value) || depth > 8) {
    return false;
  }

  if (kind(value) == "object") {
    return row_count(rows_of(value, draw)) > 0;
  }

  if (kind(value) == "array") {
    const auto slots{list(value, "slots")};
    return has_inside(at(value, "item"), draw, depth + 1) ||
           std::any_of(slots.cbegin(), slots.cend(),
                       [&draw, depth](const auto *slot) {
                         return has_inside(slot, draw, depth + 1);
                       });
  }

  if (kind(value) == "choice") {
    const auto options{list(value, "options")};
    return std::any_of(options.cbegin(), options.cend(),
                       [&draw, depth](const auto *option) {
                         return has_inside(option, draw, depth + 1);
                       });
  }

  return count(value, "conditions") > 0;
}

auto inherited_summary(const Inherited &inherited, const Draw &draw)
    -> std::string {
  const auto from{draw.name_of(inherited.from)};
  std::size_t properties{0};
  for (const auto &row : inherited.rows) {
    if (!row.condition) {
      properties += 1;
    }
  }

  const auto conditions{inherited.rows.size() - properties};
  const auto conditions_text{conditions == 1
                                 ? std::string{"condition"}
                                 : std::to_string(conditions) + " conditions"};
  if (conditions == 0) {
    return "and the " + std::to_string(properties) + " " +
           plural(properties, "property", "properties") + " every " + from +
           " carries";
  }

  if (properties == 0) {
    return "and the " + conditions_text + " every " + from + " brings";
  }

  return "and the " + std::to_string(properties) + " " +
         plural(properties, "property", "properties") + " and " +
         conditions_text + " every " + from + " brings";
}

auto render_group(const JSON *value, Draw &draw,
                  const std::optional<std::string> &under) -> std::string;

// The forms of a choice, each drawn with its properties when it has any.
auto choice_rows(Writer &out, const JSON *choice, Draw &draw,
                 const std::string &name,
                 const std::optional<std::string> &under) -> void {
  const auto options{list(choice, "options")};
  if (!std::any_of(
          options.cbegin(), options.cend(),
          [&draw](const auto *option) { return has_inside(option, draw); })) {
    nest(
        out,
        words(std::string{"and "} +
              (truthy(at(choice, "overlap")) ? "at least one" : "exactly one") +
              " of these must also hold"),
        "", leaf(choice, draw), "dep");
    return;
  }

  for (std::size_t index = 0; index < options.size(); index++) {
    const auto *option{options[index]};
    if (!truthy(option)) {
      continue;
    }

    const auto form{"form " + std::to_string(index + 1) + " of "};
    const auto amount{
        kind(option) == "object" ? row_count(rows_of(option, draw)) : 0};
    if (amount == 0) {
      const auto inner{piece([&](Writer &writer) {
        nested_of(writer, option, draw, form + name, under);
      })};
      nest(out, bold_in(form, name), "",
           leaf(option, draw, inner.empty() ? "" : sub_table(inner)), "dep");
      continue;
    }

    nest(out,
         bold_in(form, name,
                 truthy(at(option, "description"))
                     ? ": " + text(option, "description")
                     : ""),
         plural(amount, "property", "properties", true),
         sub_table(render_group(option, draw, under)), "dep");
  }
}

// Every row of a group, and the inherited ones behind a strip.
auto render_group(const JSON *value, Draw &draw,
                  const std::optional<std::string> &under) -> std::string {
  const auto rows{rows_of(value, draw)};
  Writer out;
  for (const auto &row : rows.own) {
    render_row(out, row, draw, under);
  }

  for (const auto &inherited : rows.inherited) {
    out.tr().attribute("class", "nest");
    out.td().attribute("colspan", "4");
    out.details().attribute("class", "borrow");
    out.summary().text(inherited_summary(inherited, draw));
    // A shape can inherit, somewhere inside itself, from itself. Its
    // properties are then already being drawn, so the strip links to them.
    if (draw.inlining.contains(inherited.from)) {
      out.text(", as written out in ");
      link(out, inherited.from, draw, "link");
      out.close();
    } else {
      out.close();
      draw.inlining.insert(inherited.from);
      Writer inner;
      for (const auto &row : inherited.rows) {
        render_row(inner, row, draw, under);
      }

      out.raw(sub_table(inner.take()));
      draw.inlining.erase(inherited.from);
    }

    out.close();
    out.close();
    out.close();
  }

  // A choice the whole group must also make: which forms it may take.
  for (const auto *also : list(value, "also")) {
    if (kind(also) == "choice") {
      choice_rows(out, also, draw, "it", under);
    }
  }

  // Properties written out in a part that also applies, kept apart because
  // they could not be merged with these.
  for (const auto *also : list(value, "also")) {
    if (kind(also) != "object") {
      continue;
    }

    const auto amount{row_count(rows_of(also, draw))};
    if (amount > 0) {
      nest(out, words("and it must also match these"),
           plural(amount, "property", "properties", true),
           sub_table(render_group(also, draw, under)), "dep");
    }
  }

  return out.take();
}

// Only names that must be filled in, with nothing else said about them.
auto only_requires(const JSON *value) -> bool {
  const auto properties{list(value, "properties")};
  return truthy(value) && kind(value) == "object" && !properties.empty() &&
         std::all_of(properties.cbegin(), properties.cend(),
                     [](const auto *property) {
                       return !truthy(at(property, "value")) &&
                              truthy(at(property, "required"));
                     }) &&
         only_keys(value, {"kind", "properties"});
}

auto render_branch(Writer &out, const JSON *value, Draw &draw,
                   const std::string &lead, const std::string &under) -> void {
  // A shape is written out once, so a branch that is a shape links to it.
  if (kind(value) == "ref" && draw.shape(text(value, "ref")) != nullptr &&
      !only_requires(content_of(value, draw))) {
    const auto reference{text(value, "ref")};
    nest(
        out,
        [&](Writer &title) {
          title.text(lead + " it must also be ");
          title.a()
              .attribute("class", "link")
              .attribute("href", "#" + anchor(reference))
              .text(with_article(draw.name_of(reference)))
              .close();
        },
        "", "", "dep");
    return;
  }

  const auto *body{content_of(value, draw)};
  if (only_requires(body)) {
    const auto properties{list(body, "properties")};
    nest(
        out,
        [&](Writer &title) {
          title.text(lead + " ");
          for (std::size_t index = 0; index < properties.size(); index++) {
            if (index > 0) {
              title.text(" and ");
            }

            title.b(text(properties[index], "name"));
          }

          title.text(properties.size() > 1 ? " become required"
                                           : " becomes required");
        },
        "", "", "dep");
    return;
  }

  if (truthy(body) && kind(body) == "object") {
    const auto amount{row_count(rows_of(body, draw))};
    if (amount > 0) {
      nest(out, words(lead + " these apply"),
           plural(amount, "property", "properties", true),
           sub_table(render_group(body, draw, under)), "dep");
      return;
    }
  }

  nest(out, words(lead + " it must be"), "", leaf(value, draw), "dep");
}

auto render_row(Writer &out, const Row &row, Draw &draw,
                const std::optional<std::string> &under) -> void {
  const auto beneath{under.has_value() && !under.value().empty()};
  const std::string key{row.condition  ? "cond"
                        : row.required ? (beneath ? "cond" : "req")
                                       : "opt"};
  draw.stats[key] += 1;

  if (row.condition) {
    const auto *condition{row.about};
    const auto said{condition_text(condition)};
    const auto *when{at(condition, "when")};
    out.tr();
    out.td();
    name_cell(out, row);
    out.close();
    out.td().close();
    out.td();
    required_cell(out, row, under);
    out.close();
    out.td()
        .attribute("class", "de")
        .text(truthy(at(when, "description")) ? text(when, "description")
                                              : std::string{})
        .close();
    out.close();
    if (truthy(at(condition, "then"))) {
      render_branch(out, at(condition, "then"), draw, "then", said);
    }

    if (truthy(at(condition, "otherwise"))) {
      render_branch(out, at(condition, "otherwise"), draw, "otherwise",
                    "otherwise");
    }

    return;
  }

  const auto *value{row.value};
  std::vector<std::string> meaning;
  if (truthy(value)) {
    if (truthy(at(value, "description"))) {
      meaning.push_back(text(value, "description"));
    } else if (truthy(at(value, "title"))) {
      meaning.push_back(text(value, "title"));
    }

    if (truthy(at(value, "deprecated"))) {
      meaning.emplace_back("No longer used.");
    }
  }

  const auto name{row_name(row)};
  out.tr();
  out.td();
  name_cell(out, row);
  out.close();
  out.td();
  value_cell(out, truthy(value) ? value : row.fallback, draw);
  out.close();
  out.td();
  required_cell(out, row, under);
  out.close();
  out.td()
      .attribute("class", "de")
      .text(sourcemeta::core::join(meaning, " "))
      .close();
  out.close();
  const auto child_under{
      row.required || beneath ? under : std::optional<std::string>{name}};
  nested_of(out, value, draw, name, child_under);

  for (const auto *then : row.brings) {
    const auto *body{content_of(then, draw)};
    if (only_requires(body)) {
      Writer inner;
      for (const auto *property : list(body, "properties")) {
        inner.tr();
        inner.td().span().attribute("class", "nm");
        inner.text(text(property, "name")).close().close();
        inner.td().close();
        inner.td().span().attribute("class", "rq cond");
        inner.text("Yes, once you fill in " + name).close().close();
        inner.td().close();
        inner.close();
      }

      nest(out,
           bold_in("Filling in ", name,
                   " makes " + std::to_string(count(body, "properties")) +
                       " more required"),
           "", sub_table(inner.take()), "dep");
      continue;
    }

    const auto amount{truthy(body) && kind(body) == "object"
                          ? row_count(rows_of(body, draw))
                          : 0};
    if (amount > 0) {
      nest(out,
           bold_in("Filling in ", name,
                   " brings in " + std::to_string(amount) + " more"),
           "", sub_table(render_group(body, draw, name)), "dep");
    } else {
      nest(out, bold_in("Filling in ", name, " means the whole must also be"),
           "", leaf(then, draw), "dep");
    }
  }
}

// A group made only of names the writer chooses is said on its row.
auto is_map(const JSON *value) -> bool {
  const auto *other{at(value, "otherProperties")};
  const auto patterns{count(value, "patternProperties")};
  return count(value, "properties") == 0 && count(value, "conditions") == 0 &&
         count(value, "also") == 0 &&
         ((truthy(other) && patterns == 0) ||
          (!truthy(other) && patterns == 1));
}

// Whether the properties under a map's chosen names have anything to draw.
auto map_has_inside(const JSON *value, const Draw &draw) -> bool {
  const auto *other{at(value, "otherProperties")};
  const auto *inner{
      truthy(other) ? other
                    : at(list(value, "patternProperties").front(), "value")};
  return has_inside(inner, draw) ||
         (kind(inner) == "choice" && forms_say(inner)) ||
         truthy(at(inner, "description")) ||
         (truthy(at(inner, "item")) &&
          truthy(at(at(inner, "item"), "description")));
}

// What is drawn inside a row: the properties of a group, of each entry of a
// list, of each form of a choice, and the fixed slots of a list.
auto nested_of(Writer &out, const JSON *value, Draw &draw,
               const std::string &name, const std::optional<std::string> &under)
    -> void {
  if (!truthy(value)) {
    return;
  }

  // Text that holds a document of its own, with rules of its own.
  if (const auto *content{at(value, "content")};
      truthy(content) && truthy(at(content, "value"))) {
    const auto *inner{at(content, "value")};
    const auto amount{kind(inner) == "object" ? row_count(rows_of(inner, draw))
                                              : 0};
    if (amount > 0) {
      nest(out, bold_in("the document inside ", name),
           plural(amount, "property", "properties", true),
           sub_table(render_group(inner, draw, std::nullopt)), "dep");
    } else {
      nest(out, bold_in("the document inside ", name, " is"), "",
           leaf(inner, draw), "dep");
    }
  }

  const auto group{as_group(value, draw)};
  std::optional<Rows> rows;
  if (group.has_value()) {
    rows = rows_of(group->group, draw);
  } else if (count(value, "conditions") > 0) {
    rows = rows_of(value, draw);
  }

  const auto *item{at(value, "item")};
  if (rows.has_value() && row_count(rows.value()) > 0 &&
      !(group.has_value() && is_map(group->group) &&
        !map_has_inside(group->group, draw))) {
    nest(out, bold_in("inside ", name),
         plural(row_count(rows.value()), "property", "properties", true),
         sub_table(render_group(group.has_value() ? group->group : value, draw,
                                under)));
  } else if (kind(value) == "array" && truthy(item) && kind(item) == "object" &&
             row_count(rows_of(item, draw)) > 0) {
    nest(out, bold_in("inside ", "each entry of " + name),
         plural(row_count(rows_of(item, draw)), "property", "properties", true),
         sub_table(render_group(item, draw, under)));
  } else if (kind(value) == "array" && truthy(item) && kind(item) == "choice") {
    const auto options{list(item, "options")};
    if (std::any_of(
            options.cbegin(), options.cend(),
            [&draw](const auto *option) { return has_inside(option, draw); })) {
      choice_rows(out, item, draw, "each entry of " + name, under);
    }
  }

  if (!group.has_value() && kind(value) == "choice") {
    const auto options{list(value, "options")};
    if (std::any_of(
            options.cbegin(), options.cend(),
            [&draw](const auto *option) { return has_inside(option, draw); })) {
      choice_rows(out, value, draw, name, under);
    }
  }

  // A value that is not itself a group, but must also match one.
  if (!group.has_value()) {
    for (const auto *also : list(value, "also")) {
      if (kind(also) != "object") {
        continue;
      }

      const auto amount{row_count(rows_of(also, draw))};
      if (amount > 0) {
        nest(out, words("and it must also match these"),
             plural(amount, "property", "properties", true),
             sub_table(render_group(also, draw, under)), "dep");
      }
    }
  }

  const auto slots{list(value, "slots")};
  if (kind(value) == "array" && !slots.empty()) {
    Writer slot_rows;
    for (std::size_t index = 0; index < slots.size(); index++) {
      Row row;
      row.name = "slot " + std::to_string(index + 1);
      row.has_name = true;
      row.value = truthy(slots[index]) ? slots[index] : nullptr;
      render_row(slot_rows, row, draw, under);
    }

    nest(out, bold_in("the fixed slots of ", name),
         plural(slots.size(), "slot", "slots", true),
         sub_table(slot_rows.take()));
    if (truthy(item) && kind(item) == "never") {
      nest(out, bold_in("after those slots, ", name, " holds nothing more"), "",
           "", "dep");
    } else if (truthy(item)) {
      Row row;
      row.name = "every entry after those";
      row.has_name = true;
      row.value = item;
      Writer rest;
      render_row(rest, row, draw, under);
      nest(out, bold_in("what ", name, " holds after the fixed slots"), "",
           sub_table(rest.take()), "dep");
    }
  }
}

auto used(const JSON *shape) -> std::size_t { return count(shape, "usedAt"); }

// The tags that start a block of the page. A line break next to one of them
// does not change how the page looks, while one next to an inline tag, like a
// `span`, would put a space where there was none.
auto is_block(const std::string_view name) -> bool {
  static constexpr std::array<std::string_view, 14> BLOCKS{
      {"div", "section", "h1", "h2", "h4", "p", "table", "tr", "th", "td", "ul",
       "li", "details", "summary"}};
  return std::find(BLOCKS.cbegin(), BLOCKS.cend(), name) != BLOCKS.cend();
}

auto break_line(std::string &output, const std::size_t depth) -> void {
  if (!output.empty()) {
    output += '\n';
    output.append(depth * 2, ' ');
  }
}

// Put every block of a page on a line of its own, indented by how deep it is,
// and leave what is inside a line as it was. Every attribute value on the page
// is escaped, so a tag ends at the first `>` after it starts.
auto indented(const std::string_view page) -> std::string {
  std::string output;
  output.reserve(page.size() + (page.size() / 2));
  // Whether each block still open holds another block, which then puts its
  // closing tag on a line of its own too
  std::vector<bool> holds;
  std::size_t cursor{0};
  while (cursor < page.size()) {
    if (page[cursor] != '<') {
      const auto next{page.find('<', cursor)};
      const auto end{next == std::string_view::npos ? page.size() : next};
      output.append(page.substr(cursor, end - cursor));
      cursor = end;
      continue;
    }

    const auto end{page.find('>', cursor) + 1};
    const auto tag{page.substr(cursor, end - cursor)};
    cursor = end;
    const auto closing{tag.starts_with("</")};
    const auto start{closing ? std::size_t{2} : std::size_t{1}};
    const auto name{tag.substr(start, tag.find_first_of(" />", start) - start)};
    if (!is_block(name)) {
      output.append(tag);
    } else if (closing) {
      if (holds.back()) {
        break_line(output, holds.size() - 1);
      }

      holds.pop_back();
      output.append(tag);
    } else {
      if (!holds.empty()) {
        holds.back() = true;
      }

      break_line(output, holds.size());
      output.append(tag);
      if (!tag.ends_with("/>")) {
        holds.push_back(false);
      }
    }
  }

  output += '\n';
  return output;
}

} // namespace

namespace sourcemeta::blaze {

auto to_html(const sourcemeta::core::JSON &documentation, std::string &output,
             const bool pretty) -> void {
  Draw draw;
  const auto *document{&documentation};
  const auto title{text(document, "title")};
  const auto shapes{list(document, "shapes")};

  // Two shapes whose anchors would still clash cannot both be linked to.
  std::map<std::string, std::string> anchors{{"root", ""}};
  for (const auto *shape : shapes) {
    const auto identifier{text(shape, "id")};
    if (!anchors.emplace(anchor(identifier), identifier).second) {
      throw DocumentationError{"Two shapes would share one anchor on the page",
                               sourcemeta::core::Pointer{}, identifier};
    }
  }

  for (const auto *shape : shapes) {
    draw.shapes.insert_or_assign(text(shape, "id"), shape);
  }

  auto root_shape{JSON::make_object()};
  root_shape.assign("id", JSON{std::string{}});
  root_shape.assign("name", JSON{title});
  if (const auto *root{at(document, "root")}; root != nullptr) {
    root_shape.assign("value", *root);
  }

  draw.shapes.insert_or_assign("", draw.keep(std::move(root_shape)));
  const auto *root{at(document, "root")};

  // The shapes, by the section each belongs to, in the order they come.
  std::vector<std::pair<std::string, std::vector<const JSON *>>> groups;
  for (const auto *shape : shapes) {
    const auto section{truthy(at(shape, "section")) ? text(shape, "section")
                                                    : std::string{"Shapes"}};
    auto match{std::find_if(
        groups.begin(), groups.end(),
        [&section](const auto &entry) { return entry.first == section; })};
    if (match == groups.end()) {
      groups.emplace_back(section, std::vector<const JSON *>{});
      match = std::prev(groups.end());
    }

    match->second.push_back(shape);
  }

  Writer body;

  // Which shape applies, when one property decides it.
  const auto root_group{as_group(root, draw)};
  const auto *top{root_group.has_value() ? root_group->group : root};
  const auto root_rows{root_group.has_value()
                           ? render_group(top, draw, std::nullopt)
                           : std::string{}};
  if (const auto *picker{at(top, "discriminator")}; truthy(picker)) {
    const auto cases{list(picker, "cases")};
    body.section();
    body.h2("Which kind of thing this is");
    body.p().attribute("class", "snote").text("The property ");
    body.b(text(picker, "property"));
    body.text(" decides which shape applies. There " +
              (cases.size() == 1
                   ? std::string{"is one choice"}
                   : "are " + std::to_string(cases.size()) + " choices") +
              ".");
    body.close();
    body.div().attribute("class", "chips");
    for (const auto *entry : cases) {
      body.a()
          .attribute("class", "chip pickchip")
          .attribute("href", "#" + anchor(text(entry, "ref")))
          .text(plain(at(entry, "is")))
          .close();
    }

    body.close();
    body.close();
  }

  std::vector<std::string> root_notes;
  if (root_group.has_value() && !root_group->alternatives.empty()) {
    std::vector<std::string> others;
    for (const auto *alternative : root_group->alternatives) {
      others.push_back(label(alternative, draw));
    }

    root_notes.push_back("The whole file may instead be " +
                         sourcemeta::core::join(others, " or ") + ".");
  }

  if (truthy(at(top, "closed"))) {
    root_notes.emplace_back("Nothing else may be added at the top level.");
  }

  for (const auto &phrase : not_phrases(at(top, "not"), draw)) {
    root_notes.push_back(capitalised(phrase) + ".");
  }

  if (const auto *amount{at(top, "propertyCount")}; truthy(amount)) {
    const auto *minimum{at(amount, "min")};
    const auto *maximum{at(amount, "max")};
    if (given(minimum) && given(maximum)) {
      root_notes.push_back("Between " + text(minimum) + " and " +
                           text(maximum) + " properties in all.");
    } else if (given(minimum)) {
      root_notes.push_back("At least " + text(minimum) + " " +
                           (is_one(minimum) ? "property" : "properties") +
                           " in all.");
    } else {
      root_notes.push_back("At most " + text(maximum) + " " +
                           (is_one(maximum) ? "property" : "properties") +
                           " in all.");
    }
  }

  // What a property's own row would say about the top level, which a table of
  // properties has nowhere to put.
  if (const auto *keys{at(top, "keys")}; truthy(keys)) {
    if (truthy(at(keys, "pattern"))) {
      root_notes.push_back("Every property name must match " +
                           text(keys, "pattern") + ".");
    } else if (kind(keys) == "enum" && at(keys, "values") != nullptr &&
               at(keys, "values")->is_array()) {
      root_notes.push_back("Property names can only be " +
                           plain_all(at(keys, "values"), ", ") + ".");
    } else if (truthy(at(keys, "format"))) {
      root_notes.push_back("Every property name must be " +
                           text(keys, "format") + ".");
    }

    if (const auto *length{at(keys, "length")}; truthy(length)) {
      const auto low{given(at(length, "min"))};
      const auto high{given(at(length, "max"))};
      root_notes.push_back(
          "Property names are " +
          (low ? "at least " + text(at(length, "min")) : std::string{}) +
          (low && high ? " and " : "") +
          (high ? "at most " + text(at(length, "max")) : std::string{}) +
          " characters.");
    }
  }

  if (truthy(at(top, "unique"))) {
    root_notes.emplace_back("No two entries are the same.");
  }

  if (given(at(top, "multipleOf"))) {
    root_notes.push_back("In steps of " + plain(at(top, "multipleOf")) + ".");
  }

  if (at(top, "default") != nullptr) {
    root_notes.push_back("Left out means " + plain(at(top, "default")) + ".");
  }

  if (truthy(at(top, "access"))) {
    root_notes.emplace_back(text(top, "access") == "read"
                                ? "The system supplies this; you do not "
                                  "write it."
                                : "You write this; it is never returned.");
  }

  if (truthy(at(top, "otherTypesAllowed"))) {
    root_notes.emplace_back("Data of another kind passes these rules too.");
  }

  if (const auto *content{at(top, "content")};
      truthy(content) && truthy(at(content, "mediaType"))) {
    root_notes.push_back("The text holds " + text(content, "mediaType") + ".");
  }

  body.section().attribute("id", "root");
  body.h2("What this file holds");
  if (!root_rows.empty()) {
    for (const auto &note : root_notes) {
      body.p().attribute("class", "snote").text(note).close();
    }

    table(body, root_rows);
  } else {
    body.div().attribute("class", "leafval");
    value_cell(body, root, draw);
    body.close();
    Writer inner;
    nested_of(inner, root, draw, title, std::nullopt);
    const auto rows{inner.take()};
    if (!rows.empty()) {
      body.table().attribute("class", "doc");
      body.raw(rows);
      body.close();
    }
  }

  body.close();

  if (shapes.size() > 8) {
    body.section();
    body.h2("All " + std::to_string(shapes.size()) + " shapes");
    body.p()
        .attribute("class", "snote")
        .text("Every shape this document describes. The ones used most often "
              "come first, because everything else is built on them. Click "
              "any name to jump to its rules.")
        .close();
    body.div().attribute("class", "ix");
    for (const auto &[section, members] : groups) {
      body.div().attribute("class", "ixgroup");
      body.div().attribute("class", "ixh").text(section).close();
      body.ul();
      for (const auto *shape : members) {
        body.li();
        body.a()
            .attribute("href", "#" + anchor(text(shape, "id")))
            .text(shape_name(shape))
            .close();
        if (used(shape) > 0) {
          body.text(" ")
              .span()
              .attribute("class", "ixn")
              .text("used " + std::to_string(used(shape)))
              .close();
        }

        body.close();
      }

      body.close();
      body.close();
    }

    body.close();
    body.close();
  }

  const auto shape_block = [&draw](Writer &out, const JSON *shape) {
    const auto *value{at(shape, "value")};
    const auto list_shape{kind(value) == "array"};
    const auto group{as_group(list_shape ? at(value, "item") : value, draw)};
    const auto *shape_body{group.has_value() ? group->group : value};
    std::optional<Rows> rows;
    if (group.has_value() &&
        !(is_map(shape_body) && !map_has_inside(shape_body, draw))) {
      rows = rows_of(shape_body, draw);
    } else if (count(value, "conditions") > 0) {
      rows = rows_of(value, draw);
    }

    const auto drawn{rows.has_value() && row_count(rows.value()) > 0};
    out.div()
        .attribute("class", "shapeblock")
        .attribute("id", anchor(text(shape, "id")));
    out.h4(shape_name(shape));
    const auto note = [&out](const std::string &sentence) {
      out.p().attribute("class", "snote").text(sentence).close();
    };

    if (truthy(at(value, "description"))) {
      note(text(value, "description"));
    }

    if (group.has_value() && !group->alternatives.empty()) {
      std::vector<std::string> others;
      for (const auto *alternative : group->alternatives) {
        others.push_back(label(alternative, draw));
      }

      note("It may instead be " + sourcemeta::core::join(others, " or ") + ".");
    }

    for (const auto &phrase : not_phrases(at(shape_body, "not"), draw)) {
      note(capitalised(phrase) + ".");
    }

    for (const auto *also : list(value, "also")) {
      if (kind(also) != "ref") {
        continue;
      }

      const auto *target{draw.shape(text(also, "ref"))};
      if (kind(value) == "object" && target != nullptr &&
          truthy(at(target, "value")) &&
          kind(at(target, "value")) == "object") {
        continue;
      }

      out.p()
          .attribute("class", "snote")
          .text("This also follows every rule of ");
      link(out, text(also, "ref"), draw, "link");
      out.text(".").close();
    }

    if (const auto *picker{at(shape_body, "discriminator")}; truthy(picker)) {
      std::vector<std::string> cases;
      for (const auto *entry : list(picker, "cases")) {
        cases.push_back(plain(at(entry, "is")) + " means " +
                        draw.name_of(text(entry, "ref")));
      }

      note("The property " + text(picker, "property") +
           " decides which shape applies: " +
           sourcemeta::core::join(cases, ", ") + ".");
    }

    if (list_shape) {
      note(drawn ? "This one is a list. The properties below describe a "
                   "single entry."
                 : "This one is a list.");
    }

    if (truthy(at(shape_body, "closed"))) {
      note("Nothing else may be added to it.");
    }

    if (used(shape) > 0) {
      note("Used in " + std::to_string(used(shape)) + " " +
           plural(used(shape), "place", "places") + ".");
    }

    if (drawn) {
      table(out, render_group(group.has_value() ? shape_body : value, draw,
                              std::nullopt));
    } else {
      out.div().attribute("class", "leafval");
      value_cell(out, value, draw);
      out.close();
      Writer inner;
      nested_of(inner, value, draw, shape_name(shape), std::nullopt);
      const auto rows_inside{inner.take()};
      if (!rows_inside.empty()) {
        out.table().attribute("class", "doc");
        out.raw(rows_inside);
        out.close();
      }
    }

    out.close();
  };

  if (!shapes.empty()) {
    body.section();
    body.h2("Every shape, written out once");
    body.p()
        .attribute("class", "snote")
        .text("Each shape appears here once. Anywhere else on this page that "
              "names one, it means exactly this.")
        .close();
    for (const auto &[section, members] : groups) {
      body.div().attribute("class", "defblock");
      if (groups.size() > 1) {
        body.h3(section);
      }

      for (const auto *shape : members) {
        shape_block(body, shape);
      }

      body.close();
    }

    body.close();
  }

  const auto drawn{body.take()};
  const auto stat = [&draw](const std::string &key) -> std::size_t {
    const auto match{draw.stats.find(key)};
    return match == draw.stats.cend() ? 0 : match->second;
  };

  Writer page;
  page.h1(title);
  if (truthy(at(document, "description"))) {
    page.p()
        .attribute("class", "subtitle")
        .text(text(document, "description"))
        .close();
  }

  const auto counted{stat("req") + stat("opt") + stat("cond")};
  if (counted > 0 || !shapes.empty()) {
    page.div().attribute("class", "counts");
    const auto chip = [&page](const std::string &variant,
                              const std::size_t amount,
                              const std::string &sentence) {
      page.span().attribute("class", "c " + variant);
      page.b(std::to_string(amount)).text(sentence).close();
    };

    if (stat("req") > 0) {
      chip("req", stat("req"), " you must always fill in");
    }

    if (stat("opt") > 0) {
      chip("opt", stat("opt"), " you can leave out");
    }

    if (stat("cond") > 0) {
      chip("cond", stat("cond"), " that only apply in certain cases");
    }

    if (counted == 0) {
      chip("opt", shapes.size(),
           " " + plural(shapes.size(), "shape", "shapes") +
               ", written out below");
    }

    page.close();
  }

  // Each line of the legend is a reading instruction, so it is only given
  // when the page holds the thing it talks about.
  struct Line {
    std::string marker;
    std::string lead;
    std::string rest;
  };

  const std::vector<Line> lines{
      {.marker = "<table class=\"doc\">",
       .lead = "A table inside a row",
       .rest = " means those properties live inside that one."},
      {.marker = "<details",
       .lead = "Click a strip",
       .rest = " to open what it holds."},
      {.marker = "class=\"bar\"",
       .lead = "Ranges",
       .rest = " show the lowest and highest allowed."},
      {.marker = "href=\"#",
       .lead = "Linked names",
       .rest = " lead to the shape they name."}};
  auto legend{false};
  for (const auto &line : lines) {
    if (drawn.find(line.marker) == std::string::npos) {
      continue;
    }

    if (!legend) {
      page.div().attribute("class", "legend");
      legend = true;
    }

    page.span().b(line.lead).text(line.rest).close();
  }

  if (legend) {
    page.close();
  }

  page.raw(drawn);
  if (pretty) {
    output += indented(page.str());
  } else {
    output += page.take();
  }
}

} // namespace sourcemeta::blaze
