import { describe, it } from 'node:test';
import assert from 'node:assert';
import { readFileSync } from 'node:fs';
import { fileURLToPath } from 'node:url';
import { dirname, join } from 'node:path';
import {
  BlazeJSON,
  compileSchema,
  restoreSchema,
  evaluateSchema
} from '@sourcemeta/blaze';

const currentDirectory = dirname(fileURLToPath(import.meta.url));
const bindingsDirectory = join(currentDirectory, '..', '..');
const jsonTestCases = JSON.parse(
  readFileSync(join(bindingsDirectory, 'json.test.json'), 'utf8'));
const evaluateTestCases = JSON.parse(
  readFileSync(join(bindingsDirectory, 'evaluate.test.json'), 'utf8'));

function getValueAtPath(root, path) {
  let value = root;
  for (const key of path) {
    value = value[key];
  }
  return value;
}

function getType(value) {
  if (value === null) return 'null';
  if (Array.isArray(value)) return 'array';
  return typeof value;
}

function sortForComparison(arr) {
  return [...arr].sort((a, b) => JSON.stringify(a).localeCompare(JSON.stringify(b)));
}

function executeOperation(root, op) {
  const path = op.operand;
  const parentPath = path.slice(0, -1);
  const lastKey = path[path.length - 1];

  switch (op.operation) {
    case 'get': {
      let result = getValueAtPath(root, path);
      if (result === undefined) result = null;
      if (result && typeof result === 'object' && result.toJSON) {
        result = result.toJSON();
      }
      assert.deepStrictEqual(result, op.expected);
      break;
    }
    case 'set': {
      const parent = path.length === 1 ? root : getValueAtPath(root, parentPath);
      parent[lastKey] = op.value;
      break;
    }
    case 'delete': {
      const parent = path.length === 1 ? root : getValueAtPath(root, parentPath);
      delete parent[lastKey];
      break;
    }
    case 'has': {
      if (path.length === 0) {
        throw new Error('has operation requires non-empty path');
      }
      const parent = path.length === 1 ? root : getValueAtPath(root, parentPath);
      if (parent === null || parent === undefined ||
          typeof parent !== 'object') {
        assert.strictEqual(false, op.expected);
        break;
      }
      const result = lastKey in parent;
      assert.strictEqual(result, op.expected);
      break;
    }
    case 'length': {
      const target = path.length === 0 ? root : getValueAtPath(root, path);
      assert.strictEqual(target.length, op.expected);
      break;
    }
    case 'keys': {
      const target = path.length === 0 ? root : getValueAtPath(root, path);
      const result = target.keys ? target.keys() : Object.keys(target);
      assert.deepStrictEqual(
        sortForComparison(result),
        sortForComparison(op.expected)
      );
      break;
    }
    case 'values': {
      const target = path.length === 0 ? root : getValueAtPath(root, path);
      const result = Object.values(target);
      assert.deepStrictEqual(
        sortForComparison(result),
        sortForComparison(op.expected)
      );
      break;
    }
    case 'entries': {
      const target = path.length === 0 ? root : getValueAtPath(root, path);
      const result = Object.entries(target);
      assert.deepStrictEqual(
        sortForComparison(result),
        sortForComparison(op.expected)
      );
      break;
    }
    case 'type': {
      const target = path.length === 0 ? root : getValueAtPath(root, path);
      let value = target;
      if (value && typeof value === 'object' && value.toJSON) {
        value = value.toJSON();
      }
      assert.strictEqual(getType(value), op.expected);
      break;
    }
    case 'stringify': {
      const target = path.length === 0 ? root : getValueAtPath(root, path);
      const result = BlazeJSON.stringify(target, null, op.indent);
      assert.strictEqual(result, op.expected);
      break;
    }
    default:
      throw new Error(`Unknown operation: ${op.operation}`);
  }
}

describe('json.test.json', () => {
  for (const testCase of jsonTestCases) {
    it(testCase.description, () => {
      if (testCase.error) {
        assert.throws(() => {
          BlazeJSON.parse(testCase.value);
        }, /JSON parse error/);
        return;
      }

      const parsed = BlazeJSON.parse(testCase.value);

      if (testCase.operations) {
        for (const op of testCase.operations) {
          executeOperation(parsed, op);
        }
        return;
      }

      const fromValue = BlazeJSON.from(testCase.expected);
      assert.deepStrictEqual(parsed.toJSON(), testCase.expected);
      assert.deepStrictEqual(fromValue.toJSON(), testCase.expected);
    });
  }
});

