class UpgradeDraft4ToDraft6 final : public SchemaTransformRule {
public:
  using reframe_after_transform = std::true_type;
  UpgradeDraft4ToDraft6()
      : SchemaTransformRule{"upgrade_draft_4_to_draft_6"} {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &root,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const -> bool override {
    this->sanitize_pending_ = false;

    ONLY_CONTINUE_IF(
        vocabularies.contains(SchemaVocabularies::Known::JSON_SCHEMA_DRAFT_4) &&
        schema.is_object());

    const bool is_resource_scope =
        location.type ==
            sourcemeta::core::SchemaFrame::LocationType::Resource ||
        location.pointer.empty();

    // A reference may name an anchor in a resource other than the one it sits
    // in, so the renaming has to be driven from the outermost resource whose
    // subtree needs it. Firing per resource would let an inner resource rename
    // its anchors first, leaving an outer reference pointing at a name that no
    // longer exists and nothing left to tell it so
    bool sanitization_branch =
        is_resource_scope &&
        subtree_needs_anchor_sanitization(schema, location, root, frame);

    // An outer resource whose subtree needs sanitization covers this one too,
    // so the renaming is left to it and only to it. This resource still has
    // its own work to do, and the guard below holds that back until the
    // anchors have settled
    if (sanitization_branch &&
        has_strict_ancestor_resource_scope(location, frame)) {
      sanitization_branch = false;
    }

    const bool other_branch = has_pending_draft_4_pattern(schema);

    const bool root_via_default_dialect =
        location.pointer.empty() && !schema.defines("$schema");

    ONLY_CONTINUE_IF(sanitization_branch || other_branch ||
                     root_via_default_dialect);

    if (!sanitization_branch && other_branch &&
        enclosing_resource_has_pending_sanitization(location, root, frame)) {
      return false;
    }

    if (!sanitization_branch) {
      if (frame.any_subschema_under(
              location.pointer,
              [&root](const sourcemeta::core::SchemaFrame::Location &entry)
                  -> bool {
                const auto entry_pointer{
                    sourcemeta::core::to_pointer(entry.pointer)};
                const auto &entry_schema{
                    sourcemeta::core::get(root, entry_pointer)};
                if (entry_schema.is_object() && entry_schema.defines("$ref")) {
                  return false;
                }

                return has_pending_draft_4_pattern(entry_schema);
              })) {
        return false;
      }
    }

    this->sanitize_pending_ = sanitization_branch;
    if (sanitization_branch) {
      this->subtree_renames_ = collect_subtree_renames(location, root, frame);
    }

    return true;
  }

  auto transform(sourcemeta::core::JSON &schema) const -> void override {
    if (this->sanitize_pending_) {
      std::optional<std::string> resource_base;
      if (schema.defines("id") && schema.at("id").is_string()) {
        resource_base =
            resolved_resource_base(schema.at("id").to_string(), std::nullopt);
      }

      const auto root_renames{build_resource_rename_map(schema)};
      apply_anchor_renames_in_resource(schema, true, this->subtree_renames_,
                                       resource_base, &root_renames);
      // Bumping the dialect is what stops `id` from identifying anything, so
      // it waits for every identifier below to have moved. The renaming pass
      // reaches into sub-resources, so this has to look there as well
      if (subtree_has_pending_pattern(schema, true, true)) {
        return;
      }
    }

    if (schema.defines("id") && schema.at("id").is_string()) {
      schema.rename("id", "$id");
    }

    if (schema.defines("exclusiveMinimum") &&
        schema.at("exclusiveMinimum").is_boolean()) {
      const bool exclusive{schema.at("exclusiveMinimum").to_boolean()};
      schema.erase("exclusiveMinimum");
      if (exclusive && schema.defines("minimum") &&
          schema.at("minimum").is_number()) {
        schema.rename("minimum", "exclusiveMinimum");
      }
    }

    if (schema.defines("exclusiveMaximum") &&
        schema.at("exclusiveMaximum").is_boolean()) {
      const bool exclusive{schema.at("exclusiveMaximum").to_boolean()};
      schema.erase("exclusiveMaximum");
      if (exclusive && schema.defines("maximum") &&
          schema.at("maximum").is_number()) {
        schema.rename("maximum", "exclusiveMaximum");
      }
    }

    if (schema.defines("$schema") && schema.at("$schema").is_string() &&
        schema.at("$schema").to_string() == DRAFT_4_URL) {
      schema.assign("$schema", sourcemeta::core::JSON{DRAFT_6_URL});
      drop_dialect_overrides(schema, DRAFT_6_URL, this->subschemas());
    } else {
      mark_dialect_override(schema, DRAFT_6_URL);
    }
  }

private:
  using RenameTable = std::map<std::string, std::map<std::string, std::string>>;

  // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
  static inline const std::string DRAFT_4_URL{
      "http://json-schema.org/draft-04/schema#"};
  // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
  static inline const std::string DRAFT_6_URL{
      "http://json-schema.org/draft-06/schema#"};
  // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
  static inline const std::array<std::string_view, 4> PROMOTED_KEYWORDS{
      {"const", "contains", "propertyNames", "examples"}};

  mutable bool sanitize_pending_{false};
  mutable RenameTable subtree_renames_;

  static auto
  has_pending_draft_4_pattern(const sourcemeta::core::JSON &subschema) -> bool {
    if (!subschema.is_object() ||
        declares_newer_dialect(subschema, DRAFT_4_URL)) {
      return false;
    }

    if (subschema.defines("$schema") && subschema.at("$schema").is_string() &&
        subschema.at("$schema").to_string() == DRAFT_4_URL) {
      return true;
    }

    if (subschema.defines("id") && subschema.at("id").is_string()) {
      const auto fragment{extract_id_fragment(subschema.at("id"))};
      if (!fragment.has_value() || fragment.value().empty() ||
          is_strict_plain_name(fragment.value())) {
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

    for (const auto &keyword : PROMOTED_KEYWORDS) {
      if (subschema.defines(keyword)) {
        return true;
      }
    }

    return has_stray_identifier(subschema);
  }

  // Draft 4 does not know `$id`, so one written there is inert data that
  // Draft 6 would read as the identifier, and it has to be shadowed before
  // `id` takes that name. It is also the one Draft 6 addition this rule
  // produces itself, so unlike every other promoted keyword its presence only
  // means work is pending while the subschema is still on Draft 4 or older
  static auto has_stray_identifier(const sourcemeta::core::JSON &subschema)
      -> bool {
    return subschema.defines("$id") &&
           dialect_position(declared_dialect(subschema)) <=
               dialect_position(DRAFT_4_URL);
  }

  static auto is_strict_plain_name_first_char(const char character) -> bool {
    return (character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z');
  }

  static auto is_strict_plain_name_body_char(const char character) -> bool {
    return (character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z') ||
           (character >= '0' && character <= '9') || character == '_' ||
           character == ':' || character == '.' || character == '-';
  }

  static auto is_strict_plain_name(const std::string_view fragment) -> bool {
    if (fragment.empty()) {
      return false;
    }
    if (!is_strict_plain_name_first_char(fragment.front())) {
      return false;
    }
    for (std::size_t index{1}; index < fragment.size(); ++index) {
      if (!is_strict_plain_name_body_char(fragment[index])) {
        return false;
      }
    }
    return true;
  }

  static auto sanitize_anchor_name(const std::string_view original,
                                   const std::set<std::string> &existing_names)
      -> std::string {
    static const AnchorCharPolicy POLICY{
        .is_valid_first = &is_strict_plain_name_first_char,
        .is_valid_body = &is_strict_plain_name_body_char};
    return sanitize_anchor_with_policy(original, existing_names, POLICY);
  }

  static auto extract_id_fragment(const sourcemeta::core::JSON &id_value)
      -> std::optional<std::string> {
    if (!id_value.is_string()) {
      return std::nullopt;
    }
    const sourcemeta::core::URI uri{id_value.to_string()};
    const auto fragment{uri.fragment()};
    if (!fragment.has_value()) {
      return std::nullopt;
    }
    return std::string{fragment.value()};
  }

  static auto
  subschema_id_fragment_is_invalid(const sourcemeta::core::JSON &subschema)
      -> bool {
    if (!subschema.is_object() || !subschema.defines("id") ||
        !subschema.at("id").is_string()) {
      return false;
    }
    const auto fragment{extract_id_fragment(subschema.at("id"))};
    if (!fragment.has_value() || fragment.value().empty()) {
      return false;
    }
    return !is_strict_plain_name(fragment.value());
  }

  static auto
  subschema_starts_sub_resource(const sourcemeta::core::JSON &subschema)
      -> bool {
    if (!subschema.is_object() || !subschema.defines("id") ||
        !subschema.at("id").is_string()) {
      return false;
    }
    const sourcemeta::core::URI uri{subschema.at("id").to_string()};
    if (uri.is_fragment_only()) {
      return false;
    }
    const auto without_fragment{uri.recompose_without_fragment()};
    return without_fragment.has_value() && !without_fragment.value().empty();
  }

  static auto collect_resource_anchors(const sourcemeta::core::JSON &subschema,
                                       const bool is_root,
                                       std::set<std::string> &result) -> void {
    if (!subschema.is_object()) {
      return;
    }

    if (!is_root && subschema_starts_sub_resource(subschema)) {
      return;
    }

    if (subschema.defines("id") && subschema.at("id").is_string()) {
      const auto fragment{extract_id_fragment(subschema.at("id"))};
      if (fragment.has_value() && !fragment.value().empty()) {
        result.insert(fragment.value());
      }
    }

    for (const std::string_view object_keyword :
         {"definitions", "properties", "patternProperties", "dependencies"}) {
      if (subschema.defines(object_keyword) &&
          subschema.at(object_keyword).is_object()) {
        for (const auto &entry : subschema.at(object_keyword).as_object()) {
          collect_resource_anchors(entry.second, false, result);
        }
      }
    }

    for (const std::string_view array_keyword : {"allOf", "anyOf", "oneOf"}) {
      if (subschema.defines(array_keyword) &&
          subschema.at(array_keyword).is_array()) {
        for (const auto &item : subschema.at(array_keyword).as_array()) {
          collect_resource_anchors(item, false, result);
        }
      }
    }

    for (const std::string_view single_keyword :
         {"additionalProperties", "additionalItems", "not"}) {
      if (subschema.defines(single_keyword)) {
        collect_resource_anchors(subschema.at(single_keyword), false, result);
      }
    }

    if (subschema.defines("items")) {
      const auto &items{subschema.at("items")};
      if (items.is_array()) {
        for (const auto &item : items.as_array()) {
          collect_resource_anchors(item, false, result);
        }
      } else {
        collect_resource_anchors(items, false, result);
      }
    }
  }

  static auto collect_invalid_anchors(const sourcemeta::core::JSON &subschema,
                                      const bool is_root,
                                      std::vector<std::string> &result)
      -> void {
    if (!subschema.is_object()) {
      return;
    }

    if (!is_root && subschema_starts_sub_resource(subschema)) {
      return;
    }

    if (subschema_id_fragment_is_invalid(subschema)) {
      const auto fragment{extract_id_fragment(subschema.at("id"))};
      result.push_back(fragment.value());
    }

    for (const std::string_view object_keyword :
         {"definitions", "properties", "patternProperties", "dependencies"}) {
      if (subschema.defines(object_keyword) &&
          subschema.at(object_keyword).is_object()) {
        for (const auto &entry : subschema.at(object_keyword).as_object()) {
          collect_invalid_anchors(entry.second, false, result);
        }
      }
    }

    for (const std::string_view array_keyword : {"allOf", "anyOf", "oneOf"}) {
      if (subschema.defines(array_keyword) &&
          subschema.at(array_keyword).is_array()) {
        for (const auto &item : subschema.at(array_keyword).as_array()) {
          collect_invalid_anchors(item, false, result);
        }
      }
    }

    for (const std::string_view single_keyword :
         {"additionalProperties", "additionalItems", "not"}) {
      if (subschema.defines(single_keyword)) {
        collect_invalid_anchors(subschema.at(single_keyword), false, result);
      }
    }

    if (subschema.defines("items")) {
      const auto &items{subschema.at("items")};
      if (items.is_array()) {
        for (const auto &item : items.as_array()) {
          collect_invalid_anchors(item, false, result);
        }
      } else {
        collect_invalid_anchors(items, false, result);
      }
    }
  }

  static auto
  build_resource_rename_map(const sourcemeta::core::JSON &resource_root)
      -> std::map<std::string, std::string> {
    std::set<std::string> existing;
    collect_resource_anchors(resource_root, true, existing);

    std::vector<std::string> invalid;
    collect_invalid_anchors(resource_root, true, invalid);

    std::map<std::string, std::string> renames;
    std::set<std::string> in_use{existing};
    for (const auto &original : invalid) {
      if (renames.contains(original)) {
        continue;
      }
      in_use.erase(original);
      const auto sanitized{sanitize_anchor_name(original, in_use)};
      renames.emplace(original, sanitized);
      in_use.insert(sanitized);
    }
    return renames;
  }

  static auto
  subtree_has_pending_pattern(const sourcemeta::core::JSON &subschema,
                              const bool is_root, const bool cross_resources)
      -> bool {
    if (!subschema.is_object()) {
      return false;
    }
    if (!is_root && !cross_resources &&
        subschema_starts_sub_resource(subschema)) {
      return false;
    }
    if (!is_root && has_pending_draft_4_pattern(subschema)) {
      return true;
    }

    for (const std::string_view object_keyword :
         {"definitions", "properties", "patternProperties", "dependencies"}) {
      if (subschema.defines(object_keyword) &&
          subschema.at(object_keyword).is_object()) {
        for (const auto &entry : subschema.at(object_keyword).as_object()) {
          if (subtree_has_pending_pattern(entry.second, false,
                                          cross_resources)) {
            return true;
          }
        }
      }
    }

    for (const std::string_view array_keyword : {"allOf", "anyOf", "oneOf"}) {
      if (subschema.defines(array_keyword) &&
          subschema.at(array_keyword).is_array()) {
        for (const auto &item : subschema.at(array_keyword).as_array()) {
          if (subtree_has_pending_pattern(item, false, cross_resources)) {
            return true;
          }
        }
      }
    }

    for (const std::string_view single_keyword :
         {"additionalProperties", "additionalItems", "not"}) {
      if (subschema.defines(single_keyword)) {
        if (subtree_has_pending_pattern(subschema.at(single_keyword), false,
                                        cross_resources)) {
          return true;
        }
      }
    }

    if (subschema.defines("items")) {
      const auto &items{subschema.at("items")};
      if (items.is_array()) {
        for (const auto &item : items.as_array()) {
          if (subtree_has_pending_pattern(item, false, cross_resources)) {
            return true;
          }
        }
      } else if (subtree_has_pending_pattern(items, false, cross_resources)) {
        return true;
      }
    }

    return false;
  }

  static auto apply_anchor_renames_in_resource(
      sourcemeta::core::JSON &subschema, const bool is_root,
      const RenameTable &table, const std::optional<std::string> &resource_base,
      const std::map<std::string, std::string> *own_renames) -> void {
    if (!subschema.is_object()) {
      return;
    }

    // A sub-resource is walked rather than skipped, under its own base and its
    // own renames, so that one pass from the outermost resource leaves every
    // anchor and every reference in the subtree agreeing with each other
    // The resource this pass started from carries its map directly, because a
    // resource that never named itself has no URI to look one up by
    auto base{resource_base};
    const auto *renames_for_base{own_renames};
    if (!is_root && subschema_starts_sub_resource(subschema)) {
      base =
          resolved_resource_base(subschema.at("id").to_string(), resource_base);
      renames_for_base = nullptr;
      if (base.has_value()) {
        const auto match{table.find(base.value())};
        if (match != table.cend()) {
          renames_for_base = &match->second;
        }
      }
    }

    if (renames_for_base != nullptr && subschema.defines("id") &&
        subschema.at("id").is_string()) {
      const auto &renames{*renames_for_base};
      const auto &id_string{subschema.at("id").to_string()};
      const sourcemeta::core::URI uri{id_string};
      const auto fragment{uri.fragment()};
      if (fragment.has_value() && !fragment.value().empty()) {
        const auto rename_iter{renames.find(std::string{fragment.value()})};
        if (rename_iter != renames.end()) {
          if (uri.is_fragment_only()) {
            subschema.assign("id",
                             sourcemeta::core::JSON{"#" + rename_iter->second});
          } else {
            const auto without_fragment{uri.recompose_without_fragment()};
            subschema.assign(
                "id", sourcemeta::core::JSON{(without_fragment.has_value()
                                                  ? without_fragment.value()
                                                  : std::string{}) +
                                             "#" + rename_iter->second});
          }
        }
      }
    }

    if (subschema.defines("$ref") && subschema.at("$ref").is_string()) {
      rewrite_anchor_reference(subschema, table, base, renames_for_base);
    }

    for (const std::string_view object_keyword :
         {"definitions", "properties", "patternProperties", "dependencies"}) {
      if (subschema.defines(object_keyword) &&
          subschema.at(object_keyword).is_object()) {
        std::vector<std::string> keys;
        keys.reserve(subschema.at(object_keyword).size());
        for (const auto &entry : subschema.at(object_keyword).as_object()) {
          keys.push_back(entry.first);
        }
        for (const auto &key : keys) {
          apply_anchor_renames_in_resource(subschema.at(object_keyword).at(key),
                                           false, table, base,
                                           renames_for_base);
        }
      }
    }

    for (const std::string_view array_keyword : {"allOf", "anyOf", "oneOf"}) {
      if (subschema.defines(array_keyword) &&
          subschema.at(array_keyword).is_array()) {
        auto &array_value{subschema.at(array_keyword)};
        for (std::size_t index{0}; index < array_value.size(); ++index) {
          apply_anchor_renames_in_resource(array_value.at(index), false, table,
                                           base, renames_for_base);
        }
      }
    }

    for (const std::string_view single_keyword :
         {"additionalProperties", "additionalItems", "not"}) {
      if (subschema.defines(single_keyword)) {
        apply_anchor_renames_in_resource(subschema.at(single_keyword), false,
                                         table, base, renames_for_base);
      }
    }

    if (subschema.defines("items")) {
      auto &items{subschema.at("items")};
      if (items.is_array()) {
        for (std::size_t index{0}; index < items.size(); ++index) {
          apply_anchor_renames_in_resource(items.at(index), false, table, base,
                                           renames_for_base);
        }
      } else {
        apply_anchor_renames_in_resource(items, false, table, base,
                                         renames_for_base);
      }
    }
  }

  // Which resource a reference names decides whose renames apply to it: its
  // own when the base resolves back to the resource the reference sits in, and
  // another resource's when the base names that one instead. Only the fragment
  // is rewritten, so a relative base keeps the spelling the author chose
  static auto rewrite_anchor_reference(
      sourcemeta::core::JSON &subschema, const RenameTable &table,
      const std::optional<std::string> &resource_base,
      const std::map<std::string, std::string> *own_renames) -> void {
    const sourcemeta::core::URI ref_uri{subschema.at("$ref").to_string()};
    const auto fragment{ref_uri.fragment()};
    if (!fragment.has_value() || fragment.value().empty()) {
      return;
    }

    const std::string name{fragment.value()};
    if (ref_uri.is_fragment_only()) {
      if (own_renames == nullptr) {
        return;
      }

      const auto match{own_renames->find(name)};
      if (match != own_renames->cend()) {
        subschema.assign("$ref", sourcemeta::core::JSON{"#" + match->second});
      }

      return;
    }

    const auto without_fragment{ref_uri.recompose_without_fragment()};
    if (!without_fragment.has_value()) {
      return;
    }

    auto target{without_fragment.value()};
    if (resource_base.has_value()) {
      sourcemeta::core::URI resolved{target};
      resolved.resolve_from(sourcemeta::core::URI{resource_base.value()});
      target = resolved.recompose();
    }

    const auto match{table.find(target)};
    if (match == table.cend()) {
      return;
    }

    const auto rename{match->second.find(name)};
    if (rename == match->second.cend()) {
      return;
    }

    subschema.assign("$ref", sourcemeta::core::JSON{without_fragment.value() +
                                                    "#" + rename->second});
  }

  static auto
  resolved_resource_base(const std::string &identifier,
                         const std::optional<std::string> &parent_base)
      -> std::optional<std::string> {
    const sourcemeta::core::URI uri{identifier};
    const auto without_fragment{uri.recompose_without_fragment()};
    if (!without_fragment.has_value() || without_fragment.value().empty()) {
      return parent_base;
    }

    if (!parent_base.has_value()) {
      return without_fragment;
    }

    sourcemeta::core::URI resolved{without_fragment.value()};
    resolved.resolve_from(sourcemeta::core::URI{parent_base.value()});
    return resolved.recompose();
  }

  static auto is_at_or_under(const sourcemeta::core::WeakPointer &candidate,
                             const sourcemeta::core::WeakPointer &ancestor)
      -> bool {
    if (candidate.size() < ancestor.size()) {
      return false;
    }

    for (std::size_t index{0}; index < ancestor.size(); ++index) {
      if (!(candidate.at(index) == ancestor.at(index))) {
        return false;
      }
    }

    return true;
  }

  // Every resource at or under this one, keyed by the URI it identifies itself
  // with. The table is read when rewriting a reference, so it has to be built
  // before anything is renamed, or a reference would be matched against a name
  // that has already moved
  static auto collect_subtree_renames(
      const sourcemeta::core::SchemaFrame::Location &location,
      const sourcemeta::core::JSON &root,
      const sourcemeta::core::SchemaFrame &frame) -> RenameTable {
    RenameTable result;
    frame.for_each_location(
        [&location, &root, &result](
            const sourcemeta::core::SchemaReferenceType,
            const std::string_view uri,
            const sourcemeta::core::SchemaFrame::Location &entry) -> void {
          if (entry.type !=
                  sourcemeta::core::SchemaFrame::LocationType::Resource ||
              !is_at_or_under(entry.pointer, location.pointer)) {
            return;
          }

          auto renames{build_resource_rename_map(sourcemeta::core::get(
              root, sourcemeta::core::to_pointer(entry.pointer)))};
          if (!renames.empty()) {
            result.insert_or_assign(std::string{uri}, std::move(renames));
          }
        });

    return result;
  }

  static auto subtree_needs_anchor_sanitization(
      const sourcemeta::core::JSON &schema,
      const sourcemeta::core::SchemaFrame::Location &location,
      const sourcemeta::core::JSON &root,
      const sourcemeta::core::SchemaFrame &frame) -> bool {
    if (resource_needs_anchor_sanitization(schema)) {
      return true;
    }

    bool pending{false};
    frame.for_each_location(
        [&location, &root, &pending](
            const sourcemeta::core::SchemaReferenceType, const std::string_view,
            const sourcemeta::core::SchemaFrame::Location &entry) -> void {
          if (pending ||
              entry.type !=
                  sourcemeta::core::SchemaFrame::LocationType::Resource ||
              !is_at_or_under(entry.pointer, location.pointer)) {
            return;
          }

          pending = resource_needs_anchor_sanitization(sourcemeta::core::get(
              root, sourcemeta::core::to_pointer(entry.pointer)));
        });

    return pending;
  }

  // An outer resource whose subtree needs sanitization covers this one too, so
  // deferring to it is what keeps a reference and the anchor it names moving
  // together
  static auto has_strict_ancestor_resource_scope(
      const sourcemeta::core::SchemaFrame::Location &location,
      const sourcemeta::core::SchemaFrame &frame) -> bool {
    bool found{false};
    frame.for_each_location(
        [&location, &found](
            const sourcemeta::core::SchemaReferenceType, const std::string_view,
            const sourcemeta::core::SchemaFrame::Location &entry) -> void {
          const bool entry_is_resource_scope =
              entry.type ==
                  sourcemeta::core::SchemaFrame::LocationType::Resource ||
              entry.pointer.empty();
          if (found || !entry_is_resource_scope ||
              entry.pointer.size() >= location.pointer.size() ||
              !is_at_or_under(location.pointer, entry.pointer)) {
            return;
          }

          found = true;
        });

    return found;
  }

  static auto resource_needs_anchor_sanitization(
      const sourcemeta::core::JSON &resource_root) -> bool {
    std::vector<std::string> invalid;
    collect_invalid_anchors(resource_root, true, invalid);
    return !invalid.empty();
  }

  static auto enclosing_resource_has_pending_sanitization(
      const sourcemeta::core::SchemaFrame::Location &location,
      const sourcemeta::core::JSON &root,
      const sourcemeta::core::SchemaFrame &frame) -> bool {
    std::optional<sourcemeta::core::WeakPointer> closest;
    frame.for_each_location(
        [&](const sourcemeta::core::SchemaReferenceType, const std::string_view,
            const sourcemeta::core::SchemaFrame::Location &entry) -> void {
          const bool entry_is_resource_scope =
              entry.type ==
                  sourcemeta::core::SchemaFrame::LocationType::Resource ||
              entry.pointer.empty();
          if (!entry_is_resource_scope) {
            return;
          }
          if (entry.pointer.size() > location.pointer.size()) {
            return;
          }
          bool is_ancestor{true};
          for (std::size_t index{0}; index < entry.pointer.size(); ++index) {
            if (!(entry.pointer.at(index) == location.pointer.at(index))) {
              is_ancestor = false;
              break;
            }
          }
          if (!is_ancestor) {
            return;
          }
          if (!closest.has_value() ||
              entry.pointer.size() > closest.value().size()) {
            closest = entry.pointer;
          }
        });
    if (!closest.has_value()) {
      return false;
    }
    const auto closest_pointer{sourcemeta::core::to_pointer(closest.value())};
    const auto &resource_schema{sourcemeta::core::get(root, closest_pointer)};
    return resource_needs_anchor_sanitization(resource_schema);
  }
};
