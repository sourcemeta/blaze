class UpgradeDraft7To201909 final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  UpgradeDraft7To201909()
      : SchemaTransformRule{"upgrade_draft_7_to_2019_09", ""} {};

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
        vocabularies.contains(Vocabularies::Known::JSON_Schema_Draft_7) &&
        schema.is_object());

    ONLY_CONTINUE_IF(has_pending_pattern(schema));

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

      if (has_descendant_pending_pattern(entry_schema, entry.second.dialect)) {
        return false;
      }
    }

    return true;
  }

  auto transform(sourcemeta::core::JSON &schema, const Result &) const
      -> void override {
    this->renames_.clear();

    if (schema.defines("$ref")) {
      std::vector<std::string> siblings_to_prefix;
      for (const auto &entry : schema.as_object()) {
        if (entry.first == "$ref" || is_annotation(entry.first) ||
            entry.first.starts_with("x-")) {
          continue;
        }

        siblings_to_prefix.push_back(entry.first);
      }

      for (const auto &keyword : siblings_to_prefix) {
        std::string prefixed_name{"x-" + keyword};
        while (schema.defines(prefixed_name)) {
          prefixed_name.insert(0, "x-");
        }

        this->renames_.emplace(keyword, prefixed_name);
        schema.rename(keyword, std::move(prefixed_name));
      }
    }

    if (schema.defines("$id") && schema.at("$id").is_string()) {
      const auto &id_value{schema.at("$id").to_string()};
      const sourcemeta::core::URI uri{id_value};
      const auto fragment{uri.fragment()};

      if (fragment.has_value()) {
        const auto &fragment_value{fragment.value()};
        if (uri.is_fragment_only()) {
          if (is_plain_name_fragment(fragment_value)) {
            schema.erase("$id");
            schema.assign("$anchor",
                          sourcemeta::core::JSON{std::string{fragment_value}});
          }
        } else if (is_plain_name_fragment(fragment_value)) {
          const auto without_fragment{uri.recompose_without_fragment()};
          assert(without_fragment.has_value());
          schema.assign("$id",
                        sourcemeta::core::JSON{without_fragment.value()});
          schema.assign("$anchor",
                        sourcemeta::core::JSON{std::string{fragment_value}});
        } else if (fragment_value.empty()) {
          const auto without_fragment{uri.recompose_without_fragment()};
          assert(without_fragment.has_value());
          schema.assign("$id",
                        sourcemeta::core::JSON{without_fragment.value()});
        }
      }
    }

    if (schema.defines("dependencies") &&
        schema.at("dependencies").is_object()) {
      auto dependent_required{sourcemeta::core::JSON::make_object()};
      auto dependent_schemas{sourcemeta::core::JSON::make_object()};

      for (const auto &entry : schema.at("dependencies").as_object()) {
        if (entry.second.is_array()) {
          dependent_required.assign(entry.first, entry.second);
        } else if (entry.second.is_object() || entry.second.is_boolean()) {
          dependent_schemas.assign(entry.first, entry.second);
        }
      }

      schema.erase("dependencies");

      if (!dependent_required.empty()) {
        schema.assign("dependentRequired", std::move(dependent_required));
      }

      if (!dependent_schemas.empty()) {
        schema.assign("dependentSchemas", std::move(dependent_schemas));
      }
    }

    if (schema.defines("$schema") && schema.at("$schema").is_string() &&
        schema.at("$schema").to_string() == DRAFT_7_URL) {
      schema.assign("$schema", sourcemeta::core::JSON{DRAFT_2019_09_URL});
    }
  }

  [[nodiscard]] auto rereference(const std::string_view,
                                 const sourcemeta::core::Pointer &,
                                 const sourcemeta::core::Pointer &target,
                                 const sourcemeta::core::Pointer &current) const
      -> sourcemeta::core::Pointer override {
    for (const auto &[old_name, new_name] : this->renames_) {
      const auto result{
          target.rebase(current.concat(sourcemeta::core::Pointer{old_name}),
                        current.concat(sourcemeta::core::Pointer{new_name}))};
      if (result != target) {
        return result;
      }
    }

    return target;
  }

