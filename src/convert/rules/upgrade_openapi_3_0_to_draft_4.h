class UpgradeOpenAPI30ToDraft4 final : public SchemaTransformRule {
public:
  UpgradeOpenAPI30ToDraft4(const ConvertTarget target)
      : SchemaTransformRule{"upgrade_openapi_3_0_to_draft_4"},
        keeps_read_only_{target >= ConvertTarget::Draft7},
        keeps_deprecated_{target >= ConvertTarget::Draft201909},
        keeps_openapi_annotations_{target >= ConvertTarget::OpenAPI31} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const Site &site, const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    ONLY_CONTINUE_IF(
        vocabularies.contains(SchemaVocabularies::Known::OPENAPI_3_0_BASE) &&
        schema.is_object());

    return holds_ignored_sibling(schema) ||
           this->has_pending_openapi_3_0_pattern(schema) ||
           holds_promoted_keyword(schema) ||
           holds_movable_definitions(schema) || holds_pending_shape(schema) ||
           at_dialect_declaration(schema, site);
  }

  auto transform(sourcemeta::core::JSON &schema, const Site &site) const
      -> void override {
    this->renames_.clear();
    this->relocations_.clear();

    // OpenAPI 3.0 section 4.7.23: a Reference Object cannot be extended with
    // additional properties, and any property added to one SHALL be ignored. An
    // object carrying `$ref` can only be a Reference Object, because the Schema
    // Object closes itself to additional properties and does not name `$ref`,
    // so every member beside it was ignored and has to go on being ignored.
    //
    // Carrying one across as the keyword a target names does two wrong things
    // at once: it reads a constraint the source never applied, and it hands the
    // target's own meta-schema a value to type-check that nothing ever checked.
    // So none of the rewriting below applies to a Reference Object, and its
    // members go across as the author data they already were
    if (schema.defines("$ref")) {
      for (const auto &name : member_names(schema)) {
        if (name == "$ref" || name == "$schema" || name.starts_with("x-")) {
          continue;
        }

        this->shadow(schema, name);
      }
    } else {
      // Before the shadowing below, so that a `nullable` this consumes is gone
      // by the time the annotations are renamed and one it declines is still
      // there to be renamed with them
      fold_nullable_into_type(schema);

      // Two shapes the OpenAPI 3.0 Schema Object permits that Draft 4 does not,
      // which are the only two its dialect states more loosely than Draft 4's
      // own meta-schema does
      deduplicate_enum(schema);
      fold_empty_applicators(schema);
      drop_unaccompanied_exclusive_bounds(schema);

      for (const auto &keyword : KEYWORDS) {
        if (!schema.defines(sourcemeta::core::JSON::String{keyword}) ||
            this->carries_as_keyword(schema, keyword)) {
          continue;
        }

        this->shadow(schema, keyword);
      }

      // Taken out before the shadowing below, so that what moves is the map the
      // author wrote under this name and not a `definitions` that the shadowing
      // has since put there. Doing it the other way round hands the shadowed
      // member straight back to the move, which promotes the author's data to
      // the keyword the shadowing was there to protect it from
      auto definitions{take_definitions(schema, this->relocations_)};

      for (const auto &keyword : PROMOTED_BY_DRAFT_4) {
        this->shadow(schema, keyword);
      }

      if (!definitions.empty()) {
        schema.assign("definitions", std::move(definitions));
      }
    }

    // Core reads this marker as the dialect of the position carrying it, ahead
    // of any `$schema` beside it, so one naming OpenAPI 3.0 has to go as the
    // document stops being written in it. Left behind, it would keep framing an
    // output that now declares Draft 4 as the dialect it has just left, which
    // reads a `type` array and a `$schema` as keywords it prohibits.
    //
    // `DialectOverrideBecomesDollarSchema` settles a marker naming a rung by
    // writing the `$schema` it stands for, and cannot do that here: the
    // OpenAPI 3.0 Schema Object defines no keyword to declare its own dialect
    // with, so there is no `$schema` to settle it into. Clearing it ahead of
    // this rule would take with it the only thing saying what the document is
    const auto *override{schema.try_at(DIALECT_OVERRIDE_KEYWORD)};
    if (override != nullptr && override->is_string() &&
        names_openapi_3_0_dialect(override->to_string())) {
      schema.erase(DIALECT_OVERRIDE_KEYWORD);
    }

    bump_dialect(schema, site, DRAFT_4_URL);
  }

  // A reference is rebased through these in order, so one whose source names a
  // position another's destination sits under has to come first. Shadowing
  // `definitions` names the very position the move below places its entries
  // under, so the renames are published ahead of the moves: the other way
  // round, the rename catches an entry the move has just put there and sends
  // every reference to it somewhere nothing lives
  [[nodiscard]] auto relocations() const -> std::vector<Relocation> override {
    std::vector<Relocation> result;
    result.reserve(this->renames_.size() + this->relocations_.size());
    for (const auto &[old_name, new_name] : this->renames_) {
      result.emplace_back(sourcemeta::core::Pointer{old_name},
                          sourcemeta::core::Pointer{new_name});
    }

    result.insert(result.cend(), this->relocations_.cbegin(),
                  this->relocations_.cend());
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
  // an `x-` member as the unknown keyword it is. All but `nullable` are
  // shadowed only where the target has no word for them, which
  // `carries_as_keyword` settles: three became keywords of a later draft, and
  // four are named by the OpenAPI dialects above 3.0
  // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
  static inline const std::array<std::string_view, 8> KEYWORDS{
      {"nullable", "discriminator", "xml", "externalDocs", "example",
       "deprecated", "readOnly", "writeOnly"}};

  // The other direction: what Draft 4 names that the OpenAPI 3.0 Schema Object
  // does not, so a document carrying one carries author data that the target
  // would start reading as a keyword. `id` is the one that matters most, as
  // Draft 4 takes it for the identifier that every reference in the document
  // resolves against.
  //
  // Only a Reference Object can carry one of these, since the Schema Object
  // closes itself to additional properties and admits only the extension
  // prefix, while a Reference Object constrains nothing beyond its `$ref`.
  // `$schema` is left out because it is the one of the six that names a
  // dialect, which `ShadowStrayDialectDeclaration` already answers for
  // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
  static inline const std::array<std::string_view, 5> PROMOTED_BY_DRAFT_4{
      {"id", "definitions", "dependencies", "patternProperties",
       "additionalItems"}};

  // Carry a member across as the author data it is, under a name the target
  // reads as nothing. A name already taken gains another prefix rather than
  // overwriting what is there
  auto shadow(sourcemeta::core::JSON &schema,
              const std::string_view keyword) const -> void {
    const std::string keyword_name{keyword};
    if (!schema.defines(keyword_name)) {
      return;
    }

    std::string prefixed_name{"x-" + keyword_name};
    while (schema.defines(prefixed_name)) {
      prefixed_name.insert(0, "x-");
    }

    this->renames_.emplace(keyword_name, prefixed_name);
    schema.rename(keyword_name, std::move(prefixed_name));
  }

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
          !this->carries_as_keyword(subschema, keyword)) {
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
  [[nodiscard]] auto carries_as_keyword(const sourcemeta::core::JSON &subschema,
                                        const std::string_view keyword) const
      -> bool {
    if (keyword == "readOnly" || keyword == "writeOnly") {
      return this->keeps_read_only_;
    }

    if (keyword == "deprecated") {
      return this->keeps_deprecated_;
    }

    if (!this->keeps_openapi_annotations_) {
      return false;
    }

    // Of the four the OpenAPI dialects name for themselves, only this one is
    // stated more loosely by 3.0 than by the dialects above it, so only this
    // one has a shape to answer for
    if (keyword == "discriminator") {
      return is_expressible_discriminator(
          subschema.at(sourcemeta::core::JSON::String{keyword}));
    }

    // `nullable` is not among them: no OpenAPI dialect above 3.0 has it, as a
    // type union says it there instead
    return keyword == "xml" || keyword == "externalDocs" ||
           keyword == "example";
  }

  // OpenAPI 3.0 leaves its Discriminator Object open, naming `propertyName` and
  // `mapping` without closing the object to anything else, while 3.1 and 3.2
  // close theirs to those two and the extension prefix. One carrying anything
  // more is a discriminator the target cannot read, so it goes across as the
  // author data it has to be there rather than as a keyword that would make the
  // output invalid against the dialect it declares
  static auto
  is_expressible_discriminator(const sourcemeta::core::JSON &discriminator)
      -> bool {
    if (!discriminator.is_object()) {
      return false;
    }

    for (const auto &entry : discriminator.as_object()) {
      if (entry.first != "propertyName" && entry.first != "mapping" &&
          !entry.first.starts_with("x-")) {
        return false;
      }
    }

    return true;
  }

  static auto holds_promoted_keyword(const sourcemeta::core::JSON &schema)
      -> bool {
    for (const auto &keyword : PROMOTED_BY_DRAFT_4) {
      if (schema.defines(sourcemeta::core::JSON::String{keyword})) {
        return true;
      }
    }

    return false;
  }

  // The members of a Reference Object that the dialect ignored and that a
  // target would start reading. One already carrying the extension prefix is
  // read as nothing anywhere, and a `$schema` is answered for by the rule that
  // settles a dialect declaration
  static auto holds_ignored_sibling(const sourcemeta::core::JSON &schema)
      -> bool {
    if (!schema.defines("$ref")) {
      return false;
    }

    for (const auto &entry : schema.as_object()) {
      if (entry.first != "$ref" && entry.first != "$schema" &&
          !entry.first.starts_with("x-")) {
        return true;
      }
    }

    return false;
  }

  // Taken as values, since shadowing renames the members being walked
  static auto member_names(const sourcemeta::core::JSON &schema)
      -> std::vector<sourcemeta::core::JSON::String> {
    std::vector<sourcemeta::core::JSON::String> names;
    names.reserve(schema.size());
    for (const auto &entry : schema.as_object()) {
      names.push_back(entry.first);
    }

    return names;
  }

  // Whether a shape only the OpenAPI 3.0 dialect admits is still here. Both are
  // rewritten by the transform, so the answer turns false once it has run
  static auto holds_pending_shape(const sourcemeta::core::JSON &schema)
      -> bool {
    const auto *options{schema.try_at("enum")};
    if (options != nullptr && options->is_array() && !options->unique()) {
      return true;
    }

    if ((schema.defines("exclusiveMinimum") && !schema.defines("minimum")) ||
        (schema.defines("exclusiveMaximum") && !schema.defines("maximum"))) {
      return true;
    }

    for (const auto &keyword : {"allOf", "anyOf", "oneOf"}) {
      const auto *branches{
          schema.try_at(sourcemeta::core::JSON::String{keyword})};
      if (branches != nullptr && branches->is_array() && branches->empty()) {
        return true;
      }
    }

    return false;
  }

  // The extension prefix constrains nothing, so a member of this one holds
  // whatever its author put there, while `definitions` reads every member of
  // itself as a schema. Only what is one has somewhere to go
  static auto holds_schema(const sourcemeta::core::JSON &entry) -> bool {
    return entry.is_object() || entry.is_boolean();
  }

  // Neither OpenAPI 3.0 nor Draft 4 has a boolean schema, and yet the walker
  // reads every member of this one as a subschema, so a reference naming a
  // boolean here is asserting something and has to keep asserting it. Draft 4
  // says the same two things with the schema every instance satisfies and the
  // schema none does
  static auto as_object_schema(const sourcemeta::core::JSON &entry)
      -> sourcemeta::core::JSON {
    if (!entry.is_boolean()) {
      return entry;
    }

    auto result{sourcemeta::core::JSON::make_object()};
    if (!entry.to_boolean()) {
      result.assign("not", sourcemeta::core::JSON::make_object());
    }

    return result;
  }

  static auto holds_movable_definitions(const sourcemeta::core::JSON &schema)
      -> bool {
    if (!schema.defines(DEFINITIONS) || !schema.at(DEFINITIONS).is_object()) {
      return false;
    }

    for (const auto &entry : schema.at(DEFINITIONS).as_object()) {
      if (holds_schema(entry.second)) {
        return true;
      }
    }

    return false;
  }

  // Draft 4 keeps under `definitions` what the OpenAPI 3.0 Schema Object keeps
  // here, and reads nothing of a schema under a member it does not know, so
  // every entry that is a schema is taken out for the caller to place and the
  // references reaching one follow it. Anything else stays where it was rather
  // than being carried somewhere that would read it as a schema it is not
  static auto take_definitions(sourcemeta::core::JSON &schema,
                               std::vector<Relocation> &relocations)
      -> sourcemeta::core::JSON {
    auto moved{sourcemeta::core::JSON::make_object()};
    if (!holds_movable_definitions(schema)) {
      return moved;
    }

    auto kept{sourcemeta::core::JSON::make_object()};
    for (const auto &entry : schema.at(DEFINITIONS).as_object()) {
      if (!holds_schema(entry.second)) {
        kept.assign(entry.first, entry.second);
        continue;
      }

      relocations.emplace_back(
          sourcemeta::core::Pointer{DEFINITIONS, entry.first},
          sourcemeta::core::Pointer{"definitions", entry.first});
      moved.assign(entry.first, as_object_schema(entry.second));
    }

    schema.erase(DEFINITIONS);
    if (!kept.empty()) {
      schema.assign(DEFINITIONS, std::move(kept));
    }

    return moved;
  }

  const bool keeps_read_only_;
  const bool keeps_deprecated_;
  const bool keeps_openapi_annotations_;
  mutable std::unordered_map<std::string, std::string> renames_;
  mutable std::vector<Relocation> relocations_;
};
