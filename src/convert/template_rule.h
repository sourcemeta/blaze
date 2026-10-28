#ifndef SOURCEMETA_BLAZE_CONVERT_TEMPLATE_RULE_H_
#define SOURCEMETA_BLAZE_CONVERT_TEMPLATE_RULE_H_

/// A short name for a base dialect, so that a rule can gate on one without the
/// language knowing what a base dialect is
inline auto base_dialect_name(const sourcemeta::core::SchemaBaseDialect value)
    -> std::string_view {
  using sourcemeta::core::SchemaBaseDialect;
  switch (value) {
    case SchemaBaseDialect::JSON_SCHEMA_2020_12:
      return "2020-12";
    case SchemaBaseDialect::JSON_SCHEMA_2020_12_HYPER:
      return "2020-12-hyper";
    case SchemaBaseDialect::JSON_SCHEMA_2019_09:
      return "2019-09";
    case SchemaBaseDialect::JSON_SCHEMA_2019_09_HYPER:
      return "2019-09-hyper";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_7:
      return "draft7";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_7_HYPER:
      return "draft7-hyper";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_6:
      return "draft6";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_6_HYPER:
      return "draft6-hyper";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_4:
      return "draft4";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_4_HYPER:
      return "draft4-hyper";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_3:
      return "draft3";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_3_HYPER:
      return "draft3-hyper";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_2_HYPER:
      return "draft2-hyper";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_1_HYPER:
      return "draft1-hyper";
    case SchemaBaseDialect::JSON_SCHEMA_DRAFT_0_HYPER:
      return "draft0-hyper";
  }

  return "";
}

/// What a rule asks the host while the frame still describes the document in
/// front of it. A query answers with a term, which the rule then consults as
/// an ordinary binding, so that a decision the whole document settles reaches
/// a pattern and a template the same way a captured subschema does
struct QueryContext {
  const sourcemeta::core::JSON &schema;
  const sourcemeta::core::JSON &root;
  const sourcemeta::core::SchemaVocabularies &vocabularies;
  const sourcemeta::core::SchemaFrame &frame;
  const sourcemeta::core::SchemaFrame::Location &location;
  const Site &site;
  const sourcemeta::core::SchemaWalker &walker;
  const sourcemeta::core::SchemaResolver &resolver;
};

using Query = std::function<sourcemeta::core::JSON(
    std::string_view, const std::vector<sourcemeta::core::JSON> &,
    const QueryContext &)>;

/// Rename every Draft 4 anchor whose fragment Draft 6 would reject, and move
/// the references that spell those names out. This is a whole-document
/// analysis rather than a pattern and a template: which name an anchor becomes
/// depends on every other anchor in its resource, and the references that
/// follow it may sit anywhere. It is delegated rather than expressed, and it
/// is the one rewrite in this module that is
inline auto sanitize_draft_4_anchors(sourcemeta::core::JSON &schema,
                                     const sourcemeta::core::SchemaFrame &frame)
    -> bool {
  struct Rename {
    std::string from;
    std::string to;
  };

  using Move = std::tuple<sourcemeta::core::Pointer, std::string,
                          sourcemeta::core::JSON>;
  std::vector<Move> moves;
  std::map<sourcemeta::core::Pointer, Rename> renamed;
  std::map<std::string, std::set<std::string>> taken;
  std::map<sourcemeta::core::Pointer, std::pair<std::string, std::string>>
      pending;

  frame.for_each_subschema(
      [&schema, &taken,
       &pending](const sourcemeta::core::SchemaFrame::Location &entry) -> void {
        if (base_dialect_position(entry.base_dialect) !=
            dialect_position(DRAFT_4_DIALECT)) {
          return;
        }

        std::string base{entry.base};
        auto pointer{sourcemeta::core::to_pointer(entry.pointer)};
        const auto &subschema{sourcemeta::core::get(schema, pointer)};
        if (!subschema.is_object()) {
          return;
        }

        const auto *identifier{subschema.try_at("id")};
        if (identifier == nullptr) {
          return;
        }

        const auto fragment{identifier_fragment(*identifier)};
        if (!fragment.has_value() || fragment.value().empty()) {
          return;
        }

        taken[base].insert(fragment.value());
        if (!is_draft_6_plain_name(fragment.value())) {
          pending.insert_or_assign(
              std::move(pointer),
              std::make_pair(std::move(base), fragment.value()));
        }
      });

  for (const auto &[pointer, entry] : pending) {
    const auto &[base, original] = entry;
    auto in_use{taken.at(base)};
    in_use.erase(original);
    auto sanitized{
        sanitize_anchor_with_policy(original, in_use, draft_6_anchor_policy())};
    taken.at(base).insert(sanitized);

    const auto &written{
        sourcemeta::core::get(schema, pointer).at("id").to_string()};
    auto replacement{sourcemeta::core::JSON{
        std::string{without_fragment_as_written(written)} + "#" + sanitized}};
    moves.emplace_back(pointer, "id", std::move(replacement));
    renamed.emplace(pointer,
                    Rename{.from = original, .to = std::move(sanitized)});
  }

  if (renamed.empty()) {
    return false;
  }

  frame.for_each_reference(
      [&frame, &renamed, &moves](
          const sourcemeta::core::SchemaReferenceType,
          const sourcemeta::core::WeakPointer &origin,
          const sourcemeta::core::SchemaFrame::Reference &reference) -> void {
        if (!reference.fragment.has_value() ||
            reference.fragment.value().empty()) {
          return;
        }

        const auto target{frame.traverse(reference.destination)};
        if (!target.has_value()) {
          return;
        }

        const auto match{renamed.find(
            sourcemeta::core::to_pointer(target.value().get().pointer))};
        if (match == renamed.cend()) {
          return;
        }

        if (reference.fragment.value() != match->second.from) {
          return;
        }

        auto replacement{sourcemeta::core::JSON{
            std::string{without_fragment_as_written(reference.original)} + "#" +
            match->second.to}};
        auto holder{sourcemeta::core::to_pointer(origin)};
        const auto keyword{holder.back().to_property()};
        holder.pop_back();
        moves.emplace_back(std::move(holder), keyword, std::move(replacement));
      });

  for (const auto &[pointer, keyword, value] : moves) {
    sourcemeta::core::get(schema, pointer).assign(keyword, value);
  }

  return true;
}

