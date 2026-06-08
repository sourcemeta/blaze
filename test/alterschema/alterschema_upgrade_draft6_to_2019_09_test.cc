#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft6_to_2019_09, true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, definitions_renamed_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "foo": { "$ref": "#/definitions/foo" }
    },
    "definitions": {
      "foo": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "foo": { "$ref": "#/$defs/foo" }
    },
    "$defs": {
      "foo": { "type": "string" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, dependencies_split_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "dependencies": {
      "foo": { "type": "string" },
      "qux": [ "foo" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "type": "string" }
    },
    "dependentRequired": {
      "qux": [ "foo" ]
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     ref_through_dependencies_rewritten_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "dependencies": {
      "foo": { "type": "string" }
    },
    "properties": {
      "x": { "$ref": "#/dependencies/foo" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "type": "string" }
    },
    "properties": {
      "x": { "$ref": "#/dependentSchemas/foo" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     ref_through_dependencies_deep_pointer_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "dependencies": {
      "foo": {
        "type": "object",
        "properties": {
          "x": { "type": "string" }
        }
      }
    },
    "properties": {
      "y": { "$ref": "#/dependencies/foo/properties/x" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": {
        "type": "object",
        "properties": {
          "x": { "type": "string" }
        }
      }
    },
    "properties": {
      "y": { "$ref": "#/dependentSchemas/foo/properties/x" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     ref_through_dependencies_in_mixed_split_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "dependencies": {
      "foo": { "type": "string" },
      "qux": [ "bar" ]
    },
    "properties": {
      "x": { "$ref": "#/dependencies/foo" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "type": "string" }
    },
    "dependentRequired": {
      "qux": [ "bar" ]
    },
    "properties": {
      "x": { "$ref": "#/dependentSchemas/foo" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     ref_through_dependencies_inside_defs_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "Outer": {
        "dependencies": {
          "foo": { "type": "string" }
        }
      }
    },
    "properties": {
      "x": { "$ref": "#/definitions/Outer/dependencies/foo" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "Outer": {
        "dependentSchemas": {
          "foo": { "type": "string" }
        }
      }
    },
    "properties": {
      "x": { "$ref": "#/$defs/Outer/dependentSchemas/foo" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     ref_with_sibling_validation_keywords_prefixed_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/definitions/foo",
        "type": "string",
        "minLength": 3
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/$defs/foo",
        "x-type": "string",
        "x-minLength": 3
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     id_pure_fragment_becomes_anchor_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "#tag"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": "tag"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     draft_7_promoted_keyword_in_draft_6_schema_prefixed_first) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "if": "custom-value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-if": "custom-value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, idempotent_after_first_pass) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09, single_item_enum_becomes_const) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "enum": [ "single-value" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": "single-value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     embedded_draft_4_resource_also_upgraded_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "properties": {
      "embedded": {
        "id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "type": "string"
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     ref_with_sibling_keywords_prefixed_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/definitions/foo",
        "type": "string",
        "minLength": 3
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/$defs/foo",
        "x-type": "string",
        "x-minLength": 3
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     no_dollar_schema_with_default_dialect_draft6) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$id": "https://example.com/test",
    "type": "integer"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/test",
    "type": "integer"
  })JSON");

  UPGRADE_2019_09_WITH_DIALECT(document, expected,
                               "http://json-schema.org/draft-06/schema#");
}

TEST(AlterSchema_upgrade_Draft6_to_2019_09,
     metaschema_cascade_from_draft6_emits_2019_09_vocabulary) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-06/schema#",
    "$id": "https://example.com/my-dialect",
    "type": "object"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com/my-dialect",
    "$vocabulary": {
      "https://json-schema.org/draft/2019-09/vocab/core": true,
      "https://json-schema.org/draft/2019-09/vocab/applicator": true,
      "https://json-schema.org/draft/2019-09/vocab/validation": true,
      "https://json-schema.org/draft/2019-09/vocab/meta-data": true,
      "https://json-schema.org/draft/2019-09/vocab/format": false,
      "https://json-schema.org/draft/2019-09/vocab/content": true
    },
    "type": "object"
  })JSON");

  UPGRADE_2019_09_AS_METASCHEMA(document, expected);
}
