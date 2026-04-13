class ExclusiveMinimumBooleanIntegerFold final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExclusiveMinimumBooleanIntegerFold()
      : SchemaTransformRule{
            "exclusive_minimum_boolean_integer_fold",
            "Setting boolean `exclusiveMinimum` when `type` is `integer` "
            "can be folded into an adjusted `minimum`"} {};

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
        schema.defines("exclusiveMinimum") &&
        schema.at("exclusiveMinimum").is_boolean() &&
        schema.at("exclusiveMinimum").to_boolean() &&
        schema.defines("minimum") && schema.at("minimum").is_number());
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    const auto &minimum{schema.at("minimum")};
    if (minimum.is_integer()) {
      auto new_minimum = minimum;
      new_minimum += sourcemeta::core::JSON{1};
      schema.assign("minimum", std::move(new_minimum));
    } else {
      const auto ceiled{
          static_cast<std::int64_t>(std::ceil(minimum.to_real()))};
      schema.assign("minimum", sourcemeta::core::JSON{ceiled});
    }

    schema.erase("exclusiveMinimum");
  }
};
