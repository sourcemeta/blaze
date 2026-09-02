class UnevaluatedPropertiesToAdditionalPropertiesSingleRef final
    : public SchemaTransformRule {
public:
  using reframe_after_transform = std::true_type;
  UnevaluatedPropertiesToAdditionalPropertiesSingleRef()
      : SchemaTransformRule{
            "unevaluated_properties_to_additional_properties_single_ref"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &root,
            const sourcemeta::blaze::SchemaVocabularies &vocabularies,
            const sourcemeta::blaze::SchemaFrame &frame,
            const sourcemeta::blaze::SchemaFrame::Location &location,
            const sourcemeta::blaze::SchemaWalker &walker,
            const sourcemeta::blaze::SchemaResolver &resolver) const
      -> bool override {
    ONLY_CONTINUE_IF(
        vocabularies.contains_any(
            {SchemaVocabularies::Known::JSON_Schema_2020_12_Unevaluated,
             SchemaVocabularies::Known::JSON_Schema_2019_09_Applicator}) &&
        schema.is_object() && schema.defines("unevaluatedProperties"));

    // We are going to write into `additionalProperties`, and a sibling
    // `unevaluatedItems` would keep depending on the annotations that the
    // `allOf` branch produces, which we would rather not reason about here
    ONLY_CONTINUE_IF(!schema.defines("additionalProperties") &&
                     !schema.defines("unevaluatedItems"));

    // The only in-place applicator we know how to statically account for is a
    // single `allOf` branch that consists of nothing but one `$ref`
    const auto *all_of{schema.try_at("allOf")};
    ONLY_CONTINUE_IF(all_of && all_of->is_array() && all_of->size() == 1);
    const auto &branch{all_of->at(0)};
    ONLY_CONTINUE_IF(branch.is_object() && branch.size() == 1);
    const auto *reference{branch.try_at("$ref")};
    ONLY_CONTINUE_IF(reference && reference->is_string());

    // Any other in-place applicator could contribute property annotations that
    // we cannot enumerate at compile time, and `properties` along with
    // `patternProperties` are the only other keywords that decide what counts
    // as evaluated at this level. Everything else is irrelevant to the rewrite
    for (const auto &entry : schema.as_object()) {
      if (entry.first == "unevaluatedProperties" || entry.first == "allOf" ||
          entry.first == "properties" || entry.first == "patternProperties") {
        continue;
      }
      const auto keyword_type{walker(entry.first, vocabularies).type};
      if (IS_IN_PLACE_APPLICATOR(keyword_type) ||
          keyword_type == sourcemeta::blaze::SchemaKeywordType::Reference) {
        return false;
      }
    }

    const auto *properties{schema.try_at("properties")};
    ONLY_CONTINUE_IF(!properties || properties->is_object());

    // Resolve the branch through the frame rather than through the raw
    // reference string, so that we honour whatever base the reference
    // was written against
    const sourcemeta::core::JSON::String *destination{nullptr};
    frame.for_each_reference_from(
        location.pointer,
        [&destination,
         &location](const sourcemeta::blaze::SchemaReferenceType type,
                    const sourcemeta::core::WeakPointer &source,
                    const sourcemeta::blaze::SchemaFrame::Reference &reference)
            -> void {
          if (destination ||
              type != sourcemeta::blaze::SchemaReferenceType::Static) {
            return;
          }
          const auto relative{source.resolve_from(location.pointer)};
          if (relative.size() == 3 && relative.at(0).is_property() &&
              relative.at(0).to_property() == "allOf" &&
              relative.at(1).is_index() && relative.at(1).to_index() == 0 &&
              relative.at(2).is_property() &&
              relative.at(2).to_property() == "$ref") {
            destination = &reference.destination;
          }
        });

    ONLY_CONTINUE_IF(destination);
    const auto target{frame.traverse(*destination)};
    ONLY_CONTINUE_IF(target.has_value());
    const auto &target_location{target.value().get()};
    const auto &target_schema{
        sourcemeta::core::get(root, target_location.pointer)};
    ONLY_CONTINUE_IF(target_schema.is_object());

    // The referenced schema must evaluate a property set that we can name
    // upfront, which means no further indirection of its own and no keyword
    // that evaluates properties it does not spell out one by one
    ONLY_CONTINUE_IF(!target_schema.defines("unevaluatedProperties") &&
                     !target_schema.defines("unevaluatedItems") &&
                     !target_schema.defines("additionalProperties"));
    const auto *target_pattern_properties{
        target_schema.try_at("patternProperties")};
    ONLY_CONTINUE_IF(!target_pattern_properties ||
                     (target_pattern_properties->is_object() &&
                      target_pattern_properties->empty()));

    // Older dialects grow an implicit `additionalProperties` during
    // canonicalisation, which would silently widen the property set we are
    // about to freeze, so we only reason about the modern ones
    const auto &target_vocabularies{
        frame.vocabularies(target_location, resolver)};
    ONLY_CONTINUE_IF(target_vocabularies.contains_any(
        {SchemaVocabularies::Known::JSON_Schema_2019_09_Applicator,
         SchemaVocabularies::Known::JSON_Schema_2020_12_Applicator}));

    for (const auto &entry : target_schema.as_object()) {
      const auto keyword_type{walker(entry.first, target_vocabularies).type};
      if (IS_IN_PLACE_APPLICATOR(keyword_type) ||
          keyword_type == sourcemeta::blaze::SchemaKeywordType::Reference) {
        return false;
      }
    }

    const auto *target_properties{target_schema.try_at("properties")};
    ONLY_CONTINUE_IF(!target_properties || target_properties->is_object());

    // A `required` entry that `properties` does not already spell out would
    // later get one of its own through `required_properties_in_properties`,
    // again widening the property set behind our back
    const auto *target_required{target_schema.try_at("required")};
    if (target_required && target_required->is_array()) {
      for (const auto &entry : target_required->as_array()) {
        if (entry.is_string() &&
            !(target_properties &&
              target_properties->defines(entry.to_string()))) {
          return false;
        }
      }
    }

    this->properties_.clear();
    if (target_properties) {
      for (const auto &entry : target_properties->as_object()) {
        if (properties && properties->defines(entry.first)) {
          continue;
        }
        this->properties_.emplace_back(entry.first);
      }
    }

    return true;
  }

  auto transform(sourcemeta::core::JSON &schema) const -> void override {
    if (!this->properties_.empty()) {
      schema.assign_if_missing("properties",
                               sourcemeta::core::JSON::make_object());
      for (const auto &property : this->properties_) {
        schema.at("properties").assign(property, sourcemeta::core::JSON{true});
      }
    }

    schema.rename("unevaluatedProperties", "additionalProperties");
  }

  [[nodiscard]] auto rereference(const std::string_view,
                                 const sourcemeta::core::Pointer &,
                                 const sourcemeta::core::Pointer &target,
                                 const sourcemeta::core::Pointer &current) const
      -> std::optional<sourcemeta::core::Pointer> override {
    return target.rebase(current.concat("unevaluatedProperties"),
                         current.concat("additionalProperties"));
  }

private:
  mutable std::vector<sourcemeta::core::JSON::String> properties_;
};
