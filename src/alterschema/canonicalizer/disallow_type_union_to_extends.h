class DisallowTypeUnionToExtends final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  DisallowTypeUnionToExtends()
      : SchemaTransformRule{
            "disallow_type_union_to_extends",
            "Negating a disjunction is the conjunction of the negations: a "
            "`type` union under `disallow` becomes an `extends` where each "
            "branch is its own single negation"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::blaze::Vocabularies &vocabularies,
            const sourcemeta::blaze::SchemaFrame &frame,
            const sourcemeta::blaze::SchemaFrame::Location &location,
            const sourcemeta::blaze::SchemaWalker &walker,
            const sourcemeta::blaze::SchemaResolver &, const bool) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(vocabularies.contains_any(
                         {Vocabularies::Known::JSON_Schema_Draft_3,
                          Vocabularies::Known::JSON_Schema_Draft_3_Hyper}) &&
                     schema.is_object());

    const auto *disallow{schema.try_at("disallow")};
    ONLY_CONTINUE_IF(disallow && disallow->is_array() && disallow->size() == 1);

    const auto &element{disallow->at(0)};
    ONLY_CONTINUE_IF(element.is_object() && element.defines("type") &&
                     element.at("type").is_array() &&
                     !element.at("type").empty());

    // Only a pure negation can be distributed: the schema must assert nothing
    // besides `disallow` (otherwise the new `extends` would clobber a sibling
    // constraint), and the negated schema must assert nothing besides its
    // `type` union (otherwise those conjuncts would be silently dropped)
    ONLY_CONTINUE_IF(
        wraps_single_constraint(schema, "disallow", walker, vocabularies) &&
        wraps_single_constraint(element, "type", walker, vocabularies));

    // A reference into the `disallow` subtree cannot survive the rewrite: the
    // wrapper schema is dissolved rather than relocated, so leave such cases
    // for the engine and let other rules normalize them
    const std::string keyword{"disallow"};
    ONLY_CONTINUE_IF(!frame.has_references_through(
        location.pointer, WeakPointer::Token{std::cref(keyword)}));

    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    auto branches{JSON::make_array()};
    for (auto &member : schema.at("disallow").at(0).at("type").as_array()) {
      auto negation{JSON::make_array()};
      negation.push_back(std::move(member));
      auto branch{JSON::make_object()};
      branch.assign("disallow", std::move(negation));
      branches.push_back(std::move(branch));
    }

    schema.erase("disallow");
    schema.assign("extends", std::move(branches));
  }

private:
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