constexpr std::string_view DRAFT_3_DIALECT{
    "http://json-schema.org/draft-03/schema#"};

/// Draft 3 lists the type names it defines and says a value outside that list
/// accepts any instance, which is what `any` does
inline auto draft_3_names_every_instance(const sourcemeta::core::JSON &element)
    -> bool {
  if (!element.is_string()) {
    return false;
  }

  static constexpr std::array<std::string_view, 7> NAMES{
      {"string", "number", "integer", "boolean", "object", "array", "null"}};
  const auto &name{element.to_string()};
  return std::ranges::none_of(NAMES, [&name](const auto candidate) -> bool {
    return candidate == name;
  });
}

inline auto draft_3_type_branch(const sourcemeta::core::JSON &name)
    -> sourcemeta::core::JSON {
  auto branch{sourcemeta::core::JSON::make_object()};
  if (!draft_3_names_every_instance(name)) {
    branch.assign("type", name);
  }

  return branch;
}

inline auto draft_3_type_branches(const sourcemeta::core::JSON &value)
    -> sourcemeta::core::JSON {
  auto branches{sourcemeta::core::JSON::make_array()};
  for (const auto &element : value.as_array()) {
    if (element.is_string()) {
      branches.push_back(draft_3_type_branch(element));
    } else if (element.is_object()) {
      branches.push_back(element);
    }
  }

  return branches;
}

inline auto draft_3_holds_subschema(const sourcemeta::core::JSON &value)
    -> bool {
  return value.is_array() &&
         std::ranges::any_of(value.as_array(), [](const auto &element) -> bool {
           return element.is_object();
         });
}

inline auto draft_3_has_repeated_name(const sourcemeta::core::JSON &names)
    -> bool {
  std::set<std::string> already;
  for (const auto &name : names.as_array()) {
    if (name.is_string() && !already.insert(name.to_string()).second) {
      return true;
    }
  }

  return false;
}

/// Draft 3 reads `required` beside a property as whether that property has to
/// be present, which Draft 4 says with an array on the enclosing schema. The
/// lift is a rewrite of two members at once, with a deduplicating merge in the
/// middle, so it is a named operation rather than a sequence of edits
inline auto draft_3_lift_required(const sourcemeta::core::JSON &schema)
    -> sourcemeta::core::JSON {
  auto result{schema};
  std::vector<std::string> newly_required;
  auto &properties{result.at("properties")};
  std::vector<std::string> keys;
  keys.reserve(properties.size());
  for (const auto &entry : properties.as_object()) {
    keys.push_back(entry.first);
  }

  for (const auto &key : keys) {
    auto &property{properties.at(key)};
    if (!property.is_object() || !property.defines("required")) {
      continue;
    }

    const auto declared{declared_dialect(property)};
    if (!declared.empty() &&
        dialect_position(declared) != dialect_position(DRAFT_3_DIALECT)) {
      continue;
    }

    if (!property.at("required").is_boolean()) {
      continue;
    }

    const auto is_required{property.at("required").to_boolean()};

    // Draft 3 replaces a schema with whatever its `$ref` names, so a flag
    // beside one never made the property mandatory. Shadowing keeps the record
    // without asserting anything
    if (property.defines("$ref")) {
      if (is_required) {
        std::string shadowed{"x-required"};
        while (property.defines(shadowed)) {
          shadowed.insert(0, "x-");
        }

        property.rename("required", std::move(shadowed));
      } else {
        property.erase("required");
      }

      continue;
    }

    property.erase("required");
    if (is_required) {
      newly_required.push_back(key);
    }
  }

  if (newly_required.empty()) {
    return result;
  }

  if (!result.defines("required") || !result.at("required").is_array()) {
    auto fresh{sourcemeta::core::JSON::make_array()};
    for (const auto &name : newly_required) {
      fresh.push_back(sourcemeta::core::JSON{name});
    }

    result.try_assign_before("required", fresh, "properties");
    return result;
  }

  auto &existing{result.at("required")};
  std::set<std::string> already;
  for (const auto &item : existing.as_array()) {
    if (item.is_string()) {
      already.insert(item.to_string());
    }
  }

  for (const auto &name : newly_required) {
    if (already.contains(name)) {
      continue;
    }

    existing.push_back(sourcemeta::core::JSON{name});
    already.insert(name);
  }

  return result;
}

