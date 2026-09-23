#ifndef SOURCEMETA_BLAZE_CONVERT_HELPERS_H_
#define SOURCEMETA_BLAZE_CONVERT_HELPERS_H_

// NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
const std::string DIALECT_OVERRIDE_KEYWORD{
    "x-sourcemeta-dialect-override-subschema"};

// The dialect a schema declares, honouring the marker that the upgrade rules
// leave behind while they walk a document across drafts
inline auto declared_dialect(const sourcemeta::core::JSON &schema)
    -> std::string_view {
  if (!schema.is_object()) {
    return {};
  }

  const auto *override_value{schema.try_at(DIALECT_OVERRIDE_KEYWORD)};
  if (override_value != nullptr && override_value->is_string()) {
    return override_value->to_string();
  }

  const auto *dialect{schema.try_at("$schema")};
  if (dialect != nullptr && dialect->is_string()) {
    return dialect->to_string();
  }

  return {};
}

inline auto mark_dialect_override(sourcemeta::core::JSON &schema,
                                  const std::string_view dialect) -> void {
  schema.assign(DIALECT_OVERRIDE_KEYWORD, sourcemeta::core::JSON{dialect});
}

inline auto current_dialect_or_override(const sourcemeta::core::JSON &schema)
    -> std::string_view {
  return declared_dialect(schema);
}

// The empty fragment does not change which dialect a URI names, and only some
// of the official spellings have a rule of their own to settle them
inline auto without_empty_fragment(const std::string_view uri)
    -> std::string_view {
  return uri.ends_with('#') ? uri.substr(0, uri.size() - 1) : uri;
}

// A subschema that a `$schema` of the document resolves to is a meta-schema of
// that document, no matter where within the document it sits. Every base
// dialect asks such a subschema to declare an identifier, which is what keeps
// the scan off the subschemas that could never be named that way
inline auto is_metaschema_target(const sourcemeta::core::JSON &schema,
                                 const sourcemeta::core::SchemaFrame &frame,
                                 const sourcemeta::core::WeakPointer &pointer)
    -> bool {
  if (!schema.is_object() || !schema.defines_any({"$id", "id"})) {
    return false;
  }

  // A document that takes its dialect from the caller rather than from a
  // `$schema` of its own names no meta-schema anywhere, so what the document
  // reads as is the only thing left to ask
  const auto document{frame.traverse(sourcemeta::core::EMPTY_WEAK_POINTER)};
  if (document.has_value()) {
    const auto target{frame.traverse(document.value().get().dialect)};
    if (target.has_value() && target.value().get().pointer == pointer) {
      return true;
    }
  }

  return frame.any_reference(
      [&frame, &pointer](
          const sourcemeta::core::SchemaReferenceType,
          const sourcemeta::core::WeakPointer &origin,
          const sourcemeta::core::SchemaFrame::Reference &reference) -> bool {
        if (origin.empty() || !origin.back().is_property() ||
            origin.back().to_property() != "$schema") {
          return false;
        }

        const auto destination{frame.traverse(reference.destination)};
        return destination.has_value() &&
               destination.value().get().pointer == pointer;
      });
}

