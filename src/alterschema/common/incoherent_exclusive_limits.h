class IncoherentExclusiveLimits final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  IncoherentExclusiveLimits()
      : SchemaTransformRule{
            "incoherent_exclusive_limits",
            "`exclusiveMinimum` greater than or equal to "
            "`exclusiveMaximum` makes the schema unsatisfiable"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &, const Vocabularies &vocabularies,
            const SchemaFrame &, const SchemaFrame::Location &,
            const SchemaWalker &, const SchemaResolver &, const bool) const
      -> SchemaTransformRule::Result override {
    using Known = Vocabularies::Known;
    ONLY_CONTINUE_IF(schema.is_object());

    const bool is_2020_12 =
        vocabularies.contains(Known::JSON_Schema_2020_12_Validation) &&
        vocabularies.contains(Known::JSON_Schema_2020_12_Applicator);
    const bool is_2019_09 =
        vocabularies.contains(Known::JSON_Schema_2019_09_Validation) &&
        vocabularies.contains(Known::JSON_Schema_2019_09_Applicator);
    const bool is_draft7 = vocabularies.contains(Known::JSON_Schema_Draft_7);
    const bool is_draft6 = vocabularies.contains(Known::JSON_Schema_Draft_6);

    ONLY_CONTINUE_IF(is_2020_12 || is_2019_09 || is_draft7 || is_draft6);

    const auto *exclusive_minimum{schema.try_at("exclusiveMinimum")};
    ONLY_CONTINUE_IF(exclusive_minimum && exclusive_minimum->is_number());
    const auto *exclusive_maximum{schema.try_at("exclusiveMaximum")};
    ONLY_CONTINUE_IF(exclusive_maximum && exclusive_maximum->is_number() &&
                     *exclusive_minimum >= *exclusive_maximum);
    return APPLIES_TO_KEYWORDS("exclusiveMinimum", "exclusiveMaximum");
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    bool needs_not = true;
    if (schema.defines("type")) {
      const auto &type_node = schema.at("type");
      if (type_node.is_string()) {
        const auto &type_str{type_node.to_string()};
        if (type_str == "number" || type_str == "integer") {
          schema.assign("not", JSON{true});
          schema.erase("type");
          schema.erase("exclusiveMinimum");
          schema.erase("exclusiveMaximum");
          return;
        } else {
          needs_not = false;
        }
      } else if (type_node.is_array()) {
        auto remaining_types = JSON::make_array();
        for (const auto &element : type_node.as_array()) {
          if (element.is_string()) {
            const auto &element_str{element.to_string()};
            if (element_str != "number" && element_str != "integer") {
              remaining_types.push_back(element);
            }
          } else {
            remaining_types.push_back(element);
          }
        }
        if (remaining_types.empty()) {
          schema.assign("not", JSON{true});
          schema.erase("type");
          schema.erase("exclusiveMinimum");
          schema.erase("exclusiveMaximum");
          return;
        } else if (remaining_types.size() == 1) {
          schema.assign("type", remaining_types.front());
          needs_not = false;
        } else {
          schema.assign("type", std::move(remaining_types));
          needs_not = false;
        }
      }
    }

    if (needs_not) {
      auto inner = JSON::make_object();
      inner.assign("type", JSON{"number"});

      const std::string target_key = schema.defines("exclusiveMinimum")
                                         ? "exclusiveMinimum"
                                         : "exclusiveMaximum";

      if (!schema.defines("not") && !schema.defines("allOf")) {
        schema.try_assign_before("not", inner, target_key);
      } else {
        auto new_entry = JSON::make_object();
        new_entry.assign("not", std::move(inner));

        if (schema.defines("allOf") && schema.at("allOf").is_array()) {
          schema.at("allOf").push_back(std::move(new_entry));
        } else {
          auto all_of = JSON::make_array();
          if (schema.defines("not")) {
            auto existing_not = JSON::make_object();
            existing_not.assign("not", schema.at("not"));
            all_of.push_back(std::move(existing_not));
            all_of.push_back(std::move(new_entry));

            schema.try_assign_before("allOf", all_of, "not");
            schema.erase("not");
          } else {
            all_of.push_back(std::move(new_entry));
            schema.try_assign_before("allOf", all_of, target_key);
          }
        }
      }
    }

    schema.erase("exclusiveMinimum");
    schema.erase("exclusiveMaximum");
  }
};
