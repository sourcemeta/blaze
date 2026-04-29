class UpgradeDraft4ToDraft6 final : public SchemaTransformRule {
private:
  static inline const std::string DRAFT_4_URL{
      "http://json-schema.org/draft-04/schema#"};
  static inline const std::string DRAFT_6_URL{
      "http://json-schema.org/draft-06/schema#"};
  static inline const std::array<std::string_view, 4> PROMOTED_KEYWORDS{
      "const", "contains", "propertyNames", "examples"};

  static auto
  has_pending_draft_4_pattern(const sourcemeta::core::JSON &subschema) -> bool {
    if (!subschema.is_object()) {
      return false;
    }

    if (subschema.defines("$schema") && subschema.at("$schema").is_string() &&
        subschema.at("$schema").to_string() == DRAFT_4_URL) {
      return true;
    }

    if (subschema.defines("id") && subschema.at("id").is_string() &&
        !subschema.defines("$id")) {
      return true;
    }

    const auto *exclusive_minimum{subschema.try_at("exclusiveMinimum")};
    if (exclusive_minimum != nullptr && exclusive_minimum->is_boolean()) {
      return true;
    }

    const auto *exclusive_maximum{subschema.try_at("exclusiveMaximum")};
    if (exclusive_maximum != nullptr && exclusive_maximum->is_boolean()) {
      return true;
    }

    for (const auto &keyword : PROMOTED_KEYWORDS) {
      if (subschema.defines(std::string{keyword})) {
        return true;
      }
    }

    return false;
  }

  static auto
  is_strict_descendant(const sourcemeta::core::WeakPointer &ancestor,
                       const sourcemeta::core::WeakPointer &candidate) -> bool {
    if (candidate.size() <= ancestor.size()) {
      return false;
    }
    for (std::size_t index{0}; index < ancestor.size(); ++index) {
      if (!(ancestor.at(index) == candidate.at(index))) {
        return false;
      }
    }
    return true;
  }

public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  UpgradeDraft4ToDraft6()
      : SchemaTransformRule{"upgrade_draft_4_to_draft_6", ""} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &root,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(
        vocabularies.contains(Vocabularies::Known::JSON_Schema_Draft_4) &&
        schema.is_object());

    ONLY_CONTINUE_IF(has_pending_draft_4_pattern(schema));

    for (const auto &entry : frame.locations()) {
      if (entry.second.type !=
              sourcemeta::core::SchemaFrame::LocationType::Resource &&
          entry.second.type !=
              sourcemeta::core::SchemaFrame::LocationType::Subschema) {
        continue;
      }

      if (!is_strict_descendant(location.pointer, entry.second.pointer)) {
        continue;
      }

      const auto entry_pointer{
          sourcemeta::core::to_pointer(entry.second.pointer)};
      const auto &entry_schema{sourcemeta::core::get(root, entry_pointer)};

      if (entry_schema.is_object() && entry_schema.defines("$ref")) {
        continue;
      }

      if (has_pending_draft_4_pattern(entry_schema)) {
        return false;
      }
    }

    return true;
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    if (schema.defines("id") && schema.at("id").is_string() &&
        !schema.defines("$id")) {
      schema.rename("id", "$id");
    }

    if (schema.defines("exclusiveMinimum") &&
        schema.at("exclusiveMinimum").is_boolean()) {
      const bool exclusive{schema.at("exclusiveMinimum").to_boolean()};
      schema.erase("exclusiveMinimum");
      if (exclusive && schema.defines("minimum") &&
          schema.at("minimum").is_number()) {
        schema.rename("minimum", "exclusiveMinimum");
      }
    }

    if (schema.defines("exclusiveMaximum") &&
        schema.at("exclusiveMaximum").is_boolean()) {
      const bool exclusive{schema.at("exclusiveMaximum").to_boolean()};
      schema.erase("exclusiveMaximum");
      if (exclusive && schema.defines("maximum") &&
          schema.at("maximum").is_number()) {
        schema.rename("maximum", "exclusiveMaximum");
      }
    }

    if (schema.defines("$schema") && schema.at("$schema").is_string() &&
        schema.at("$schema").to_string() == DRAFT_4_URL) {
      schema.assign("$schema", sourcemeta::core::JSON{DRAFT_6_URL});
    }
  }
};
