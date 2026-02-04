#ifndef SOURCEMETA_BLAZE_EVALUATOR_UTILS_H_
#define SOURCEMETA_BLAZE_EVALUATOR_UTILS_H_

#include <cassert>
#include <tuple>
#include <vector>

inline auto FIRST_PROPERTY_IS(const sourcemeta::core::JSON &document,
                              const std::string &check) -> bool {
  assert(document.is_object());
  return document.as_object().cbegin()->first == check;
}

#define EVALUATE_WITH_TRACE(schema_template, instance, count)                  \
  std::vector<std::tuple<                                                      \
      bool, sourcemeta::core::WeakPointer, sourcemeta::core::WeakPointer,      \
      sourcemeta::blaze::Instruction, sourcemeta::core::JSON>>                 \
      trace_pre;                                                               \
  std::vector<std::tuple<                                                      \
      bool, sourcemeta::core::WeakPointer, sourcemeta::core::WeakPointer,      \
      sourcemeta::blaze::Instruction, sourcemeta::core::JSON>>                 \
      trace_post;                                                              \
  sourcemeta::blaze::Evaluator evaluator;                                      \
  const auto result{evaluator.validate(                                        \
      schema_template, instance,                                               \
      [&trace_pre, &trace_post](                                               \
          const sourcemeta::blaze::EvaluationType type, const bool valid,      \
          const sourcemeta::blaze::Instruction &step,                          \
          const sourcemeta::core::WeakPointer &evaluate_path,                  \
          const sourcemeta::core::WeakPointer &instance_location,              \
          const sourcemeta::core::JSON &annotation) {                          \
        if (type == sourcemeta::blaze::EvaluationType::Pre) {                  \
          trace_pre.push_back(                                                 \
              {valid, evaluate_path, instance_location, step, annotation});    \
        } else if (type == sourcemeta::blaze::EvaluationType::Post) {          \
          trace_post.push_back(                                                \
              {valid, evaluate_path, instance_location, step, annotation});    \
        }                                                                      \
      })};                                                                     \
  EXPECT_EQ(trace_pre.size(), count);                                          \
  EXPECT_EQ(trace_post.size(), count);

#define __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema)                  \
  {                                                                            \
    const auto template_json{sourcemeta::blaze::to_json(compiled_schema)};     \
    EXPECT_TRUE(template_json.is_array());                                     \
    const auto template_back{sourcemeta::blaze::from_json(template_json)};     \
    EXPECT_TRUE(template_back.has_value());                                    \
    const auto template_json_back{                                             \
        sourcemeta::blaze::to_json(template_back.value())};                    \
    EXPECT_EQ(template_json, template_json_back);                              \
  }

#define EVALUATE_WITH_TRACE_FAST_SUCCESS(schema, instance, count, entrypoint)  \
  const auto compiled_schema{sourcemeta::blaze::compile(                       \
      schema, sourcemeta::core::schema_walker,                                 \
      sourcemeta::core::schema_resolver,                                       \
      sourcemeta::blaze::default_schema_compiler,                              \
      sourcemeta::blaze::Mode::FastValidation, "", "", (entrypoint))};         \
  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);                       \
  EVALUATE_WITH_TRACE(compiled_schema, instance, count)                        \
  EXPECT_TRUE(result);

#define EVALUATE_WITH_TRACE_FAST_FAILURE(schema, instance, count, entrypoint)  \
  const auto compiled_schema{sourcemeta::blaze::compile(                       \
      schema, sourcemeta::core::schema_walker,                                 \
      sourcemeta::core::schema_resolver,                                       \
      sourcemeta::blaze::default_schema_compiler,                              \
      sourcemeta::blaze::Mode::FastValidation, "", "", (entrypoint))};         \
  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);                       \
  EVALUATE_WITH_TRACE(compiled_schema, instance, count)                        \
  EXPECT_FALSE(result);

#define EVALUATE_WITH_TRACE_EXHAUSTIVE_SUCCESS(schema, instance, count,        \
                                               entrypoint)                     \
  const auto compiled_schema{sourcemeta::blaze::compile(                       \
      schema, sourcemeta::core::schema_walker,                                 \
      sourcemeta::core::schema_resolver,                                       \
      sourcemeta::blaze::default_schema_compiler,                              \
      sourcemeta::blaze::Mode::Exhaustive, "", "", (entrypoint))};             \
  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);                       \
  EVALUATE_WITH_TRACE(compiled_schema, instance, count)                        \
  EXPECT_TRUE(result);

#define EVALUATE_WITH_TRACE_EXHAUSTIVE_FAILURE(schema, instance, count,        \
                                               entrypoint)                     \
  const auto compiled_schema{sourcemeta::blaze::compile(                       \
      schema, sourcemeta::core::schema_walker,                                 \
      sourcemeta::core::schema_resolver,                                       \
      sourcemeta::blaze::default_schema_compiler,                              \
      sourcemeta::blaze::Mode::Exhaustive, "", "", (entrypoint))};             \
  __ASSERT_TEMPLATE_JSON_SERIALISATION(compiled_schema);                       \
  EVALUATE_WITH_TRACE(compiled_schema, instance, count)                        \
  EXPECT_FALSE(result);

