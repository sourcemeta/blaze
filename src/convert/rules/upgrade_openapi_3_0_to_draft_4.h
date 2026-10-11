class UpgradeOpenAPI30ToDraft4 final : public SchemaTransformRule {
public:
  UpgradeOpenAPI30ToDraft4(const ConvertTarget target)
      : SchemaTransformRule{"upgrade_openapi_3_0_to_draft_4"},
        keeps_read_only_{target >= ConvertTarget::Draft7},
        keeps_deprecated_{target >= ConvertTarget::Draft201909} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const Site &site, const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    ONLY_CONTINUE_IF(
        vocabularies.contains(SchemaVocabularies::Known::OPENAPI_3_0_BASE) &&
        schema.is_object());

    return this->has_pending_openapi_3_0_pattern(schema) ||
           schema.defines(DEFINITIONS) || at_dialect_declaration(schema, site);
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
      if (!schema.defines(keyword_name) || this->carries_as_keyword(keyword)) {
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
  // rather than asserts, so shadowing one changes no verdict, and Draft 4 reads
  // an `x-` member as the unknown keyword it is. Three of them are shadowed
  // only where the target cannot express them, which `carries_as_keyword`
  // settles
  // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
  static inline const std::array<std::string_view, 8> KEYWORDS{
      {"nullable", "discriminator", "xml", "externalDocs", "example",
       "deprecated", "readOnly", "writeOnly"}};

  // Whether this subschema still carries something of the dialect that the
  // transform will act on. Each of those is either consumed or shadowed, so the
  // answer turns false once it has run and the conversion stops finding work
  // here. One carried across as itself is not work, or the answer would never
  // turn false
  [[nodiscard]] auto
  has_pending_openapi_3_0_pattern(const sourcemeta::core::JSON &subschema) const
      -> bool {
    for (const auto &keyword : KEYWORDS) {
      if (subschema.defines(sourcemeta::core::JSON::String{keyword}) &&
          !this->carries_as_keyword(keyword)) {
        return true;
      }
    }

    return false;
  }

  // Three of these became keywords of a later draft with the meaning OpenAPI
  // 3.0 already gave them, so a target defining one takes it as it stands
  // rather than as the author data the shadowing would make of it. `readOnly`
  // and `writeOnly` are native from Draft 7 and `deprecated` from 2019-09.
  //
  // This is the one place in the module where a rule reads the target the
  // caller finally asked for rather than the rung in front of it. It has to:
  // Draft 4 cannot express any of the three, so what the waypoint should carry
  // is only answerable from where the document is going. The cost is that
  // converting by way of Draft 4 no longer reproduces the direct result for
  // these three, which `convertsuite` records per fixture
  [[nodiscard]] auto carries_as_keyword(const std::string_view keyword) const
      -> bool {
    if (keyword == "readOnly" || keyword == "writeOnly") {
      return this->keeps_read_only_;
    }

    return keyword == "deprecated" && this->keeps_deprecated_;
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

  const bool keeps_read_only_;
  const bool keeps_deprecated_;
  mutable std::unordered_map<std::string, std::string> renames_;
  mutable std::vector<Relocation> relocations_;
};
