#ifndef SOURCEMETA_BLAZE_CODEGEN_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_CODEGEN_TEST_UTILS_H_

#include <cstddef> // std::size_t
#include <string>  // std::string
#include <variant> // std::visit

// TODO: Have macros for objects and enumerations

// Where the entry describing a given place in the schema sits. The order the
// entries come in is not part of what a solution has to reproduce, and neither
// is the set of entries nothing refers to, so a test says which place it means
inline auto ir_index_of(const sourcemeta::blaze::CodegenIRResult &result,
                        const std::string &pointer) -> std::size_t {
  for (std::size_t index = 0; index < result.size(); index++) {
    const auto &current{std::visit(
        [](const auto &entity) -> const sourcemeta::core::Pointer & {
          return entity.pointer;
        },
        result.at(index))};
    if (sourcemeta::core::to_string(current) == pointer) {
      return index;
    }
  }

  return result.size();
}

#define EXPECT_AS_STRING(actual, expected)                                     \
  EXPECT_EQ(sourcemeta::core::to_string(actual), expected)

#define EXPECT_SYMBOL(actual, ...)                                             \
  EXPECT_EQ(actual, (std::vector<std::string>{__VA_ARGS__}))

// Nothing in the result stands for the given place
#define EXPECT_IR_NOTHING(result, expected_pointer)                            \
  EXPECT_EQ(ir_index_of(result, expected_pointer), result.size())

// A place the result does not stand for would otherwise go out of range, which
// says nothing of the place a test went looking for. Saying so is not enough on
// its own, as an expectation carries on where it fails, so each macro below
// leaves off here rather than reaching for the place it could not find.
//
// Every macro that reads a place wraps its body in a loop, so that leaving off
// is a `break` and so that the macro expands into a single statement
// NOLINTBEGIN(cppcoreguidelines-avoid-do-while)
#define EXPECT_IR_SOMEWHERE(result, index)                                     \
  EXPECT_NE(index, result.size());                                             \
  if ((index) == (result).size()) {                                            \
    break;                                                                     \
  }

#define EXPECT_IR_SCALAR(result, index, scalar_type, expected_pointer)         \
  do {                                                                         \
    EXPECT_IR_SOMEWHERE(result, index);                                        \
    EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::CodegenIRScalar>(    \
        result.at(index)));                                                    \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRScalar>(result.at(index))         \
            .pointer,                                                          \
        expected_pointer);                                                     \
    EXPECT_EQ(                                                                 \
        std::get<sourcemeta::blaze::CodegenIRScalar>(result.at(index)).value,  \
        sourcemeta::blaze::CodegenIRScalarType::scalar_type);                  \
  } while (false)

#define EXPECT_IR_IMPOSSIBLE(result, index, expected_pointer)                  \
  do {                                                                         \
    EXPECT_IR_SOMEWHERE(result, index);                                        \
    EXPECT_TRUE(                                                               \
        std::holds_alternative<sourcemeta::blaze::CodegenIRImpossible>(        \
            result.at(index)));                                                \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRImpossible>(result.at(index))     \
            .pointer,                                                          \
        expected_pointer);                                                     \
  } while (false)

#define EXPECT_IR_ANY(result, index, expected_pointer)                         \
  do {                                                                         \
    EXPECT_IR_SOMEWHERE(result, index);                                        \
    EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::CodegenIRAny>(       \
        result.at(index)));                                                    \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRAny>(result.at(index)).pointer,   \
        expected_pointer);                                                     \
  } while (false)

#define EXPECT_IR_ARRAY(result, index, expected_pointer,                       \
                        expected_items_pointer)                                \
  do {                                                                         \
    EXPECT_IR_SOMEWHERE(result, index);                                        \
    EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::CodegenIRArray>(     \
        result.at(index)));                                                    \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRArray>(result.at(index)).pointer, \
        expected_pointer);                                                     \
    EXPECT_TRUE(std::get<sourcemeta::blaze::CodegenIRArray>(result.at(index))  \
                    .items.has_value());                                       \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRArray>(result.at(index))          \
            .items->pointer,                                                   \
        expected_items_pointer);                                               \
  } while (false)

#define EXPECT_IR_INTERSECTION(result, index, expected_pointer,                \
                               expected_count)                                 \
  do {                                                                         \
    EXPECT_IR_SOMEWHERE(result, index);                                        \
    EXPECT_TRUE(                                                               \
        std::holds_alternative<sourcemeta::blaze::CodegenIRIntersection>(      \
            result.at(index)));                                                \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRIntersection>(result.at(index))   \
            .pointer,                                                          \
        expected_pointer);                                                     \
    EXPECT_EQ(                                                                 \
        std::get<sourcemeta::blaze::CodegenIRIntersection>(result.at(index))   \
            .values.size(),                                                    \
        expected_count);                                                       \
  } while (false)

#define EXPECT_IR_CONDITIONAL(result, index, expected_pointer, expected_if,    \
                              expected_then, expected_else)                    \
  do {                                                                         \
    EXPECT_IR_SOMEWHERE(result, index);                                        \
    EXPECT_TRUE(                                                               \
        std::holds_alternative<sourcemeta::blaze::CodegenIRConditional>(       \
            result.at(index)));                                                \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRConditional>(result.at(index))    \
            .pointer,                                                          \
        expected_pointer);                                                     \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRConditional>(result.at(index))    \
            .condition.pointer,                                                \
        expected_if);                                                          \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRConditional>(result.at(index))    \
            .consequent.pointer,                                               \
        expected_then);                                                        \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRConditional>(result.at(index))    \
            .alternative.pointer,                                              \
        expected_else);                                                        \
  } while (false)

#define EXPECT_IR_REFERENCE(result, index, expected_pointer,                   \
                            expected_target_pointer)                           \
  do {                                                                         \
    EXPECT_IR_SOMEWHERE(result, index);                                        \
    EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::CodegenIRReference>( \
        result.at(index)));                                                    \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRReference>(result.at(index))      \
            .pointer,                                                          \
        expected_pointer);                                                     \
    EXPECT_AS_STRING(                                                          \
        std::get<sourcemeta::blaze::CodegenIRReference>(result.at(index))      \
            .target.pointer,                                                   \
        expected_target_pointer);                                              \
  } while (false)
// NOLINTEND(cppcoreguidelines-avoid-do-while)

#endif
