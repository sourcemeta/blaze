/// What the 2019-09 rung needs to know before it can rewrite anything. Every
/// one of these answers is a property of the whole document or of where a
/// subschema sits in it, which no pattern over a subschema can see, so the
/// rung asks for them by name and the rule consults the answers as bindings
class Analysis201909To202012 {
public:
  auto begin_pass() const -> void {
    this->plans_.clear();
    this->unevaluated_items_.reset();
    this->recursive_anchors_.clear();
    this->pending_sanitizations_.clear();
  }

  auto plan(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &root,
            const sourcemeta::core::SchemaVocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location,
            const Site &site, const sourcemeta::core::SchemaWalker &walker,
            const sourcemeta::core::SchemaResolver &resolver) const -> void {
    this->reset();

    if (!vocabularies.contains(
            SchemaVocabularies::Known::JSON_SCHEMA_2019_09_CORE) ||
        !schema.is_object()) {
      this->blocked_ = true;
      this->record(site);
      return;
    }

    // Answered here rather than beside its use, because more than one branch
    // below returns without reaching that point, and a stale answer from the
    // subschema visited before this one would decide whether a referenced
    // schema is kept
    this->additional_items_is_referenced_ =
        schema.defines("additionalItems") &&
        compute_additional_items_is_referenced(frame, location);

    const bool is_resource_scope{
        location.type ==
            sourcemeta::core::SchemaFrame::LocationType::Resource ||
        location.pointer.empty()};

    if (is_resource_scope) {
      compute_anchor_sanitization(root, frame, location);
      if (!this->anchor_renames_.empty() ||
          !this->anchor_ref_rewrites_.empty()) {
        this->resource_has_recursive_anchor_ =
            this->resource_has_recursive_anchor(root, frame, location, site);
        this->anchor_at_resource_root_ = is_resource_root(frame, location);
        if (needs_dynamic_anchor_name(schema)) {
          this->dynamic_anchor_name_ = compute_dynamic_anchor_name(root);
        }

        this->document_has_unevaluated_items_ =
            this->document_has_unevaluated_items(root, frame, walker, resolver);
        this->is_inside_contains_wrapper_ = false;
        this->sanitize_pending_ = true;
        this->record(site);
        return;
      }
    }

    if (this->resource_has_pending_sanitization(root, frame, location, site)) {
      this->blocked_ = true;
      this->record(site);
      return;
    }

    this->is_inside_contains_wrapper_ =
        location_inside_contains_wrapper(schema, location);

    this->resource_has_recursive_anchor_ =
        this->resource_has_recursive_anchor(root, frame, location, site);
    this->anchor_at_resource_root_ = is_resource_root(frame, location);
    if (needs_dynamic_anchor_name(schema)) {
      this->dynamic_anchor_name_ = compute_dynamic_anchor_name(root);
    }

    this->document_has_unevaluated_items_ =
        this->document_has_unevaluated_items(root, frame, walker, resolver);

    this->record(site);
  }

  /// What this rung settled for a position, as the terms a rule consults
  [[nodiscard]] auto fact(const Site &site, const std::string_view name) const
      -> sourcemeta::core::JSON {
    if (!this->load(site)) {
      return sourcemeta::core::JSON{true};
    }

    if (name == "blocked") {
      return sourcemeta::core::JSON{this->blocked_};
    }

    if (name == "sanitize-pending") {
      return sourcemeta::core::JSON{this->sanitize_pending_};
    }

    if (name == "additional-items-is-referenced") {
      return sourcemeta::core::JSON{this->additional_items_is_referenced_};
    }

    if (name == "resource-has-recursive-anchor") {
      return sourcemeta::core::JSON{this->resource_has_recursive_anchor_};
    }

    if (name == "anchor-at-resource-root") {
      return sourcemeta::core::JSON{this->anchor_at_resource_root_};
    }

    if (name == "is-inside-contains-wrapper") {
      return sourcemeta::core::JSON{this->is_inside_contains_wrapper_};
    }

    if (name == "document-has-unevaluated-items") {
      return sourcemeta::core::JSON{this->document_has_unevaluated_items_};
    }

    if (name == "dynamic-anchor-name") {
      return sourcemeta::core::JSON{this->dynamic_anchor_name_};
    }

    if (name == "dynamic-ref-value") {
      return sourcemeta::core::JSON{"#" + this->dynamic_anchor_name_};
    }

    throw TransformError{"Unknown 2019-09 fact"};
  }

