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
    } else if (minimum.is_decimal()) {
      auto current{minimum.to_decimal()};
      auto ceiled{current.to_integral()};
      if (ceiled < current) {
        ceiled += sourcemeta::core::Decimal{1};
      }

      if (current.is_integer()) {
        ceiled += sourcemeta::core::Decimal{1};
      }

      if (ceiled.is_int64()) {
        schema.assign("minimum", sourcemeta::core::JSON{ceiled.to_int64()});
      } else {
        schema.assign("minimum", sourcemeta::core::JSON{std::move(ceiled)});
      }
    } else {
      const auto value{minimum.to_real()};
      auto ceiled{static_cast<std::int64_t>(std::ceil(value))};
      if (std::ceil(value) == value) {
        ceiled += 1;
      }

      schema.assign("minimum", sourcemeta::core::JSON{ceiled});
    }

    schema.erase("exclusiveMinimum");
  }
};
