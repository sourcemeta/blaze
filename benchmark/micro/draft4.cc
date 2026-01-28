#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

static void Micro_Draft4_Meta_1_No_Callback(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "integer" }
    }
  })JSON")};

  const auto metaschema{
      sourcemeta::core::metaschema(schema, sourcemeta::core::schema_resolver)};
  const auto metaschema_template{
      sourcemeta::blaze::compile(metaschema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(metaschema_template, schema)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Required_Properties(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [
      "a", "b", "c", "d", "e", "f", "g", "h", "i",
      "j", "k", "l", "m", "n", "o", "p", "q", "r",
      "s", "t", "u", "v", "w", "x", "y", "z"
    ],
    "properties": {
      "a": { "type": "boolean" },
      "b": { "type": "boolean" },
      "c": { "type": "boolean" },
      "d": { "type": "boolean" },
      "e": { "type": "boolean" },
      "f": { "type": "boolean" },
      "g": { "type": "boolean" },
      "h": { "type": "boolean" },
      "i": { "type": "boolean" },
      "j": { "type": "boolean" },
      "k": { "type": "boolean" },
      "l": { "type": "boolean" },
      "m": { "type": "boolean" },
      "n": { "type": "boolean" },
      "o": { "type": "boolean" },
      "p": { "type": "boolean" },
      "q": { "type": "boolean" },
      "r": { "type": "boolean" },
      "s": { "type": "boolean" },
      "t": { "type": "boolean" },
      "u": { "type": "boolean" },
      "v": { "type": "boolean" },
      "w": { "type": "boolean" },
      "x": { "type": "boolean" },
      "y": { "type": "boolean" },
      "z": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "a": true,
    "b": true,
    "c": true,
    "d": true,
    "e": true,
    "f": true,
    "g": true,
    "h": true,
    "i": true,
    "j": true,
    "k": true,
    "l": true,
    "m": true,
    "n": true,
    "o": true,
    "p": true,
    "q": true,
    "r": true,
    "s": true,
    "t": true,
    "u": true,
    "v": true,
    "w": true,
    "x": true,
    "y": true,
    "z": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void
Micro_Draft4_Many_Optional_Properties_Minimal_Match(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "a": { "type": "boolean" },
      "b": { "type": "boolean" },
      "c": { "type": "boolean" },
      "d": { "type": "boolean" },
      "e": { "type": "boolean" },
      "f": { "type": "boolean" },
      "g": { "type": "boolean" },
      "h": { "type": "boolean" },
      "i": { "type": "boolean" },
      "j": { "type": "boolean" },
      "k": { "type": "boolean" },
      "l": { "type": "boolean" },
      "m": { "type": "boolean" },
      "n": { "type": "boolean" },
      "o": { "type": "boolean" },
      "p": { "type": "boolean" },
      "q": { "type": "boolean" },
      "r": { "type": "boolean" },
      "s": { "type": "boolean" },
      "t": { "type": "boolean" },
      "u": { "type": "boolean" },
      "v": { "type": "boolean" },
      "w": { "type": "boolean" },
      "x": { "type": "boolean" },
      "y": { "type": "boolean" },
      "z": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "p": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void
Micro_Draft4_Few_Optional_Properties_Minimal_Match(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "a": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "a": true,
    "b": true,
    "c": true,
    "d": true,
    "e": true,
    "f": true,
    "g": true,
    "h": true,
    "i": true,
    "j": true,
    "k": true,
    "l": true,
    "m": true,
    "n": true,
    "o": true,
    "p": true,
    "q": true,
    "r": true,
    "s": true,
    "t": true,
    "u": true,
    "v": true,
    "w": true,
    "x": true,
    "y": true,
    "z": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Items_Schema(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "items": {
      "items": {
        "items": {
          "items": {
            "items": {
              "items": {
                "type": "string"
              }
            }
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON([
    [
      [
        [
          [ [ "red", "blue" ], [ "green", "yellow" ] ],
          [ [ "circle", "square" ], [ "triangle", "rectangle" ] ]
        ],
        [
          [ [ "cat", "dog" ], [ "fish", "bird" ] ],
          [ [ "apple", "banana" ], [ "cherry", "date" ] ]
        ]
      ],
      [
        [
          [ [ "hot", "cold" ], [ "wet", "dry" ] ],
          [ [ "big", "small" ], [ "tall", "short" ] ]
        ],
        [
          [ [ "happy", "sad" ], [ "angry", "calm" ] ],
          [ [ "fast", "slow" ], [ "loud", "quiet" ] ]
        ]
      ]
    ],
    [
      [
        [
          [ [ "sun", "moon" ], [ "star", "planet" ] ],
          [ [ "ocean", "mountain" ], [ "forest", "desert" ] ]
        ],
        [
          [ [ "car", "bike" ], [ "train", "plane" ] ],
          [ [ "pencil", "pen" ], [ "paper", "eraser" ] ]
        ]
      ],
      [
        [
          [ [ "jazz", "rock" ], [ "pop", "classical" ] ],
          [ [ "comedy", "drama" ], [ "action", "romance" ] ]
        ],
        [
          [ [ "spring", "summer" ], [ "autumn", "winter" ] ],
          [ [ "breakfast", "lunch" ], [ "dinner", "snack" ] ]
        ]
      ]
    ]
  ])JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Nested_Object(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON(
{
  "$schema": "http://json-schema.org/draft-04/schema#",
  "additionalProperties": {
    "additionalProperties": {
      "additionalProperties": {
        "additionalProperties": {
          "additionalProperties": {
            "additionalProperties": {
              "additionalProperties": {
                "additionalProperties": {
                  "additionalProperties": {
                    "additionalProperties": {
                      "additionalProperties": {
                        "additionalProperties": {
                          "additionalProperties": {
                            "additionalProperties": {
                              "additionalProperties": {
                                "additionalProperties": {
                                  "additionalProperties": {
                                    "additionalProperties": {
                                      "additionalProperties": true
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
  )JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON(
{
  "a1": {
    "a2": {
      "a3": {
        "a4": {
          "a5": {
            "a6": {
              "a7": {
                "a8": {
                  "a9": {
                    "a10": {
                      "a11": {
                        "a12": {
                          "a13": {
                            "a14": {
                              "a15": {
                                "a16": {
                                  "a17": {
                                    "a18": {
                                      "a19": {}
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  },
  "b1": {
    "b2": {
      "b3": {
        "b4": {
          "b5": {
            "b6": {
              "b7": {
                "b8": {
                  "b9": {
                    "b10": {
                      "b11": {
                        "b12": {
                          "b13": {
                            "b14": {
                              "b15": {
                                "b16": {
                                  "b17": {
                                    "b18": {
                                      "b19": {}
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
  )JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Properties_Triad_Optional(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "a": { "type": "boolean" },
      "b": { "type": "boolean" },
      "c": { "type": "boolean" },
      "d": { "type": "boolean" },
      "e": { "type": "boolean" },
      "f": { "type": "boolean" }
    },
    "patternProperties": {
      "^[A-Z]": { "type": "null" }
    },
    "additionalProperties": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "A": null,
    "Z": null,
    "foo": "bar",
    "a": true,
    "c": true,
    "d": true,
    "e": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Properties_Triad_Required(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "required": [ "a", "A", "d" ],
    "properties": {
      "a": { "type": "boolean" },
      "b": { "type": "boolean" },
      "c": { "type": "boolean" },
      "d": { "type": "boolean" },
      "e": { "type": "boolean" },
      "f": { "type": "boolean" }
    },
    "patternProperties": {
      "^[A-Z]": { "type": "null" }
    },
    "additionalProperties": {
      "type": "string"
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "A": null,
    "Z": null,
    "foo": "bar",
    "a": true,
    "c": true,
    "d": true,
    "e": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Properties_Triad_Closed(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "a": { "type": "boolean" },
      "b": { "type": "boolean" },
      "c": { "type": "boolean" },
      "d": { "type": "boolean" },
      "e": { "type": "boolean" },
      "f": { "type": "boolean" }
    },
    "patternProperties": {
      "^[A-Z]": { "type": "null" }
    },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "A": null,
    "Z": null,
    "a": true,
    "c": true,
    "d": true,
    "e": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Properties_Closed(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "properties": {
      "a": { "type": "boolean" },
      "b": { "type": "boolean" },
      "c": { "type": "boolean" },
      "d": { "type": "boolean" },
      "e": { "type": "boolean" },
      "f": { "type": "boolean" },
      "g": { "type": "boolean" },
      "h": { "type": "boolean" },
      "i": { "type": "boolean" },
      "j": { "type": "boolean" },
      "k": { "type": "boolean" },
      "l": { "type": "boolean" },
      "m": { "type": "boolean" },
      "m": { "type": "boolean" },
      "o": { "type": "boolean" },
      "p": { "type": "boolean" },
      "q": { "type": "boolean" }
    },
    "additionalProperties": false
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "a": true,
    "b": true,
    "c": true,
    "d": true,
    "e": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Non_Recursive_Ref(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": { "$ref": "#/definitions/one" },
    "definitions": {
      "one": { "$ref": "#/definitions/two" },
      "two": { "$ref": "#/definitions/three" },
      "three": { "$ref": "#/definitions/four" },
      "four": { "$ref": "#/definitions/five" },
      "five": { "$ref": "#/definitions/six" },
      "six": { "$ref": "#/definitions/seven" },
      "seven": { "$ref": "#/definitions/eight" },
      "eight": { "$ref": "#/definitions/nine" },
      "nine": { "$ref": "#/definitions/ten" },
      "ten": { "type": "boolean" }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "a": true,
    "b": true,
    "c": true,
    "d": true,
    "e": true,
    "f": true,
    "g": true,
    "h": true,
    "i": true,
    "j": true,
    "k": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Pattern_Properties_True(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "patternProperties": { "^@": true },
    "additionalProperties": { "type": "string" }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "@a": true,
    "@b": true,
    "@c": true,
    "@d": true,
    "@e": true,
    "@f": true,
    "a": "test",
    "b": "test",
    "c": "test",
    "d": "test",
    "e": "test",
    "f": "test",
    "g": "test",
    "h": "test",
    "i": "test",
    "j": "test",
    "k": "test"
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Ref_To_Single_Property(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/test" } ],
    "definitions": {
      "test": {
        "properties": {
          "test": {
            "type": "string"
          }
        }
      }
    }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "test": "foo",
    "a": true,
    "b": true,
    "c": true,
    "d": true,
    "e": true,
    "f": true,
    "g": true,
    "h": true,
    "i": true,
    "j": true,
    "k": true,
    "l": true,
    "m": true,
    "n": true,
    "o": true,
    "p": true,
    "q": true,
    "r": true,
    "s": true,
    "t": true,
    "u": true,
    "v": true,
    "w": true,
    "x": true,
    "y": true,
    "z": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Additional_Properties_Type(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "additionalProperties": { "type": "boolean" }
  })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
    "a": true,
    "b": true,
    "c": true,
    "d": true,
    "e": true,
    "f": true,
    "g": true,
    "h": true,
    "i": true,
    "j": true,
    "k": true,
    "l": true,
    "m": true,
    "n": true,
    "o": true,
    "p": true,
    "q": true,
    "r": true,
    "s": true,
    "t": true,
    "u": true,
    "v": true,
    "w": true,
    "x": true,
    "y": true,
    "z": true
  })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Nested_Oneof(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
        "$schema": "http://json-schema.org/draft-04/schema#",
        "oneOf": [
          {
            "oneOf": [
              { "type": "string" },
              { "type": "number" }
            ]
          },
          {
            "oneOf": [
              { "type": "boolean" },
              { "type": "null" }
            ]
          },
          {
            "oneOf": [
              { "type": "array" },
              { "type": "object" }
            ]
          }
        ]
      })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json(R"JSON({
        "key": "value"
      })JSON")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Short_Enum(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
        "$schema": "http://json-schema.org/draft-04/schema#",
        "enum": [ "development", "production", "all" ]
      })JSON")};

  const sourcemeta::core::JSON instance{"production"};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Long_Enum(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
        "$schema": "http://json-schema.org/draft-04/schema#",
        "enum": [
          "apple_orchard_sunset_view",
          "bright_yellow_daffodils_blooming",
          "serene_lakeside_retreat",
          "whispering_pine_forest",
          "vivid_rainbow_arching_over_mountains",
          "peaceful_zen_garden_path",
          "midnight_cityscape_with_stars",
          "crisp_autumn_leaves_falling",
          "gentle_waves_on_sandy_beach",
          "sparkling_winter_snowflake",
          "glimmering_golden_sunrise",
          "tranquil_hills_with_mist",
          "lush_meadow_with_wildflowers",
          "sunlit_tree_canopy",
          "calm_ocean_surf_at_twilight",
          "ancient_castle_ruins",
          "rolling_green_valleys",
          "colorful_parrot_in_rainforest",
          "majestic_eagle_in_flight",
          "hidden_cove_with_turquoise_water",
          "mystical_cave_with_crystals",
          "silent_desert_dunes",
          "starlit_skies_over_open_plains",
          "rustic_farmhouse_in_countryside",
          "cheerful_market_square",
          "picturesque_cliffside_village",
          "bustling_metropolis_skyline",
          "golden_grain_field",
          "charming_floral_garden",
          "wild_horses_running",
          "serene_mountain_lake",
          "gentle_stream_through_forest",
          "historic_bridge_in_morning_fog",
          "vintage_lighthouse_by_sea",
          "cozy_fireplace_in_cabin",
          "mystic_willow_tree",
          "glistening_dew_on_grass",
          "exotic_butterfly_collection",
          "crystal_clear_pond",
          "hidden_waterfall_in_jungle",
          "verdant_bamboo_grove"
        ]
      })JSON")};

  const sourcemeta::core::JSON instance{"verdant_bamboo_grove"};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Long_Enum_Short_Strings(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
        "$schema": "http://json-schema.org/draft-04/schema#",
        "enum": [
          "apple_orchard",
          "bright_yellow",
          "serene_lakeside",
          "whispering_pine",
          "vivid_rainbow",
          "peaceful_zen",
          "midnight_cityscape",
          "crisp_autumn",
          "gentle_waves",
          "sparkling_winter",
          "glimmering_golden",
          "tranquil_hills",
          "lush_meadow",
          "sunlit_tree",
          "calm_ocean",
          "ancient_castle",
          "rolling_green",
          "colorful_parrot",
          "majestic_eagle",
          "hidden_cove",
          "mystical_cave",
          "silent_desert",
          "starlit_skies",
          "rustic_farmhouse",
          "cheerful_market",
          "picturesque_cliffside",
          "bustling_metropolis",
          "golden_grain",
          "charming_floral",
          "wild_horses",
          "serene_mountain",
          "gentle_stream",
          "historic_bridge",
          "vintage_lighthouse",
          "cozy_fireplace",
          "mystic_willow",
          "glistening_dew",
          "exotic_butterfly",
          "crystal_clear",
          "hidden_waterfall",
          "verdant_bamboo"
        ]
      })JSON")};

  const sourcemeta::core::JSON instance{"verdant_bamboo"};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

static void Micro_Draft4_Type_Object(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
        "$schema": "http://json-schema.org/draft-04/schema#",
        "type": "object"
      })JSON")};

  const sourcemeta::core::JSON instance{sourcemeta::core::parse_json("{}")};

  const auto schema_template{
      sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                 sourcemeta::core::schema_resolver,
                                 sourcemeta::blaze::default_schema_compiler)};
  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto result{evaluator.validate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

// Pathological Case: OMC-like Pattern
static void Micro_Draft4_Ref_Single_100(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "common": { "type": "string", "minLength": 1 }
    },
    "properties": {
      "prop0": { "$ref": "#/definitions/common" },
      "prop1": { "$ref": "#/definitions/common" },
      "prop2": { "$ref": "#/definitions/common" },
      "prop3": { "$ref": "#/definitions/common" },
      "prop4": { "$ref": "#/definitions/common" },
      "prop5": { "$ref": "#/definitions/common" },
      "prop6": { "$ref": "#/definitions/common" },
      "prop7": { "$ref": "#/definitions/common" },
      "prop8": { "$ref": "#/definitions/common" },
      "prop9": { "$ref": "#/definitions/common" },
      "prop10": { "$ref": "#/definitions/common" },
      "prop11": { "$ref": "#/definitions/common" },
      "prop12": { "$ref": "#/definitions/common" },
      "prop13": { "$ref": "#/definitions/common" },
      "prop14": { "$ref": "#/definitions/common" },
      "prop15": { "$ref": "#/definitions/common" },
      "prop16": { "$ref": "#/definitions/common" },
      "prop17": { "$ref": "#/definitions/common" },
      "prop18": { "$ref": "#/definitions/common" },
      "prop19": { "$ref": "#/definitions/common" },
      "prop20": { "$ref": "#/definitions/common" },
      "prop21": { "$ref": "#/definitions/common" },
      "prop22": { "$ref": "#/definitions/common" },
      "prop23": { "$ref": "#/definitions/common" },
      "prop24": { "$ref": "#/definitions/common" },
      "prop25": { "$ref": "#/definitions/common" },
      "prop26": { "$ref": "#/definitions/common" },
      "prop27": { "$ref": "#/definitions/common" },
      "prop28": { "$ref": "#/definitions/common" },
      "prop29": { "$ref": "#/definitions/common" },
      "prop30": { "$ref": "#/definitions/common" },
      "prop31": { "$ref": "#/definitions/common" },
      "prop32": { "$ref": "#/definitions/common" },
      "prop33": { "$ref": "#/definitions/common" },
      "prop34": { "$ref": "#/definitions/common" },
      "prop35": { "$ref": "#/definitions/common" },
      "prop36": { "$ref": "#/definitions/common" },
      "prop37": { "$ref": "#/definitions/common" },
      "prop38": { "$ref": "#/definitions/common" },
      "prop39": { "$ref": "#/definitions/common" },
      "prop40": { "$ref": "#/definitions/common" },
      "prop41": { "$ref": "#/definitions/common" },
      "prop42": { "$ref": "#/definitions/common" },
      "prop43": { "$ref": "#/definitions/common" },
      "prop44": { "$ref": "#/definitions/common" },
      "prop45": { "$ref": "#/definitions/common" },
      "prop46": { "$ref": "#/definitions/common" },
      "prop47": { "$ref": "#/definitions/common" },
      "prop48": { "$ref": "#/definitions/common" },
      "prop49": { "$ref": "#/definitions/common" },
      "prop50": { "$ref": "#/definitions/common" },
      "prop51": { "$ref": "#/definitions/common" },
      "prop52": { "$ref": "#/definitions/common" },
      "prop53": { "$ref": "#/definitions/common" },
      "prop54": { "$ref": "#/definitions/common" },
      "prop55": { "$ref": "#/definitions/common" },
      "prop56": { "$ref": "#/definitions/common" },
      "prop57": { "$ref": "#/definitions/common" },
      "prop58": { "$ref": "#/definitions/common" },
      "prop59": { "$ref": "#/definitions/common" },
      "prop60": { "$ref": "#/definitions/common" },
      "prop61": { "$ref": "#/definitions/common" },
      "prop62": { "$ref": "#/definitions/common" },
      "prop63": { "$ref": "#/definitions/common" },
      "prop64": { "$ref": "#/definitions/common" },
      "prop65": { "$ref": "#/definitions/common" },
      "prop66": { "$ref": "#/definitions/common" },
      "prop67": { "$ref": "#/definitions/common" },
      "prop68": { "$ref": "#/definitions/common" },
      "prop69": { "$ref": "#/definitions/common" },
      "prop70": { "$ref": "#/definitions/common" },
      "prop71": { "$ref": "#/definitions/common" },
      "prop72": { "$ref": "#/definitions/common" },
      "prop73": { "$ref": "#/definitions/common" },
      "prop74": { "$ref": "#/definitions/common" },
      "prop75": { "$ref": "#/definitions/common" },
      "prop76": { "$ref": "#/definitions/common" },
      "prop77": { "$ref": "#/definitions/common" },
      "prop78": { "$ref": "#/definitions/common" },
      "prop79": { "$ref": "#/definitions/common" },
      "prop80": { "$ref": "#/definitions/common" },
      "prop81": { "$ref": "#/definitions/common" },
      "prop82": { "$ref": "#/definitions/common" },
      "prop83": { "$ref": "#/definitions/common" },
      "prop84": { "$ref": "#/definitions/common" },
      "prop85": { "$ref": "#/definitions/common" },
      "prop86": { "$ref": "#/definitions/common" },
      "prop87": { "$ref": "#/definitions/common" },
      "prop88": { "$ref": "#/definitions/common" },
      "prop89": { "$ref": "#/definitions/common" },
      "prop90": { "$ref": "#/definitions/common" },
      "prop91": { "$ref": "#/definitions/common" },
      "prop92": { "$ref": "#/definitions/common" },
      "prop93": { "$ref": "#/definitions/common" },
      "prop94": { "$ref": "#/definitions/common" },
      "prop95": { "$ref": "#/definitions/common" },
      "prop96": { "$ref": "#/definitions/common" },
      "prop97": { "$ref": "#/definitions/common" },
      "prop98": { "$ref": "#/definitions/common" },
      "prop99": { "$ref": "#/definitions/common" }
    }
  })JSON")};

  for (auto _ : state) {
    auto result{
        sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler)};
    benchmark::DoNotOptimize(result.targets);
  }
}

static void Micro_Draft4_Compile_Ref_Many_Nested(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "definitions": {
      "def0": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def1" }, "b": { "$ref": "#/definitions/def2" } } },
      "def1": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def2" }, "b": { "$ref": "#/definitions/def3" } } },
      "def2": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def3" }, "b": { "$ref": "#/definitions/def4" } } },
      "def3": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def4" }, "b": { "$ref": "#/definitions/def5" } } },
      "def4": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def5" }, "b": { "$ref": "#/definitions/def6" } } },
      "def5": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def6" }, "b": { "$ref": "#/definitions/def7" } } },
      "def6": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def7" }, "b": { "$ref": "#/definitions/def8" } } },
      "def7": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def8" }, "b": { "$ref": "#/definitions/def9" } } },
      "def8": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def9" }, "b": { "$ref": "#/definitions/def10" } } },
      "def9": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def10" }, "b": { "$ref": "#/definitions/def11" } } },
      "def10": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def11" }, "b": { "$ref": "#/definitions/def12" } } },
      "def11": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def12" }, "b": { "$ref": "#/definitions/def13" } } },
      "def12": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def13" }, "b": { "$ref": "#/definitions/def14" } } },
      "def13": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def14" }, "b": { "$ref": "#/definitions/def0" } } },
      "def14": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def0" }, "b": { "$ref": "#/definitions/def1" } } }
    },
    "properties": {
      "p0": { "$ref": "#/definitions/def0" },
      "p1": { "$ref": "#/definitions/def0" },
      "p2": { "$ref": "#/definitions/def0" },
      "p3": { "$ref": "#/definitions/def0" },
      "p4": { "$ref": "#/definitions/def0" },
      "p5": { "$ref": "#/definitions/def1" },
      "p6": { "$ref": "#/definitions/def1" },
      "p7": { "$ref": "#/definitions/def1" },
      "p8": { "$ref": "#/definitions/def1" },
      "p9": { "$ref": "#/definitions/def1" }
    }
  })JSON")};

  for (auto _ : state) {
    auto result{
        sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler)};
    benchmark::DoNotOptimize(result.targets);
  }
}

static void Micro_Draft4_Compile_Wrap(benchmark::State &state) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "allOf": [ { "$ref": "#/definitions/test/definitions/leaf" } ],
    "definitions": {
      "test": {
        "id": "nested",
        "definitions": {
          "def0": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def1" }, "b": { "$ref": "#/definitions/def2" } } },
          "def1": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def2" }, "b": { "$ref": "#/definitions/def3" } } },
          "def2": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def3" }, "b": { "$ref": "#/definitions/def4" } } },
          "def3": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def4" }, "b": { "$ref": "#/definitions/def5" } } },
          "def4": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def5" }, "b": { "$ref": "#/definitions/def6" } } },
          "def5": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def6" }, "b": { "$ref": "#/definitions/def7" } } },
          "def6": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def7" }, "b": { "$ref": "#/definitions/def8" } } },
          "def7": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def8" }, "b": { "$ref": "#/definitions/def9" } } },
          "def8": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def9" }, "b": { "$ref": "#/definitions/def10" } } },
          "def9": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def10" }, "b": { "$ref": "#/definitions/def11" } } },
          "def10": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def11" }, "b": { "$ref": "#/definitions/def12" } } },
          "def11": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def12" }, "b": { "$ref": "#/definitions/def13" } } },
          "def12": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def13" }, "b": { "$ref": "#/definitions/def14" } } },
          "def13": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def14" }, "b": { "$ref": "#/definitions/def0" } } },
          "def14": { "type": "object", "properties": { "a": { "$ref": "#/definitions/def0" }, "b": { "$ref": "#/definitions/def1" } } },
          "leaf": { "type": "string" }
        },
        "properties": {
          "p0": { "$ref": "#/definitions/def0" },
          "p1": { "$ref": "#/definitions/def0" },
          "p2": { "$ref": "#/definitions/def0" },
          "p3": { "$ref": "#/definitions/def0" },
          "p4": { "$ref": "#/definitions/def0" },
          "p5": { "$ref": "#/definitions/def1" },
          "p6": { "$ref": "#/definitions/def1" },
          "p7": { "$ref": "#/definitions/def1" },
          "p8": { "$ref": "#/definitions/def1" },
          "p9": { "$ref": "#/definitions/def1" }
        }
      }
    }
  })JSON")};

  for (auto _ : state) {
    auto result{
        sourcemeta::blaze::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::blaze::default_schema_compiler)};
    benchmark::DoNotOptimize(result.targets);
  }
}

BENCHMARK(Micro_Draft4_Meta_1_No_Callback);
BENCHMARK(Micro_Draft4_Required_Properties);
BENCHMARK(Micro_Draft4_Many_Optional_Properties_Minimal_Match);
BENCHMARK(Micro_Draft4_Few_Optional_Properties_Minimal_Match);
BENCHMARK(Micro_Draft4_Items_Schema);
BENCHMARK(Micro_Draft4_Nested_Object);
BENCHMARK(Micro_Draft4_Properties_Triad_Optional);
BENCHMARK(Micro_Draft4_Properties_Triad_Closed);
BENCHMARK(Micro_Draft4_Properties_Triad_Required);
BENCHMARK(Micro_Draft4_Properties_Closed);
BENCHMARK(Micro_Draft4_Non_Recursive_Ref);
BENCHMARK(Micro_Draft4_Pattern_Properties_True);
BENCHMARK(Micro_Draft4_Ref_To_Single_Property);
BENCHMARK(Micro_Draft4_Additional_Properties_Type);
BENCHMARK(Micro_Draft4_Nested_Oneof);
BENCHMARK(Micro_Draft4_Short_Enum);
BENCHMARK(Micro_Draft4_Long_Enum);
BENCHMARK(Micro_Draft4_Long_Enum_Short_Strings);
BENCHMARK(Micro_Draft4_Type_Object);
BENCHMARK(Micro_Draft4_Ref_Single_100);
BENCHMARK(Micro_Draft4_Compile_Ref_Many_Nested);
BENCHMARK(Micro_Draft4_Compile_Wrap);
