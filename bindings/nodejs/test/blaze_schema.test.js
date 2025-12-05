import { describe, it } from 'node:test';
import assert from 'node:assert';
import { BlazeJSON, compileSchema, restoreSchema, evaluateSchema } from '@sourcemeta/blaze';

const parse = BlazeJSON.parse;

describe('compileSchema', () => {
  it('should compile a simple schema', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string"
    }));

    const compiled = compileSchema(schema);
    assert.ok(compiled);
    assert.ok(typeof compiled.toJSON === 'function');
  });

  it('should accept defaultDialect option', () => {
    const schema = parse('{ "type": "string" }');
    const compiled = compileSchema(schema, {
      defaultDialect: "https://json-schema.org/draft/2020-12/schema"
    });
    assert.ok(compiled);
  });

  it('should accept mode option', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string"
    }));

    const fastCompiled = compileSchema(schema, { mode: 'fast' });
    assert.ok(fastCompiled);

    const exhaustiveCompiled = compileSchema(schema, { mode: 'exhaustive' });
    assert.ok(exhaustiveCompiled);
  });

  it('should throw on invalid schema type', () => {
    assert.throws(() => {
      compileSchema("not an object");
    }, /compileSchema\(\) schema must be an object/);
  });

  it('should throw when schema is a plain object instead of BlazeJSON', () => {
    assert.throws(() => {
      compileSchema({ type: "string" });
    }, /compileSchema\(\) schema must be a BlazeJSON document/);
  });

  describe('resolve callback', () => {
    it('should resolve external $ref with BlazeJSON', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$ref": "https://example.com/number-schema"
      }));

      const compiled = compileSchema(schema, {
        resolve: (identifier) => {
          if (identifier === "https://example.com/number-schema") {
            return parse(JSON.stringify({
              "$schema": "https://json-schema.org/draft/2020-12/schema",
              "$id": "https://example.com/number-schema",
              "type": "number"
            }));
          }
          return null;
        }
      });

      assert.deepStrictEqual(evaluateSchema(compiled, parse("42")), { valid: true });
    });

    it('should invalidate when resolved schema does not match', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$ref": "https://example.com/string-schema"
      }));

      const compiled = compileSchema(schema, {
        resolve: (identifier) => {
          if (identifier === "https://example.com/string-schema") {
            return parse(JSON.stringify({
              "$schema": "https://json-schema.org/draft/2020-12/schema",
              "$id": "https://example.com/string-schema",
              "type": "string"
            }));
          }
          return null;
        }
      });

      assert.deepStrictEqual(evaluateSchema(compiled, parse("123")), { valid: false });
    });

    it('should resolve nested $ref', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object",
        "properties": {
          "name": { "$ref": "https://example.com/name-schema" }
        }
      }));

      const compiled = compileSchema(schema, {
        resolve: (identifier) => {
          if (identifier === "https://example.com/name-schema") {
            return parse(JSON.stringify({
              "$schema": "https://json-schema.org/draft/2020-12/schema",
              "$id": "https://example.com/name-schema",
              "type": "string",
              "minLength": 1
            }));
          }
          return null;
        }
      });

      assert.deepStrictEqual(evaluateSchema(compiled, parse('{ "name": "John" }')), { valid: true });
    });

    it('should invalidate when nested $ref schema does not match', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object",
        "properties": {
          "name": { "$ref": "https://example.com/name-schema" }
        }
      }));

      const compiled = compileSchema(schema, {
        resolve: (identifier) => {
          if (identifier === "https://example.com/name-schema") {
            return parse(JSON.stringify({
              "$schema": "https://json-schema.org/draft/2020-12/schema",
              "$id": "https://example.com/name-schema",
              "type": "string",
              "minLength": 1
            }));
          }
          return null;
        }
      });

      assert.deepStrictEqual(evaluateSchema(compiled, parse('{ "name": "" }')), { valid: false });
    });

    it('should throw when resolve callback returns plain object', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "$ref": "https://example.com/test-schema"
      }));

      assert.throws(() => {
        compileSchema(schema, {
          resolve: (identifier) => {
            if (identifier === "https://example.com/test-schema") {
              return { type: "string" };
            }
            return null;
          }
        });
      }, /resolve\(\) callback must return a BlazeJSON document/);
    });
  });
});