  /// This resource with its anchors renamed and the references that name them
  /// moved, which is a rewrite across the whole resource rather than an edit
  /// to the subschema the rule fired on
  [[nodiscard]] auto sanitized(const sourcemeta::core::JSON &schema,
                               const Site &site) const
      -> sourcemeta::core::JSON {
    auto result{schema};
    if (!this->load(site)) {
      return result;
    }

    this->apply_anchor_sanitization(result);
    return result;
  }

  /// The 2019-09 vocabulary URIs as 2020-12 spells them, which is not a plain
  /// table: a declaration the target already carries is left alone, and the
  /// applicator one speaks for the unevaluated keywords as well
  [[nodiscard]] static auto vocabulary(const sourcemeta::core::JSON &schema)
      -> sourcemeta::core::JSON {
    if (!schema.is_object()) {
      return sourcemeta::core::JSON{nullptr};
    }

    auto result{schema};
    rewrite_vocabulary(result);
    const auto *rewritten{result.try_at("$vocabulary")};
    return rewritten == nullptr ? sourcemeta::core::JSON{nullptr} : *rewritten;
  }

private:
  static constexpr std::string_view APPLICATOR_2019_09_URI{
      "https://json-schema.org/draft/2019-09/vocab/applicator"};
  static constexpr std::string_view APPLICATOR_2020_12_URI{
      "https://json-schema.org/draft/2020-12/vocab/applicator"};
  static constexpr std::string_view UNEVALUATED_2020_12_URI{
      "https://json-schema.org/draft/2020-12/vocab/unevaluated"};

  static inline const std::unordered_map<std::string, std::string>
      // NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
      VOCAB_URI_MAP_2019_09_TO_2020_12{
          {"https://json-schema.org/draft/2019-09/vocab/core",
           "https://json-schema.org/draft/2020-12/vocab/core"},
          {"https://json-schema.org/draft/2019-09/vocab/applicator",
           "https://json-schema.org/draft/2020-12/vocab/applicator"},
          {"https://json-schema.org/draft/2019-09/vocab/validation",
           "https://json-schema.org/draft/2020-12/vocab/validation"},
          {"https://json-schema.org/draft/2019-09/vocab/meta-data",
           "https://json-schema.org/draft/2020-12/vocab/meta-data"},
          {"https://json-schema.org/draft/2019-09/vocab/format",
           "https://json-schema.org/draft/2020-12/vocab/format-annotation"},
          {"https://json-schema.org/draft/2019-09/vocab/content",
           "https://json-schema.org/draft/2020-12/vocab/content"}};

  static auto rewrite_vocabulary(sourcemeta::core::JSON &schema) -> void {
    if (!schema.is_object() || !schema.defines("$vocabulary") ||
        !schema.at("$vocabulary").is_object()) {
      return;
    }

    std::unordered_set<std::string> source_keys;
    std::optional<sourcemeta::core::JSON> applicator_2019_09_value;
    for (const auto &entry : schema.at("$vocabulary").as_object()) {
      source_keys.insert(entry.first);
      if (entry.first == APPLICATOR_2019_09_URI) {
        applicator_2019_09_value = entry.second;
      }
    }

    const bool unevaluated_already_present{
        source_keys.contains(std::string{UNEVALUATED_2020_12_URI})};
    const bool should_inline_unevaluated{applicator_2019_09_value.has_value() &&
                                         !unevaluated_already_present};

    auto fresh{sourcemeta::core::JSON::make_object()};

    for (const auto &entry : schema.at("$vocabulary").as_object()) {
      const auto iter{VOCAB_URI_MAP_2019_09_TO_2020_12.find(entry.first)};
      if (iter == VOCAB_URI_MAP_2019_09_TO_2020_12.cend()) {
        fresh.assign(entry.first, entry.second);
        // The unevaluated keywords are defined in terms of the annotations
        // the applicator ones produce, so the declaration that survives for
        // the applicator vocabulary is the one that speaks for both
        if (entry.first == APPLICATOR_2020_12_URI &&
            should_inline_unevaluated) {
          fresh.assign(std::string{UNEVALUATED_2020_12_URI}, entry.second);
        }
        continue;
      }

      if (source_keys.contains(iter->second)) {
        continue;
      }

      fresh.assign(iter->second, entry.second);

      if (entry.first == APPLICATOR_2019_09_URI && should_inline_unevaluated) {
        fresh.assign(std::string{UNEVALUATED_2020_12_URI}, entry.second);
      }
    }

    schema.at("$vocabulary").into(std::move(fresh));
  }

