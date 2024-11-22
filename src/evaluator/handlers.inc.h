HANDLER(AssertionDefines) {
  SOURCEMETA_MAYBE_UNUSED(depth);
  SOURCEMETA_MAYBE_UNUSED(context);
  SOURCEMETA_TRACE_REGISTER_ID(trace_id);
  EVALUATE_BEGIN(assertion, sourcemeta::blaze::AssertionDefines,
                 target.is_object());
  result = target.defines(assertion.value);
  EVALUATE_END(assertion, sourcemeta::blaze::AssertionDefines);
}