#define EVALUATE_TRACE_PRE(index, step_type, evaluate_path,                    \
                           expected_keyword_location,                          \
                           expected_instance_location)                         \
  EXPECT_TRUE(index < trace_pre.size());                                       \
  EXPECT_TRUE(std::get<0>(trace_pre.at(index)));                               \
  EXPECT_EQ(sourcemeta::core::to_string(std::get<1>(trace_pre.at(index))),     \
            evaluate_path);                                                    \
  EXPECT_EQ(sourcemeta::core::to_string(std::get<2>(trace_pre.at(index))),     \
            expected_instance_location);                                       \
  EXPECT_TRUE(std::get<3>(trace_pre.at(index)).type ==                         \
              sourcemeta::blaze::InstructionIndex::step_type);                 \
  EXPECT_EQ(std::get<3>(trace_pre.at(index)).keyword_location,                 \
            expected_keyword_location);                                        \
  EXPECT_TRUE(std::get<4>(trace_pre.at(index)).is_null());

#define EVALUATE_TRACE_POST(index, step_type, evaluate_path,                   \
                            expected_keyword_location,                         \
                            expected_instance_location)                        \
  EXPECT_EQ(sourcemeta::core::to_string(std::get<1>(trace_post.at(index))),    \
            evaluate_path);                                                    \
  EXPECT_EQ(sourcemeta::core::to_string(std::get<2>(trace_post.at(index))),    \
            expected_instance_location);                                       \
  EXPECT_TRUE(std::get<3>(trace_post.at(index)).type ==                        \
              sourcemeta::blaze::InstructionIndex::step_type);                 \
  EXPECT_EQ(std::get<3>(trace_post.at(index)).keyword_location,                \
            expected_keyword_location);

#define EVALUATE_TRACE_POST_SUCCESS(index, step_type, evaluate_path,           \
                                    keyword_location, instance_location)       \
  EXPECT_TRUE(index < trace_post.size());                                      \
  EXPECT_TRUE(std::get<0>(trace_post.at(index)));                              \
  EVALUATE_TRACE_POST(index, step_type, evaluate_path, keyword_location,       \
                      instance_location);                                      \
  EXPECT_TRUE(std::get<4>(trace_post.at(index)).is_null());

#define EVALUATE_TRACE_PRE_ANNOTATION(index, evaluate_path, keyword_location,  \
                                      instance_location)                       \
  if (std::get<3>(trace_pre.at(index)).type ==                                 \
      sourcemeta::blaze::InstructionIndex::AnnotationBasenameToParent) {       \
    EVALUATE_TRACE_PRE(index, AnnotationBasenameToParent, evaluate_path,       \
                       keyword_location, instance_location);                   \
  } else if (std::get<3>(trace_pre.at(index)).type ==                          \
             sourcemeta::blaze::InstructionIndex::AnnotationToParent) {        \
    EVALUATE_TRACE_PRE(index, AnnotationToParent, evaluate_path,               \
                       keyword_location, instance_location);                   \
  } else {                                                                     \
    EVALUATE_TRACE_PRE(index, AnnotationEmit, evaluate_path, keyword_location, \
                       instance_location);                                     \
  }                                                                            \
  EXPECT_TRUE(std::get<4>(trace_pre.at(index)).is_null());

#define EVALUATE_TRACE_POST_ANNOTATION(index, evaluate_path, keyword_location, \
                                       instance_location, expected_annotation) \
  EXPECT_TRUE(index < trace_post.size());                                      \
  EXPECT_TRUE(std::get<0>(trace_post.at(index)));                              \
  if (std::get<3>(trace_post.at(index)).type ==                                \
      sourcemeta::blaze::InstructionIndex::AnnotationBasenameToParent) {       \
    EVALUATE_TRACE_POST(index, AnnotationBasenameToParent, evaluate_path,      \
                        keyword_location, instance_location);                  \
  } else if (std::get<3>(trace_post.at(index)).type ==                         \
             sourcemeta::blaze::InstructionIndex::AnnotationToParent) {        \
    EVALUATE_TRACE_POST(index, AnnotationToParent, evaluate_path,              \
                        keyword_location, instance_location);                  \
  } else {                                                                     \
    EVALUATE_TRACE_POST(index, AnnotationEmit, evaluate_path,                  \
                        keyword_location, instance_location);                  \
  }                                                                            \
  EXPECT_EQ(std::get<4>(trace_post.at(index)),                                 \
            sourcemeta::core::JSON(expected_annotation));

#define EVALUATE_TRACE_POST_FAILURE(index, step_type, evaluate_path,           \
                                    keyword_location, instance_location)       \
  EXPECT_TRUE(index < trace_post.size());                                      \
  EXPECT_FALSE(std::get<0>(trace_post.at(index)));                             \
  EVALUATE_TRACE_POST(index, step_type, evaluate_path, keyword_location,       \
                      instance_location);                                      \
  EXPECT_TRUE(std::get<4>(trace_post.at(index)).is_null());

#define EVALUATE_TRACE_POST_DESCRIBE(instance, index, message)                 \
  EXPECT_EQ(sourcemeta::blaze::describe(std::get<0>(trace_post.at(index)),     \
                                        std::get<3>(trace_post.at(index)),     \
                                        std::get<1>(trace_post.at(index)),     \
                                        std::get<2>(trace_post.at(index)),     \
                                        instance,                              \
                                        std::get<4>(trace_post.at(index))),    \
            (message));

#endif