private:
  static inline const std::string DRAFT_4_URL{
      "http://json-schema.org/draft-04/schema#"};
  static inline const std::string DRAFT_6_URL{
      "http://json-schema.org/draft-06/schema#"};
  static inline const std::string DRAFT_7_URL{
      "http://json-schema.org/draft-07/schema#"};
  static inline const std::string DRAFT_2019_09_URL{
      "https://json-schema.org/draft/2019-09/schema"};

  static inline const std::array<std::string_view, 5> ANNOTATION_KEYWORDS{
      {"title", "description", "default", "examples", "$comment"}};

  static inline const std::array<std::string_view, 13>
      PROMOTED_2019_09_KEYWORDS{{"$anchor", "$recursiveAnchor", "$recursiveRef",
                                 "$vocabulary", "$defs", "dependentSchemas",
                                 "dependentRequired", "unevaluatedItems",
                                 "unevaluatedProperties", "maxContains",
                                 "minContains", "contentSchema", "deprecated"}};

  static inline const std::array<std::string_view, 8> PROMOTED_DRAFT_7_KEYWORDS{
      {"$comment", "if", "then", "else", "readOnly", "writeOnly",
       "contentMediaType", "contentEncoding"}};

  static inline const std::array<std::string_view, 4> PROMOTED_DRAFT_6_KEYWORDS{
      {"const", "contains", "propertyNames", "examples"}};

  mutable std::unordered_map<std::string, std::string> renames_;

  static auto is_annotation(const std::string_view keyword) -> bool {
    return std::ranges::any_of(
        ANNOTATION_KEYWORDS,
        [&keyword](const auto &candidate) { return candidate == keyword; });
  }

  static auto is_plain_name_fragment(const std::string_view fragment) -> bool {
    if (fragment.empty()) {
      return false;
    }

    for (const auto character : fragment) {
      const bool is_alpha{(character >= 'A' && character <= 'Z') ||
                          (character >= 'a' && character <= 'z')};
      const bool is_digit{character >= '0' && character <= '9'};
      const bool is_punct{character == '_' || character == ':' ||
                          character == '.' || character == '-'};
      if (!is_alpha && !is_digit && !is_punct) {
        return false;
      }
    }

    return true;
  }

  static auto has_pending_pattern(const sourcemeta::core::JSON &subschema)
      -> bool {
    if (!subschema.is_object()) {
      return false;
    }

    if (subschema.defines("$schema") && subschema.at("$schema").is_string() &&
        subschema.at("$schema").to_string() == DRAFT_7_URL) {
      return true;
    }

    if (subschema.defines("dependencies")) {
      return true;
    }

    if (subschema.defines("$id") && subschema.at("$id").is_string()) {
      const sourcemeta::core::URI uri{subschema.at("$id").to_string()};
      const auto fragment{uri.fragment()};
      if (fragment.has_value()) {
        return true;
      }
    }

    if (subschema.defines("$ref")) {
      for (const auto &entry : subschema.as_object()) {
        if (entry.first == "$ref" || is_annotation(entry.first) ||
            entry.first.starts_with("x-")) {
          continue;
        }
        return true;
      }
    }

    return false;
  }

  static auto
  has_descendant_pending_pattern(const sourcemeta::core::JSON &subschema,
                                 const std::string_view descendant_dialect)
      -> bool {
    if (!subschema.is_object()) {
      return false;
    }

    if (subschema.defines("$schema") && subschema.at("$schema").is_string()) {
      const auto &dialect{subschema.at("$schema").to_string()};
      if (dialect == DRAFT_4_URL || dialect == DRAFT_6_URL ||
          dialect == DRAFT_7_URL) {
        return true;
      }
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

    if (descendant_dialect == DRAFT_4_URL) {
      for (const auto &keyword : PROMOTED_DRAFT_6_KEYWORDS) {
        if (subschema.defines(std::string{keyword})) {
          return true;
        }
      }
    }

    if (descendant_dialect == DRAFT_6_URL) {
      for (const auto &keyword : PROMOTED_DRAFT_7_KEYWORDS) {
        if (subschema.defines(std::string{keyword})) {
          return true;
        }
      }
    }

    if (descendant_dialect == DRAFT_7_URL) {
      for (const auto &keyword : PROMOTED_2019_09_KEYWORDS) {
        if (subschema.defines(std::string{keyword})) {
          return true;
        }
      }
    }

    if (has_pending_pattern(subschema)) {
      return true;
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
};
