class ImplicitObjectKeywords final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ImplicitObjectKeywords()
      : SchemaTransformRule{"implicit_object_keywords", ""} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(schema.is_object() && schema.defines("type") &&
                     schema.at("type").is_string() &&
                     schema.at("type").to_string() == "object");

    this->add_pattern_properties_ =
        !schema.defines("patternProperties") &&
        vocabularies.contains_any(
            {Vocabularies::Known::JSON_Schema_Draft_3,
             Vocabularies::Known::JSON_Schema_Draft_4,
             Vocabularies::Known::JSON_Schema_Draft_6,
             Vocabularies::Known::JSON_Schema_Draft_7,
             Vocabularies::Known::JSON_Schema_2019_09_Applicator,
             Vocabularies::Known::JSON_Schema_2020_12_Applicator});

    this->add_property_names_ =
        !schema.defines("propertyNames") &&
        vocabularies.contains_any(
            {Vocabularies::Known::JSON_Schema_Draft_6,
             Vocabularies::Known::JSON_Schema_Draft_7,
             Vocabularies::Known::JSON_Schema_2019_09_Applicator,
             Vocabularies::Known::JSON_Schema_2020_12_Applicator});

    this->add_min_properties_ =
        !schema.defines("minProperties") &&
        vocabularies.contains_any(
            {Vocabularies::Known::JSON_Schema_2020_12_Validation,
             Vocabularies::Known::JSON_Schema_2019_09_Validation,
             Vocabularies::Known::JSON_Schema_Draft_7,
             Vocabularies::Known::JSON_Schema_Draft_6,
             Vocabularies::Known::JSON_Schema_Draft_4});

    this->add_properties_ =
        !schema.defines("properties") &&
        ((vocabularies.contains(
              Vocabularies::Known::JSON_Schema_2020_12_Validation) &&
          vocabularies.contains(
              Vocabularies::Known::JSON_Schema_2020_12_Applicator)) ||
         (vocabularies.contains(
              Vocabularies::Known::JSON_Schema_2019_09_Validation) &&
          vocabularies.contains(
              Vocabularies::Known::JSON_Schema_2019_09_Applicator)) ||
         vocabularies.contains_any({Vocabularies::Known::JSON_Schema_Draft_7,
                                    Vocabularies::Known::JSON_Schema_Draft_6,
                                    Vocabularies::Known::JSON_Schema_Draft_4,
                                    Vocabularies::Known::JSON_Schema_Draft_3,
                                    Vocabularies::Known::JSON_Schema_Draft_2,
                                    Vocabularies::Known::JSON_Schema_Draft_1,
                                    Vocabularies::Known::JSON_Schema_Draft_0}));

    const bool is_legacy{
        vocabularies.contains_any({Vocabularies::Known::JSON_Schema_Draft_0,
                                   Vocabularies::Known::JSON_Schema_Draft_1,
                                   Vocabularies::Known::JSON_Schema_Draft_2,
                                   Vocabularies::Known::JSON_Schema_Draft_3,
                                   Vocabularies::Known::JSON_Schema_Draft_4,
                                   Vocabularies::Known::JSON_Schema_Draft_6,
                                   Vocabularies::Known::JSON_Schema_Draft_7})};

    this->add_additional_properties_ =
        is_legacy && !schema.defines("additionalProperties");
    this->additional_properties_as_object_ =
        vocabularies.contains_any({Vocabularies::Known::JSON_Schema_Draft_0,
                                   Vocabularies::Known::JSON_Schema_Draft_1,
                                   Vocabularies::Known::JSON_Schema_Draft_2,
                                   Vocabularies::Known::JSON_Schema_Draft_3});

    ONLY_CONTINUE_IF(this->add_pattern_properties_ ||
                     this->add_property_names_ || this->add_min_properties_ ||
                     this->add_properties_ || this->add_additional_properties_);
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    if (this->add_pattern_properties_) {
      schema.assign("patternProperties", sourcemeta::core::JSON::make_object());
    }

    if (this->add_property_names_) {
      schema.assign("propertyNames", sourcemeta::core::JSON{true});
    }

    if (this->add_min_properties_) {
      if (schema.defines("required") && schema.at("required").is_array()) {
        schema.assign("minProperties",
                      sourcemeta::core::JSON{schema.at("required").size()});
      } else {
        schema.assign("minProperties", sourcemeta::core::JSON{0});
      }
    }

    if (this->add_properties_) {
      schema.assign("properties", sourcemeta::core::JSON::make_object());
    }

    if (this->add_additional_properties_) {
      schema.assign("additionalProperties",
                    this->additional_properties_as_object_
                        ? sourcemeta::core::JSON::make_object()
                        : sourcemeta::core::JSON{true});
    }
  }

private:
  mutable bool add_pattern_properties_{false};
  mutable bool add_property_names_{false};
  mutable bool add_min_properties_{false};
  mutable bool add_properties_{false};
  mutable bool add_additional_properties_{false};
  mutable bool additional_properties_as_object_{false};
};
