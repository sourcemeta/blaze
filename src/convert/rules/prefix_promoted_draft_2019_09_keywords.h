class PrefixPromoted201909Keywords final : public SchemaTransformRule {
public:
  using reframe_after_transform = std::true_type;
  PrefixPromoted201909Keywords()
      : SchemaTransformRule{"prefix_promoted_2019_09_keywords"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    ONLY_CONTINUE_IF(
        vocabularies.contains(SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_7) &&
        schema.is_object());

    // Several of these keywords are also what the upgrade writes as it climbs,
    // so one sitting in a subschema that already declares the dialect that
    // promoted it is the keyword doing its job rather than author data that
    // still needs shadowing. Reading it as data shadows the upgrade's own
    // output, and the rule then never settles
    ONLY_CONTINUE_IF(dialect_position(declared_dialect(schema)) <
                     dialect_position(PROMOTING_DIALECT));

    for (const auto &keyword : KEYWORDS) {
      if (schema.defines(keyword)) {
        return true;
      }
    }

    return false;
  }

  auto transform(sourcemeta::core::JSON &schema) const -> void override {
    this->renames_.clear();
    for (const auto &keyword : KEYWORDS) {
      const std::string keyword_name{keyword};
      if (!schema.defines(keyword_name)) {
        continue;
      }

      std::string prefixed_name{"x-" + keyword_name};
      while (schema.defines(prefixed_name)) {
        prefixed_name.insert(0, "x-");
      }

      this->renames_.emplace(keyword_name, prefixed_name);
      schema.rename(keyword_name, std::move(prefixed_name));
    }
  }

  [[nodiscard]] auto rereference(const std::string_view,
                                 const sourcemeta::core::Pointer &,
                                 const sourcemeta::core::Pointer &target,
                                 const sourcemeta::core::Pointer &current) const
      -> std::optional<sourcemeta::core::Pointer> override {
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
  static constexpr std::string_view PROMOTING_DIALECT{
      "https://json-schema.org/draft/2019-09/schema"};

  // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
  static inline const std::array<std::string_view, 13> KEYWORDS{
      {"$anchor", "$recursiveAnchor", "$recursiveRef", "$vocabulary", "$defs",
       "dependentSchemas", "dependentRequired", "unevaluatedItems",
       "unevaluatedProperties", "maxContains", "minContains", "contentSchema",
       "deprecated"}};

  mutable std::unordered_map<std::string, std::string> renames_;
};
