#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft4_to_2019_09, true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09, false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     ref_through_dependencies_rewritten_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     ref_through_dependencies_deep_pointer_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     ref_through_dependencies_in_mixed_split_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     ref_through_dependencies_inside_defs_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     uri_fragment_ref_resolves_to_anchor_after_id_split) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "Outer": {
        "id": "#tag",
        "type": "string"
      }
    },
    "properties": {
      "x": { "$ref": "#tag" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "Outer": {
        "$anchor": "tag",
        "type": "string"
      }
    },
    "properties": {
      "x": { "$ref": "#tag" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     ref_with_sibling_validation_keywords_prefixed_through_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     id_renamed_definitions_to_defs_dependencies_split) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "https://example.com",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "ref-to-foo": { "$ref": "#/definitions/foo" }
    },
    "dependencies": {
      "alpha": { "type": "object" },
      "beta": [ "gamma" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com",
    "$defs": {
      "foo": { "type": "string" }
    },
    "properties": {
      "ref-to-foo": { "$ref": "#/$defs/foo" }
    },
    "dependentSchemas": {
      "alpha": { "type": "object" }
    },
    "dependentRequired": {
      "beta": [ "gamma" ]
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(
    AlterSchema_upgrade_Draft4_to_2019_09,
    boolean_exclusive_minimum_folded_then_definitions_renamed_then_dependencies_split) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "minimum": 3,
    "exclusiveMinimum": true,
    "definitions": {
      "foo": { "type": "string" }
    },
    "dependencies": {
      "alpha": [ "beta" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "exclusiveMinimum": 3,
    "$defs": {
      "foo": { "type": "string" }
    },
    "dependentRequired": {
      "alpha": [ "beta" ]
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     id_with_fragment_anchor_split_after_id_promoted) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "id": "#tag"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": "tag"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09, idempotent_after_first_pass) {
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

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     embedded_draft_4_inside_outer_draft_4_both_upgraded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
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

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     mixed_chain_with_promoted_keyword_prefixing) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "const": "draft6-promoted",
    "if": "draft7-promoted",
    "$anchor": "twentynineteen-promoted"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-const": "draft6-promoted",
    "x-if": "draft7-promoted",
    "x-$anchor": "twentynineteen-promoted"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     id_fragment_only_leading_digit_becomes_anchor) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": { "id": "#1foo" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": { "$anchor": "x-1foo" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft4_to_2019_09,
     id_fragment_only_with_local_ref_chain) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "foo": { "id": "#with/slash" }
    },
    "properties": {
      "p": { "$ref": "#with/slash" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": { "$anchor": "with-slash" }
    },
    "properties": {
      "p": { "$ref": "#with-slash" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}
