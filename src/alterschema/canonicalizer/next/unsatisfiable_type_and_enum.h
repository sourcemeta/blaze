class UnsatisfiableTypeAndEnum final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::false_type;
  UnsatisfiableTypeAndEnum()
      : SchemaTransformRule{
            "unsatisfiable_type_and_enum",
            "When `type` and `enum` are both present and no enum value "
            "matches the declared type, the schema is unsatisfiable"} {};

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
    ONLY_CONTINUE_IF(std::ranges::none_of(
        schema.at("enum").as_array(),
        [&declared_types, integer_matches_real](const auto &value) {
          if (declared_types.test(std::to_underlying(value.type()))) {
            return true;
          }

          if (integer_matches_real && value.is_real() &&
              std::floor(value.to_real()) == value.to_real()) {
            return true;
          }

          if (integer_matches_real && value.is_decimal() &&
              value.to_decimal() == value.to_decimal().to_integral()) {
            return true;
          }

          return false;
        }));
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    schema.into(JSON{false});
  }
};