/// Draft 3 satisfies an empty property dependency vacuously and tolerates a
/// repeated name, neither of which Draft 4 accepts, and it spells a single
/// dependency as a bare string
inline auto draft_3_normalize_dependencies(const sourcemeta::core::JSON &value)
    -> sourcemeta::core::JSON {
  auto result{sourcemeta::core::JSON::make_object()};
  for (const auto &entry : value.as_object()) {
    if (entry.second.is_string()) {
      auto array{sourcemeta::core::JSON::make_array()};
      array.push_back(entry.second);
      result.assign(entry.first, std::move(array));
      continue;
    }

    if (!entry.second.is_array()) {
      result.assign(entry.first, entry.second);
      continue;
    }

    if (entry.second.empty()) {
      continue;
    }

    auto fresh{sourcemeta::core::JSON::make_array()};
    std::set<std::string> already;
    for (const auto &name : entry.second.as_array()) {
      if (name.is_string() && !already.insert(name.to_string()).second) {
        continue;
      }

      fresh.push_back(name);
    }

    result.assign(entry.first, std::move(fresh));
  }

  return result;
}

/// Whether the Draft 3 rung still has work in this subschema
inline auto has_pending_draft_3_pattern(const sourcemeta::core::JSON &subschema,
                                        const std::string_view dialect)
    -> bool {
  static constexpr std::array<std::string_view, 7> PROMOTED{
      {"multipleOf", "maxProperties", "minProperties", "allOf", "anyOf",
       "oneOf", "not"}};

  if (!subschema.is_object() ||
      declares_dialect_out_of_reach(subschema, DRAFT_3_DIALECT) ||
      dialect_position(dialect) > dialect_position(DRAFT_3_DIALECT)) {
    return false;
  }

  if (subschema.defines("$schema") && subschema.at("$schema").is_string() &&
      subschema.at("$schema").to_string() == DRAFT_3_DIALECT) {
    return true;
  }

  const auto *type_value{subschema.try_at("type")};
  if (type_value != nullptr) {
    if (draft_3_names_every_instance(*type_value)) {
      return true;
    }

    if (type_value->is_array()) {
      for (const auto &element : type_value->as_array()) {
        if (draft_3_names_every_instance(element) || element.is_object()) {
          return true;
        }
      }
    }
  }

  const auto *disallow{subschema.try_at("disallow")};
  if (disallow != nullptr && (disallow->is_string() || disallow->is_array() ||
                              disallow->is_object())) {
    return true;
  }

  const auto *extends{subschema.try_at("extends")};
  if (extends != nullptr && (extends->is_array() || extends->is_object())) {
    return true;
  }

  if (subschema.defines("divisibleBy")) {
    return true;
  }

  const auto *items{subschema.try_at("items")};
  if (items != nullptr && items->is_array() && items->empty()) {
    return true;
  }

  const auto *properties{subschema.try_at("properties")};
  if (properties != nullptr && properties->is_object()) {
    for (const auto &entry : properties->as_object()) {
      if (entry.second.is_object() && entry.second.defines("required") &&
          entry.second.at("required").is_boolean()) {
        return true;
      }
    }
  }

  const auto *dependencies{subschema.try_at("dependencies")};
  if (dependencies != nullptr && dependencies->is_object()) {
    for (const auto &entry : dependencies->as_object()) {
      if (entry.second.is_string() ||
          (entry.second.is_array() &&
           (entry.second.empty() || draft_3_has_repeated_name(entry.second)))) {
        return true;
      }
    }
  }

  const auto *format{subschema.try_at("format")};
  if (format != nullptr && format->is_string() &&
      (format->to_string() == "host-name" ||
       format->to_string() == "ip-address")) {
    return true;
  }

  // A keyword Draft 4 promotes is inert data here, and the rule that shadows
  // it only fires while the subschema is still read as Draft 3
  return std::ranges::any_of(PROMOTED,
                             [&subschema](const auto keyword) -> bool {
                               return subschema.defines(keyword);
                             });
}

constexpr std::string_view OPENAPI_3_0_DEFINITIONS{"x-definitions"};

/// The OpenAPI 3.0 Schema Object members Draft 4 has no word for
constexpr std::array<std::string_view, 8> OPENAPI_3_0_KEYWORDS{
    {"nullable", "discriminator", "xml", "externalDocs", "example",
     "deprecated", "readOnly", "writeOnly"}};

/// What Draft 4 names that the OpenAPI 3.0 Schema Object does not
constexpr std::array<std::string_view, 5> OPENAPI_3_0_PROMOTED_BY_DRAFT_4{
    {"id", "definitions", "dependencies", "patternProperties",
     "additionalItems"}};

/// Each of these modifies the bound beside it, which Draft 4 requires to be
/// there and OpenAPI 3.0 does not
constexpr std::array<std::pair<std::string_view, std::string_view>, 2>
    OPENAPI_3_0_UNACCOMPANIED{
        {{"exclusiveMinimum", "minimum"}, {"exclusiveMaximum", "maximum"}}};

/// The extension prefix is not a free namespace: core reads this dialect's
/// subschema container and the dialect marker within it
inline auto openapi_3_0_names_core_reads(const std::string_view name) -> bool {
  return name == OPENAPI_3_0_DEFINITIONS || name == DIALECT_OVERRIDE_KEYWORD;
}

