class ExclusiveMaximumBooleanIntegerFold final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExclusiveMaximumBooleanIntegerFold()
      : SchemaTransformRule{
            "exclusive_maximum_boolean_integer_fold",
            "Setting boolean `exclusiveMaximum` when `type` is `integer` "
            "can be folded into an adjusted `maximum`"} {};

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
        schema.at("type").is_string() &&
        schema.at("type").to_string() == "integer" &&
        schema.defines("exclusiveMaximum") &&
        schema.at("exclusiveMaximum").is_boolean() &&
        schema.at("exclusiveMaximum").to_boolean() &&
        schema.defines("maximum") && schema.at("maximum").is_number());
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    const auto &maximum{schema.at("maximum")};
    if (maximum.is_integer()) {
      auto new_maximum = maximum;
      new_maximum += sourcemeta::core::JSON{-1};
      schema.assign("maximum", std::move(new_maximum));
    } else {
      const auto floored{
          static_cast<std::int64_t>(std::floor(maximum.to_real()))};
      schema.assign("maximum", sourcemeta::core::JSON{floored});
    }

    schema.erase("exclusiveMaximum");
  }
};