// Whether any subschema that names this one through `$schema` still has work
// of its own left. Such a referrer is read under the dialect this subschema
// defines, so moving this one first would take the referrer off the dialect
// the caller is acting on before its turn ever comes
template <typename Predicate>
auto has_pending_metaschema_referrer(
    const sourcemeta::core::JSON &root,
    const sourcemeta::core::SchemaFrame &frame,
    const sourcemeta::core::WeakPointer &pointer, const Predicate &pending)
    -> bool {
  return frame.any_reference(
      [&root, &frame, &pointer, &pending](
          const sourcemeta::core::SchemaReferenceType,
          const sourcemeta::core::WeakPointer &origin,
          const sourcemeta::core::SchemaFrame::Reference &reference) -> bool {
        if (origin.empty() || !origin.back().is_property() ||
            origin.back().to_property() != "$schema") {
          return false;
        }

        const auto destination{frame.traverse(reference.destination)};
        if (!destination.has_value() ||
            destination.value().get().pointer != pointer) {
          return false;
        }

        const auto referrer{sourcemeta::core::to_pointer(origin).initial()};
        const auto referrer_pointer{
            sourcemeta::core::to_weak_pointer(referrer)};

        // A meta-schema that describes itself is its own referrer, and waiting
        // on itself would leave it on the dialect it came in with for good
        if (referrer_pointer == pointer) {
          return false;
        }

        if (pending(sourcemeta::core::get(root, referrer))) {
          return true;
        }

        // Everything under the referrer is read under the dialect this
        // subschema defines too, so work down there counts just as much as
        // work on the referrer itself. Another meta-schema is governed by its
        // own referrers rather than by this one
        return frame.any_subschema_under(
            referrer_pointer,
            [&root, &frame, &pending](
                const sourcemeta::core::SchemaFrame::Location &entry) -> bool {
              const auto &entry_schema{sourcemeta::core::get(
                  root, sourcemeta::core::to_pointer(entry.pointer))};
              return !is_metaschema_target(entry_schema, frame,
                                           entry.pointer) &&
                     pending(entry_schema);
            });
      });
}

inline auto
subschema_at_dialect(const sourcemeta::core::JSON &schema,
                     const sourcemeta::core::SchemaFrame::Location &location,
                     const std::string_view dialect) -> bool {
  const auto current{current_dialect_or_override(schema)};
  if (!current.empty()) {
    return current == dialect;
  }
  return schema.is_object() && location.pointer.empty();
}

// The official dialects the upgrade walks through, oldest first, so that a
// marker recording a newer one can be told apart from a stale one
// NOLINTNEXTLINE(cert-err58-cpp,bugprone-throwing-static-initialization)
constexpr std::array<std::string_view, 6> LADDER_DIALECTS{
    {"http://json-schema.org/draft-03/schema#",
     "http://json-schema.org/draft-04/schema#",
     "http://json-schema.org/draft-06/schema#",
     "http://json-schema.org/draft-07/schema#",
     "https://json-schema.org/draft/2019-09/schema",
     "https://json-schema.org/draft/2020-12/schema"}};

// How far along the ladder a dialect sits, counting from one so that anything
// the ladder does not name sits before all of them
inline auto dialect_position(const std::string_view dialect) -> std::size_t {
  for (std::size_t index = 0; index < LADDER_DIALECTS.size(); index += 1) {
    if (LADDER_DIALECTS[index] == dialect) {
      return index + 1;
    }
  }

  return 0;
}

// Core reads this keyword as a dialect too, so it may well be a keyword the
// caller wrote. The ladder only ever records one of the dialects it walks
// through, so anything else is not ours to clear
inline auto is_own_dialect_override(const sourcemeta::core::JSON &value)
    -> bool {
  return value.is_string() && dialect_position(value.to_string()) > 0;
}

// A `$schema` the conversion did not write stays as it is, so a dialect the
// ladder does not name is only ours to move when the meta-schema defining it
// travels in the same document, where it moves along with everything that
// names it. Bundling is what hands a dialect over, the same way it is what
// hands over a reference to somewhere else
inline auto
owns_dialect(const sourcemeta::core::SchemaFrame &frame,
             const sourcemeta::core::SchemaFrame::Location &location) -> bool {
  const auto dialect{without_empty_fragment(location.dialect)};
  return std::ranges::any_of(LADDER_DIALECTS,
                             [&dialect](const auto &candidate) -> bool {
                               return without_empty_fragment(candidate) ==
                                      dialect;
                             }) ||
         frame.traverse(dialect).has_value();
}

