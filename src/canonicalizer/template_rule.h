#ifndef SOURCEMETA_BLAZE_CANONICALIZER_TEMPLATE_RULE_H_
#define SOURCEMETA_BLAZE_CANONICALIZER_TEMPLATE_RULE_H_

/// What a rule may ask about where it fired. Every answer is a verdict, which
/// a pattern reads as one and nothing else looks at
inline auto
verdict_for(const std::string_view name,
            const std::vector<sourcemeta::core::JSON> &arguments,
            const sourcemeta::core::JSON &schema,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame::Location &location)
    -> std::optional<bool> {
  if (name == "schema:in-vocabulary") {
    for (const auto &argument : arguments) {
      if (vocabularies.contains(argument.to_string())) {
        return true;
      }
    }

    return false;
  }

  // Whether what a term says its meta-schema is differs from the one actually
  // in effect there, which the frame alone can say
  if (name == "canonicalizer:declares-other-dialect") {
    const auto dialect{declared_dialect(schema)};
    return !dialect.empty() && dialect != location.dialect;
  }

  // Whether every value an `enum` offers already narrows the instance to what
  // `type` names, so that the `type` adds nothing. Which spellings count
  // depends on the dialect, so this cannot be stated structurally
  if (name == "canonicalizer:type-implied-by-enum") {
    const auto *type{schema.try_at("type")};
    const auto *options{schema.try_at("enum")};
    if (type == nullptr || options == nullptr || !options->is_array()) {
      return false;
    }

    return type_is_implied_by_enum(*type, *options, vocabularies);
  }

  // Whether `minProperties` says less than the names `required` already
  // insists on, which is a comparison between two parts of the term
  if (name == "canonicalizer:min-properties-below-required") {
    const auto *minimum{schema.try_at("minProperties")};
    const auto *required{schema.try_at("required")};
    if (minimum == nullptr || !minimum->is_integer() || required == nullptr ||
        !is_property_name_array(*required)) {
      return false;
    }

    return std::cmp_greater(required->size(),
                            static_cast<std::uint64_t>(minimum->to_integer()));
  }

  return std::nullopt;
}

/// The terms a rule may ask the host to build
inline auto term_for(const std::string_view name,
                     const std::vector<sourcemeta::core::JSON> &arguments,
                     const sourcemeta::core::SchemaVocabularies &vocabularies)
    -> sourcemeta::core::JSON {
  // The dialect's own spelling of a schema nothing satisfies. Which keywords
  // it uses is a property of the dialect rather than of the term
  if (name == "canonicalizer:unsatisfiable-form") {
    return unsatisfiable_schema(vocabularies);
  }

  // The entries of an array in canonical order and without repeats, which is
  // an ordering rather than a shape and so cannot be stated structurally
  if (name == "canonicalizer:sorted-unique") {
    if (arguments.size() != 1 || !arguments.front().is_array()) {
      throw sourcemeta::blaze::TransformError{"A sorted unique takes an array"};
    }

    auto result{arguments.front()};
    std::sort(result.as_array().begin(), result.as_array().end());
    const auto last{
        std::unique(result.as_array().begin(), result.as_array().end())};
    result.erase(last, result.as_array().end());
    return result;
  }

  // How many entries a term holds, which a pattern can test but not state
  if (name == "canonicalizer:count") {
    if (arguments.size() != 1 ||
        (!arguments.front().is_array() && !arguments.front().is_object())) {
      throw sourcemeta::blaze::TransformError{
          "A count takes an array or an object"};
    }

    return sourcemeta::core::JSON{arguments.front().size()};
  }

  throw sourcemeta::blaze::TransformError{"Unknown canonicalizer question"};
}

/// One way to ask the host something. A name the verdict chain knows answers
/// with a verdict, and every other name is one this module does not define
/// Where a rule fired, which is everything the host reads. Holding it in one
/// place means a host costs one pointer rather than three, which matters
/// because the driver asks every rule its condition at every subschema
struct Site {
  const sourcemeta::core::JSON &schema;
  const sourcemeta::core::SchemaVocabularies &vocabularies;
  const sourcemeta::core::SchemaFrame::Location &location;
};

inline auto make_host(const Site &site) -> sourcemeta::blaze::TransformHost {
  return [&site](const std::string_view name,
                 const std::vector<sourcemeta::core::JSON> &arguments)
             -> sourcemeta::core::JSON {
    const auto answer{verdict_for(name, arguments, site.schema,
                                  site.vocabularies, site.location)};
    if (answer.has_value()) {
      return sourcemeta::core::JSON{answer.value()};
    }

    return term_for(name, arguments, site.vocabularies);
  };
}

/// A rule whose condition and transform are data rather than code. The driver
/// asks a rule its condition and, where it holds, transforms right away, so
/// what the pattern bound carries straight across to the build
class TemplateRule final : public SchemaTransformRule {
public:
  using reframe_after_transform = std::true_type;

  // The definition outlives every rule built from it, as the ones this module
  // states as data are parsed once and kept for the life of the process
  TemplateRule(const sourcemeta::core::JSON &definition)
      : SchemaTransformRule{definition.at("name").to_string()},
        definition_{definition} {}

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    this->bindings_.clear();
    this->vocabularies_ = &vocabularies;
    this->location_ = &location;
    const Site site{
        .schema = schema, .vocabularies = vocabularies, .location = location};
    return sourcemeta::blaze::transform_match(this->definition_.at("match"),
                                              schema, make_host(site),
                                              this->bindings_);
  }

  auto transform(sourcemeta::core::JSON &schema) const -> void override {
    assert(this->vocabularies_ != nullptr);
    assert(this->location_ != nullptr);
    const Site site{.schema = schema,
                    .vocabularies = *this->vocabularies_,
                    .location = *this->location_};
    [[maybe_unused]] const auto trace{sourcemeta::blaze::transform_apply(
        this->definition_.at("build"), schema, this->bindings_,
        make_host(site))};
  }

private:
  const sourcemeta::core::JSON &definition_;
  mutable sourcemeta::blaze::TransformBindings bindings_;
  mutable const sourcemeta::core::SchemaVocabularies *vocabularies_{nullptr};
  mutable const sourcemeta::core::SchemaFrame::Location *location_{nullptr};
};

#endif