  struct AnchorRename {
    sourcemeta::core::Pointer subschema_pointer;
    std::string new_name;
  };

  struct AnchorRefRewrite {
    sourcemeta::core::Pointer ref_pointer;
    std::string new_value;
  };

  // Beside an `items` that is not an array this keyword asserts nothing, and
  // 2020-12 does not define it at all, so dropping it loses nothing unless a
  // reference reaches the schema it holds. Such a reference uses it as a
  // definition, and `$defs` is where 2020-12 keeps a schema it does not apply.
  // A reference naming something nested inside it counts too, since erasing
  // the schema takes everything under it along
  static auto compute_additional_items_is_referenced(
      const sourcemeta::core::SchemaFrame &frame,
      const sourcemeta::core::SchemaFrame::Location &location) -> bool {
    const auto wanted{
        sourcemeta::core::to_pointer(location.pointer)
            .concat(sourcemeta::core::Pointer{"additionalItems"})};
    return frame.any_reference(
        [&frame, &wanted](
            const sourcemeta::core::SchemaReferenceType,
            const sourcemeta::core::WeakPointer &,
            const sourcemeta::core::SchemaFrame::Reference &reference) -> bool {
          const auto destination{frame.traverse(reference.destination)};
          return destination.has_value() &&
                 sourcemeta::core::to_pointer(destination.value().get().pointer)
                     .starts_with(wanted);
        });
  }

  // What the frame had to say about one position, kept as values rather than
  // as views, so that it still reads correctly once the document has been
  // edited. The working members below are loaded from this just before the
  // position is answered for or rewritten
  struct Plan {
    bool blocked;
    bool sanitize;
    bool additional_items_is_referenced;
    bool resource_has_recursive_anchor;
    bool anchor_at_resource_root;
    bool is_inside_contains_wrapper;
    bool document_has_unevaluated_items;
    std::string dynamic_anchor_name;
    std::vector<AnchorRename> anchor_renames;
    std::vector<AnchorRefRewrite> anchor_ref_rewrites;
  };

  auto reset() const -> void {
    this->blocked_ = false;
    this->sanitize_pending_ = false;
    this->additional_items_is_referenced_ = false;
    this->resource_has_recursive_anchor_ = false;
    this->anchor_at_resource_root_ = false;
    this->is_inside_contains_wrapper_ = false;
    this->document_has_unevaluated_items_ = false;
    this->anchor_renames_.clear();
    this->anchor_ref_rewrites_.clear();
  }

  auto record(const Site &site) const -> void {
    this->plans_.insert_or_assign(
        site.pointer,
        Plan{.blocked = this->blocked_,
             .sanitize = this->sanitize_pending_,
             .additional_items_is_referenced =
                 this->additional_items_is_referenced_,
             .resource_has_recursive_anchor =
                 this->resource_has_recursive_anchor_,
             .anchor_at_resource_root = this->anchor_at_resource_root_,
             .is_inside_contains_wrapper = this->is_inside_contains_wrapper_,
             .document_has_unevaluated_items =
                 this->document_has_unevaluated_items_,
             .dynamic_anchor_name = this->dynamic_anchor_name_,
             .anchor_renames = this->anchor_renames_,
             .anchor_ref_rewrites = this->anchor_ref_rewrites_});
  }

  [[nodiscard]] auto load(const Site &site) const -> bool {
    const auto found{this->plans_.find(site.pointer)};
    if (found == this->plans_.cend()) {
      return false;
    }

    const auto &plan{found->second};
    this->blocked_ = plan.blocked;
    this->sanitize_pending_ = plan.sanitize;
    this->additional_items_is_referenced_ = plan.additional_items_is_referenced;
    this->resource_has_recursive_anchor_ = plan.resource_has_recursive_anchor;
    this->anchor_at_resource_root_ = plan.anchor_at_resource_root;
    this->is_inside_contains_wrapper_ = plan.is_inside_contains_wrapper;
    this->document_has_unevaluated_items_ = plan.document_has_unevaluated_items;
    this->dynamic_anchor_name_ = plan.dynamic_anchor_name;
    this->anchor_renames_ = plan.anchor_renames;
    this->anchor_ref_rewrites_ = plan.anchor_ref_rewrites;
    return true;
  }