/// A `mapping` entry naming a schema inside the container this rung moves
/// would be left pointing where nothing is, and the frame indexes no such
/// reference to follow
inline auto
openapi_3_0_mapping_survives(const sourcemeta::core::JSON &discriminator)
    -> bool {
  const auto *mapping{discriminator.try_at("mapping")};
  if (mapping == nullptr || !mapping->is_object()) {
    return true;
  }

  return std::ranges::none_of(
      mapping->as_object(), [](const auto &entry) -> bool {
        return entry.second.is_string() &&
               entry.second.to_string().starts_with("#/x-definitions/");
      });
}

/// OpenAPI 3.0 leaves its Discriminator Object open while 3.1 and 3.2 close
/// theirs, so one carrying anything more cannot go across as a keyword
inline auto
openapi_3_0_expressible_discriminator(const sourcemeta::core::JSON &value,
                                      const bool keeps_default_mapping)
    -> bool {
  if (!value.is_object()) {
    return false;
  }

  for (const auto &entry : value.as_object()) {
    if (entry.first == "propertyName" || entry.first == "mapping" ||
        entry.first.starts_with("x-")) {
      continue;
    }

    if (entry.first == "defaultMapping" && keeps_default_mapping) {
      continue;
    }

    return false;
  }

  return true;
}

/// Neither dialect has a boolean schema, yet the walker reads every member of
/// the container as a subschema, so a boolean becomes the object saying the
/// same thing
inline auto openapi_3_0_as_object_schema(const sourcemeta::core::JSON &entry)
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

/// Whether a shape only the OpenAPI 3.0 dialect admits is still here
inline auto openapi_3_0_holds_pending_shape(const sourcemeta::core::JSON &value)
    -> bool {
  const auto *options{value.try_at("enum")};
  if (options != nullptr && options->is_array() && !options->unique()) {
    return true;
  }

  for (const auto &[keyword, companion] : OPENAPI_3_0_UNACCOMPANIED) {
    if (value.defines(sourcemeta::core::JSON::String{keyword}) &&
        !value.defines(sourcemeta::core::JSON::String{companion})) {
      return true;
    }
  }

  return std::ranges::any_of(
      std::array<std::string_view, 3>{{"allOf", "anyOf", "oneOf"}},
      [&value](const auto keyword) -> bool {
        const auto *branches{
            value.try_at(sourcemeta::core::JSON::String{keyword})};
        return branches != nullptr && branches->is_array() && branches->empty();
      });
}

/// The grammar 2019-09 gives a plain-name fragment
inline auto is_plain_name_anchor(const std::string_view fragment) -> bool {
  if (fragment.empty()) {
    return false;
  }

  for (const auto character : fragment) {
    const bool is_alpha{(character >= 'A' && character <= 'Z') ||
                        (character >= 'a' && character <= 'z')};
    const bool is_digit{character >= '0' && character <= '9'};
    const bool is_punct{character == '_' || character == ':' ||
                        character == '.' || character == '-'};
    if (!is_alpha && !is_digit && !is_punct) {
      return false;
    }
  }

  return true;
}

/// Whether the Draft 4 rung still has work in this subschema. Moved here from
/// the rule that used to own it, because a question about where a rule fires
/// is what the profile answers
inline auto has_pending_draft_4_pattern(const sourcemeta::core::JSON &subschema,
                                        const std::string_view dialect)
    -> bool {
  static constexpr std::array<std::string_view, 4> PROMOTED{
      {"const", "contains", "propertyNames", "examples"}};

  if (!subschema.is_object()) {
    return false;
  }

  if (dialect_position(dialect) > dialect_position(DRAFT_4_DIALECT)) {
    return false;
  }

  if (subschema.defines("$schema") && subschema.at("$schema").is_string() &&
      subschema.at("$schema").to_string() == DRAFT_4_DIALECT) {
    return true;
  }

  if (subschema.defines("id") && subschema.at("id").is_string()) {
    const auto fragment{identifier_fragment(subschema.at("id"))};
    if (!fragment.has_value() || fragment.value().empty() ||
        is_draft_6_plain_name(fragment.value())) {
      return true;
    }
  }

  const auto *exclusive_minimum{subschema.try_at("exclusiveMinimum")};
  if (exclusive_minimum != nullptr && exclusive_minimum->is_boolean()) {
    return true;
  }

  const auto *exclusive_maximum{subschema.try_at("exclusiveMaximum")};
  if (exclusive_maximum != nullptr && exclusive_maximum->is_boolean()) {
    return true;
  }

  for (const auto &keyword : PROMOTED) {
    if (subschema.defines(keyword)) {
      return true;
    }
  }

  // Draft 4 does not know `$id`, so one written there is inert data that
  // Draft 6 would read as the identifier, and it has to be shadowed before
  // `id` takes that name
  return subschema.defines("$id") &&
         dialect_position(dialect) <= dialect_position(DRAFT_4_DIALECT) &&
         dialect_position(declared_dialect(subschema)) <=
             dialect_position(DRAFT_4_DIALECT);
}

