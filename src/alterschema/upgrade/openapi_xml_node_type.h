class OpenAPIXmlNodeType final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  OpenAPIXmlNodeType() : SchemaTransformRule{"openapi_xml_node_type", ""} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::blaze::SchemaVocabularies &vocabularies,
            const sourcemeta::blaze::SchemaFrame &,
            const sourcemeta::blaze::SchemaFrame::Location &,
            const sourcemeta::blaze::SchemaWalker &,
            const sourcemeta::blaze::SchemaResolver &, const bool) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(vocabularies.contains_any(
                         {SchemaVocabularies::Known::OPENAPI_3_1_BASE,
                          SchemaVocabularies::Known::OPENAPI_3_2_BASE}) &&
                     schema.is_object() && schema.defines("xml"));

    const auto &xml{schema.at("xml")};
    ONLY_CONTINUE_IF(xml.is_object() && !xml.defines("nodeType") &&
                     is_boolean_or_absent(xml, "attribute") &&
                     is_boolean_or_absent(xml, "wrapped"));

    const auto attribute{legacy_flag(xml, "attribute")};
    const auto wrapped{legacy_flag(xml, "wrapped")};
    ONLY_CONTINUE_IF(!attribute.value_or(false) || !wrapped.value_or(false));

    return attribute.has_value() || wrapped.has_value() ||
           reference_needs_element_node(schema, xml);
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    auto &xml{schema.at("xml")};
    const auto attribute{legacy_flag(xml, "attribute")};
    const auto wrapped{legacy_flag(xml, "wrapped")};

    if (attribute.value_or(false)) {
      xml.rename("attribute", sourcemeta::core::JSON::String{"nodeType"});
      xml.at("nodeType").into(sourcemeta::core::JSON{ATTRIBUTE_NODE_TYPE});
      if (wrapped.has_value()) {
        xml.erase("wrapped");
      }

      return;
    }

    if (wrapped.value_or(false)) {
      xml.rename("wrapped", sourcemeta::core::JSON::String{"nodeType"});
      xml.at("nodeType").into(sourcemeta::core::JSON{ELEMENT_NODE_TYPE});
      if (attribute.has_value()) {
        xml.erase("attribute");
      }

      return;
    }

    if (attribute.has_value()) {
      xml.erase("attribute");
    }

    if (wrapped.has_value()) {
      xml.erase("wrapped");
    }

    if (reference_needs_element_node(schema, xml)) {
      xml.assign("nodeType", sourcemeta::core::JSON{ELEMENT_NODE_TYPE});
    }
  }

private:
  static constexpr std::string_view ATTRIBUTE_NODE_TYPE{"attribute"};
  static constexpr std::string_view ELEMENT_NODE_TYPE{"element"};

  static auto
  is_boolean_or_absent(const sourcemeta::core::JSON &xml,
                       const sourcemeta::core::JSON::StringView name) -> bool {
    const auto *value{xml.try_at(name)};
    return value == nullptr || value->is_boolean();
  }

  static auto legacy_flag(const sourcemeta::core::JSON &xml,
                          const sourcemeta::core::JSON::StringView name)
      -> std::optional<bool> {
    const auto *value{xml.try_at(name)};
    if (value == nullptr || !value->is_boolean()) {
      return std::nullopt;
    }

    return value->to_boolean();
  }

  static auto has_array_type(const sourcemeta::core::JSON &schema) -> bool {
    const auto *type{schema.try_at("type")};
    if (type == nullptr) {
      return false;
    }

    if (type->is_string()) {
      return type->to_string() == "array";
    }

    if (!type->is_array()) {
      return false;
    }

    for (const auto &entry : type->as_array()) {
      if (entry.is_string() && entry.to_string() == "array") {
        return true;
      }
    }

    return false;
  }

  // A schema that references another one used to describe an element node,
  // whereas OpenAPI v3.2 defaults it to no node at all, silently discarding
  // the naming information that the XML object carries
  static auto reference_needs_element_node(const sourcemeta::core::JSON &schema,
                                           const sourcemeta::core::JSON &xml)
      -> bool {
    return schema.defines_any({"$ref", "$dynamicRef"}) &&
           !has_array_type(schema) &&
           xml.defines_any({"name", "namespace", "prefix"});
  }
};