  mutable std::map<sourcemeta::core::Pointer, Plan> plans_;
  mutable bool blocked_{false};
  mutable bool additional_items_is_referenced_{false};
  mutable std::vector<
      std::pair<sourcemeta::core::Pointer, sourcemeta::core::Pointer>>
      renames_;

  mutable bool resource_has_recursive_anchor_{false};
  mutable bool anchor_at_resource_root_{false};
  mutable std::string dynamic_anchor_name_{"meta"};
  mutable bool dynamic_anchor_name_chosen_{false};
  mutable bool is_inside_contains_wrapper_{false};
  mutable bool document_has_unevaluated_items_{false};
  mutable bool sanitize_pending_{false};
  mutable std::vector<AnchorRename> anchor_renames_;
  mutable std::vector<AnchorRefRewrite> anchor_ref_rewrites_;

  // Whether the document has an `unevaluatedItems` anywhere does not change
  // while a pass runs, and asking it per position is asking a question about
  // the whole document once for every position in it
  [[nodiscard]] auto document_has_unevaluated_items(
      const sourcemeta::core::JSON &root,
      const sourcemeta::core::SchemaFrame &frame,
      const sourcemeta::core::SchemaWalker &walker,
      const sourcemeta::core::SchemaResolver &resolver) const -> bool {
    if (!this->unevaluated_items_.has_value()) {
      this->unevaluated_items_ =
          compute_document_has_unevaluated_items(root, frame, walker, resolver);
    }

    return this->unevaluated_items_.value();
  }

  mutable std::optional<bool> unevaluated_items_;

  static auto compute_document_has_unevaluated_items(
      const sourcemeta::core::JSON &root,
      const sourcemeta::core::SchemaFrame &frame,
      const sourcemeta::core::SchemaWalker &walker,
      const sourcemeta::core::SchemaResolver &resolver) -> bool {
    if (frame.any_subschema(
            [&](const sourcemeta::core::SchemaFrame::Location &entry) -> bool {
              const auto absolute{sourcemeta::core::to_pointer(entry.pointer)};
              const auto &subschema{sourcemeta::core::get(root, absolute)};
              if (!subschema.is_object() ||
                  !subschema.defines("unevaluatedItems")) {
                return false;
              }
              const auto &location_vocabularies{
                  frame.vocabularies(entry, resolver)};
              const auto &keyword_metadata{
                  walker("unevaluatedItems", location_vocabularies)};
              if (keyword_metadata.type !=
                  sourcemeta::core::SchemaKeywordType::Unknown) {
                return true;
              }

              return false;
            })) {
      return true;
    }
    return false;
  }