/// The questions a rule may ask about where it fired
inline auto
verdict_for(const std::string_view name,
            const std::vector<sourcemeta::core::JSON> &arguments,
            const sourcemeta::core::JSON &schema,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const Site &site, const sourcemeta::core::JSON &settings)
    -> std::optional<bool> {
  if (name == "schema:in-vocabulary") {
    for (const auto &argument : arguments) {
      if (vocabularies.contains(argument.to_string())) {
        return true;
      }
    }

    return false;
  }

  if (name == "convert:at-root") {
    return site.pointer.empty();
  }

  if (name == "convert:at-resource-root") {
    return site.pointer.size() == site.relative_pointer;
  }

  if (name == "convert:base-dialect-in") {
    const auto actual{base_dialect_name(site.base_dialect)};
    for (const auto &argument : arguments) {
      if (argument.to_string() == actual) {
        return true;
      }
    }

    return false;
  }

  if (name == "convert:promoted-keyword-is-author-data") {
    return !arguments.empty() && arguments.front().is_string() &&
           promoted_keyword_is_author_data(schema,
                                           arguments.front().to_string());
  }

  if (name == "convert:has-pending-draft-4-pattern") {
    return has_pending_draft_4_pattern(schema, site.dialect);
  }

  if (name == "convert:has-pending-draft-3-pattern") {
    return has_pending_draft_3_pattern(schema, site.dialect);
  }

  // Draft 3's `required` is a question only the enclosing `properties` can
  // answer, so one anywhere else is stray and simply goes
  if (name == "convert:has-stray-required-boolean") {
    if (!schema.is_object()) {
      return false;
    }

    if (declares_dialect_out_of_reach(schema, DRAFT_3_DIALECT)) {
      return false;
    }

    const auto *required{schema.try_at("required")};
    if (required == nullptr || !required->is_boolean()) {
      return false;
    }

    return site.pointer.size() < 2 ||
           !site.pointer.at(site.pointer.size() - 2).is_property() ||
           site.pointer.at(site.pointer.size() - 2).to_property() !=
               "properties";
  }

  if (name == "convert:draft3-shape") {
    if (arguments.size() != 2 || !arguments.front().is_object()) {
      throw TransformError{"A Draft 3 shape takes an object and a shape name"};
    }

    const auto &term{arguments.front()};
    const auto shape{arguments.back().to_string()};

    if (shape == "type-vacuous") {
      const auto *value{term.try_at("type")};
      if (value == nullptr) {
        return false;
      }

      if (value->is_string()) {
        return draft_3_names_every_instance(*value);
      }

      return value->is_array() && !draft_3_holds_subschema(*value) &&
             std::ranges::any_of(value->as_array(),
                                 draft_3_names_every_instance);
    }

    if (shape == "type-has-subschema") {
      const auto *value{term.try_at("type")};
      return value != nullptr && draft_3_holds_subschema(*value);
    }

    if (shape == "disallow-collapses") {
      const auto *value{term.try_at("disallow")};
      if (value == nullptr) {
        return false;
      }

      if (value->is_string()) {
        return draft_3_names_every_instance(*value);
      }

      return value->is_array() && !draft_3_holds_subschema(*value) &&
             std::ranges::any_of(value->as_array(),
                                 draft_3_names_every_instance);
    }

    if (shape == "disallow-names-only") {
      const auto *value{term.try_at("disallow")};
      return value != nullptr &&
             (value->is_string() ||
              (value->is_array() && !draft_3_holds_subschema(*value)));
    }

    if (shape == "disallow-has-subschema") {
      const auto *value{term.try_at("disallow")};
      return value != nullptr && draft_3_holds_subschema(*value);
    }

    if (shape == "disallow-is-schema") {
      const auto *value{term.try_at("disallow")};
      return value != nullptr && value->is_object();
    }

    if (shape == "liftable-required") {
      const auto *properties{term.try_at("properties")};
      if (properties == nullptr || !properties->is_object()) {
        return false;
      }

      return std::ranges::any_of(
          properties->as_object(), [](const auto &entry) -> bool {
            return entry.second.is_object() &&
                   entry.second.defines("required") &&
                   entry.second.at("required").is_boolean();
          });
    }

    if (shape == "normalizable-dependencies") {
      const auto *value{term.try_at("dependencies")};
      if (value == nullptr || !value->is_object()) {
        return false;
      }

      return std::ranges::any_of(
          value->as_object(), [](const auto &entry) -> bool {
            return entry.second.is_string() ||
                   (entry.second.is_array() &&
                    (entry.second.empty() ||
                     draft_3_has_repeated_name(entry.second)));
          });
    }

    if (shape == "dependencies-empty-after-normalizing") {
      const auto *value{term.try_at("dependencies")};
      return value != nullptr && value->is_object() &&
             draft_3_normalize_dependencies(*value).empty();
    }

    throw TransformError{"Unknown Draft 3 shape"};
  }

  // A Draft 7 `$id` may carry a fragment that 2019-09 splits into an
  // `$anchor`. Which of the four shapes it has decides what moves, and a URI
  // is not something the language can take apart
  if (name == "convert:id-fragment-shape") {
    if (arguments.size() != 2 || !arguments.front().is_object()) {
      throw TransformError{
          "An identifier shape takes an object and a shape name"};
    }

    const auto *identifier{arguments.front().try_at("$id")};
    if (identifier == nullptr || !identifier->is_string()) {
      return false;
    }

    const sourcemeta::core::URI uri{identifier->to_string()};
    const auto fragment{uri.fragment()};
    const auto shape{arguments.back().to_string()};
    if (shape == "present") {
      return fragment.has_value();
    }

    if (!fragment.has_value()) {
      return false;
    }

    if (shape == "fragment-only") {
      return uri.is_fragment_only();
    }

    if (shape == "plain-name") {
      return is_plain_name_anchor(fragment.value());
    }

    if (shape == "empty") {
      return fragment.value().empty();
    }

    if (shape == "recomposes") {
      return uri.recompose_without_fragment().has_value();
    }

    throw TransformError{"Unknown identifier shape"};
  }

  if (name == "convert:starts-with") {
    if (arguments.size() != 2 || !arguments.front().is_string() ||
        !arguments.back().is_string()) {
      throw TransformError{"A prefix test takes two strings"};
    }

    return arguments.front().to_string().starts_with(
        arguments.back().to_string());
  }

  // What the caller finally asked for, which one rung has to read because
  // Draft 4 cannot express what the target may still name
  // Whether a member the OpenAPI 3.0 Schema Object names goes across as the
  // keyword it was, which only the target the caller asked for can answer
  if (name == "convert:openapi30-carries") {
    if (arguments.size() != 2 || !arguments.front().is_object() ||
        !arguments.back().is_string()) {
      throw TransformError{"A carry test takes an object and a keyword"};
    }

    const auto keeps{[&settings](const char *const flag) -> bool {
      const auto *value{settings.try_at(sourcemeta::core::JSON::String{flag})};
      return value != nullptr && value->is_boolean() && value->to_boolean();
    }};

    const auto keyword{arguments.back().to_string()};
    if (keyword == "readOnly" || keyword == "writeOnly") {
      return keeps("read-only");
    }

    if (keyword == "deprecated") {
      return keeps("deprecated");
    }

    if (!keeps("openapi-annotations")) {
      return false;
    }

    if (keyword == "discriminator") {
      const auto &value{arguments.front().at(keyword)};
      return openapi_3_0_expressible_discriminator(value,
                                                   keeps("default-mapping")) &&
             openapi_3_0_mapping_survives(value);
    }

    return keyword == "xml" || keyword == "externalDocs" ||
           keyword == "example";
  }

  if (name == "convert:openapi30-shape") {
    if (arguments.size() != 2 || !arguments.front().is_object()) {
      throw TransformError{
          "An OpenAPI 3.0 shape takes an object and a shape name"};
    }

    const auto &term{arguments.front()};
    const auto shape{arguments.back().to_string()};

    if (shape == "ignored-sibling") {
      if (!term.defines("$ref")) {
        return false;
      }

      return std::ranges::any_of(
          term.as_object(), [](const auto &entry) -> bool {
            return entry.first != "$ref" && entry.first != "$schema" &&
                   !entry.first.starts_with("x-");
          });
    }

    if (shape == "pending-shape") {
      return openapi_3_0_holds_pending_shape(term);
    }

    if (shape == "promoted-keyword") {
      return std::ranges::any_of(
          OPENAPI_3_0_PROMOTED_BY_DRAFT_4, [&term](const auto keyword) -> bool {
            return term.defines(sourcemeta::core::JSON::String{keyword});
          });
    }

    if (shape == "openapi-3-0-override") {
      const auto *value{term.try_at(DIALECT_OVERRIDE_KEYWORD)};
      return value != nullptr && value->is_string() &&
             names_openapi_3_0_dialect(value->to_string());
    }

    if (shape == "movable-definitions") {
      const auto *container{
          term.try_at(sourcemeta::core::JSON::String{OPENAPI_3_0_DEFINITIONS})};
      if (container == nullptr || !container->is_object()) {
        return false;
      }

      return std::ranges::any_of(
          container->as_object(), [](const auto &entry) -> bool {
            return entry.second.is_object() || entry.second.is_boolean();
          });
    }

    throw TransformError{"Unknown OpenAPI 3.0 shape"};
  }

  if (name == "convert:setting") {
    if (arguments.empty() || !arguments.front().is_string()) {
      throw TransformError{"A setting takes a name"};
    }

    const auto *value{settings.try_at(arguments.front().to_string())};
    return value != nullptr && value->is_boolean() && value->to_boolean();
  }

  if (name == "convert:is-own-dialect-override") {
    return !arguments.empty() && is_own_dialect_override(arguments.front());
  }

  if (name == "convert:names-ladder-dialect") {
    return !arguments.empty() && arguments.front().is_string() &&
           names_ladder_dialect(arguments.front().to_string());
  }

  return std::nullopt;
}

