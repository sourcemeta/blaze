class EnumFilterByType final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  EnumFilterByType()
      : SchemaTransformRule{
            "enum_filter_by_type",
            "When `type` and `enum` coexist, enum values whose JSON type "
            "does not match the declared type can be removed"} {};

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
        vocabularies.contains_any({Vocabularies::Known::JSON_Schema_Draft_4,
                                   Vocabularies::Known::JSON_Schema_Draft_6}) &&
        schema.is_object() && schema.defines("type") &&
        schema.at("type").is_string() && schema.defines("enum") &&
        schema.at("enum").is_array() && !schema.at("enum").empty());

    const auto declared_types{parse_schema_type(schema.at("type"))};
    const bool integer_matches_real{
        vocabularies.contains(Vocabularies::Known::JSON_Schema_Draft_6) &&
        declared_types.test(std::to_underlying(JSON::Type::Integer))};

    this->matching_indices_.clear();
    bool has_mismatch{false};
    std::size_t index{0};
    for (const auto &value : schema.at("enum").as_array()) {
      bool matches{declared_types.test(std::to_underlying(value.type()))};
      if (!matches && integer_matches_real) {
        if (value.is_real() && std::floor(value.to_real()) == value.to_real()) {
          matches = true;
        } else if (value.is_decimal() &&
                   value.to_decimal() == value.to_decimal().to_integral()) {
          matches = true;
        }
      }

      if (matches) {
        this->matching_indices_.push_back(index);
      } else {
        has_mismatch = true;
      }
      index++;
    }

    ONLY_CONTINUE_IF(!this->matching_indices_.empty() && has_mismatch);
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    auto filtered{JSON::make_array()};
    for (const auto &index : this->matching_indices_) {
      filtered.push_back(schema.at("enum").at(index));
    }

    schema.assign("enum", std::move(filtered));
  }

private:
  mutable std::vector<std::size_t> matching_indices_;
};
