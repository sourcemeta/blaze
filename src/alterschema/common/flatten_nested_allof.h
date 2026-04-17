class FlattenNestedAllOf final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  FlattenNestedAllOf()
      : SchemaTransformRule{
            "flatten_nested_allof",
            "An `allOf` branch that only contains another `allOf` can "
            "be flattened into the parent `allOf`"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    static const JSON::String KEYWORD{"allOf"};
    ONLY_CONTINUE_IF(vocabularies.contains_any(
                         {Vocabularies::Known::JSON_Schema_2020_12_Applicator,
                          Vocabularies::Known::JSON_Schema_2019_09_Applicator,
                          Vocabularies::Known::JSON_Schema_Draft_7,
                          Vocabularies::Known::JSON_Schema_Draft_6,
                          Vocabularies::Known::JSON_Schema_Draft_4}) &&
                     schema.is_object() && schema.defines(KEYWORD) &&
                     schema.at(KEYWORD).is_array());

    const auto &branches{schema.at(KEYWORD)};
    bool found{false};
    for (const auto &branch : branches.as_array()) {
      if (branch.is_object() && branch.size() == 1 && branch.defines(KEYWORD) &&
          branch.at(KEYWORD).is_array()) {
        found = true;
        break;
      }
    }

    ONLY_CONTINUE_IF(found);
    ONLY_CONTINUE_IF(!frame.has_references_through(
        location.pointer, WeakPointer::Token{std::cref(KEYWORD)}));
    return APPLIES_TO_KEYWORDS(KEYWORD);
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    static const JSON::String KEYWORD{"allOf"};
    this->index_mapping_.clear();
    const auto &original{schema.at(KEYWORD)};
    auto result{JSON::make_array()};
    std::size_t new_index{0};

    for (std::size_t index = 0; index < original.size(); ++index) {
      const auto &branch{original.at(index)};
      if (branch.is_object() && branch.size() == 1 && branch.defines(KEYWORD) &&
          branch.at(KEYWORD).is_array()) {
        const auto &inner{branch.at(KEYWORD)};
        for (std::size_t inner_index = 0; inner_index < inner.size();
             ++inner_index) {
          this->index_mapping_.emplace_back(index, inner_index, new_index);
          result.push_back(inner.at(inner_index));
          ++new_index;
        }
      } else {
        this->index_mapping_.emplace_back(index, std::nullopt, new_index);
        result.push_back(branch);
        ++new_index;
      }
    }

    schema.assign(KEYWORD, std::move(result));
  }

  [[nodiscard]] auto rereference(const std::string_view, const Pointer &,
                                 const Pointer &target,
                                 const Pointer &current) const
      -> Pointer override {
    static const JSON::String KEYWORD{"allOf"};
    const auto prefix{current.concat({KEYWORD})};
    if (!target.starts_with(prefix)) {
      return target;
    }
    const auto relative{target.resolve_from(prefix)};
    if (relative.empty() || !relative.at(0).is_index()) {
      return target;
    }
    const auto old_index{relative.at(0).to_index()};
    for (const auto &[outer, inner, mapped] : this->index_mapping_) {
      if (inner.has_value()) {
        const Pointer old_prefix{
            prefix.concat({old_index, KEYWORD, inner.value()})};
        if (target.starts_with(old_prefix)) {
          const Pointer new_prefix{prefix.concat({mapped})};
          return target.rebase(old_prefix, new_prefix);
        }
      } else if (outer == old_index) {
        const Pointer old_prefix{prefix.concat({old_index})};
        const Pointer new_prefix{prefix.concat({mapped})};
        return target.rebase(old_prefix, new_prefix);
      }
    }
    return target;
  }

private:
  mutable std::vector<
      std::tuple<std::size_t, std::optional<std::size_t>, std::size_t>>
      index_mapping_;
};