/// The terms a rule may ask the host to build
inline auto term_for(const std::string_view name,
                     const std::vector<sourcemeta::core::JSON> &arguments)
    -> sourcemeta::core::JSON {
  // Where a keyword goes when a rename has to carry it across as the
  // author data it was. A name already taken gains another prefix, and a
  // caller may name spellings that are not free either, such as the two
  // that core reads
  if (name == "convert:shadow-pointer") {
    if (arguments.size() < 2 || !arguments.front().is_object() ||
        !arguments.at(1).is_string()) {
      throw TransformError{"A shadow pointer takes an object and a keyword"};
    }

    auto candidate{"x-" + arguments.at(1).to_string()};
    const auto taken{[&arguments, &candidate]() -> bool {
      if (arguments.front().defines(candidate)) {
        return true;
      }

      for (std::size_t index = 2; index < arguments.size(); index += 1) {
        if (arguments.at(index).to_string() == candidate) {
          return true;
        }
      }

      return false;
    }};

    while (taken()) {
      candidate.insert(0, "x-");
    }

    return sourcemeta::core::JSON{
        sourcemeta::core::to_string(sourcemeta::core::Pointer{candidate})};
  }

  if (name == "convert:draft3-type-branches" ||
      name == "convert:draft3-disallow-branches") {
    const auto *const keyword{
        name == "convert:draft3-type-branches" ? "type" : "disallow"};
    return draft_3_type_branches(arguments.front().at(keyword));
  }

  if (name == "convert:draft3-lift-required") {
    return draft_3_lift_required(arguments.front());
  }

  if (name == "convert:draft3-normalize-dependencies") {
    return draft_3_normalize_dependencies(arguments.front().at("dependencies"));
  }

  // The value of a member, so that a template can place what the term
  // already holds without the match having bound it
  if (name == "convert:member") {
    if (arguments.size() != 2 || !arguments.front().is_object() ||
        !arguments.back().is_string()) {
      throw TransformError{"A member lookup takes an object and a name"};
    }

    const auto *value{arguments.front().try_at(arguments.back().to_string())};
    if (value == nullptr) {
      throw TransformError{"A member lookup names a member that is not there"};
    }

    return *value;
  }

  // The three places the OpenAPI 3.0 Schema Object is looser than Draft 4,
  // folded in the order the rung needs: `nullable` before the annotations
  // are shadowed, so that one it consumes is gone and one it declines is
  // still there to be shadowed with them
  if (name == "convert:openapi30-fold") {
    auto result{arguments.front()};
    fold_nullable_into_type(result);
    deduplicate_enum(result);
    fold_empty_applicators(result);
    return result;
  }

  // 2020-12 keeps under `$defs` a schema it does not apply, and a name
  // already taken there gains a prefix rather than overwriting
  if (name == "convert:defs-pointer") {
    if (arguments.size() != 2 || !arguments.front().is_object() ||
        !arguments.back().is_string()) {
      throw TransformError{"A defs pointer takes an object and a keyword"};
    }

    auto candidate{arguments.back().to_string()};
    const auto *defs{arguments.front().is_object()
                         ? arguments.front().try_at("$defs")
                         : nullptr};
    while (defs != nullptr && defs->is_object() && defs->defines(candidate)) {
      candidate.insert(0, "x-");
    }

    return sourcemeta::core::JSON{sourcemeta::core::to_string(
        sourcemeta::core::Pointer{"$defs", candidate})};
  }

  // Where the next branch of an applicator array goes, which depends on how
  // many it already holds
  if (name == "convert:slot-pointer") {
    if (arguments.size() != 3 || !arguments.front().is_object() ||
        !arguments.at(1).is_string() || !arguments.back().is_string()) {
      throw TransformError{
          "A slot pointer takes an object, a keyword and a suffix"};
    }

    const auto keyword{arguments.at(1).to_string()};
    const auto *branches{arguments.front().is_object()
                             ? arguments.front().try_at(keyword)
                             : nullptr};
    const auto slot{
        branches != nullptr && branches->is_array() ? branches->size() : 0};
    return sourcemeta::core::JSON{"/" + keyword + "/" + std::to_string(slot) +
                                  arguments.back().to_string()};
  }

  if (name == "convert:openapi30-boolean-schema") {
    return openapi_3_0_as_object_schema(arguments.front());
  }

  if (name == "convert:id-fragment" || name == "convert:id-without-fragment") {
    if (arguments.empty() || !arguments.front().is_object()) {
      throw TransformError{"An identifier part takes an object"};
    }

    const sourcemeta::core::URI uri{arguments.front().at("$id").to_string()};
    if (name == "convert:id-fragment") {
      return sourcemeta::core::JSON{
          sourcemeta::core::JSON::String{uri.fragment().value()}};
    }

    return sourcemeta::core::JSON{uri.recompose_without_fragment().value()};
  }

  throw TransformError{"Unknown convert question"};
}

