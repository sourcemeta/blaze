class DuplicateDisallowEntries final : public SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  DuplicateDisallowEntries()
      : SchemaTransformRule{
            "duplicate_disallow_entries",
            "Setting duplicate subschemas in `disallow` is redundant, as "
            "negating the same subschema more than once is guaranteed to not "
            "affect the validation result"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::blaze::Vocabularies &vocabularies,
            const sourcemeta::blaze::SchemaFrame &,
            const sourcemeta::blaze::SchemaFrame::Location &,
            const sourcemeta::blaze::SchemaWalker &,
            const sourcemeta::blaze::SchemaResolver &, const bool) const
      -> SchemaTransformRule::Result override {
    ONLY_CONTINUE_IF(vocabularies.contains_any(
                         {Vocabularies::Known::JSON_Schema_Draft_3,
                          Vocabularies::Known::JSON_Schema_Draft_3_Hyper}) &&
                     schema.is_object());

    const auto *disallow{schema.try_at("disallow")};
    ONLY_CONTINUE_IF(disallow && disallow->is_array() && !disallow->unique());
    return true;
  }

  auto transform(JSON &schema, const Result &) const -> void override {
    this->index_mapping_.clear();
    const auto &original{schema.at("disallow")};

    std::unordered_map<std::reference_wrapper<const JSON>, std::size_t,
                       HashJSON<std::reference_wrapper<const JSON>>,
                       EqualJSON<std::reference_wrapper<const JSON>>>
        seen;
    auto result{JSON::make_array()};

    for (std::size_t index = 0; index < original.size(); ++index) {
      const auto &value{original.at(index)};
      const auto match{seen.find(std::cref(value))};

      if (match == seen.end()) {
        this->index_mapping_[index] = seen.size();
        seen.emplace(std::cref(value), seen.size());
        result.push_back(value);
      } else {
        this->index_mapping_[index] = match->second;
      }
    }

    schema.assign("disallow", std::move(result));
  }

  [[nodiscard]] auto rereference(const std::string_view, const Pointer &,
                                 const Pointer &target,
                                 const Pointer &current) const
      -> Pointer override {
    const auto disallow_prefix{current.concat({"disallow"})};
    if (!target.starts_with(disallow_prefix)) {
      return target;
    }

    const auto relative{target.resolve_from(disallow_prefix)};
    if (relative.empty() || !relative.at(0).is_index()) {
      return target;
    }

    const auto old_index{relative.at(0).to_index()};
    const auto new_index{this->index_mapping_.at(old_index)};
    return target.rebase(disallow_prefix.concat({old_index}),
                         disallow_prefix.concat({new_index}));
  }

private:
  mutable std::unordered_map<std::size_t, std::size_t> index_mapping_;
};
