#include <gtest/gtest.h>

#include <sourcemeta/blaze/alterschema.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include "alterschema_test_utils.h"

TEST(AlterSchema_upgrade_Draft7_to_2019_09, true_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("true");
  const auto expected = sourcemeta::core::parse_json("true");
  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, false_boolean_schema_unchanged) {
  auto document = sourcemeta::core::parse_json("false");
  const auto expected = sourcemeta::core::parse_json("false");
  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, dollar_schema_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     dollar_schema_with_https_scheme_normalized_and_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     dollar_schema_without_empty_fragment_normalized_and_bumped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, trivial_root) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "string"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, idempotent_after_first_pass) {
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

TEST(AlterSchema_upgrade_Draft7_to_2019_09, already_2019_09_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": { "type": "string" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, already_2020_12_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, id_pure_fragment_becomes_anchor) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "#tag"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$anchor": "tag"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     id_uri_with_empty_fragment_strips_fragment) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com#"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, id_uri_only_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$id": "https://example.com"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$id": "https://example.com"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     definitions_renamed_via_definitions_to_defs_linter) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     definitions_inside_embedded_resource) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-07/schema#",
        "definitions": {
          "foo": { "type": "string" }
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "$defs": {
          "foo": { "type": "string" }
        }
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     empty_definitions_renamed_in_place) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {}
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, dependencies_split_mixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "dependencies": {
      "foo": { "type": "string" },
      "bar": false,
      "baz": true,
      "qux": [ "foo" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "type": "string" },
      "bar": false,
      "baz": true
    },
    "dependentRequired": {
      "qux": [ "foo" ]
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     dependencies_only_arrays_no_schemas_branch_emitted) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "dependencies": {
      "qux": [ "foo" ]
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentRequired": {
      "qux": [ "foo" ]
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     dependencies_only_schemas_no_required_branch_emitted) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "dependencies": {
      "foo": { "type": "string" },
      "bar": false,
      "baz": true
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "type": "string" },
      "bar": false,
      "baz": true
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     dependencies_with_invalid_value_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "dependencies": {
      "foo": "not-a-valid-value"
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependencies": {
      "foo": "not-a-valid-value"
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     dependencies_left_alone_when_dependent_schemas_already_present) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "dependencies": {
      "foo": [ "bar" ]
    },
    "x-dependentSchemas": {
      "qux": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentRequired": {
      "foo": [ "bar" ]
    },
    "x-dependentSchemas": {
      "qux": { "type": "string" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, dependencies_empty_object_dropped) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "dependencies": {}
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_through_dependencies_rewritten_to_dependentSchemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_through_dependencies_deep_pointer) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_through_dependencies_cross_entries) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "dependencies": {
      "foo": { "$ref": "#/dependencies/bar" },
      "bar": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "dependentSchemas": {
      "foo": { "$ref": "#/dependentSchemas/bar" },
      "bar": { "type": "string" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     id_fragment_becomes_anchor_inside_defs) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "Outer": {
        "$id": "#tag"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "Outer": {
        "$anchor": "tag"
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_through_dependencies_inside_defs) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     dependencies_two_levels_deep_inside_defs) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "Outer": {
        "definitions": {
          "Inner": {
            "dependencies": {
              "foo": { "type": "string" }
            }
          }
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "Outer": {
        "$defs": {
          "Inner": {
            "dependentSchemas": {
              "foo": { "type": "string" }
            }
          }
        }
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     id_fragment_inside_dependencies_inside_defs) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "Outer": {
        "dependencies": {
          "foo": { "$id": "#tag" }
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "Outer": {
        "dependentSchemas": {
          "foo": { "$anchor": "tag" }
        }
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     dependencies_in_embedded_resource_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "dependentSchemas": {
          "foo": { "type": "string" }
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
        "dependentSchemas": {
          "foo": { "type": "string" }
        }
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_through_dependencies_in_mixed_split_targets_dependentSchemas) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_with_sibling_validation_keywords_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_upgrade_Draft7_to_2019_09, ref_with_no_siblings_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/definitions/foo"
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
        "$ref": "#/$defs/foo"
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_with_sibling_collision_double_prefix) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/definitions/foo",
        "type": "string",
        "x-type": "already-here"
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
        "x-x-type": "string",
        "x-type": "already-here"
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_with_read_only_sibling_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/definitions/foo",
        "readOnly": true
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
        "readOnly": true
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_with_content_keywords_siblings_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/definitions/foo",
        "contentMediaType": "text/plain",
        "contentEncoding": "base64"
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
        "contentMediaType": "text/plain",
        "contentEncoding": "base64"
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_with_dollar_id_sibling_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$id": "https://example.com/inner",
        "$ref": "#/definitions/foo"
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
        "$id": "https://example.com/inner",
        "$ref": "#/definitions/foo"
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_with_pure_annotation_siblings_left_alone) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/definitions/foo",
        "title": "My Title",
        "description": "My Description",
        "default": "x",
        "examples": [ "y" ],
        "$comment": "A comment"
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
        "title": "My Title",
        "description": "My Description",
        "default": "x",
        "examples": [ "y" ],
        "$comment": "A comment"
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     ref_with_mixed_annotation_and_validation_siblings) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": { "type": "string" }
    },
    "properties": {
      "value": {
        "$ref": "#/definitions/foo",
        "title": "My Title",
        "type": "string",
        "description": "My Description",
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
        "title": "My Title",
        "x-type": "string",
        "description": "My Description",
        "x-minLength": 3
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, ref_alone_inside_definitions) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "definitions": {
      "foo": { "$ref": "#/definitions/bar" },
      "bar": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "$defs": {
      "foo": { "$ref": "#/$defs/bar" },
      "bar": { "type": "string" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, custom_dollar_anchor_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$anchor": "my-anchor"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-$anchor": "my-anchor"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     custom_dollar_recursive_anchor_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$recursiveAnchor": true
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-$recursiveAnchor": true
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     custom_dollar_recursive_ref_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$recursiveRef": "#"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-$recursiveRef": "#"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, custom_dollar_vocabulary_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$vocabulary": { "https://example.com/vocab": true }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-$vocabulary": { "https://example.com/vocab": true }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     custom_dollar_defs_prefixed_then_definitions_promoted) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$defs": "old-defs-value",
    "definitions": {
      "foo": { "type": "string" }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-$defs": "old-defs-value",
    "$defs": {
      "foo": { "type": "string" }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, custom_dependent_schemas_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "dependentSchemas": "custom-value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-dependentSchemas": "custom-value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     custom_dependent_required_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "dependentRequired": "custom-value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-dependentRequired": "custom-value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, custom_unevaluated_items_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "unevaluatedItems": "custom-value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-unevaluatedItems": "custom-value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     custom_unevaluated_properties_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "unevaluatedProperties": "custom-value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-unevaluatedProperties": "custom-value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, custom_max_contains_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "maxContains": "custom-value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-maxContains": "custom-value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, custom_min_contains_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "minContains": "custom-value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-minContains": "custom-value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, custom_content_schema_prefixed) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "contentSchema": "custom-value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-contentSchema": "custom-value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     custom_deprecated_prefixed_to_preserve_metaschema_validity) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "deprecated": "string explanation"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-deprecated": "string explanation"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     multiple_promoted_keywords_prefixed_in_one_pass) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "$anchor": "tag",
    "deprecated": "reason",
    "minContains": 1,
    "maxContains": 5
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "x-$anchor": "tag",
    "x-deprecated": "reason",
    "x-minContains": 1,
    "x-maxContains": 5
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     unrelated_custom_keyword_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "myAnnotation": "value"
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "myAnnotation": "value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, single_item_enum_becomes_const) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ "single-value" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "const": "single-value"
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09, multi_item_enum_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "enum": [ "foo", "bar" ]
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "enum": [ "foo", "bar" ]
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     nested_subschemas_only_root_changes_when_no_inner_pending) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "properties": {
      "foo": { "type": "string" },
      "bar": {
        "type": "object",
        "properties": {
          "nested": { "type": "integer" }
        }
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "foo": { "type": "string" },
      "bar": {
        "type": "object",
        "properties": {
          "nested": { "type": "integer" }
        }
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     embedded_draft_7_resource_also_upgraded) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "http://json-schema.org/draft-07/schema#",
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

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     nested_2020_12_resource_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string"
      }
    }
  })JSON");

  const auto expected = sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string"
      }
    }
  })JSON");

  UPGRADE_2019_09(document, expected);
}

TEST(AlterSchema_upgrade_Draft7_to_2019_09,
     nested_2019_09_resource_left_unchanged) {
  auto document = sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-07/schema#",
    "properties": {
      "embedded": {
        "$id": "https://example.com/inner",
        "$schema": "https://json-schema.org/draft/2019-09/schema",
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
