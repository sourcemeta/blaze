#ifndef SOURCEMETA_BLAZE_CONVERT_TRANSFORM_BUILD_H_
#define SOURCEMETA_BLAZE_CONVERT_TRANSFORM_BUILD_H_

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <algorithm> // std::ranges::find
#include <cstddef>   // std::size_t
#include <cstdint>   // std::uint8_t
#include <iterator>  // std::distance
#include <utility>   // std::move, std::pair
#include <vector>    // std::vector

namespace {

using namespace sourcemeta::core;

/// What a template produced, and where its material came from
struct Built {
  JSON value;
  std::vector<TransformRelocation> relocations;
  std::vector<Pointer> opaque;
};

/// Where a set puts a member it is introducing
struct Placement {
  enum class Kind : std::uint8_t { Last, First, Before, After };
  Kind kind{Kind::Last};
  JSON::String anchor;
};

auto build_template(const JSON &specification, const JSON &self,
                    const JSON &current, const TransformBindings &bindings,
                    const TransformFunction &function, const Pointer &target)
    -> Built;

auto build_reference(const JSON::String &name, const JSON &self,
                     const JSON &current, const TransformBindings &bindings,
                     const Pointer &target) -> Built {
  // `$self` is the term as the build found it, `$current` is the term as it
  // stands, which is what an edit that rebuilds the whole term needs
  if (name == "$current") {
    return {
        .value = current, .relocations = {{Pointer{}, target}}, .opaque = {}};
  }

  if (name == "$self") {
    return {.value = self, .relocations = {{Pointer{}, target}}, .opaque = {}};
  }

  const auto iterator{bindings.find(name)};
  if (iterator == bindings.cend()) {
    throw TransformError{"A template names a binding that was never bound"};
  }

  return {.value = iterator->second.value,
          .relocations = {{iterator->second.pointer, target}},
          .opaque = {}};
}

auto absorb(Built &result, Built &&part) -> void {
  for (auto &relocation : part.relocations) {
    result.relocations.push_back(std::move(relocation));
  }

  for (auto &pointer : part.opaque) {
    result.opaque.push_back(std::move(pointer));
  }
}

auto build_object(const JSON &members, const JSON &self, const JSON &current,
                  const TransformBindings &bindings,
                  const TransformFunction &function, const Pointer &target)
    -> Built {
  if (!members.is_object()) {
    throw TransformError{"An object template takes an object"};
  }

  Built result{.value = JSON::make_object(), .relocations = {}, .opaque = {}};
  for (const auto &entry : members.as_object()) {
    auto position{target};
    position.push_back(entry.first);
    auto member{build_template(entry.second, self, current, bindings, function,
                               position)};
    result.value.assign(entry.first, member.value);
    absorb(result, std::move(member));
  }

  return result;
}

auto build_array(const JSON &elements, const JSON &self, const JSON &current,
                 const TransformBindings &bindings,
                 const TransformFunction &function, const Pointer &target)
    -> Built {
  if (!elements.is_array()) {
    throw TransformError{"An array template takes an array"};
  }

  Built result{.value = JSON::make_array(), .relocations = {}, .opaque = {}};
  for (const auto &element : elements.as_array()) {
    if (element.is_object() && element.defines("spread")) {
      auto spread{build_template(element.at("spread"), self, current, bindings,
                                 function, target)};
      if (!spread.value.is_array()) {
        throw TransformError{"A spread takes an array"};
      }

      for (const auto &item : spread.value.as_array()) {
        result.value.push_back(item);
      }

      continue;
    }

    auto position{target};
    position.push_back(result.value.size());
    auto item{
        build_template(element, self, current, bindings, function, position)};
    result.value.push_back(item.value);
    absorb(result, std::move(item));
  }

  return result;
}

/// Select a table entry by the string a key resolves to. A finite map is data
/// rather than computation, so the result is an ordinary template and the
/// trace it derives is exact
auto build_lookup(const JSON &specification, const JSON &self,
                  const JSON &current, const TransformBindings &bindings,
                  const TransformFunction &function, const Pointer &target)
    -> Built {
  if (!specification.is_object() || !specification.defines("key") ||
      !specification.defines("table")) {
    throw TransformError{"A lookup takes an object with a key and a table"};
  }

  if (!specification.at("table").is_object()) {
    throw TransformError{"A lookup table must be an object"};
  }

  const auto key{build_template(specification.at("key"), self, current,
                                bindings, function, target)};
  if (!key.value.is_string()) {
    throw TransformError{"A lookup key must resolve to a string"};
  }

  const auto *entry{specification.at("table").try_at(key.value.to_string())};
  if (entry == nullptr) {
    throw TransformError{"A lookup key is not in the table"};
  }

  return build_template(*entry, self, current, bindings, function, target);
}

auto build_call(const JSON &call, const JSON &self, const JSON &current,
                const TransformBindings &bindings,
                const TransformFunction &function, const Pointer &target)
    -> Built {
  if (!call.is_object() || !call.defines("name") ||
      !call.at("name").is_string()) {
    throw TransformError{"A call takes an object with a string name"};
  }

  std::vector<JSON> arguments;
  if (call.defines("args")) {
    if (!call.at("args").is_array()) {
      throw TransformError{"A call takes an array of arguments"};
    }

    arguments.reserve(call.at("args").size());
    for (const auto &argument : call.at("args").as_array()) {
      arguments.push_back(
          build_template(argument, self, current, bindings, function, target)
              .value);
    }
  }

  return {.value = function(call.at("name").to_string(), arguments),
          .relocations = {},
          .opaque = {target}};
}

auto build_template(const JSON &specification, const JSON &self,
                    const JSON &current, const TransformBindings &bindings,
                    const TransformFunction &function, const Pointer &target)
    -> Built {
  if (specification.is_string() && specification.to_string().starts_with('$')) {
    return build_reference(specification.to_string(), self, current, bindings,
                           target);
  }

  if (!specification.is_object()) {
    return {.value = specification, .relocations = {}, .opaque = {}};
  }

  if (specification.defines("object")) {
    return build_object(specification.at("object"), self, current, bindings,
                        function, target);
  }

  if (specification.defines("array")) {
    return build_array(specification.at("array"), self, current, bindings,
                       function, target);
  }

  if (specification.defines("lookup")) {
    return build_lookup(specification.at("lookup"), self, current, bindings,
                        function, target);
  }

  if (specification.defines("call")) {
    return build_call(specification.at("call"), self, current, bindings,
                      function, target);
  }

  return {.value = specification, .relocations = {}, .opaque = {}};
}

auto read_placement(const JSON &edit) -> Placement {
  if (edit.defines("before")) {
    if (!edit.at("before").is_string()) {
      throw TransformError{"A placement anchor must be a string"};
    }

    return {.kind = Placement::Kind::Before,
            .anchor = edit.at("before").to_string()};
  }

  if (edit.defines("after")) {
    if (!edit.at("after").is_string()) {
      throw TransformError{"A placement anchor must be a string"};
    }

    return {.kind = Placement::Kind::After,
            .anchor = edit.at("after").to_string()};
  }

  if (edit.defines("first")) {
    if (!edit.at("first").is_boolean() || !edit.at("first").to_boolean()) {
      throw TransformError{"A first placement takes true"};
    }

    return {.kind = Placement::Kind::First, .anchor = {}};
  }

  return {.kind = Placement::Kind::Last, .anchor = {}};
}

/// Where a placement wants a new member, counted in members the term still has
auto placement_slot(const JSON &term, const Placement &placement,
                    const std::vector<JSON::String> &current,
                    const std::vector<JSON::String> &original) -> std::size_t {
  if (placement.kind == Placement::Kind::First) {
    return 0;
  }

  const auto found{std::ranges::find(current, placement.anchor)};
  if (found != current.cend()) {
    const auto slot{
        static_cast<std::size_t>(std::distance(current.cbegin(), found))};
    return placement.kind == Placement::Kind::After ? slot + 1 : slot;
  }

  // The anchor is gone, so where it used to be decides, counted in the members
  // that are still here
  const auto gone{std::ranges::find(original, placement.anchor)};
  if (gone == original.cend()) {
    throw TransformError{"A placement names an anchor the term never had"};
  }

  std::size_t surviving{0};
  for (auto iterator = original.cbegin(); iterator != gone; ++iterator) {
    if (term.defines(*iterator)) {
      surviving += 1;
    }
  }

  return placement.kind == Placement::Kind::After ? surviving + 1 : surviving;
}

/// Rebuild an object with one member at the requested position, because the
/// underlying container only appends
auto insert_member(JSON &term, const JSON::String &key, const JSON &value,
                   const Placement &placement,
                   const std::vector<JSON::String> &original) -> void {
  if (term.defines(key) || placement.kind == Placement::Kind::Last) {
    term.assign(key, value);
    return;
  }

  std::vector<JSON::String> current;
  current.reserve(term.size());
  for (const auto &entry : term.as_object()) {
    current.push_back(entry.first);
  }

  const auto slot{placement_slot(term, placement, current, original)};
  auto rebuilt{JSON::make_object()};
  for (std::size_t index = 0; index < current.size(); index += 1) {
    if (index == slot) {
      rebuilt.assign(key, value);
    }

    rebuilt.assign(current.at(index), term.at(current.at(index)));
  }

  if (slot >= current.size()) {
    rebuilt.assign(key, value);
  }

  term.into(std::move(rebuilt));
}

/// Write a value at a pointer, creating the containers along the way, because
/// the core setter assigns into a position that already exists
auto assign_creating(JSON &container, const Pointer &pointer,
                     const std::size_t offset, const JSON &value) -> void {
  if (offset == pointer.size()) {
    container.into(value);
    return;
  }

  const auto &token{pointer.at(offset)};
  if (token.is_property()) {
    if (!container.is_object()) {
      throw TransformError{"A destination names a member of a non-object"};
    }

    if (!container.defines(token.to_property())) {
      // What a missing container has to be is decided by the token that
      // follows it, so that a destination such as `/allOf/0` builds an array
      // rather than an object with a member named `0`
      const auto wants_array{offset + 1 < pointer.size() &&
                             pointer.at(offset + 1).is_index()};
      container.assign(token.to_property(),
                       wants_array ? JSON::make_array() : JSON::make_object());
    }

    assign_creating(container.at(token.to_property()), pointer, offset + 1,
                    value);
    return;
  }

  if (!container.is_array()) {
    throw TransformError{"A destination names an element of a non-array"};
  }

  while (container.size() <= token.to_index()) {
    const auto wants_array{offset + 1 < pointer.size() &&
                           pointer.at(offset + 1).is_index()};
    container.push_back(wants_array ? JSON::make_array() : JSON::make_object());
  }

  assign_creating(container.at(token.to_index()), pointer, offset + 1, value);
}

auto apply_erase(const JSON &edit, JSON &term,
                 const TransformBindings &bindings,
                 const TransformPredicate &predicate) -> void {
  const auto &specification{edit.at("erase")};
  if (!term.is_object()) {
    throw TransformError{"An erase takes an object term"};
  }

  const auto optional{edit.defines("optional") &&
                      edit.at("optional").to_boolean()};

  if (specification.is_string()) {
    if (!term.defines(specification.to_string())) {
      if (optional) {
        return;
      }

      throw TransformError{"An erase names a member that is not there"};
    }

    if (edit.defines("when")) {
      TransformBindings discarded{bindings};
      if (!transform_guard(edit.at("when"), term.at(specification.to_string()),
                           predicate, discarded)) {
        return;
      }
    }

    term.erase(specification.to_string());
    return;
  }

  if (!specification.is_array()) {
    throw TransformError{"An erase takes a string or an array"};
  }

  for (const auto &key : specification.as_array()) {
    if (!key.is_string()) {
      throw TransformError{"An erase takes string entries"};
    }

    if (!term.defines(key.to_string())) {
      if (optional) {
        continue;
      }

      throw TransformError{"An erase names a member that is not there"};
    }

    term.erase(key.to_string());
  }
}

auto apply_set(const JSON &edit, JSON &term, const JSON &self,
               const TransformBindings &bindings,
               const TransformFunction &function,
               const std::vector<JSON::String> &original, TransformTrace &trace)
    -> void {
  const auto &current{term};
  const auto &members{edit.at("set")};
  if (!members.is_object()) {
    throw TransformError{"A set takes an object"};
  }

  if (!term.is_object()) {
    throw TransformError{"A set takes an object term"};
  }

  const auto placement{read_placement(edit)};
  for (const auto &entry : members.as_object()) {
    Pointer position;
    position.push_back(entry.first);
    auto built{build_template(entry.second, self, current, bindings, function,
                              position)};
    insert_member(term, entry.first, built.value, placement, original);
    for (auto &relocation : built.relocations) {
      trace.relocations.push_back(std::move(relocation));
    }

    for (auto &pointer : built.opaque) {
      trace.opaque.push_back(std::move(pointer));
    }
  }
}

/// A move pointer may be written out or built, so that a destination which
/// depends on what the term already holds can be named at all
auto move_pointer(const JSON &specification, const JSON &self,
                  const JSON &current, const TransformBindings &bindings,
                  const TransformFunction &function) -> Pointer {
  if (specification.is_string()) {
    return to_pointer(specification.to_string());
  }

  const auto built{build_template(specification, self, current, bindings,
                                  function, Pointer{})};
  if (!built.value.is_string()) {
    throw TransformError{"A move pointer must resolve to a string"};
  }

  return to_pointer(built.value.to_string());
}

auto apply_move(const JSON &specification, JSON &term, const JSON &self,
                const TransformBindings &bindings,
                const TransformPredicate &predicate,
                const TransformFunction &function,
                const std::vector<JSON::String> &original,
                TransformTrace &trace) -> void {
  if (!specification.is_object() || !specification.defines("from") ||
      !specification.defines("to")) {
    throw TransformError{"A move takes an object with from and to"};
  }

  const auto source{
      move_pointer(specification.at("from"), self, term, bindings, function)};
  const auto target{
      move_pointer(specification.at("to"), self, term, bindings, function)};
  if (source.empty() || target.empty()) {
    throw TransformError{"A move pointer must name a position"};
  }

  if (try_get(term, source) == nullptr) {
    if (specification.defines("optional") &&
        specification.at("optional").to_boolean()) {
      return;
    }

    throw TransformError{"A move names a source that is not there"};
  }

  // A move may decline on what it finds, which is how a rule leaves alone a
  // keyword that happens to carry the shape the older dialect gave it
  if (specification.defines("when")) {
    TransformBindings discarded{bindings};
    if (!transform_guard(specification.at("when"), get(term, source), predicate,
                         discarded)) {
      return;
    }
  }

  const auto value{get(term, source)};

  // A move within one parent keeps its position, so it reads as a rename,
  // unless it says otherwise. A rewrite that drops a keyword and introduces a
  // different one at the end is not a rename and has to say so
  if (source.size() == 1 && target.size() == 1 && source.at(0).is_property() &&
      target.at(0).is_property() && term.is_object()) {
    const auto stated{
        specification.defines("before") || specification.defines("after") ||
        specification.defines("first") || specification.defines("last")};
    const auto placement{stated
                             ? read_placement(specification)
                             : Placement{.kind = Placement::Kind::Before,
                                         .anchor = source.at(0).to_property()}};
    insert_member(term, target.at(0).to_property(), value, placement, original);
    term.erase(source.at(0).to_property());
    trace.relocations.emplace_back(source, target);
    return;
  }

  // A destination nested under a member the term does not have yet is placed
  // where the move says, which is how a rewrite that wraps a keyword keeps the
  // object in the order it was written
  if (target.size() > 1 && target.at(0).is_property() && term.is_object() &&
      !term.defines(target.at(0).to_property()) && source.size() == 1 &&
      source.at(0).is_property()) {
    insert_member(term, target.at(0).to_property(),
                  target.at(1).is_index() ? JSON::make_array()
                                          : JSON::make_object(),
                  read_placement(specification), original);
  }

  assign_creating(term, target, 0, value);
  [[maybe_unused]] const auto removed{remove(term, source)};
  trace.relocations.emplace_back(source, target);
}

auto substitute_key(const JSON::String &destination, const JSON::String &key)
    -> Pointer {
  const auto parsed{to_pointer(destination)};
  Pointer result;
  for (std::size_t index = 0; index < parsed.size(); index += 1) {
    const auto &token{parsed.at(index)};
    if (token.is_property()) {
      result.push_back(token.to_property() == "$key" ? key
                                                     : token.to_property());
      continue;
    }

    result.push_back(token.to_index());
  }

  return result;
}

auto apply_distribute(const JSON &specification, JSON &term, const JSON &self,
                      const TransformBindings &bindings,
                      const TransformPredicate &predicate,
                      const TransformFunction &function,
                      const std::vector<JSON::String> &original,
                      TransformTrace &trace) -> void {
  if (!specification.is_object() || !specification.defines("from") ||
      !specification.defines("cases")) {
    throw TransformError{"A distribute takes an object with from and cases"};
  }

  if (!specification.at("from").is_string()) {
    throw TransformError{"A distribute takes a binding name"};
  }

  // Distributing the term's own members is how a rule moves a set of keywords
  // it cannot name ahead of time, such as every sibling of a `$ref`
  const auto &source_name{specification.at("from").to_string()};
  const auto over_self{source_name == "$self"};
  Pointer origin;
  JSON source{self};
  if (source_name.starts_with('/')) {
    // Naming a position rather than a binding is what lets a rule whose match
    // reached the member through a branch of an `any` still distribute it
    origin = to_pointer(source_name);
    const auto *value{try_get(self, origin)};
    if (value == nullptr) {
      throw TransformError{"A distribute names a source that is not there"};
    }

    source = *value;
  } else if (!over_self) {
    const auto iterator{bindings.find(source_name)};
    if (iterator == bindings.cend()) {
      throw TransformError{"A distribute names a binding that was never bound"};
    }

    source = iterator->second.value;
    origin = iterator->second.pointer;
  }

  if (!source.is_object()) {
    throw TransformError{"A distribute takes an object source"};
  }

  const auto &cases{specification.at("cases")};
  if (!cases.is_array() || cases.empty()) {
    throw TransformError{"A distribute takes a non-empty array of cases"};
  }

  const auto prune{specification.defines("prune-empty") &&
                   specification.at("prune-empty").to_boolean()};
  const auto placement{read_placement(specification)};

  // Every destination a case names, in the order the cases name them, so that
  // output member order follows the rule rather than the input
  std::vector<std::pair<JSON::String, JSON>> destinations;
  for (const auto &entry : cases.as_array()) {
    if (!entry.is_object() || !entry.defines("to")) {
      throw TransformError{"A case takes a destination"};
    }

    if (!entry.at("to").is_string()) {
      continue;
    }

    const auto root{to_pointer(entry.at("to").to_string())};
    if (root.empty() || !root.at(0).is_property()) {
      throw TransformError{"A case destination must name a member"};
    }

    const auto name{root.at(0).to_property()};
    if (name == "$key") {
      continue;
    }

    auto existing{false};
    for (const auto &candidate : destinations) {
      existing = existing || candidate.first == name;
    }

    if (!existing) {
      destinations.emplace_back(name, JSON::make_object());
    }
  }

  const auto keep{specification.defines("unclaimed") &&
                  specification.at("unclaimed").to_string() == "keep"};

  for (const auto &member : source.as_object()) {
    auto claimed{false};
    TransformBindings local{bindings};
    local.insert_or_assign("$key",
                           TransformBinding{.value = JSON{member.first},
                                            .pointer = Pointer{member.first}});
    local.insert_or_assign("$value",
                           TransformBinding{.value = member.second,
                                            .pointer = Pointer{member.first}});

    for (const auto &entry : cases.as_array()) {
      TransformBindings discarded{bindings};
      if (entry.defines("key") &&
          !transform_guard(entry.at("key"), JSON{member.first}, predicate,
                           discarded)) {
        continue;
      }

      if (entry.defines("when") &&
          !transform_guard(entry.at("when"), member.second, predicate,
                           discarded)) {
        continue;
      }

      // A destination of `/$key` leaves the member exactly where it is, which
      // is how a case says that this one is not the rule's business
      if (entry.at("to").is_string() && entry.at("to").to_string() == "/$key") {
        claimed = true;
        break;
      }

      // A computed destination is resolved against the term as it stands,
      // not as it began, so that a name an earlier member of this same
      // distribute has already taken is one this one moves around
      const auto destination{
          entry.at("to").is_string()
              ? substitute_key(entry.at("to").to_string(), member.first)
              : move_pointer(entry.at("to"), term, term, local, function)};

      // A case may rewrite what it moves, which is how a container that
      // reads its members differently from the one they came from takes a
      // value across in the shape it can read
      const auto moved{entry.defines("as")
                           ? build_template(entry.at("as"), self, term, local,
                                            function, destination)
                                 .value
                           : member.second};

      for (auto &candidate : destinations) {
        if (candidate.first != destination.at(0).to_property()) {
          continue;
        }

        Pointer tail;
        for (std::size_t index = 1; index < destination.size(); index += 1) {
          if (destination.at(index).is_property()) {
            tail.push_back(destination.at(index).to_property());
            continue;
          }

          tail.push_back(destination.at(index).to_index());
        }

        assign_creating(candidate.second, tail, 0, moved);
      }

      auto landed{false};
      for (auto &candidate : destinations) {
        landed = landed || candidate.first == destination.at(0).to_property();
      }

      if (!landed) {
        const auto &value{moved};
        // A member that moves to a sibling keeps the position it had, the way
        // a rename does, so that shadowing a keyword does not reorder the
        // object around it
        if (destination.size() == 1 && destination.at(0).is_property()) {
          const Placement where{.kind = Placement::Kind::Before,
                                .anchor = member.first};
          insert_member(term, destination.at(0).to_property(), value, where,
                        original);
          term.erase(member.first);
        } else {
          term.erase(member.first);
          assign_creating(term, destination, 0, value);
        }
      }

      auto from{origin};
      from.push_back(member.first);
      trace.relocations.emplace_back(std::move(from), destination);
      claimed = true;
      break;
    }

    if (!claimed && !keep) {
      throw TransformError{"A distribute left a member unclaimed"};
    }
  }

  const auto named_source{!over_self && origin.size() == 1 &&
                          origin.at(0).is_property()};
  auto rebuilt_source{false};
  for (auto &destination : destinations) {
    if (prune && destination.second.empty()) {
      continue;
    }

    rebuilt_source =
        rebuilt_source ||
        (named_source && destination.first == origin.at(0).to_property());
    insert_member(term, destination.first, destination.second, placement,
                  original);
  }

  // The source is consumed unless a case sent something back under its own
  // name, in which case what was placed there is what it now holds
  if (named_source && !rebuilt_source && term.is_object() &&
      term.defines(origin.at(0).to_property())) {
    term.erase(origin.at(0).to_property());
  }
}

} // namespace

