class ImplicitArrayKeywords final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ImplicitArrayKeywords()
      : SchemaTransformRule{"implicit_array_keywords", ""} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(
        vocabularies.contains_any(
            {Vocabularies::Known::JSON_Schema_Draft_0,
             Vocabularies::Known::JSON_Schema_Draft_1,
             Vocabularies::Known::JSON_Schema_Draft_2,
             Vocabularies::Known::JSON_Schema_Draft_3,
             Vocabularies::Known::JSON_Schema_Draft_4,
             Vocabularies::Known::JSON_Schema_Draft_6,
             Vocabularies::Known::JSON_Schema_Draft_7,
             Vocabularies::Known::JSON_Schema_2019_09_Applicator,
             Vocabularies::Known::JSON_Schema_2020_12_Applicator}) &&
        schema.is_object() && schema.defines("type") &&
        schema.at("type").is_string() &&
        schema.at("type").to_string() == "array");

    const bool is_modern{vocabularies.contains_any(
        {Vocabularies::Known::JSON_Schema_2019_09_Applicator,
         Vocabularies::Known::JSON_Schema_2020_12_Applicator})};
    this->is_pre_draft4_ =
        vocabularies.contains_any({Vocabularies::Known::JSON_Schema_Draft_0,
                                   Vocabularies::Known::JSON_Schema_Draft_1,
                                   Vocabularies::Known::JSON_Schema_Draft_2,
                                   Vocabularies::Known::JSON_Schema_Draft_3});
    this->has_unique_items_ =
        !vocabularies.contains_any({Vocabularies::Known::JSON_Schema_Draft_0,
                                    Vocabularies::Known::JSON_Schema_Draft_1});
    const bool needs_items{!is_modern && !schema.defines("items")};
    ONLY_CONTINUE_IF(
        (this->has_unique_items_ && !schema.defines("uniqueItems")) ||
        needs_items || !schema.defines("minItems"));

    this->add_items_ = needs_items;
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    if (this->has_unique_items_ && !schema.defines("uniqueItems")) {
      schema.assign("uniqueItems", sourcemeta::core::JSON{false});
    }
    if (this->add_items_ && !schema.defines("items")) {
      schema.assign("items", this->is_pre_draft4_
                                 ? sourcemeta::core::JSON::make_object()
                                 : sourcemeta::core::JSON{true});
    }
    if (!schema.defines("minItems")) {
      schema.assign("minItems", sourcemeta::core::JSON{0});
    }
  }

private:
  mutable bool add_items_{true};
  mutable bool is_pre_draft4_{false};
  mutable bool has_unique_items_{true};
};