describe('restoreSchema', () => {
  it('should round-trip simple string schema and validate correctly', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string"
    }));

    const compiled = compileSchema(schema);
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));

    assert.deepStrictEqual(evaluateSchema(restored, parse('"hello"')), { valid: true });
  });

  it('should round-trip simple string schema and invalidate non-string', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string"
    }));

    const compiled = compileSchema(schema);
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));

    assert.deepStrictEqual(evaluateSchema(restored, parse("123")), { valid: false });
  });

  it('should round-trip object schema with required properties and validate correctly', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "object",
      "properties": {
        "name": { "type": "string" },
        "age": { "type": "integer", "minimum": 0 }
      },
      "required": ["name"]
    }));

    const compiled = compileSchema(schema);
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));

    assert.deepStrictEqual(evaluateSchema(restored, parse('{ "name": "Alice", "age": 30 }')), { valid: true });
  });

  it('should round-trip object schema and invalidate missing required property', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "object",
      "properties": {
        "name": { "type": "string" },
        "age": { "type": "integer", "minimum": 0 }
      },
      "required": ["name"]
    }));

    const compiled = compileSchema(schema);
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));

    assert.deepStrictEqual(evaluateSchema(restored, parse('{ "age": 30 }')), { valid: false });
  });

  it('should round-trip object schema and invalidate negative age', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "object",
      "properties": {
        "name": { "type": "string" },
        "age": { "type": "integer", "minimum": 0 }
      },
      "required": ["name"]
    }));

    const compiled = compileSchema(schema);
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));

    assert.deepStrictEqual(evaluateSchema(restored, parse('{ "name": "Bob", "age": -5 }')), { valid: false });
  });

  it('should round-trip array schema and validate correctly', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "array",
      "items": { "type": "number" },
      "minItems": 1,
      "maxItems": 5
    }));

    const compiled = compileSchema(schema);
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));

    assert.deepStrictEqual(evaluateSchema(restored, parse("[1, 2, 3]")), { valid: true });
  });

  it('should round-trip array schema and invalidate empty array', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "array",
      "items": { "type": "number" },
      "minItems": 1,
      "maxItems": 5
    }));

    const compiled = compileSchema(schema);
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));

    assert.deepStrictEqual(evaluateSchema(restored, parse("[]")), { valid: false });
  });

  it('should round-trip array schema and invalidate too many items', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "array",
      "items": { "type": "number" },
      "minItems": 1,
      "maxItems": 5
    }));

    const compiled = compileSchema(schema);
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));

    assert.deepStrictEqual(evaluateSchema(restored, parse("[1, 2, 3, 4, 5, 6]")), { valid: false });
  });

  it('should round-trip schema with pattern and validate matching string', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string",
      "pattern": "^[A-Z][a-z]+$"
    }));

    const compiled = compileSchema(schema);
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));

    assert.deepStrictEqual(evaluateSchema(restored, parse('"Hello"')), { valid: true });
  });

  it('should round-trip schema with pattern and invalidate non-matching string', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string",
      "pattern": "^[A-Z][a-z]+$"
    }));

    const compiled = compileSchema(schema);
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));

    assert.deepStrictEqual(evaluateSchema(restored, parse('"hello"')), { valid: false });
  });

  it('should round-trip exhaustive mode schema and return errors for invalid instance', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string"
    }));

    const compiled = compileSchema(schema, { mode: 'exhaustive' });
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));
    const result = evaluateSchema(restored, parse("42"));

    assert.deepStrictEqual(result.toJSON(), {
      valid: false,
      errors: [
        {
          absoluteKeywordLocation: "#/type",
          error: "The value was expected to be of type string but it was of type integer",
          instanceLocation: "",
          keywordLocation: "/type"
        }
      ]
    });
  });

  it('should round-trip exhaustive mode schema and return valid result', () => {
    const schema = parse(JSON.stringify({
      "$schema": "https://json-schema.org/draft/2020-12/schema",
      "type": "string"
    }));

    const compiled = compileSchema(schema, { mode: 'exhaustive' });
    const json = compiled.toJSON();
    const serialized = BlazeJSON.stringify(json);
    const restored = restoreSchema(parse(serialized));
    const result = evaluateSchema(restored, parse('"hello"'));

    assert.deepStrictEqual(result.toJSON(), { valid: true });
  });

  it('should throw when restoreSchema receives a plain object', () => {
    assert.throws(() => {
      restoreSchema({ instructions: [] });
    }, /restoreSchema\(\) argument must be a BlazeJSON document/);
  });
});

