class TypeWithApplicatorToAllOf final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  TypeWithApplicatorToAllOf()
      : SchemaTransformRule{
            "type_with_applicator_to_allof",
            "When multiple structural keywords coexist (type with "
            "applicator, or multiple applicators), wrap in allOf to "
            "isolate each one"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(
        vocabularies.contains_any({Vocabularies::Known::JSON_Schema_Draft_4,
                                   Vocabularies::Known::JSON_Schema_Draft_6}) &&
        schema.is_object());

    const bool has_not{schema.defines("not")};
    const bool has_anyof{schema.defines("anyOf")};
    const bool has_allof{schema.defines("allOf")};
    const bool has_oneof{schema.defines("oneOf")};
    const bool has_type{schema.defines("type") &&
                        schema.at("type").is_string()};
    const bool has_enum{schema.defines("enum")};
    const bool has_ref{schema.defines("$ref")};
    const unsigned int applicator_count{
        (has_not ? 1U : 0U) + (has_anyof ? 1U : 0U) + (has_allof ? 1U : 0U) +
        (has_oneof ? 1U : 0U)};
    const bool has_structural{has_type || has_enum || has_ref};

    ONLY_CONTINUE_IF((has_structural && applicator_count >= 1) ||
                     applicator_count >= 2);

    this->strategy_ = Strategy::FullRestructure;
    this->applicators_with_refs_ = 0;
    for (const auto &reference : frame.references()) {
      const auto &source_pointer{reference.first.second};
      if (!source_pointer.starts_with(location.pointer)) {
        continue;
      }
      const auto relative{source_pointer.resolve_from(location.pointer)};
      if (relative.empty() || !relative.at(0).is_property()) {
        continue;
      }
      const auto &first_keyword{relative.at(0).to_property()};
      const auto bit{applicator_bit(first_keyword)};
      if (bit != 0) {
        this->strategy_ = Strategy::SafeExtract;
        this->applicators_with_refs_ |= bit;
      }
    }

    if (this->strategy_ == Strategy::SafeExtract && !has_structural) {
      if (!has_allof) {
        return false;
      }

      bool all_refs_fixed{true};
      for (const auto &reference : frame.references()) {
        const auto &source_pointer{reference.first.second};
        if (!source_pointer.starts_with(location.pointer)) {
          continue;
        }
        const auto relative_src{source_pointer.resolve_from(location.pointer)};
        if (relative_src.empty() || !relative_src.at(0).is_property()) {
          continue;
        }
        const auto &src_keyword{relative_src.at(0).to_property()};
        if (src_keyword != "not" && src_keyword != "anyOf" &&
            src_keyword != "oneOf") {
          continue;
        }

        const auto destination{frame.traverse(reference.second.destination)};
        if (!destination.has_value()) {
          all_refs_fixed = false;
          break;
        }

        const auto relative_dest{
            destination->get().pointer.resolve_from(location.pointer)};
        if (relative_dest.empty() || !relative_dest.at(0).is_property() ||
            relative_dest.at(0).to_property() != "allOf") {
          all_refs_fixed = false;
          break;
        }
      }

      if (all_refs_fixed) {
        this->strategy_ = Strategy::MergeIntoAllOf;
      } else {
        return false;
      }
    }

    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    this->typed_keywords_.clear();

    if (this->strategy_ == Strategy::MergeIntoAllOf) {
      for (const auto &applicator : APPLICATORS_WITHOUT_ALLOF) {
        if (!schema.defines(applicator)) {
          continue;
        }
        auto branch{JSON::make_object()};
        branch.assign(applicator, schema.at(applicator));
        schema.at("allOf").push_back(std::move(branch));
        schema.erase(applicator);
      }
      return;
    }

    auto typed_branch{JSON::make_object()};
    for (const auto &entry : schema.as_object()) {
      if (entry.first == "not" || entry.first == "anyOf" ||
          entry.first == "allOf" || entry.first == "oneOf" ||
          entry.first == "$schema" || entry.first == "id" ||
          entry.first == "$id") {
        continue;
      }
      typed_branch.assign(entry.first, entry.second);
      this->typed_keywords_.emplace_back(entry.first);
    }

    for (const auto &key : this->typed_keywords_) {
      schema.erase(key);
    }

    if (this->strategy_ == Strategy::SafeExtract) {
      if (schema.defines("allOf") && schema.at("allOf").is_array()) {
        this->typed_branch_index_ = schema.at("allOf").size();
        schema.at("allOf").push_back(std::move(typed_branch));
      } else {
        this->typed_branch_index_ = 0;
        auto new_allof{JSON::make_array()};
        new_allof.push_back(std::move(typed_branch));
        schema.assign("allOf", std::move(new_allof));
      }

      for (const auto &applicator : APPLICATORS_WITHOUT_ALLOF) {
        if (!schema.defines(applicator)) {
          continue;
        }
        if (this->applicators_with_refs_ & applicator_bit(applicator)) {
          continue;
        }
        auto branch{JSON::make_object()};
        branch.assign(applicator, schema.at(applicator));
        schema.at("allOf").push_back(std::move(branch));
        schema.erase(applicator);
      }

      return;
    }

    auto new_allof{JSON::make_array()};
    this->applicator_indices_ = 0;

    for (const auto &applicator : APPLICATORS) {
      if (!schema.defines(applicator)) {
        continue;
      }
      auto branch{JSON::make_object()};
      branch.assign(applicator, schema.at(applicator));
      new_allof.push_back(std::move(branch));
      this->applicator_indices_ |= applicator_bit(applicator);
    }

    if (!this->typed_keywords_.empty()) {
      new_allof.push_back(std::move(typed_branch));
    }

    auto new_schema{JSON::make_object()};
    if (schema.defines("$schema")) {
      new_schema.assign("$schema", schema.at("$schema"));
    }
    if (schema.defines("id")) {
      new_schema.assign("id", schema.at("id"));
    }
    if (schema.defines("$id")) {
      new_schema.assign("$id", schema.at("$id"));
    }
    new_schema.assign("allOf", std::move(new_allof));
    schema.into(std::move(new_schema));
  }

  [[nodiscard]] auto rereference(const std::string_view, const Pointer &,
                                 const Pointer &target,
                                 const Pointer &current) const
      -> Pointer override {
    const auto relative{target.resolve_from(current)};
    if (relative.empty() || !relative.at(0).is_property()) {
      return target;
    }

    const auto &keyword{relative.at(0).to_property()};
    static const JSON::String allof_keyword{"allOf"};

    for (const auto &typed_kw : this->typed_keywords_) {
      if (typed_kw == keyword) {
        const Pointer old_prefix{current.concat({keyword})};
        if (this->strategy_ == Strategy::SafeExtract) {
          const Pointer new_prefix{current.concat(
              {allof_keyword, this->typed_branch_index_, keyword})};
          return target.rebase(old_prefix, new_prefix);
        } else {
          const std::size_t typed_index{static_cast<std::size_t>(
              std::popcount(this->applicator_indices_))};
          const Pointer new_prefix{
              current.concat({allof_keyword, typed_index, keyword})};
          return target.rebase(old_prefix, new_prefix);
        }
      }
    }

    if (this->strategy_ == Strategy::FullRestructure) {
      std::size_t index{0};
      for (const auto &applicator : APPLICATORS) {
        if (keyword == applicator) {
          const Pointer old_prefix{current.concat({keyword})};
          const Pointer new_prefix{
              current.concat({allof_keyword, index, keyword})};
          return target.rebase(old_prefix, new_prefix);
        }
        if (this->applicator_indices_ & applicator_bit(applicator)) {
          index++;
        }
      }
    }

    return target;
  }

private:
  static constexpr std::array<const char *, 4> APPLICATORS{
      {"not", "anyOf", "allOf", "oneOf"}};
  static constexpr std::array<const char *, 3> APPLICATORS_WITHOUT_ALLOF{
      {"not", "anyOf", "oneOf"}};

  static constexpr auto applicator_bit(std::string_view keyword)
      -> std::uint8_t {
    if (keyword == "not")
      return 1;
    if (keyword == "anyOf")
      return 2;
    if (keyword == "allOf")
      return 4;
    if (keyword == "oneOf")
      return 8;
    return 0;
  }

  enum class Strategy : std::uint8_t {
    FullRestructure,
    SafeExtract,
    MergeIntoAllOf
  };
  mutable Strategy strategy_{Strategy::FullRestructure};
  mutable std::vector<std::string> typed_keywords_;
  mutable std::uint8_t applicator_indices_{0};
  mutable std::uint8_t applicators_with_refs_{0};
  mutable std::size_t typed_branch_index_{0};
};
