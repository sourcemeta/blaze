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
            {Vocabularies::Known::JSON_Schema_Draft_4,
             Vocabularies::Known::JSON_Schema_Draft_6,
             Vocabularies::Known::JSON_Schema_Draft_7,
             Vocabularies::Known::JSON_Schema_2019_09_Applicator}) &&
        schema.is_object() && schema.defines("type") &&
        schema.at("type").is_string() &&
        schema.at("type").to_string() == "array");

    // In 2019-09+, the absence of `items` is semantically meaningful
    // because adding `items: true` marks all items as "evaluated",
    // which changes the behavior of `unevaluatedItems` at higher
    // levels
    const bool is_2019_09{vocabularies.contains(
        Vocabularies::Known::JSON_Schema_2019_09_Applicator)};
    const bool needs_items{!is_2019_09 && !schema.defines("items")};
    ONLY_CONTINUE_IF(!schema.defines("uniqueItems") || needs_items ||
                     !schema.defines("minItems"));

    this->add_items_ = needs_items;
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    if (!schema.defines("uniqueItems")) {
      schema.assign("uniqueItems", sourcemeta::core::JSON{false});
    }
    if (this->add_items_ && !schema.defines("items")) {
      schema.assign("items", sourcemeta::core::JSON{true});
    }
    if (!schema.defines("minItems")) {
      schema.assign("minItems", sourcemeta::core::JSON{0});
    }
  }

private:
  mutable bool add_items_{true};
};
