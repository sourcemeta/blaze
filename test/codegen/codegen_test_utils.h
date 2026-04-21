#ifndef SOURCEMETA_BLAZE_CODEGEN_TEST_UTILS_H_
#define SOURCEMETA_BLAZE_CODEGEN_TEST_UTILS_H_

// TODO: Have macros for objects and enumerations

#define EXPECT_AS_STRING(actual, expected)                                     \
  EXPECT_EQ(sourcemeta::core::to_string(actual), expected)

#define EXPECT_SYMBOL(actual, ...)                                             \
  EXPECT_EQ(actual, (std::vector<std::string>{__VA_ARGS__}))

#define EXPECT_IR_SCALAR(result, index, scalar_type, expected_pointer)         \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::CodegenIRScalar>(      \
      result.at(index)))                                                       \
      << "Expected CodegenIRScalar at index " << index;                        \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRScalar>(result.at(index)).pointer,  \
      expected_pointer);                                                       \
  EXPECT_EQ(                                                                   \
      std::get<sourcemeta::blaze::CodegenIRScalar>(result.at(index)).value,    \
      sourcemeta::blaze::CodegenIRScalarType::scalar_type)

#define EXPECT_IR_IMPOSSIBLE(result, index, expected_pointer)                  \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::CodegenIRImpossible>(  \
      result.at(index)))                                                       \
      << "Expected CodegenIRImpossible at index " << index;                    \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRImpossible>(result.at(index))       \
          .pointer,                                                            \
      expected_pointer)

#define EXPECT_IR_ANY(result, index, expected_pointer)                         \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::CodegenIRAny>(         \
      result.at(index)))                                                       \
      << "Expected CodegenIRAny at index " << index;                           \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRAny>(result.at(index)).pointer,     \
      expected_pointer)

#define EXPECT_IR_ARRAY(result, index, expected_pointer,                       \
                        expected_items_pointer)                                \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::CodegenIRArray>(       \
      result.at(index)))                                                       \
      << "Expected CodegenIRArray at index " << index;                         \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRArray>(result.at(index)).pointer,   \
      expected_pointer);                                                       \
  EXPECT_TRUE(std::get<sourcemeta::blaze::CodegenIRArray>(result.at(index))    \
                  .items.has_value())                                          \
      << "Expected CodegenIRArray items to have a value";                      \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRArray>(result.at(index))            \
          .items->pointer,                                                     \
      expected_items_pointer)

#define EXPECT_IR_INTERSECTION(result, index, expected_pointer,                \
                               expected_count)                                 \
  EXPECT_TRUE(                                                                 \
      std::holds_alternative<sourcemeta::blaze::CodegenIRIntersection>(        \
          result.at(index)))                                                   \
      << "Expected CodegenIRIntersection at index " << index;                  \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRIntersection>(result.at(index))     \
          .pointer,                                                            \
      expected_pointer);                                                       \
  EXPECT_EQ(                                                                   \
      std::get<sourcemeta::blaze::CodegenIRIntersection>(result.at(index))     \
          .values.size(),                                                      \
      expected_count)

#define EXPECT_IR_CONDITIONAL(result, index, expected_pointer, expected_if,    \
                              expected_then, expected_else)                    \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::CodegenIRConditional>( \
      result.at(index)))                                                       \
      << "Expected CodegenIRConditional at index " << index;                   \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRConditional>(result.at(index))      \
          .pointer,                                                            \
      expected_pointer);                                                       \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRConditional>(result.at(index))      \
          .condition.pointer,                                                  \
      expected_if);                                                            \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRConditional>(result.at(index))      \
          .consequent.pointer,                                                 \
      expected_then);                                                          \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRConditional>(result.at(index))      \
          .alternative.pointer,                                                \
      expected_else)

#define EXPECT_IR_REFERENCE(result, index, expected_pointer,                   \
                            expected_target_pointer)                           \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::blaze::CodegenIRReference>(   \
      result.at(index)))                                                       \
      << "Expected CodegenIRReference at index " << index;                     \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRReference>(result.at(index))        \
          .pointer,                                                            \
      expected_pointer);                                                       \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::blaze::CodegenIRReference>(result.at(index))        \
          .target.pointer,                                                     \
      expected_target_pointer)

#endif