describe('evaluateSchema', () => {
  describe('fast mode', () => {
    it('should return valid: true for matching instance', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string"
      }));

      const compiled = compileSchema(schema, { mode: 'fast' });
      const result = evaluateSchema(compiled, parse('"hello"'));

      assert.deepStrictEqual(result, { valid: true });
    });

    it('should return valid: false for non-matching instance', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string"
      }));

      const compiled = compileSchema(schema, { mode: 'fast' });
      const result = evaluateSchema(compiled, parse("42"));

      assert.deepStrictEqual(result, { valid: false });
    });

    it('should validate valid object with required properties', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object",
        "properties": {
          "name": { "type": "string" },
          "age": { "type": "integer" }
        },
        "required": ["name"]
      }));

      const compiled = compileSchema(schema, { mode: 'fast' });
      assert.deepStrictEqual(evaluateSchema(compiled, parse('{ "name": "John", "age": 30 }')), { valid: true });
    });

    it('should invalidate object missing required property', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object",
        "properties": {
          "name": { "type": "string" },
          "age": { "type": "integer" }
        },
        "required": ["name"]
      }));

      const compiled = compileSchema(schema, { mode: 'fast' });
      assert.deepStrictEqual(evaluateSchema(compiled, parse('{ "age": 30 }')), { valid: false });
    });

    it('should invalidate object with wrong property type', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object",
        "properties": {
          "name": { "type": "string" },
          "age": { "type": "integer" }
        },
        "required": ["name"]
      }));

      const compiled = compileSchema(schema, { mode: 'fast' });
      assert.deepStrictEqual(evaluateSchema(compiled, parse('{ "name": 123 }')), { valid: false });
    });

    it('should validate valid array', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "array",
        "items": { "type": "number" }
      }));

      const compiled = compileSchema(schema, { mode: 'fast' });
      assert.deepStrictEqual(evaluateSchema(compiled, parse("[1, 2, 3]")), { valid: true });
    });

    it('should invalidate array with wrong item type', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "array",
        "items": { "type": "number" }
      }));

      const compiled = compileSchema(schema, { mode: 'fast' });
      assert.deepStrictEqual(evaluateSchema(compiled, parse('[1, "two", 3]')), { valid: false });
    });

    it('should throw when instance is a plain object instead of BlazeJSON', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object"
      }));

      const compiled = compileSchema(schema, { mode: 'fast' });

      assert.throws(() => {
        evaluateSchema(compiled, { foo: 1 });
      }, /evaluateSchema\(\) instance must be a BlazeJSON document/);
    });
  });

  describe('exhaustive mode', () => {
    it('should return detailed output for valid instance', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string"
      }));

      const compiled = compileSchema(schema, { mode: 'exhaustive' });
      const result = evaluateSchema(compiled, parse('"hello"'));

      assert.deepStrictEqual(result.toJSON(), { valid: true });
    });

    it('should return errors for invalid instance', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string"
      }));

      const compiled = compileSchema(schema, { mode: 'exhaustive' });
      const result = evaluateSchema(compiled, parse("42"));

      assert.deepStrictEqual(result.toJSON(), {
        valid: false,
        errors: [
          {
            absoluteKeywordLocation: "#/type",
            error: "The value was expected to be of type string but it was of type integer",
            instanceLocation: "",
            keywordLocation: "/type"
          }
        ]
      });
    });

    it('should return annotations for valid object', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object",
        "properties": {
          "foo": { "type": "string" }
        }
      }));

      const compiled = compileSchema(schema, { mode: 'exhaustive' });
      const result = evaluateSchema(compiled, parse('{ "foo": "bar" }'));

      assert.deepStrictEqual(result.toJSON(), {
        valid: true,
        annotations: [
          {
            absoluteKeywordLocation: "#/properties",
            annotation: ["foo"],
            instanceLocation: "",
            keywordLocation: "/properties"
          }
        ]
      });
    });
  });

  describe('primitives', () => {
    it('should validate null value against null type', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "null"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse("null")), { valid: true });
    });

    it('should invalidate string against null type', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "null"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('"not null"')), { valid: false });
    });

    it('should validate true against boolean type', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "boolean"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse("true")), { valid: true });
    });

    it('should validate false against boolean type', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "boolean"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse("false")), { valid: true });
    });

    it('should invalidate string against boolean type', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "boolean"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('"true"')), { valid: false });
    });

    it('should validate number within range', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "number",
        "minimum": 0,
        "maximum": 100
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse("50")), { valid: true });
    });

    it('should invalidate number below minimum', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "number",
        "minimum": 0,
        "maximum": 100
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse("-1")), { valid: false });
    });

    it('should invalidate number above maximum', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "number",
        "minimum": 0,
        "maximum": 100
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse("101")), { valid: false });
    });

    it('should validate integer against integer type', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "integer"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse("42")), { valid: true });
    });

    it('should invalidate float against integer type', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "integer"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse("3.14")), { valid: false });
    });
  });

  describe('complex schemas', () => {
    it('should validate valid nested object', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object",
        "properties": {
          "user": {
            "type": "object",
            "properties": {
              "name": { "type": "string" },
              "email": { "type": "string", "format": "email" }
            },
            "required": ["name", "email"]
          }
        }
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(
        evaluateSchema(compiled, parse('{ "user": { "name": "John", "email": "john@example.com" } }')),
        { valid: true }
      );
    });

    it('should invalidate nested object missing required property', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object",
        "properties": {
          "user": {
            "type": "object",
            "properties": {
              "name": { "type": "string" },
              "email": { "type": "string", "format": "email" }
            },
            "required": ["name", "email"]
          }
        }
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(
        evaluateSchema(compiled, parse('{ "user": { "name": "John" } }')),
        { valid: false }
      );
    });

    it('should validate value in enum', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "enum": ["red", "green", "blue"]
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('"red"')), { valid: true });
    });

    it('should invalidate value not in enum', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "enum": ["red", "green", "blue"]
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('"yellow"')), { valid: false });
    });

    it('should validate matching const value', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "const": "expected"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('"expected"')), { valid: true });
    });

    it('should invalidate non-matching const value', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "const": "expected"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('"other"')), { valid: false });
    });

    it('should validate string matching pattern', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string",
        "pattern": "^[a-z]+$"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('"hello"')), { valid: true });
    });

    it('should invalidate string with uppercase against lowercase pattern', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string",
        "pattern": "^[a-z]+$"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('"Hello"')), { valid: false });
    });

    it('should invalidate string with numbers against alpha pattern', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "string",
        "pattern": "^[a-z]+$"
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('"hello123"')), { valid: false });
    });

    it('should validate object without additional properties', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object",
        "properties": {
          "name": { "type": "string" }
        },
        "additionalProperties": false
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('{ "name": "John" }')), { valid: true });
    });

    it('should invalidate object with additional properties when not allowed', () => {
      const schema = parse(JSON.stringify({
        "$schema": "https://json-schema.org/draft/2020-12/schema",
        "type": "object",
        "properties": {
          "name": { "type": "string" }
        },
        "additionalProperties": false
      }));

      const compiled = compileSchema(schema);
      assert.deepStrictEqual(evaluateSchema(compiled, parse('{ "name": "John", "extra": 1 }')), { valid: false });
    });
  });
});