/// One way to ask the host something. A name the verdict chain knows answers
/// with a verdict, which a pattern reads as one, and every other name answers
/// with the term it builds
inline auto make_host(const sourcemeta::core::JSON &schema,
                      const sourcemeta::core::SchemaVocabularies &vocabularies,
                      const Site &site, const sourcemeta::core::JSON &settings)
    -> TransformHost {
  return [&schema, &vocabularies, &site,
          &settings](const std::string_view name,
                     const std::vector<sourcemeta::core::JSON> &arguments)
             -> sourcemeta::core::JSON {
    const auto answer{
        verdict_for(name, arguments, schema, vocabularies, site, settings)};
    if (answer.has_value()) {
      return sourcemeta::core::JSON{answer.value()};
    }

    return term_for(name, arguments);
  };
}

/// Where a query goes for its answer. One analysis per rule, cleared when the
/// driver starts a pass, so that what a position settled is still there when
/// its turn to write comes round
struct QuerySource {
  Query answer;
  std::function<void()> begin_pass;
};

inline auto make_query() -> QuerySource {
  const auto analysis{std::make_shared<Analysis201909To202012>()};
  return {
      .answer =
          [analysis](const std::string_view name,
                     const std::vector<sourcemeta::core::JSON> &arguments,
                     const QueryContext &context) -> sourcemeta::core::JSON {
        analysis->plan(context.schema, context.root, context.vocabularies,
                       context.frame, context.location, context.site,
                       context.walker, context.resolver);

        // Whether this resource still has an anchor Draft 6 would
        // reject, which the rung that moves the dialect waits on
        if (name == "convert:draft-4-anchors-pending") {
          return sourcemeta::core::JSON{
              has_unsanitized_draft_4_anchor(context.root, context.frame)};
        }

        // This document with every Draft 4 anchor Draft 6 would reject
        // renamed, and the references naming them moved. Null where
        // there is nothing to do, or anywhere but the document root,
        // which is the only position that may write across the whole of it
        if (name == "convert:sanitized-draft-4-anchors") {
          if (!context.site.pointer.empty() || !context.schema.is_object()) {
            return sourcemeta::core::JSON{nullptr};
          }

          auto document{context.schema};
          if (!sanitize_draft_4_anchors(document, context.frame)) {
            return sourcemeta::core::JSON{nullptr};
          }

          return document;
        }

        // Whether the dialect this position would read as without its
        // marker is the one the marker names, which only the resource
        // around it can say
        if (name == "convert:marker-says-nothing") {
          if (!context.location.parent.has_value() ||
              !context.schema.is_object()) {
            return sourcemeta::core::JSON{false};
          }

          const auto *marker{context.schema.try_at(DIALECT_OVERRIDE_KEYWORD)};
          if (marker == nullptr || !marker->is_string()) {
            return sourcemeta::core::JSON{false};
          }

          const auto enclosing{
              context.frame.traverse(context.location.parent.value())};
          return sourcemeta::core::JSON{
              enclosing.has_value() &&
              without_empty_fragment(enclosing.value().get().dialect) ==
                  without_empty_fragment(marker->to_string())};
        }

        if (name == "convert:2019-09-fact") {
          return analysis->fact(context.site, arguments.front().to_string());
        }

        if (name == "convert:2019-09-sanitized") {
          return analysis->sanitized(context.schema, context.site);
        }

        if (name == "convert:2019-09-vocabulary") {
          return Analysis201909To202012::vocabulary(context.schema);
        }

        throw TransformError{"Unknown convert query"};
      },
      .begin_pass = [analysis]() -> void { analysis->begin_pass(); }};
}

