class EnumDropRedundantValidation final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  EnumDropRedundantValidation()
      : SchemaTransformRule{
            "enum_drop_redundant_validation",
            "Validation keywords alongside `enum` are redundant because "
            "the enumeration already fully constrains the allowed values"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &walker,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(
        vocabularies.contains(Vocabularies::Known::JSON_Schema_Draft_4) &&
        schema.is_object() && schema.defines("enum") &&
        schema.at("enum").is_array() && !schema.defines("type"));

    std::vector<Pointer> locations;
    for (const auto &entry : schema.as_object()) {
      if (entry.first == "enum") {
        continue;
      }

      const auto &metadata{walker(entry.first, vocabularies)};
      if (metadata.type != sourcemeta::core::SchemaKeywordType::Assertion) {
        continue;
      }

      if (frame.has_references_through(
              location.pointer, WeakPointer::Token{std::cref(entry.first)})) {
        continue;
      }

      locations.push_back(Pointer{entry.first});
    }

    ONLY_CONTINUE_IF(!locations.empty());
    return APPLIES_TO_POINTERS(std::move(locations));
  }

  auto transform(JSON &schema, const Result &result) const -> void override {
    for (const auto &location : result.locations) {
      schema.erase(location.at(0).to_property());
    }
  }
};