// Whether an identifier and a dialect name the same thing once both are
// resolved against what the caller said the document is called
inline auto names_the_same_uri(const sourcemeta::core::JSON &schema,
                               const char *keyword,
                               const std::string_view dialect,
                               const std::string_view default_id) -> bool {
  const auto *identifier{schema.try_at(keyword)};
  if (identifier == nullptr || !identifier->is_string()) {
    return false;
  }

  if (without_empty_fragment(identifier->to_string()) ==
      without_empty_fragment(dialect)) {
    return true;
  }

  // Resolving is what lets an identifier written relative to whatever the
  // caller named the document meet a dialect that is spelled out in full.
  // A value that does not parse is not for this question to complain about,
  // as framing says so in better words a moment later
  try {
    sourcemeta::core::URI left{identifier->to_string()};
    sourcemeta::core::URI right{std::string{dialect}};
    if (!default_id.empty()) {
      const sourcemeta::core::URI base{std::string{default_id}};
      left.resolve_from(base);
      right.resolve_from(base);
    }

    left.canonicalize();
    right.canonicalize();
    return left.recompose() == right.recompose();
  } catch (const sourcemeta::core::URIParseError &) {
    return false;
  } catch (const sourcemeta::core::URIError &) {
    return false;
  }
}

// A document whose identifier is the very dialect it declares describes
// itself, so it is a meta-schema on the strongest evidence there is. The
// ladder rewrites that `$schema` on the first bump, taking the evidence with
// it, so the question has to be asked before any rule runs
inline auto describes_itself(const sourcemeta::core::JSON &schema,
                             const std::string_view default_id) -> bool {
  if (!schema.is_object()) {
    return false;
  }

  const auto *dialect{schema.try_at("$schema")};
  if (dialect == nullptr || !dialect->is_string()) {
    return false;
  }

  // Draft 3 and Draft 4 carry the identifier in `id` and everything the ladder
  // names after them in `$id`, so the other keyword is ordinary data there. A
  // dialect the ladder does not name leaves the question open
  const auto position{dialect_position(dialect->to_string())};
  const auto &value{dialect->to_string()};
  if (position != 1 && position != 2 &&
      names_the_same_uri(schema, "$id", value, default_id)) {
    return true;
  }

  return position <= 2 && names_the_same_uri(schema, "id", value, default_id);
}

inline auto moved_past(const sourcemeta::core::JSON &schema,
                       const std::string_view dialect) -> bool {
  const auto *override_value{schema.try_at(DIALECT_OVERRIDE_KEYWORD)};
  return override_value != nullptr && override_value->is_string() &&
         dialect_position(override_value->to_string()) >
             dialect_position(dialect);
}

// The marker is state of the ladder rather than of the schema. A resource that
// declares a dialect the conversion does not own can never materialise it into
// a `$schema`, so whatever survives the ladder has to come off before the
// caller ever sees it
inline auto erase_dialect_overrides(sourcemeta::core::JSON &schema) -> void {
  if (schema.is_array()) {
    for (auto &item : schema.as_array()) {
      erase_dialect_overrides(item);
    }

    return;
  }

  if (!schema.is_object()) {
    return;
  }

  const auto *marker{schema.try_at(DIALECT_OVERRIDE_KEYWORD)};
  if (marker != nullptr && is_own_dialect_override(*marker)) {
    schema.erase(DIALECT_OVERRIDE_KEYWORD);
  }

  std::vector<std::string> keys;
  keys.reserve(schema.size());
  for (const auto &entry : schema.as_object()) {
    keys.push_back(entry.first);
  }
  for (const auto &key : keys) {
    erase_dialect_overrides(schema.at(key));
  }
}

inline auto drop_dialect_overrides(sourcemeta::core::JSON &schema,
                                   const bool is_root,
                                   const std::string_view dialect) -> void {
  if (schema.is_array()) {
    for (auto &item : schema.as_array()) {
      drop_dialect_overrides(item, false, dialect);
    }
    return;
  }

  if (!schema.is_object()) {
    return;
  }

  if (!is_root && schema.defines("$schema") &&
      schema.at("$schema").is_string()) {
    return;
  }

  // A subschema that already moved past the dialect being established keeps
  // its marker. Dropping it would leave the keywords that move brought in
  // looking like keywords of the dialect it has left behind, and the rules
  // that reserve those names would prefix them away
  const auto *marker{schema.try_at(DIALECT_OVERRIDE_KEYWORD)};
  if (marker != nullptr && is_own_dialect_override(*marker) &&
      (is_root || !moved_past(schema, dialect))) {
    schema.erase(DIALECT_OVERRIDE_KEYWORD);
  }

  std::vector<std::string> keys;
  keys.reserve(schema.size());
  for (const auto &entry : schema.as_object()) {
    keys.push_back(entry.first);
  }
  for (const auto &key : keys) {
    drop_dialect_overrides(schema.at(key), false, dialect);
  }
}

