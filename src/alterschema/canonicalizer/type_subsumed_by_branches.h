class TypeSubsumedByBranches final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  TypeSubsumedByBranches()
      : SchemaTransformRule{
            "type_subsumed_by_branches",
            "A `type` already guaranteed by every branch of a sibling `anyOf`, "
            "`oneOf`, or `if`/`then`/`else` is redundant and can be removed"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::blaze::Vocabularies &vocabularies,
            const sourcemeta::blaze::SchemaFrame &,
            const sourcemeta::blaze::SchemaFrame::Location &,
            const sourcemeta::blaze::SchemaWalker &walker,
            const sourcemeta::blaze::SchemaResolver &, const bool) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(
        (vocabularies.contains_any({Vocabularies::Known::JSON_Schema_Draft_7,
                                    Vocabularies::Known::JSON_Schema_Draft_6,
                                    Vocabularies::Known::JSON_Schema_Draft_4}) ||
         (vocabularies.contains(
              Vocabularies::Known::JSON_Schema_2019_09_Validation) &&
          vocabularies.contains(
              Vocabularies::Known::JSON_Schema_2019_09_Applicator)) ||
         (vocabularies.contains(
              Vocabularies::Known::JSON_Schema_2020_12_Validation) &&
          vocabularies.contains(
              Vocabularies::Known::JSON_Schema_2020_12_Applicator))) &&
        schema.is_object());

    const auto *type_value{schema.try_at("type")};
    ONLY_CONTINUE_IF(type_value && type_value->is_string());
    const auto &type_string{type_value->to_string()};

    bool subsumed{false};

    static const std::array<const char *, 2> UNIONS{{"anyOf", "oneOf"}};
    for (const auto *keyword : UNIONS) {
      const auto *branches{schema.try_at(keyword)};
      if (branches == nullptr || !branches->is_array() || branches->empty()) {
        continue;
      }

      bool all_branches_assert{true};
      for (const auto &branch : branches->as_array()) {
        if (!asserts_type(branch, type_string)) {
          all_branches_assert = false;
          break;
        }
      }

      if (all_branches_assert) {
        subsumed = true;
        break;
      }
    }

    // The `if` schema only selects which arm applies, so both arms must assert
    // the type for the conditional to guarantee it
    if (!subsumed && schema.defines("if")) {
      const auto *then_schema{schema.try_at("then")};
      const auto *else_schema{schema.try_at("else")};
      subsumed = then_schema != nullptr && else_schema != nullptr &&
                 asserts_type(*then_schema, type_string) &&
                 asserts_type(*else_schema, type_string);
    }

    ONLY_CONTINUE_IF(subsumed);

    // Only drop the type when the subsuming branches are the sole
    // instance-affecting sibling. Otherwise removing it would orphan another
    // assertion (such as `properties`) that relies on the type being present
    for (const auto &entry : schema.as_object()) {
      if (entry.first == "type" || entry.first == "anyOf" ||
          entry.first == "oneOf" || entry.first == "if" ||
          entry.first == "then" || entry.first == "else") {
        continue;
      }

      if (walker(entry.first, vocabularies).instances.any()) {
        return false;
      }
    }

    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    schema.erase("type");
  }

private:
  static auto asserts_type(const sourcemeta::core::JSON &schema,
                           const sourcemeta::core::JSON::String &type) -> bool {
    if (!schema.is_object()) {
      return false;
    }

    const auto *value{schema.try_at("type")};
    return value != nullptr && value->is_string() && value->to_string() == type;
  }
};