auto transform_apply(const sourcemeta::core::JSON &build,
                     sourcemeta::core::JSON &term,
                     const TransformBindings &bindings,
                     const TransformPredicate &predicate,
                     const TransformFunction &function) -> TransformTrace {
  if (!build.is_array()) {
    throw TransformError{"A build takes an array of edits"};
  }

  TransformTrace trace;
  const auto self{term};

  // Placement anchors resolve against the term as it stood before any edit
  std::vector<sourcemeta::core::JSON::String> original;
  if (term.is_object()) {
    original.reserve(term.size());
    for (const auto &entry : term.as_object()) {
      original.push_back(entry.first);
    }
  }

  for (const auto &edit : build.as_array()) {
    if (!edit.is_object() || edit.empty()) {
      throw TransformError{"An edit must be an object with one operation"};
    }

    // An edit may stand down on what the term held before the build began,
    // which is how one rule expresses a rewrite whose shape depends on a
    // member an earlier edit has already taken away
    if (edit.defines("if")) {
      TransformBindings discarded{bindings};
      if (!transform_guard(edit.at("if"), self, predicate, discarded)) {
        continue;
      }
    }

    // And it may stand down on what the term holds now, which is what an edit
    // placed after one that fills a member in needs to ask about
    if (edit.defines("if-current")) {
      TransformBindings discarded{bindings};
      if (!transform_guard(edit.at("if-current"), term, predicate, discarded)) {
        continue;
      }
    }

    if (edit.defines("set")) {
      apply_set(edit, term, self, bindings, function, original, trace);
    } else if (edit.defines("erase")) {
      apply_erase(edit, term, bindings, predicate);
    } else if (edit.defines("move")) {
      apply_move(edit.at("move"), term, self, bindings, predicate, function,
                 original, trace);
    } else if (edit.defines("distribute")) {
      apply_distribute(edit.at("distribute"), term, self, bindings, predicate,
                       function, original, trace);
    } else if (edit.defines("replace")) {
      auto built{build_template(edit.at("replace"), self, term, bindings,
                                function, sourcemeta::core::Pointer{})};
      term.into(std::move(built.value));
      for (auto &relocation : built.relocations) {
        trace.relocations.push_back(std::move(relocation));
      }

      for (auto &pointer : built.opaque) {
        trace.opaque.push_back(std::move(pointer));
      }
    } else {
      throw TransformError{"Unknown edit"};
    }
  }

  return trace;
}

#endif