/// A rule whose condition and transform are read from JSON rather than
/// written
class TemplateRule final : public SchemaTransformRule {
public:
  TemplateRule(
      sourcemeta::core::JSON definition,
      sourcemeta::core::JSON settings = sourcemeta::core::JSON::make_object())
      : SchemaTransformRule{definition.at("name").to_string()},
        definition_{std::move(definition)}, settings_{std::move(settings)} {}

  auto begin_pass() const -> void override {
    this->planned_.clear();
    this->queries_.begin_pass();
  }

  auto plan(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &root,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const Site &site, const sourcemeta::core::SchemaWalker &walker,
            const sourcemeta::core::SchemaResolver &resolver) const
      -> void override {
    // What a query answers is settled here, while the frame still describes
    // the document, and kept against the position that asked. The driver
    // gathers every match in a pass before applying any of them, so a rule
    // that answered for one position must still have that answer when its
    // turn to write comes round
    if (this->definition_.defines("queries")) {
      const QueryContext context{.schema = schema,
                                 .root = root,
                                 .vocabularies = vocabularies,
                                 .frame = frame,
                                 .location = location,
                                 .site = site,
                                 .walker = walker,
                                 .resolver = resolver};
      TransformBindings answers;
      for (const auto &entry : this->definition_.at("queries").as_object()) {
        std::vector<sourcemeta::core::JSON> arguments;
        if (entry.second.defines("args")) {
          for (const auto &argument : entry.second.at("args").as_array()) {
            arguments.push_back(argument);
          }
        }

        answers.insert_or_assign(
            entry.first,
            TransformBinding{
                .value = this->queries_.answer(
                    entry.second.at("name").to_string(), arguments, context),
                .pointer = sourcemeta::core::Pointer{}});
      }

      this->planned_.insert_or_assign(site.pointer, std::move(answers));
    }
  }

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const Site &site, const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    this->bindings_.clear();
    this->relocations_.clear();
    this->vocabularies_ = vocabularies;
    const auto answers{this->planned_.find(site.pointer)};
    if (answers != this->planned_.cend()) {
      this->bindings_ = answers->second;
    }

    return transform_match(
        this->definition_.at("match"), schema,
        make_host(schema, vocabularies, site, this->settings_),
        this->bindings_);
  }

  auto transform(sourcemeta::core::JSON &schema, const Site &site) const
      -> void override {
    const auto trace{transform_apply(
        this->definition_.at("build"), schema, this->bindings_,
        make_host(schema, this->vocabularies_, site, this->settings_))};
    this->relocations_ = trace.relocations;
  }

  [[nodiscard]] auto relocations() const -> std::vector<Relocation> override {
    return {this->relocations_.cbegin(), this->relocations_.cend()};
  }

private:
  sourcemeta::core::JSON definition_;
  sourcemeta::core::JSON settings_;
  QuerySource queries_{make_query()};
  mutable std::map<sourcemeta::core::Pointer, TransformBindings> planned_;
  mutable TransformBindings bindings_;
  mutable std::vector<TransformRelocation> relocations_;
  mutable sourcemeta::core::SchemaVocabularies vocabularies_;
};

#endif
