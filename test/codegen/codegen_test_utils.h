#ifndef SOURCEMETA_BLAZE_CODEGEN_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_CODEGEN_TEST_UTILS_H_

// TODO: Have macros for objects and enumerations

#define EXPECT_AS_STRING(actual, expected)                                     \
  EXPECT_EQ(sourcemeta::core::to_string(actual), expected)

#define EXPECT_SYMBOL(actual, ...)                                             \
  EXPECT_EQ(actual, (std::vector<std::string>{__VA_ARGS__}))

#define EXPECT_IR_SCALAR(result, index, scalar_type, expected_pointer)         \
  EXPECT_TRUE(                                                                 \
      std::holds_alternative<sourcemeta::blaze::IRScalar>(result.at(index)))   \
      << "Expected IRScalar at index " << index;                               \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRScalar>(result.at(index)).pointer,         \
      expected_pointer);                                                       \
  EXPECT_EQ(std::get<sourcemeta::blaze::IRScalar>(result.at(index)).value,     \
            sourcemeta::blaze::IRScalarType::scalar_type)

#define EXPECT_IR_IMPOSSIBLE(result, index, expected_pointer)                  \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::IRImpossible>(         \
      result.at(index)))                                                       \
      << "Expected IRImpossible at index " << index;                           \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRImpossible>(result.at(index)).pointer,     \
      expected_pointer)

#define EXPECT_IR_ANY(result, index, expected_pointer)                         \
  EXPECT_TRUE(                                                                 \
      std::holds_alternative<sourcemeta::blaze::IRAny>(result.at(index)))      \
      << "Expected IRAny at index " << index;                                  \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRAny>(result.at(index)).pointer,            \
      expected_pointer)

#define EXPECT_IR_ARRAY(result, index, expected_pointer,                       \
                        expected_items_pointer)                                \
  EXPECT_TRUE(                                                                 \
      std::holds_alternative<sourcemeta::blaze::IRArray>(result.at(index)))    \
      << "Expected IRArray at index " << index;                                \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRArray>(result.at(index)).pointer,          \
      expected_pointer);                                                       \
  EXPECT_TRUE(std::get<sourcemeta::blaze::IRArray>(result.at(index))           \
                  .items.has_value())                                          \
      << "Expected IRArray items to have a value";                             \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRArray>(result.at(index)).items->pointer,   \
      expected_items_pointer)

#define EXPECT_IR_INTERSECTION(result, index, expected_pointer,                \
                               expected_count)                                 \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::IRIntersection>(       \
      result.at(index)))                                                       \
      << "Expected IRIntersection at index " << index;                         \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRIntersection>(result.at(index)).pointer,   \
      expected_pointer);                                                       \
  EXPECT_EQ(std::get<sourcemeta::blaze::IRIntersection>(result.at(index))      \
                .values.size(),                                                \
            expected_count)

#define EXPECT_IR_CONDITIONAL(result, index, expected_pointer, expected_if,    \
                              expected_then, expected_else)                    \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::IRConditional>(        \
      result.at(index)))                                                       \
      << "Expected IRConditional at index " << index;                          \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRConditional>(result.at(index)).pointer,    \
      expected_pointer);                                                       \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRConditional>(result.at(index))             \
          .condition.pointer,                                                  \
      expected_if);                                                            \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRConditional>(result.at(index))             \
          .consequent.pointer,                                                 \
      expected_then);                                                          \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRConditional>(result.at(index))             \
          .alternative.pointer,                                                \
      expected_else)

#define EXPECT_IR_REFERENCE(result, index, expected_pointer,                   \
                            expected_target_pointer)                           \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::IRReference>(          \
      result.at(index)))                                                       \
      << "Expected IRReference at index " << index;                            \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::IRReference>(result.at(index)).pointer,      \
      expected_pointer);                                                       \
  EXPECT_AS_STRING(std::get<sourcemeta::blaze::IRReference>(result.at(index))  \
                       .target.pointer,                                        \
                   expected_target_pointer)

#endif
