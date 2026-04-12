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
        vocabularies.contains(Vocabularies::Known::JSON_Schema_Draft_4) &&
        schema.is_object() && schema.defines("type") &&
        schema.at("type").is_string() && schema.defines("enum") &&
        schema.at("enum").is_array() && !schema.at("enum").empty());

    const auto declared_types{parse_schema_type(schema.at("type"))};

    bool has_match{false};
    bool has_mismatch{false};
    for (const auto &value : schema.at("enum").as_array()) {
      if (declared_types.test(std::to_underlying(value.type()))) {
        has_match = true;
      } else {
        has_mismatch = true;
      }
    }

    // Only fire when there is a MIX: some match, some don't.
    // If all match, EnumWithType handles it.
    // If none match, UnsatisfiableTypeAndEnum handles it.
    ONLY_CONTINUE_IF(has_match && has_mismatch);
    return APPLIES_TO_KEYWORDS("enum", "type");
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    const auto declared_types{parse_schema_type(schema.at("type"))};
    auto filtered{JSON::make_array()};
    for (const auto &value : schema.at("enum").as_array()) {
      if (declared_types.test(std::to_underlying(value.type()))) {
        filtered.push_back(value);
      }
    }

    schema.assign("enum", std::move(filtered));
  }
};
