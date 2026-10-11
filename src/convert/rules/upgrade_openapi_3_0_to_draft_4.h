class UpgradeOpenAPI30ToDraft4 final : public SchemaTransformRule {
public:
  UpgradeOpenAPI30ToDraft4()
      : SchemaTransformRule{"upgrade_openapi_3_0_to_draft_4"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const Site &site, const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    ONLY_CONTINUE_IF(
        vocabularies.contains(SchemaVocabularies::Known::OPENAPI_3_0_BASE) &&
        schema.is_object());

    return has_pending_openapi_3_0_pattern(schema) ||
           schema.defines(DEFINITIONS) ||
           at_dialect_declaration(schema, site);
  }

  auto transform(sourcemeta::core::JSON &schema, const Site &site) const
      -> void override {
    this->renames_.clear();
    this->relocations_.clear();

    // Before the shadowing below, so that a `nullable` this consumes is gone
    // by the time the annotations are renamed and one it declines is still
    // there to be renamed with them
    fold_nullable_into_type(schema);

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

    move_definitions(schema, this->relocations_);

    bump_dialect(schema, site, DRAFT_4_URL);
  }

  [[nodiscard]] auto relocations() const -> std::vector<Relocation> override {
    std::vector<Relocation> result{this->relocations_};
    result.reserve(result.size() + this->renames_.size());
    for (const auto &[old_name, new_name] : this->renames_) {
      result.emplace_back(sourcemeta::core::Pointer{old_name},
                          sourcemeta::core::Pointer{new_name});
    }

    return result;
  }

private:
  // The only member the dialect reads subschemas under, which is how a
  // document on it keeps anything reusable at all
  // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
  static inline const std::string DEFINITIONS{"x-definitions"};

  // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
  static inline const std::string DRAFT_4_URL{
      "http://json-schema.org/draft-04/schema#"};

  // What the OpenAPI 3.0 Schema Object adds that Draft 4 has no word for, less
  // the `nullable` the rewrite above consumes. Every one of these annotates
  // rather than asserts, so shadowing them changes no verdict, and Draft 4
  // reads an `x-` member as the unknown keyword it is.
  //
  // `readOnly` and `writeOnly` are native from Draft 7 and `deprecated` from
  // 2019-09, so a caller asking for one of those targets gets `x-readOnly`
  // where the keyword itself would have served. Repairing that would mean this
  // edge reasoning about the target the caller finally asked for rather than
  // the rung in front of it, which no other rule in this module does
  // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
  static inline const std::array<std::string_view, 8> KEYWORDS{
      {"nullable", "discriminator", "xml", "externalDocs", "example",
       "deprecated", "readOnly", "writeOnly"}};

  // Whether this subschema still carries something of the dialect. Each of
  // these is either consumed or shadowed by the transform, so the answer turns
  // false once it has run and the conversion stops finding work here
  static auto
  has_pending_openapi_3_0_pattern(const sourcemeta::core::JSON &subschema)
      -> bool {
    return std::ranges::any_of(
        KEYWORDS, [&subschema](const auto &keyword) -> bool {
          return subschema.defines(sourcemeta::core::JSON::String{keyword});
        });
  }

  // Draft 4 keeps under `definitions` what the OpenAPI 3.0 Schema Object keeps
  // here, and reads nothing of a schema under a member it does not know, so
  // every entry moves and the references reaching one follow it
  static auto move_definitions(sourcemeta::core::JSON &schema,
                               std::vector<Relocation> &relocations) -> void {
    if (!schema.defines(DEFINITIONS) || !schema.at(DEFINITIONS).is_object()) {
      return;
    }

    auto moved{sourcemeta::core::JSON::make_object()};
    for (const auto &entry : schema.at(DEFINITIONS).as_object()) {
      relocations.emplace_back(
          sourcemeta::core::Pointer{DEFINITIONS, entry.first},
          sourcemeta::core::Pointer{"definitions", entry.first});
      moved.assign(entry.first, entry.second);
    }

    schema.erase(DEFINITIONS);
    schema.assign("definitions", std::move(moved));
  }

  mutable std::unordered_map<std::string, std::string> renames_;
  mutable std::vector<Relocation> relocations_;
};
