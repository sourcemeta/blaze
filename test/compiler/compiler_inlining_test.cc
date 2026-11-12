#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

#include <sourcemeta/core/json.h>

#include <cstddef> // std::size_t
#include <string>  // std::to_string
#include <utility> // std::move

namespace {

auto shared_references(const std::size_t depth, const bool nested)
    -> sourcemeta::core::JSON {
  auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$defs": { "d0": { "type": "string" } }
  })JSON")};

  for (std::size_t index = 1; index <= depth; ++index) {
    auto branch{sourcemeta::core::JSON::make_object()};
    branch.assign("$ref", sourcemeta::core::JSON{"#/$defs/d" +
                                                 std::to_string(index - 1)});
    auto branches{sourcemeta::core::JSON::make_array()};
    branches.push_back(branch);
    branches.push_back(branch);
    auto target{sourcemeta::core::JSON::make_object()};
    target.assign("allOf", std::move(branches));
    if (nested) {
      auto wrapper{sourcemeta::core::JSON::make_object()};
      wrapper.assign("not", std::move(target));
      target = std::move(wrapper);
    }

    schema.at("$defs").assign("d" + std::to_string(index), std::move(target));
  }

  schema.assign("$ref",
                sourcemeta::core::JSON{"#/$defs/d" + std::to_string(depth)});
  return schema;
}

auto check_shared_references(const bool nested) -> void {
  const auto schema{shared_references(16, nested)};
  sourcemeta::blaze::Tweaks tweaks;
  // This is ample room for the small shared graph, but not for the tree that
  // stale target sizes let the inliner expand it into.
  tweaks.max_instructions = 4096;
  const auto compiled{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};

  tweaks.target_inline_threshold = 0;
  const auto without_inlining{sourcemeta::blaze::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};

  sourcemeta::blaze::Evaluator evaluator;
  const sourcemeta::core::JSON valid{"example"};
  const sourcemeta::core::JSON invalid{42};
  EXPECT_TRUE(evaluator.validate(compiled, valid));
  EXPECT_FALSE(evaluator.validate(compiled, invalid));
  EXPECT_EQ(evaluator.validate(compiled, valid),
            evaluator.validate(without_inlining, valid));
  EXPECT_EQ(evaluator.validate(compiled, invalid),
            evaluator.validate(without_inlining, invalid));
}

} // namespace

TEST(inlining_uses_current_target_sizes) { check_shared_references(false); }

TEST(inlining_counts_nested_instructions) { check_shared_references(true); }
