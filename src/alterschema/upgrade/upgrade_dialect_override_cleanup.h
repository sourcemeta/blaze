class UpgradeDialectOverrideCleanup final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  UpgradeDialectOverrideCleanup(std::string target_dialect)
      : SchemaTransformRule{"upgrade_dialect_override_cleanup", ""},
        target_dialect_{std::move(target_dialect)} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(location.pointer.empty() && schema.is_object());

    const auto *override_value{
        schema.try_at(std::string{DIALECT_OVERRIDE_KEYWORD})};
    ONLY_CONTINUE_IF(override_value != nullptr &&
                     override_value->is_string() &&
                     override_value->to_string() == this->target_dialect_);

    return true;
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    if (!schema.defines("$schema")) {
      sourcemeta::core::JSON dialect_value{
          schema.at(std::string{DIALECT_OVERRIDE_KEYWORD}).to_string()};

      std::optional<std::string> anchor_key;
      for (const auto &entry : schema.as_object()) {
        if (entry.first != DIALECT_OVERRIDE_KEYWORD) {
          anchor_key = entry.first;
          break;
        }
      }

      if (anchor_key.has_value()) {
        schema.try_assign_before("$schema", dialect_value, anchor_key.value());
      } else {
        schema.assign("$schema", dialect_value);
      }
    }

    drop_dialect_overrides(schema, true);
  }

private:
  std::string target_dialect_;
};
