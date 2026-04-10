#ifndef SOURCEMETA_BLAZE_ALTERSCHEMA_TEST_TRANSFORM_RULES_H_
#define SOURCEMETA_BLAZE_ALTERSCHEMA_TEST_TRANSFORM_RULES_H_

#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/core/jsonschema.h>

class ExampleRule1 final : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRule1()
      : sourcemeta::blaze::SchemaTransformRule(
            "example_rule_1", "Keyword foo is not permitted") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return schema.defines("foo");
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.erase("foo");
  }
};

class ExampleRule1WithPointer final
    : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRule1WithPointer()
      : sourcemeta::blaze::SchemaTransformRule(
            "example_rule_1", "Keyword foo is not permitted") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    if (schema.defines("foo")) {
      return sourcemeta::core::Pointer{"foo"};
    } else {
      return false;
    }
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.erase("foo");
  }
};

class ExampleRule1WithDescription final
    : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRule1WithDescription()
      : sourcemeta::blaze::SchemaTransformRule(
            "example_rule_1", "Keyword foo is not permitted") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    if (schema.defines("foo")) {
      std::ostringstream message;
      message << "This is a message from the rule";
      return {{sourcemeta::core::Pointer{"foo"}}, std::move(message).str()};
    } else {
      return false;
    }
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.erase("foo");
  }
};

class ExampleRuleWithManyPointers final
    : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRuleWithManyPointers()
      : sourcemeta::blaze::SchemaTransformRule(
            "example_rule_with_many_pointers", "Foo Bar") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    if (schema.defines("foo") && schema.defines("bar")) {
      std::vector<sourcemeta::core::Pointer> locations;
      locations.emplace_back(sourcemeta::core::Pointer{"foo"});
      locations.emplace_back(sourcemeta::core::Pointer{"bar"});
      return locations;
    } else {
      return false;
    }
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.erase("foo");
  }
};

class ExampleRule2 final : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRule2()
      : sourcemeta::blaze::SchemaTransformRule(
            "example_rule_2", "Keyword bar is not permitted") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return schema.defines("bar");
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.erase("bar");
  }
};

class ExampleRule3 final : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRule3()
      : sourcemeta::blaze::SchemaTransformRule("example_rule_3",
                                               "Example rule 3") {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return !schema.defines("top") && location.pointer.empty();
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.assign("top", sourcemeta::core::JSON{true});
  }
};

class ExampleRule4 final : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRule4()
      : sourcemeta::blaze::SchemaTransformRule("example_rule_4",
                                               "Example rule 4") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return !schema.defines("here");
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.assign("here", sourcemeta::core::JSON{true});
  }
};

class ExampleRule5 final : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRule5()
      : sourcemeta::blaze::SchemaTransformRule("example_rule_5",
                                               "Example rule 5") {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    const sourcemeta::core::Pointer expected{"properties", "baz"};
    return !schema.defines("baz") &&
           location.pointer == sourcemeta::core::to_weak_pointer(expected);
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.assign("baz", sourcemeta::core::JSON{true});
  }
};

class ExampleRule6 final : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRule6()
      : sourcemeta::blaze::SchemaTransformRule("example_rule_6",
                                               "Example rule 6") {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &location,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return !schema.defines("draft") &&
           location.dialect == "http://json-schema.org/draft-03/schema#";
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.assign("draft", sourcemeta::core::JSON{3});
  }
};

class ExampleRule7 final : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRule7()
      : sourcemeta::blaze::SchemaTransformRule("example_rule_1",
                                               "My custom message") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return schema.defines("foo");
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.erase("foo");
  }
};

class ExampleRuleConflictsWith1 final
    : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRuleConflictsWith1()
      : sourcemeta::blaze::SchemaTransformRule(
            "example_rule_conflicts_with_1",
            "Example rule that conflicts with rule 1") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return schema.defines("$schema") && schema.size() == 1;
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.assign("foo", sourcemeta::core::JSON{true});
  }
};

class ExampleRuleUnfixable1 final
    : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::false_type;
  using reframe_after_transform = std::false_type;
  ExampleRuleUnfixable1()
      : sourcemeta::blaze::SchemaTransformRule(
            "example_rule_unfixable_1",
            "An example rule that cannot be fixed") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return schema.defines("foo");
  }
};

