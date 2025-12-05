import { describe, it } from 'node:test';
import assert from 'node:assert';
import { BlazeJSON } from '@sourcemeta/blaze';

describe('BlazeJSON', () => {
  describe('parse primitives', () => {
    it('should parse null', () => {
      const result = BlazeJSON.parse('null');
      assert.strictEqual(result, null);
    });

    it('should parse true', () => {
      const result = BlazeJSON.parse('true');
      assert.strictEqual(result, true);
    });

    it('should parse false', () => {
      const result = BlazeJSON.parse('false');
      assert.strictEqual(result, false);
    });

    it('should parse integer', () => {
      const result = BlazeJSON.parse('42');
      assert.strictEqual(result, 42);
    });

    it('should parse negative integer', () => {
      const result = BlazeJSON.parse('-123');
      assert.strictEqual(result, -123);
    });

    it('should parse float', () => {
      const result = BlazeJSON.parse('3.14');
      assert.strictEqual(result, 3.14);
    });

    it('should parse string', () => {
      const result = BlazeJSON.parse('"hello"');
      assert.strictEqual(result, 'hello');
    });

    it('should parse empty string', () => {
      const result = BlazeJSON.parse('""');
      assert.strictEqual(result, '');
    });

    it('should parse string with escape sequences', () => {
      const result = BlazeJSON.parse('"hello\\nworld"');
      assert.strictEqual(result, 'hello\nworld');
    });

    it('should parse string with unicode', () => {
      const result = BlazeJSON.parse('"\\u0048\\u0065\\u006c\\u006c\\u006f"');
      assert.strictEqual(result, 'Hello');
    });
  });

  describe('parse arrays', () => {
    it('should parse empty array', () => {
      const result = BlazeJSON.parse('[]');
      assert.deepStrictEqual(result.toJSON(), []);
    });

    it('should parse array with single element', () => {
      const result = BlazeJSON.parse('[1]');
      assert.deepStrictEqual(result.toJSON(), [1]);
    });

    it('should parse array with multiple elements', () => {
      const result = BlazeJSON.parse('[1, 2, 3]');
      assert.deepStrictEqual(result.toJSON(), [1, 2, 3]);
    });

    it('should parse array with mixed types', () => {
      const result = BlazeJSON.parse('[1, "two", true, null]');
      assert.deepStrictEqual(result.toJSON(), [1, 'two', true, null]);
    });

    it('should parse nested arrays', () => {
      const result = BlazeJSON.parse('[[1, 2], [3, 4]]');
      assert.deepStrictEqual(result.toJSON(), [[1, 2], [3, 4]]);
    });

    it('should access array elements by index', () => {
      const result = BlazeJSON.parse('[10, 20, 30]');
      assert.strictEqual(result[0], 10);
      assert.strictEqual(result[1], 20);
      assert.strictEqual(result[2], 30);
    });

    it('should return undefined for out of bounds index', () => {
      const result = BlazeJSON.parse('[1, 2, 3]');
      assert.strictEqual(result[10], undefined);
    });

    it('should report correct length', () => {
      const result = BlazeJSON.parse('[1, 2, 3, 4, 5]');
      assert.strictEqual(result.length, 5);
    });

    it('should support in operator for valid indices', () => {
      const result = BlazeJSON.parse('[1, 2, 3]');
      assert.strictEqual(0 in result, true);
      assert.strictEqual(2 in result, true);
      assert.strictEqual(5 in result, false);
    });
  });

  describe('parse objects', () => {
    it('should parse empty object', () => {
      const result = BlazeJSON.parse('{}');
      assert.deepStrictEqual(result.toJSON(), {});
    });

    it('should parse object with single property', () => {
      const result = BlazeJSON.parse('{"foo": 1}');
      assert.deepStrictEqual(result.toJSON(), { foo: 1 });
    });

    it('should parse object with multiple properties', () => {
      const result = BlazeJSON.parse('{"a": 1, "b": 2, "c": 3}');
      assert.deepStrictEqual(result.toJSON(), { a: 1, b: 2, c: 3 });
    });

    it('should parse nested objects', () => {
      const result = BlazeJSON.parse('{"outer": {"inner": "value"}}');
      assert.deepStrictEqual(result.toJSON(), { outer: { inner: 'value' } });
    });

    it('should access object properties', () => {
      const result = BlazeJSON.parse('{"foo": "bar", "num": 42}');
      assert.strictEqual(result.foo, 'bar');
      assert.strictEqual(result.num, 42);
    });

    it('should access nested object properties', () => {
      const result = BlazeJSON.parse('{"a": {"b": {"c": "deep"}}}');
      assert.strictEqual(result.a.b.c, 'deep');
    });

    it('should return undefined for missing properties', () => {
      const result = BlazeJSON.parse('{"foo": 1}');
      assert.strictEqual(result.bar, undefined);
    });

    it('should support in operator for properties', () => {
      const result = BlazeJSON.parse('{"foo": 1, "bar": 2}');
      assert.strictEqual('foo' in result, true);
      assert.strictEqual('bar' in result, true);
      assert.strictEqual('baz' in result, false);
    });

    it('should support Object.keys()', () => {
      const result = BlazeJSON.parse('{"a": 1, "b": 2}');
      const keys = Object.keys(result);
      assert.ok(keys.includes('a'));
      assert.ok(keys.includes('b'));
      assert.strictEqual(keys.length, 2);
    });
  });

  describe('mutation', () => {
    it('should set object property', () => {
      const result = BlazeJSON.parse('{"foo": 1}');
      result.bar = 2;
      assert.strictEqual(result.bar, 2);
    });

    it('should update object property', () => {
      const result = BlazeJSON.parse('{"foo": 1}');
      result.foo = 100;
      assert.strictEqual(result.foo, 100);
    });

    it('should delete object property', () => {
      const result = BlazeJSON.parse('{"foo": 1, "bar": 2}');
      delete result.foo;
      assert.strictEqual('foo' in result, false);
      assert.strictEqual('bar' in result, true);
    });

    it('should set array element', () => {
      const result = BlazeJSON.parse('[1, 2, 3]');
      result[1] = 200;
      assert.strictEqual(result[1], 200);
    });
  });

  describe('stringify', () => {
    it('should stringify to compact JSON', () => {
      const result = BlazeJSON.parse('{"foo": 1, "bar": [1, 2, 3]}');
      const str = BlazeJSON.stringify(result);
      assert.ok(typeof str === 'string');
      assert.deepStrictEqual(JSON.parse(str), { foo: 1, bar: [1, 2, 3] });
    });

    it('should stringify with indentation', () => {
      const result = BlazeJSON.parse('{"foo": 1}');
      const str = BlazeJSON.stringify(result, null, 2);
      assert.ok(str.includes('\n'));
    });
  });

  describe('error handling', () => {
    it('should throw on invalid JSON', () => {
      assert.throws(() => {
        BlazeJSON.parse('invalid');
      }, /JSON parse error/);
    });

    it('should throw on incomplete JSON', () => {
      assert.throws(() => {
        BlazeJSON.parse('{"foo":');
      }, /JSON parse error/);
    });

    it('should throw on trailing comma', () => {
      assert.throws(() => {
        BlazeJSON.parse('[1, 2, 3,]');
      }, /JSON parse error/);
    });
  });

  describe('edge cases', () => {
    it('should handle large numbers', () => {
      const result = BlazeJSON.parse('9007199254740991');
      assert.strictEqual(result, 9007199254740991);
    });

    it('should handle deeply nested structures', () => {
      const json = '{"a":{"b":{"c":{"d":{"e":"deep"}}}}}';
      const result = BlazeJSON.parse(json);
      assert.strictEqual(result.a.b.c.d.e, 'deep');
    });

    it('should handle arrays of objects', () => {
      const result = BlazeJSON.parse('[{"id": 1}, {"id": 2}]');
      assert.strictEqual(result[0].id, 1);
      assert.strictEqual(result[1].id, 2);
    });

    it('should handle objects with array values', () => {
      const result = BlazeJSON.parse('{"items": [1, 2, 3]}');
      assert.strictEqual(result.items[0], 1);
      assert.strictEqual(result.items.length, 3);
    });
  });

  describe('JSON.parse compatibility', () => {
    it('should work as drop-in replacement for simple cases', () => {
      const jsonString = '{"name": "test", "value": 42}';
      const native = JSON.parse(jsonString);
      const blaze = BlazeJSON.parse(jsonString);

      assert.strictEqual(blaze.name, native.name);
      assert.strictEqual(blaze.value, native.value);
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

    it('should return Array.isArray true for arrays', () => {
      const result = BlazeJSON.parse('[1, 2, 3]');
      assert.strictEqual(Array.isArray(result), true);
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

    it('should support Object.keys on objects', () => {
      const result = BlazeJSON.parse('{"a": 1, "b": 2}');
      const keys = Object.keys(result);
      assert.ok(keys.includes('a'));
      assert.ok(keys.includes('b'));
    });

    it('should support Object.values on objects', () => {
      const result = BlazeJSON.parse('{"a": 1, "b": 2}');
      const values = Object.values(result);
      assert.ok(values.includes(1));
      assert.ok(values.includes(2));
    });

    it('should support Object.entries on objects', () => {
      const result = BlazeJSON.parse('{"a": 1, "b": 2}');
      const entries = Object.entries(result);
      assert.strictEqual(entries.length, 2);
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
  });

  describe('JSON.stringify compatibility', () => {
    it('should stringify plain objects', () => {
      const result = BlazeJSON.stringify({a: 1, b: 2});
      assert.strictEqual(result, '{"a":1,"b":2}');
    });

    it('should stringify plain arrays', () => {
      const result = BlazeJSON.stringify([1, 2, 3]);
      assert.strictEqual(result, '[1,2,3]');
    });

    it('should stringify primitives', () => {
      assert.strictEqual(BlazeJSON.stringify(42), '42');
      assert.strictEqual(BlazeJSON.stringify('hello'), '"hello"');
      assert.strictEqual(BlazeJSON.stringify(true), 'true');
      assert.strictEqual(BlazeJSON.stringify(null), 'null');
    });

    it('should support replacer array', () => {
      const result = BlazeJSON.stringify({a: 1, b: 2, c: 3}, ['a', 'c']);
      assert.strictEqual(result, '{"a":1,"c":3}');
    });

    it('should support replacer function', () => {
      const result = BlazeJSON.stringify({a: 1, b: 2}, (key, value) => {
        if (key === 'a') return undefined;
        return value;
      });
      assert.strictEqual(result, '{"b":2}');
    });

    it('should support space parameter for formatting', () => {
      const result = BlazeJSON.stringify({a: 1}, null, 2);
      assert.ok(result.includes('\n'));
      assert.ok(result.includes('  '));
    });

    it('should stringify BlazeJSON parsed values', () => {
      const parsed = BlazeJSON.parse('{"x": 1, "y": 2}');
      const result = BlazeJSON.stringify(parsed);
      assert.deepStrictEqual(JSON.parse(result), {x: 1, y: 2});
    });
  });
});
