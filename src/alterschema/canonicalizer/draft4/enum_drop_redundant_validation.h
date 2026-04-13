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

    this->locations_.clear();
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

      this->locations_.push_back(Pointer{entry.first});
    }

    ONLY_CONTINUE_IF(!this->locations_.empty());
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    for (const auto &location : this->locations_) {
      schema.erase(location.at(0).to_property());
    }
  }

private:
  // TODO: Use WeakPointer to avoid copies
  mutable std::vector<Pointer> locations_;
};