class ExampleRuleDefinitionsToDefsNoRereference final
    : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRuleDefinitionsToDefsNoRereference()
      : sourcemeta::blaze::SchemaTransformRule(
            "example_rule_definitions_to_defs_no_rereference",
            "Rename `definitions` to `$defs`") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return schema.defines("definitions") && !schema.defines("$defs");
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.rename("definitions", "$defs");
  }
};

class ExampleRuleDefinitionsToDefsWithRereference final
    : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRuleDefinitionsToDefsWithRereference()
      : sourcemeta::blaze::SchemaTransformRule(
            "example_rule_definitions_to_defs_with_rereference",
            "Rename `definitions` to `$defs`") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return schema.defines("definitions") && !schema.defines("$defs");
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.rename("definitions", "$defs");
  }

  [[nodiscard]] auto rereference(const std::string_view,
                                 const sourcemeta::core::Pointer &,
                                 const sourcemeta::core::Pointer &target,
                                 const sourcemeta::core::Pointer &current) const
      -> sourcemeta::core::Pointer override {
    return target.rebase(current.concat({"definitions"}),
                         current.concat({"$defs"}));
  }
};

class ExampleRuleRemoveIdentifiers final
    : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRuleRemoveIdentifiers()
      : sourcemeta::blaze::SchemaTransformRule(
            "example_rule_remove_identifiers", "Remove all identifiers") {};

  [[nodiscard]] auto condition(const sourcemeta::core::JSON &schema,
                               const sourcemeta::core::JSON &,
                               const sourcemeta::core::Vocabularies &,
                               const sourcemeta::core::SchemaFrame &,
                               const sourcemeta::core::SchemaFrame::Location &,
                               const sourcemeta::core::SchemaWalker &,
                               const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    return schema.is_object() &&
           (schema.defines("$id") || schema.defines("$anchor"));
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.erase_keys({"$id", "$anchor"});
  }
};

class ExampleRuleDraftTag final
    : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRuleDraftTag()
      : sourcemeta::blaze::SchemaTransformRule("example_rule_draft_tag", "") {};

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    if (!schema.is_object() || schema.defines("x-dialect-type")) {
      return false;
    }

    return vocabularies.contains(
               sourcemeta::core::Vocabularies::Known::JSON_Schema_Draft_7) ||
           vocabularies.contains(
               sourcemeta::core::Vocabularies::Known::JSON_Schema_Draft_6) ||
           vocabularies.contains(
               sourcemeta::core::Vocabularies::Known::JSON_Schema_Draft_4);
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.assign("x-dialect-type", sourcemeta::core::JSON{"draft"});
  }
};

class ExampleRuleModernTag final
    : public sourcemeta::blaze::SchemaTransformRule {
public:
  using mutates = std::true_type;
  using reframe_after_transform = std::true_type;
  ExampleRuleModernTag()
      : sourcemeta::blaze::SchemaTransformRule("example_rule_modern_tag", "") {
        };

  [[nodiscard]] auto
  condition(const sourcemeta::core::JSON &schema,
            const sourcemeta::core::JSON &,
            const sourcemeta::core::Vocabularies &vocabularies,
            const sourcemeta::core::SchemaFrame &,
            const sourcemeta::core::SchemaFrame::Location &,
            const sourcemeta::core::SchemaWalker &,
            const sourcemeta::core::SchemaResolver &) const
      -> sourcemeta::blaze::SchemaTransformRule::Result override {
    if (!schema.is_object() || schema.defines("x-dialect-type")) {
      return false;
    }

    return vocabularies.contains(sourcemeta::core::Vocabularies::Known::
                                     JSON_Schema_2020_12_Core) ||
           vocabularies.contains(
               sourcemeta::core::Vocabularies::Known::JSON_Schema_2019_09_Core);
  }

  auto transform(sourcemeta::core::JSON &schema,
                 const sourcemeta::blaze::SchemaTransformRule::Result &) const
      -> void override {
    schema.assign("x-dialect-type", sourcemeta::core::JSON{"modern"});
  }
};

#endif