describe('evaluate.test.json', () => {
  for (const testCase of evaluateTestCases) {
    it(testCase.description, () => {
      if (testCase.error) {
        assert.throws(() => {
          const schema = testCase.rawSchema
            ? testCase.schema
            : BlazeJSON.from(testCase.schema);
          compileSchema(schema, testCase.options);
        });
        return;
      }

      const schema = BlazeJSON.from(testCase.schema);

      const options = { ...testCase.options };
      if (options.resolve && typeof options.resolve === 'object') {
        const resolveMap = options.resolve;
        options.resolve = (identifier) => {
          if (resolveMap[identifier]) {
            return BlazeJSON.from(resolveMap[identifier]);
          }

          return null;
        };
      }

      const compiled = compileSchema(schema, options);
      const instance = BlazeJSON.from(testCase.instance);
      const result = evaluateSchema(compiled, instance);
      assert.deepStrictEqual(result.toJSON(), testCase.result);

      const serialized = BlazeJSON.stringify(compiled.toJSON());
      const restored = restoreSchema(BlazeJSON.parse(serialized));
      const restoredResult = evaluateSchema(restored, instance);
      assert.deepStrictEqual(restoredResult.toJSON(), testCase.result);
    });
  }
});

it('should throw when passed a plain object', () => {
  assert.throws(() => {
    BlazeJSON.stringify({ a: 1, b: 2 });
  }, /stringify\(\) argument must be a BlazeJSON document/);
});

it('should throw when passed a plain array', () => {
  assert.throws(() => {
    BlazeJSON.stringify([1, 2, 3]);
  }, /stringify\(\) argument must be a BlazeJSON document/);
});

it('should throw when passed a primitive', () => {
  assert.throws(() => {
    BlazeJSON.stringify(42);
  }, /stringify\(\) argument must be a BlazeJSON document/);
});

it('should support replacer array', () => {
  const parsed = BlazeJSON.parse('{"a": 1, "b": 2, "c": 3}');
  const result = BlazeJSON.stringify(parsed, ['a', 'c']);
  assert.strictEqual(result, '{"a":1,"c":3}');
});

it('should support replacer function', () => {
  const parsed = BlazeJSON.parse('{"a": 1, "b": 2}');
  const result = BlazeJSON.stringify(parsed, (key, value) => {
    if (key === 'a') return undefined;
    return value;
  });
  assert.strictEqual(result, '{"b":2}');
});

it('should support reviver function', () => {
  const result = BlazeJSON.parse('{"date": "2024-01-01"}', (key, value) => {
    if (key === 'date') {
      return new Date(value);
    }
    return value;
  });
  assert.ok(result.date instanceof Date);
});

it('should support reviver on primitives', () => {
  const result = BlazeJSON.parse('42', (key, value) => value * 2);
  assert.strictEqual(result, 84);
});

it('should call reviver in correct order', () => {
  const calls = [];
  BlazeJSON.parse('{"a": 1, "b": 2}', (key, value) => {
    calls.push(key);
    return value;
  });
  assert.strictEqual(calls[calls.length - 1], '');
});

it('should delete properties when reviver returns undefined', () => {
  const result = BlazeJSON.parse('{"a": 1, "b": 2}', (key, value) => {
    if (key === 'a') return undefined;
    return value;
  });
  assert.strictEqual('a' in result, false);
  assert.strictEqual(result.b, 2);
});

it('should support forEach on arrays', () => {
  const result = BlazeJSON.parse('[1, 2, 3]');
  const values = [];
  result.forEach(value => values.push(value));
  assert.deepStrictEqual(values, [1, 2, 3]);
});

it('should support map on arrays', () => {
  const result = BlazeJSON.parse('[1, 2, 3]');
  const mapped = result.map(value => value * 2);
  assert.deepStrictEqual(mapped, [2, 4, 6]);
});

it('should support filter on arrays', () => {
  const result = BlazeJSON.parse('[1, 2, 3, 4, 5]');
  const filtered = result.filter(value => value > 2);
  assert.deepStrictEqual(filtered, [3, 4, 5]);
});

it('should support reduce on arrays', () => {
  const result = BlazeJSON.parse('[1, 2, 3, 4]');
  const sum = result.reduce((acc, value) => acc + value, 0);
  assert.strictEqual(sum, 10);
});

it('should support spread operator on arrays', () => {
  const result = BlazeJSON.parse('[1, 2, 3]');
  const spread = [...result];
  assert.deepStrictEqual(spread, [1, 2, 3]);
});

it('should support for...in on objects', () => {
  const result = BlazeJSON.parse('{"a": 1, "b": 2}');
  const keys = [];
  for (const key in result) {
    keys.push(key);
  }
  assert.ok(keys.includes('a'));
  assert.ok(keys.includes('b'));
});

it('should throw when schema is a plain object instead of BlazeJSON', () => {
  assert.throws(() => {
    compileSchema({ type: "string" });
  }, /compileSchema\(\) schema must be a BlazeJSON document/);
});

it('should throw when resolve callback returns plain object', () => {
  const schema = BlazeJSON.parse(JSON.stringify({
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

it('should throw when restoreSchema receives a plain object', () => {
  assert.throws(() => {
    restoreSchema({ instructions: [] });
  }, /restoreSchema\(\) argument must be a BlazeJSON document/);
});

it('should throw when instance is a plain object instead of BlazeJSON', () => {
  const schema = BlazeJSON.parse(JSON.stringify({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  }));

  const compiled = compileSchema(schema, { mode: 'fast' });

  assert.throws(() => {
    evaluateSchema(compiled, { foo: 1 });
  }, /evaluateSchema\(\) instance must be a BlazeJSON document/);
});
