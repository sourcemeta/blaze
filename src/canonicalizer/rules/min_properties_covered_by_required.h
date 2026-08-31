class MinPropertiesCoveredByRequired final : public SchemaTransformRule {
public:
  using reframe_after_transform = std::false_type;
  MinPropertiesCoveredByRequired()
      : SchemaTransformRule{"min_properties_covered_by_required"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::blaze::SchemaVocabularies &vocabularies,
            const sourcemeta::blaze::SchemaFrame &,
            const sourcemeta::blaze::SchemaFrame::Location &,
            const sourcemeta::blaze::SchemaWalker &,
            const sourcemeta::blaze::SchemaResolver &) const -> bool override {
    ONLY_CONTINUE_IF(
        vocabularies.contains_any(
            {SchemaVocabularies::Known::JSON_Schema_2020_12_Validation,
             SchemaVocabularies::Known::JSON_Schema_2019_09_Validation,
             SchemaVocabularies::Known::JSON_Schema_Draft_7,
             SchemaVocabularies::Known::JSON_Schema_Draft_6,
             SchemaVocabularies::Known::JSON_Schema_Draft_4}) &&
        schema.is_object());

    const auto *min_properties{schema.try_at("minProperties")};
    ONLY_CONTINUE_IF(min_properties && min_properties->is_integer());
    const auto *required{schema.try_at("required")};
    ONLY_CONTINUE_IF(required && required->is_array());

    // Only string entries name a property, and only distinct ones raise the
    // lower bound, as a repeated name is satisfied by a single property
    std::unordered_set<sourcemeta::core::JSON::String> names;
    for (const auto &property : required->as_array()) {
      if (property.is_string()) {
        names.emplace(property.to_string());
      }
    }

    ONLY_CONTINUE_IF(std::cmp_greater(
        names.size(),
        static_cast<std::uint64_t>(min_properties->to_integer())));
    this->names_ = names.size();
    return true;
  }

  auto transform(sourcemeta::core::JSON &schema) const -> void override {
    schema.assign("minProperties", sourcemeta::core::JSON{this->names_});
  }

private:
  mutable std::size_t names_{0};
};