using Vocabulary = std::pair<std::string_view, bool>;

constexpr std::array<Vocabulary, 6> VOCABULARIES_2019_09{
    {{"https://json-schema.org/draft/2019-09/vocab/core", true},
     {"https://json-schema.org/draft/2019-09/vocab/applicator", true},
     {"https://json-schema.org/draft/2019-09/vocab/validation", true},
     {"https://json-schema.org/draft/2019-09/vocab/meta-data", true},
     {"https://json-schema.org/draft/2019-09/vocab/format", false},
     {"https://json-schema.org/draft/2019-09/vocab/content", true}}};

constexpr std::array<Vocabulary, 7> VOCABULARIES_2020_12{
    {{"https://json-schema.org/draft/2020-12/vocab/core", true},
     {"https://json-schema.org/draft/2020-12/vocab/applicator", true},
     {"https://json-schema.org/draft/2020-12/vocab/unevaluated", true},
     {"https://json-schema.org/draft/2020-12/vocab/validation", true},
     {"https://json-schema.org/draft/2020-12/vocab/meta-data", true},
     {"https://json-schema.org/draft/2020-12/vocab/format-annotation", true},
     {"https://json-schema.org/draft/2020-12/vocab/content", true}}};

// A meta-schema on 2019-09 or newer that does not declare its vocabularies
// leaves every schema naming it unreadable, down to whether a `$ref` counts as
// a reference at all. Whatever moves a meta-schema onto one of those dialects
// has to say what they are in the same breath, as a document the conversion
// cannot read is a document whose references it cannot keep whole
template <std::size_t Size>
auto synthesize_vocabulary(sourcemeta::core::JSON &schema,
                           const std::array<Vocabulary, Size> &entries)
    -> void {
  std::string_view anchor;
  if (schema.defines("$id")) {
    anchor = "$id";
  } else if (schema.defines("$schema")) {
    anchor = "$schema";
  }

  const std::string *next_key{nullptr};
  if (!anchor.empty()) {
    bool found_anchor{false};
    for (const auto &entry : schema.as_object()) {
      if (found_anchor) {
        next_key = &entry.first;
        break;
      }
      if (entry.first == anchor) {
        found_anchor = true;
      }
    }
  }

  if (next_key != nullptr) {
    schema.try_assign_before("$vocabulary",
                             sourcemeta::core::JSON::make_object(), *next_key);
  } else {
    schema.assign_assume_new("$vocabulary",
                             sourcemeta::core::JSON::make_object());
  }

  auto &vocabularies{schema.at("$vocabulary")};
  for (const auto &[uri, required] : entries) {
    vocabularies.assign_assume_new(std::string{uri},
                                   sourcemeta::core::JSON{required});
  }
}

struct AnchorCharPolicy {
  std::function<bool(char)> is_valid_first;
  std::function<bool(char)> is_valid_body;
};

inline auto sanitize_anchor_with_policy(const std::string_view original,
                                        const std::set<std::string> &in_use,
                                        const AnchorCharPolicy &policy)
    -> std::string {
  std::string sanitized;
  sanitized.reserve(original.size());
  for (const char character : original) {
    sanitized.push_back(policy.is_valid_body(character) ? character : '-');
  }
  while (sanitized.empty() || !policy.is_valid_first(sanitized.front()) ||
         in_use.contains(sanitized)) {
    sanitized.insert(0, "x-");
  }
  return sanitized;
}

#define ONLY_CONTINUE_IF(condition)                                            \
  if (!(condition)) {                                                          \
    return false;                                                              \
  }

#endif
