class OpenAPIExampleToExamples final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  OpenAPIExampleToExamples()
      : SchemaTransformRule{"openapi_example_to_examples", ""} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::blaze::SchemaVocabularies &vocabularies,
            const sourcemeta::blaze::SchemaFrame &,
            const sourcemeta::blaze::SchemaFrame::Location &,
            const sourcemeta::blaze::SchemaWalker &,
            const sourcemeta::blaze::SchemaResolver &, const bool) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(vocabularies.contains_any(
                         {SchemaVocabularies::Known::OPENAPI_3_1_BASE,
                          SchemaVocabularies::Known::OPENAPI_3_2_BASE}) &&
                     schema.is_object() && schema.defines("example"));

    const auto *examples{schema.try_at("examples")};
    return examples == nullptr || examples->is_array();
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    if (schema.defines("examples")) {
      schema.at("examples").push_back(std::move(schema.at("example")));
      schema.erase("example");
      return;
    }

    schema.rename("example", "examples");
    auto examples{sourcemeta::core::JSON::make_array()};
    examples.push_back(std::move(schema.at("examples")));
    schema.at("examples").into(std::move(examples));
  }
};
