class ImplicitContainsKeywords final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ImplicitContainsKeywords()
      : SchemaTransformRule{"implicit_contains_keywords", ""} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &root,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &walker,
            const sourcemeta::core::SchemaResolver &resolver) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(
        vocabularies.contains_any(
            {Vocabularies::Known::JSON_Schema_2019_09_Applicator,
             Vocabularies::Known::JSON_Schema_2020_12_Applicator}) &&
        schema.is_object() && schema.defines("type") &&
        schema.at("type").is_string() &&
        schema.at("type").to_string() == "array");

    if (schema.defines("contains")) {
      // `contains` is present, just fill in the default `minContains`
      ONLY_CONTINUE_IF(!schema.defines("minContains"));
    } else {
      // Only synthesize `contains` when no contains-related keywords
      // exist. If `minContains`/`maxContains` are present without
      // `contains`, they are no-ops per the spec and should be stripped
      // by other rules first
      ONLY_CONTINUE_IF(!schema.defines("minContains") &&
                       !schema.defines("maxContains"));

      // In 2020-12, `contains` annotations affect `unevaluatedItems`,
      // so adding implicit `contains: true` with `minContains: 0`
      // would change semantics when `unevaluatedItems` is at an ancestor.
      // This does NOT apply to 2019-09 where `contains` does not
      // produce annotations that affect `unevaluatedItems`
      ONLY_CONTINUE_IF(!WALK_UP_IN_PLACE_APPLICATORS(
                            root, frame, location, walker, resolver,
                            [](const JSON &ancestor,
                               const Vocabularies &ancestor_vocabularies) {
                              return ancestor.defines("unevaluatedItems") &&
                                     ancestor_vocabularies.contains(
                                         Vocabularies::Known::
                                             JSON_Schema_2020_12_Unevaluated);
                            })
                            .has_value());
    }

    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    if (!schema.defines("contains")) {
      schema.assign("contains", sourcemeta::core::JSON{true});
      schema.assign("minContains", sourcemeta::core::JSON{0});
    } else {
      schema.assign("minContains", sourcemeta::core::JSON{1});
    }
  }
};
