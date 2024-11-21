#ifndef SOURCEMETA_BLAZE_EVALUATOR_H_
#define SOURCEMETA_BLAZE_EVALUATOR_H_

#ifndef SOURCEMETA_BLAZE_EVALUATOR_EXPORT
#include <sourcemeta/blaze/evaluator_export.h>
#endif

#include <sourcemeta/blaze/evaluator_context.h>
#include <sourcemeta/blaze/evaluator_error.h>
#include <sourcemeta/blaze/evaluator_instruction.h>

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonpointer.h>

#include <cstdint>    // std::uint8_t
#include <functional> // std::function
#include <utility>    // std::pair

/// @defgroup evaluator Evaluator
/// @brief A high-performance JSON Schema evaluator
///
/// This functionality is included as follows:
///
/// ```cpp
/// #include <sourcemeta/blaze/evaluator.h>
/// ```

namespace sourcemeta::blaze {

/// @ingroup evaluator
/// Represents the state of an instruction evaluation
enum class EvaluationType : std::uint8_t { Pre, Post };

/// @ingroup evaluator
/// Flags that affect how evaluation is carried
struct Modifiers {};

/// @ingroup evaluator
/// Represents a compiled schema ready for execution
using Template = std::pair<Instructions, Modifiers>;

/// @ingroup evaluator
/// A callback of this type is invoked after evaluating any keyword. The
/// arguments go as follows:
///
/// - The stage at which the instruction in question is
/// - Whether the evaluation was successful or not (always true before
/// evaluation)
/// - The instruction that was just evaluated
/// - The evaluation path
/// - The instance location
/// - The annotation result, if any (otherwise null)
///
/// You can use this callback mechanism to implement arbitrary output formats.
using Callback =
    std::function<void(const EvaluationType, bool, const Instruction &,
                       const sourcemeta::jsontoolkit::WeakPointer &,
                       const sourcemeta::jsontoolkit::WeakPointer &,
                       const sourcemeta::jsontoolkit::JSON &)>;

/// @ingroup evaluator
///
/// This function evaluates a schema compiler template, returning a boolean
/// without error information. For example:
///
/// ```cpp
/// #include <sourcemeta/blaze/evaluator.h>
/// #include <sourcemeta/blaze/compiler.h>
///
/// #include <sourcemeta/jsontoolkit/json.h>
/// #include <sourcemeta/jsontoolkit/jsonschema.h>
///
/// #include <cassert>
///
/// const sourcemeta::jsontoolkit::JSON schema =
///     sourcemeta::jsontoolkit::parse(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "type": "string"
/// })JSON");
///
/// const auto schema_template{sourcemeta::blaze::compile(
///     schema, sourcemeta::jsontoolkit::default_schema_walker,
///     sourcemeta::jsontoolkit::official_resolver,
///     sourcemeta::jsontoolkit::default_schema_compiler)};
///
/// const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
/// const auto result{sourcemeta::blaze::evaluate(
///   schema_template, instance)};
/// assert(result);
/// ```
auto SOURCEMETA_BLAZE_EVALUATOR_EXPORT
evaluate(const Template &schema, const sourcemeta::jsontoolkit::JSON &instance)
    -> bool;

/// @ingroup evaluator
///
/// This function evaluates a schema compiler template, executing the given
/// callback at every step of the way. For example:
///
/// ```cpp
/// #include <sourcemeta/blaze/evaluator.h>
/// #include <sourcemeta/blaze/compiler.h>
///
/// #include <sourcemeta/jsontoolkit/json.h>
/// #include <sourcemeta/jsontoolkit/jsonschema.h>
///
/// #include <cassert>
/// #include <iostream>
///
/// const sourcemeta::jsontoolkit::JSON schema =
///     sourcemeta::jsontoolkit::parse(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "type": "string"
/// })JSON");
///
/// const auto schema_template{sourcemeta::blaze::compile(
///     schema, sourcemeta::jsontoolkit::default_schema_walker,
///     sourcemeta::jsontoolkit::official_resolver,
///     sourcemeta::jsontoolkit::default_schema_compiler)};
///
/// static auto callback(
///     bool result,
///     const sourcemeta::blaze::Instruction &instruction,
///     const sourcemeta::jsontoolkit::Pointer &evaluate_path,
///     const sourcemeta::jsontoolkit::Pointer &instance_location,
///     const sourcemeta::jsontoolkit::JSON &document,
///     const sourcemeta::jsontoolkit::JSON &annotation) -> void {
///   std::cout << "TYPE: " << (result ? "Success" : "Failure") << "\n";
///   std::cout << "INSTRUCTION:\n";
///   sourcemeta::jsontoolkit::prettify(sourcemeta::blaze::to_json({instruction}),
///                                     std::cout);
///   std::cout << "\nEVALUATE PATH:";
///   sourcemeta::jsontoolkit::stringify(evaluate_path, std::cout);
///   std::cout << "\nINSTANCE LOCATION:";
///   sourcemeta::jsontoolkit::stringify(instance_location, std::cout);
///   std::cout << "\nANNOTATION:\n";
///   sourcemeta::jsontoolkit::prettify(annotation, std::cout);
///   std::cout << "\n";
/// }
///
/// const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
/// const auto result{sourcemeta::blaze::evaluate(
///   schema_template, instance, callback)};
///
/// assert(result);
/// ```
auto SOURCEMETA_BLAZE_EVALUATOR_EXPORT
evaluate(const Template &schema, const sourcemeta::jsontoolkit::JSON &instance,
         const Callback &callback) -> bool;

/// @ingroup evaluator
///
/// This function evaluates a schema compiler template from an evaluation
/// context, returning a boolean without error information. The evaluation
/// context can be re-used among evaluations (as long as its always loaded with
/// the new instance first) for performance reasons. For example:
///
/// ```cpp
/// #include <sourcemeta/blaze/evaluator.h>
/// #include <sourcemeta/blaze/compiler.h>
///
/// #include <sourcemeta/jsontoolkit/json.h>
/// #include <sourcemeta/jsontoolkit/jsonschema.h>
/// #include <cassert>
///
/// const sourcemeta::jsontoolkit::JSON schema =
///     sourcemeta::jsontoolkit::parse(R"JSON({
///   "$schema": "https://json-schema.org/draft/2020-12/schema",
///   "type": "string"
/// })JSON");
///
/// const auto schema_template{sourcemeta::blaze::compile(
///     schema, sourcemeta::jsontoolkit::default_schema_walker,
///     sourcemeta::jsontoolkit::official_resolver,
///     sourcemeta::jsontoolkit::default_schema_compiler)};
///
/// const sourcemeta::jsontoolkit::JSON instance{"foo bar"};
/// sourcemeta::blaze::EvaluationContext context;
/// const auto result{sourcemeta::blaze::evaluate(
///   schema_template, instance, context)};
/// assert(result);
/// ```
auto SOURCEMETA_BLAZE_EVALUATOR_EXPORT
evaluate(const Template &schema, const sourcemeta::jsontoolkit::JSON &instance,
         EvaluationContext &context) -> bool;

} // namespace sourcemeta::blaze

#endif