  static auto is_2020_12_anchor_first_char(const char character) -> bool {
    return (character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z') || character == '_';
  }

  static auto is_2020_12_anchor_body_char(const char character) -> bool {
    return (character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z') ||
           (character >= '0' && character <= '9') || character == '_' ||
           character == '.' || character == '-';
  }

  static auto is_valid_2020_12_anchor(const std::string_view name) -> bool {
    if (name.empty()) {
      return false;
    }
    if (!is_2020_12_anchor_first_char(name.front())) {
      return false;
    }
    for (std::size_t index{1}; index < name.size(); ++index) {
      if (!is_2020_12_anchor_body_char(name[index])) {
        return false;
      }
    }
    return true;
  }

  // The wrapper this rule builds holds nothing but the `contains` it moved and
  // the two bounds that go with it, so a double negation the document wrote
  // itself can be told apart by what sits beside them. Reading the position
  // alone would mistake an authored `not` of a `not` for the rule's own output
  // and leave the `contains` inside it bare
  static auto
  subschema_is_contains_wrapper(const sourcemeta::core::JSON &subschema)
      -> bool {
    if (!subschema.is_object() || !subschema.defines("contains")) {
      return false;
    }

    for (const auto &entry : subschema.as_object()) {
      if (entry.first != "contains" && entry.first != "minContains" &&
          entry.first != "maxContains") {
        return false;
      }
    }

    return true;
  }

  static auto location_inside_contains_wrapper(
      const sourcemeta::core::JSON &subschema,
      const sourcemeta::core::SchemaFrame::Location &location) -> bool {
    if (location.pointer.size() < 2) {
      return false;
    }
    const auto &last{location.pointer.back()};
    if (!last.is_property() || last.to_property() != "not") {
      return false;
    }
    const auto &second_last{location.pointer.at(location.pointer.size() - 2)};
    if (!second_last.is_property() || second_last.to_property() != "not") {
      return false;
    }
    return subschema_is_contains_wrapper(subschema);
  }

  static auto find_enclosing_resource(
      const sourcemeta::core::SchemaFrame &frame,
      const sourcemeta::core::SchemaFrame::Location &current_location)
      -> std::optional<std::reference_wrapper<
          const sourcemeta::core::SchemaFrame::Location>> {
    std::optional<
        std::reference_wrapper<const sourcemeta::core::SchemaFrame::Location>>
        closest;
    frame.for_each_location(
        [&](const sourcemeta::core::SchemaReferenceType, const std::string_view,
            const sourcemeta::core::SchemaFrame::Location &entry) -> void {
          const bool entry_is_resource_scope{
              entry.type ==
                  sourcemeta::core::SchemaFrame::LocationType::Resource ||
              entry.pointer.empty()};
          if (!entry_is_resource_scope) {
            return;
          }
          if (entry.pointer.size() > current_location.pointer.size()) {
            return;
          }
          if (!current_location.pointer.starts_with(entry.pointer)) {
            return;
          }
          if (!closest.has_value() ||
              entry.pointer.size() > closest.value().get().pointer.size()) {
            closest = std::cref(entry);
          }
        });
    return closest;
  }

  static auto
  pointer_within_resource(const sourcemeta::core::WeakPointer &candidate,
                          const sourcemeta::core::WeakPointer &resource_pointer)
      -> bool {
    if (!candidate.starts_with(resource_pointer)) {
      return false;
    }
    return true;
  }

  auto compute_anchor_sanitization(
      const sourcemeta::core::JSON &root,
      const sourcemeta::core::SchemaFrame &frame,
      const sourcemeta::core::SchemaFrame::Location &resource_location) const
      -> void {
    this->anchor_renames_.clear();
    this->anchor_ref_rewrites_.clear();

    const auto &resource_pointer{resource_location.pointer};

    std::set<std::string> existing_valid;
    std::vector<std::pair<std::string, sourcemeta::core::WeakPointer>> invalid;

    frame.for_each_anchor(
        sourcemeta::core::SchemaReferenceType::Static,
        [&](const std::string_view uri,
            const sourcemeta::core::SchemaFrame::Location &entry) -> void {
          if (!pointer_within_resource(entry.pointer, resource_pointer)) {
            return;
          }
          const sourcemeta::core::URI anchor_uri{uri};
          const auto fragment{anchor_uri.fragment()};
          if (!fragment.has_value() || fragment.value().empty()) {
            return;
          }
          const std::string anchor_name{fragment.value()};
          if (is_valid_2020_12_anchor(anchor_name)) {
            existing_valid.insert(anchor_name);
          } else {
            invalid.emplace_back(anchor_name, entry.pointer);
          }
        });

    if (invalid.empty()) {
      return;
    }

    static const AnchorCharPolicy POLICY{
        .is_valid_first = &is_2020_12_anchor_first_char,
        .is_valid_body = &is_2020_12_anchor_body_char};

    std::map<std::string, std::string> rename_map;
    std::set<std::string> in_use{existing_valid};
    for (const auto &[original, pointer] : invalid) {
      if (rename_map.contains(original)) {
        continue;
      }
      in_use.erase(original);
      const auto sanitized{
          sanitize_anchor_with_policy(original, in_use, POLICY)};
      rename_map.emplace(original, sanitized);
      in_use.insert(sanitized);
    }

    std::set<std::string> processed_pointers;
    for (const auto &[original, pointer] : invalid) {
      const auto pointer_str{sourcemeta::core::to_string(pointer)};
      if (processed_pointers.contains(pointer_str)) {
        continue;
      }
      processed_pointers.insert(pointer_str);

      const auto absolute{sourcemeta::core::to_pointer(pointer)};
      const auto &subschema{sourcemeta::core::get(root, absolute)};
      if (!subschema.is_object() || !subschema.defines("$anchor") ||
          !subschema.at("$anchor").is_string()) {
        continue;
      }
      const auto current_value{subschema.at("$anchor").to_string()};
      const auto rename_iter{rename_map.find(current_value)};
      if (rename_iter == rename_map.end()) {
        continue;
      }

      const auto relative_weak{pointer.resolve_from(resource_pointer)};
      this->anchor_renames_.push_back(
          {.subschema_pointer = sourcemeta::core::to_pointer(relative_weak),
           .new_name = rename_iter->second});
    }

    frame.for_each_reference_from(
        resource_pointer,
        [&](const sourcemeta::core::SchemaReferenceType,
            const sourcemeta::core::WeakPointer &origin,
            const sourcemeta::core::SchemaFrame::Reference &reference) -> void {
          if (!reference.fragment.has_value()) {
            return;
          }
          const auto &fragment{reference.fragment.value()};
          if (fragment.empty() || fragment.front() == '/') {
            return;
          }
          const auto rename_iter{rename_map.find(std::string{fragment})};
          if (rename_iter == rename_map.end()) {
            return;
          }

          // Spelling the same fragment is not enough. Another document may
          // name an anchor identically, and following the renamed one would
          // point this reference at a schema it never named. What decides is
          // where framing says the reference actually lands
          const auto destination{frame.traverse(reference.destination)};
          if (!destination.has_value() ||
              !pointer_within_resource(destination.value().get().pointer,
                                       resource_pointer)) {
            return;
          }

          sourcemeta::core::URI ref_uri{reference.original};
          ref_uri.fragment(rename_iter->second);
          const auto new_value{ref_uri.recompose()};

          const auto relative_weak{origin.resolve_from(resource_pointer)};
          this->anchor_ref_rewrites_.push_back(
              {.ref_pointer = sourcemeta::core::to_pointer(relative_weak),
               .new_value = new_value});
        });
  }

  static auto enclosing_resource_has_pending_sanitization(
      const sourcemeta::core::JSON &root,
      const sourcemeta::core::SchemaFrame &frame,
      const sourcemeta::core::SchemaFrame::Location &current_location) -> bool {
    const auto closest{find_enclosing_resource(frame, current_location)};
    if (!closest.has_value()) {
      return false;
    }
    const auto &resource_pointer{closest.value().get().pointer};

    return frame.any_anchor(
        sourcemeta::core::SchemaReferenceType::Static,
        [&](const std::string_view uri,
            const sourcemeta::core::SchemaFrame::Location &entry) -> bool {
          if (!pointer_within_resource(entry.pointer, resource_pointer)) {
            return false;
          }
          const sourcemeta::core::URI anchor_uri{uri};
          const auto fragment{anchor_uri.fragment()};
          if (!fragment.has_value() || fragment.value().empty()) {
            return false;
          }
          if (!is_valid_2020_12_anchor(fragment.value())) {
            const auto absolute{sourcemeta::core::to_pointer(entry.pointer)};
            const auto &subschema{sourcemeta::core::get(root, absolute)};
            if (subschema.is_object() && subschema.defines("$anchor") &&
                subschema.at("$anchor").is_string() &&
                subschema.at("$anchor").to_string() == fragment.value()) {
              return true;
            }
          }

          return false;
        });
  }

  auto apply_anchor_sanitization(sourcemeta::core::JSON &schema) const -> void {
    for (const auto &rename : this->anchor_renames_) {
      auto &target{sourcemeta::core::get(schema, rename.subschema_pointer)};
      target.at("$anchor").into(sourcemeta::core::JSON{rename.new_name});
    }
    for (const auto &rewrite : this->anchor_ref_rewrites_) {
      auto &target{sourcemeta::core::get(schema, rewrite.ref_pointer)};
      target.into(sourcemeta::core::JSON{rewrite.new_value});
    }
  }

  // Whichever frame entry the traversal happens to reach first decides the
  // entry type, and a resource has several. Asking the frame which resource
  // encloses this location answers the same question the same way every time
  static auto
  is_resource_root(const sourcemeta::core::SchemaFrame &frame,
                   const sourcemeta::core::SchemaFrame::Location &location)
      -> bool {
    if (location.pointer.empty()) {
      return true;
    }

    const auto closest{find_enclosing_resource(frame, location)};
    return closest.has_value() &&
           closest.value().get().pointer == location.pointer;
  }

  // A dynamic anchor is what a dynamic reference binds to across every
  // resource in the same scope, so every resource that gets one has to spell
  // it the same way. That makes the name a property of the document. Only the
  // static anchors it already spells are in the way: another dynamic anchor
  // carrying this very name is the point rather than a collision
  static auto collect_static_anchors(const sourcemeta::core::JSON &node,
                                     std::set<std::string> &names) -> void {
    if (node.is_array()) {
      for (const auto &item : node.as_array()) {
        collect_static_anchors(item, names);
      }

      return;
    }

    if (!node.is_object()) {
      return;
    }

    const auto *anchor{node.try_at("$anchor")};
    if (anchor != nullptr && anchor->is_string()) {
      names.emplace(anchor->to_string());
    }

    // An author's own dynamic anchor has to be stepped around too, or the
    // name chosen here lands on it and, being declared further out, takes
    // over every reference that named it. This is read once, before this rule
    // has written any dynamic anchor of its own, so what it finds is the
    // author's and nothing else
    const auto *dynamic{node.try_at("$dynamicAnchor")};
    if (dynamic != nullptr && dynamic->is_string()) {
      names.emplace(dynamic->to_string());
    }

    for (const auto &entry : node.as_object()) {
      collect_static_anchors(entry.second, names);
    }
  }

  // Naming a dynamic anchor means reading the whole document, so only a
  // subschema that is about to carry one or point at one pays for it
  static auto needs_dynamic_anchor_name(const sourcemeta::core::JSON &schema)
      -> bool {
    return schema.is_object() &&
           schema.defines_any({"$recursiveAnchor", "$recursiveRef"});
  }

  // Answered once per document. The driver runs this rule to a fixed point, so
  // a later pass would read back the dynamic anchor this one wrote and keep
  // stepping around its own name
  auto compute_dynamic_anchor_name(const sourcemeta::core::JSON &root) const
      -> std::string {
    if (this->dynamic_anchor_name_chosen_) {
      return this->dynamic_anchor_name_;
    }

    std::set<std::string> in_use;
    collect_static_anchors(root, in_use);

    std::string name{"meta"};
    while (in_use.contains(name)) {
      name.insert(0, "x-");
    }

    this->dynamic_anchor_name_chosen_ = true;
    return name;
  }

  // Both of these ask about the resource holding a position rather than about
  // the position, so they are asked once per resource instead of once per
  // position in it. `relative_pointer` is how deep the resource begins, so the
  // resource is the pointer cut to that depth
  [[nodiscard]] static auto enclosing_resource(const Site &site)
      -> sourcemeta::core::Pointer {
    return site.pointer.slice(0, site.relative_pointer);
  }

  [[nodiscard]] auto resource_has_recursive_anchor(
      const sourcemeta::core::JSON &root,
      const sourcemeta::core::SchemaFrame &frame,
      const sourcemeta::core::SchemaFrame::Location &location,
      const Site &site) const -> bool {
    const auto resource{enclosing_resource(site)};
    const auto cached{this->recursive_anchors_.find(resource)};
    if (cached != this->recursive_anchors_.cend()) {
      return cached->second;
    }

    const auto answer{
        compute_resource_has_recursive_anchor(root, frame, location)};
    this->recursive_anchors_.emplace(resource, answer);
    return answer;
  }

  [[nodiscard]] auto resource_has_pending_sanitization(
      const sourcemeta::core::JSON &root,
      const sourcemeta::core::SchemaFrame &frame,
      const sourcemeta::core::SchemaFrame::Location &location,
      const Site &site) const -> bool {
    const auto resource{enclosing_resource(site)};
    const auto cached{this->pending_sanitizations_.find(resource)};
    if (cached != this->pending_sanitizations_.cend()) {
      return cached->second;
    }

    const auto answer{
        enclosing_resource_has_pending_sanitization(root, frame, location)};
    this->pending_sanitizations_.emplace(resource, answer);
    return answer;
  }

  mutable std::map<sourcemeta::core::Pointer, bool> recursive_anchors_;
  mutable std::map<sourcemeta::core::Pointer, bool> pending_sanitizations_;

  static auto compute_resource_has_recursive_anchor(
      const sourcemeta::core::JSON &root,
      const sourcemeta::core::SchemaFrame &frame,
      const sourcemeta::core::SchemaFrame::Location &current_location) -> bool {
    const auto closest{find_enclosing_resource(frame, current_location)};
    if (!closest.has_value()) {
      return false;
    }

    // A recursive reference binds to the anchor of the resource it sits in,
    // and only that resource's root can declare one
    const auto &resource{sourcemeta::core::get(
        root, sourcemeta::core::to_pointer(closest.value().get().pointer))};
    return resource.is_object() && resource.defines("$recursiveAnchor") &&
           resource.at("$recursiveAnchor").is_boolean() &&
           resource.at("$recursiveAnchor").to_boolean();
  }
};
