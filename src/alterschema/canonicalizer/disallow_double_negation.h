class DisallowDoubleNegation final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  DisallowDoubleNegation()
      : SchemaTransformRule{
            "disallow_double_negation",
            "A `disallow` whose single negated schema is itself a `disallow` "
            "of "
            "a single schema is a double negation equivalent to the inner "
            "schema"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::blaze::Vocabularies &vocabularies,
            const sourcemeta::blaze::SchemaFrame &frame,
            const sourcemeta::blaze::SchemaFrame::Location &location,
            const sourcemeta::blaze::SchemaWalker &walker,
            const sourcemeta::blaze::SchemaResolver &, const bool) const
      -> SchemaTransformRule::Result override {
    static const JSON::String KEYWORD{"disallow"};
    ONLY_CONTINUE_IF(vocabularies.contains_any(
                         {Vocabularies::Known::JSON_Schema_Draft_3,
                          Vocabularies::Known::JSON_Schema_Draft_3_Hyper}) &&
                     schema.is_object());

    const auto *disallow{schema.try_at(KEYWORD)};
    ONLY_CONTINUE_IF(disallow && disallow->is_array() && disallow->size() == 1);
    ONLY_CONTINUE_IF(is_single_negation(disallow->at(0)));

    // Lifting the inner schema merges its keywords into this node, so the node
    // must assert nothing besides `disallow` (otherwise a sibling constraint
    // sharing a key with the inner schema would be silently clobbered)
    ONLY_CONTINUE_IF(
        wraps_single_constraint(schema, "disallow", walker, vocabularies));

    ONLY_CONTINUE_IF(!frame.has_references_through(
        location.pointer, WeakPointer::Token{std::cref(KEYWORD)}));
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    auto inner{schema.at("disallow").at(0).at("disallow").at(0)};
    schema.erase("disallow");

    while (is_single_negation(inner) &&
           is_single_negation(inner.at("disallow").at(0))) {
      auto next{inner.at("disallow").at(0).at("disallow").at(0)};
      inner = std::move(next);
    }

    if (inner.is_object()) {
      schema.merge(inner.as_object());
    }
  }

private:
  static auto is_single_negation(const sourcemeta::core::JSON &schema) -> bool {
    return schema.is_object() && schema.size() == 1 &&
           schema.defines("disallow") && schema.at("disallow").is_array() &&
           schema.at("disallow").size() == 1;
  }

  static auto wraps_single_constraint(
      const sourcemeta::core::JSON &schema, const std::string_view keyword,
      const sourcemeta::blaze::SchemaWalker &walker,
      const sourcemeta::blaze::Vocabularies &vocabularies) -> bool {
    for (const auto &entry : schema.as_object()) {
      if (entry.first == keyword) {
        continue;
      }

      const auto type{walker(entry.first, vocabularies).type};
      if (type != SchemaKeywordType::Annotation &&
          type != SchemaKeywordType::Comment &&
          type != SchemaKeywordType::Other &&
          type != SchemaKeywordType::Unknown &&
          type != SchemaKeywordType::LocationMembers) {
        return false;
      }
    }

    return true;
  }
};
