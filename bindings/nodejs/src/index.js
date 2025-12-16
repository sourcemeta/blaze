import { createRequire } from 'module';
import { dirname, join } from 'path';
import { fileURLToPath } from 'url';

const __dirname = dirname(fileURLToPath(import.meta.url));
const require = createRequire(import.meta.url);

let native;
try {
  native = require(join(__dirname, '../build/Release/blaze.node'));
} catch {
  native = require(join(__dirname, '../build/Debug/blaze.node'));
}

function createArrayProxy(blazeJson) {
  const handler = {
    get(target, property, receiver) {
      if (property === '__blazeJson__') {
        return blazeJson;
      }

      if (property === 'toJSON') {
        return () => blazeJson.toJSON();
      }

      if (property === Symbol.toStringTag) {
        return 'Array';
      }

      if (typeof property === 'string') {
        const numericIndex = Number(property);
        if (Number.isInteger(numericIndex) && numericIndex >= 0) {
          const value = blazeJson.get(numericIndex);
          return wrapValue(value);
        }
      }

      return Reflect.get(target, property, receiver);
    },

    set(target, property, value, receiver) {
      const numericIndex = Number(property);
      if (Number.isInteger(numericIndex) && numericIndex >= 0) {
        blazeJson.set(numericIndex, unwrapValue(value));
        Reflect.set(target, property, value, receiver);
        return true;
      }
      return Reflect.set(target, property, value, receiver);
    },

    has(target, property) {
      if (typeof property === 'string') {
        const numericIndex = Number(property);
        if (Number.isInteger(numericIndex) && numericIndex >= 0) {
          return blazeJson.has(numericIndex);
        }
      }
      return Reflect.has(target, property);
    }
  };

  const length = blazeJson.length;
  const arrayTarget = new Array(length);
  for (let index = 0; index < length; index++) {
    const value = blazeJson.get(index);
    arrayTarget[index] = wrapValue(value);
  }

  return new Proxy(arrayTarget, handler);
}

function createObjectProxy(blazeJson) {
  return new Proxy(blazeJson, {
    get(target, property, receiver) {
      if (property === Symbol.iterator) {
        const keys = target.keys();
        let index = 0;
        return function* () {
          while (index < keys.length) {
            const key = keys[index++];
            const value = target.get(key);
            yield [key, wrapValue(value)];
          }
        };
      }

      if (property === Symbol.toStringTag) {
        return 'Object';
      }

      if (property === 'toJSON') {
        return () => target.toJSON();
      }

      if (property === 'toString') {
        return () => native.stringify(target);
      }

      if (property === 'valueOf') {
        return () => target.toJSON();
      }

      if (property === 'keys') {
        return () => target.keys();
      }

      if (property === 'has') {
        return (key) => target.has(key);
      }

      if (property === '__blazeJson__') {
        return target;
      }

      if (typeof property === 'string') {
        const value = target.get(property);
        return wrapValue(value);
      }

      return undefined;
    },

    set(target, property, value, receiver) {
      return target.set(property, unwrapValue(value));
    },

    deleteProperty(target, property) {
      return target.delete(property);
    },

    has(target, property) {
      if (typeof property === 'string') {
        return target.has(property);
      }
      return false;
    },

    ownKeys(target) {
      return target.keys();
    },

    getOwnPropertyDescriptor(target, property) {
      if (target.has(property)) {
        return {
          enumerable: true,
          configurable: true,
          writable: true,
          value: wrapValue(target.get(property))
        };
      }
      return undefined;
    }
  });
}

function createPrimitiveWrapper(blazeJson) {
  return {
    __blazeJson__: blazeJson,
    toJSON() {
      return blazeJson.toJSON();
    },
    toString() {
      return native.stringify(blazeJson);
    },
    valueOf() {
      return blazeJson.toJSON();
    }
  };
}

function createProxy(blazeJson) {
  const type = blazeJson.type();
  if (type === 'array') {
    return createArrayProxy(blazeJson);
  }
  if (type === 'object') {
    return createObjectProxy(blazeJson);
  }
  return createPrimitiveWrapper(blazeJson);
}

function wrapValue(value) {
  if (value && typeof value === 'object' && value.constructor && value.constructor.name === 'BlazeJSON') {
    return createProxy(value);
  }
  return value;
}

function unwrapValue(value) {
  if (value && value.__blazeJson__) {
    return value.__blazeJson__.toJSON();
  }
  return value;
}

function parse(text, reviver) {
  const result = native.parse(text);
  const proxy = createProxy(result);

  if (reviver) {
    return applyReviver({ '': proxy }, '', reviver);
  }

  return proxy;
}

function applyReviver(holder, key, reviver, parentIsPlain = false) {
  let value = holder[key];

  if (value && typeof value === 'object') {
    const isBlazeJson = value.__blazeJson__ !== undefined;

    if (isBlazeJson) {
      const type = value.__blazeJson__.type();
      if (type !== 'object' && type !== 'array') {
        return reviver.call(holder, key, value.toJSON());
      }
    }

    const keys = isBlazeJson ? value.keys() : Object.keys(value);
    const plainObj = isBlazeJson ? (Array.isArray(value.toJSON()) ? [] : {}) : value;

    for (const k of keys) {
      const newValue = applyReviver(isBlazeJson ? value : plainObj, k, reviver, !isBlazeJson);
      if (newValue === undefined) {
        if (!isBlazeJson) {
          delete plainObj[k];
        }
      } else {
        plainObj[k] = newValue;
      }
    }

    value = isBlazeJson ? plainObj : value;
  }

  return reviver.call(holder, key, value);
}

function stringify(value, replacer, space) {
  if (!value || !value.__blazeJson__) {
    throw new Error('stringify() argument must be a BlazeJSON document');
  }
  if (replacer) {
    return JSON.stringify(value.__blazeJson__.toJSON(), replacer, space);
  }
  return native.stringify(value.__blazeJson__, null, space);
}

function wrapCompiledSchema(nativeCompiled) {
  return {
    __nativeCompiled__: nativeCompiled,
    toJSON() {
      return createProxy(nativeCompiled.toJSON());
    }
  };
}

function compileSchema(schema, options = {}) {
  const nativeSchema = schema && schema.__blazeJson__ ? schema.__blazeJson__ : schema;

  const nativeOptions = { ...options };
  if (options.resolve) {
    nativeOptions.resolve = (identifier) => {
      const result = options.resolve(identifier);
      if (result && result.__blazeJson__) {
        return result.__blazeJson__;
      }
      return result;
    };
  }

  const result = native.compileSchema(nativeSchema, nativeOptions);
  return wrapCompiledSchema(result);
}

function restoreSchema(json) {
  const nativeJson = json && json.__blazeJson__ ? json.__blazeJson__ : json;
  const result = native.restoreSchema(nativeJson);
  return wrapCompiledSchema(result);
}

function createResultWrapper(plainResult) {
  // Wrap a plain JS result object in a BlazeJSON-compatible interface
  return {
    ...plainResult,
    __blazeJson__: null, // Marker that this is a result wrapper, not native
    toJSON() {
      return plainResult;
    },
    toString() {
      return JSON.stringify(plainResult);
    },
    valueOf() {
      return plainResult;
    }
  };
}

function evaluateSchema(compiledSchema, instance) {
  const nativeSchema = compiledSchema && compiledSchema.__nativeCompiled__
    ? compiledSchema.__nativeCompiled__
    : compiledSchema;

  let nativeInstance;
  if (instance && instance.__blazeJson__) {
    nativeInstance = instance.__blazeJson__;
  } else if (instance === null || typeof instance !== 'object') {
    // For primitives (null, boolean, number, string), wrap them in BlazeJSON
    nativeInstance = native.parse(JSON.stringify(instance));
  } else {
    // Plain objects - will fail in native code with helpful error message
    nativeInstance = instance;
  }

  // Both fast and exhaustive modes return plain JS objects for GC efficiency
  const result = native.evaluateSchema(nativeSchema, nativeInstance);
  return createResultWrapper(result);
}

function from(value) {
  const result = native.from(value);
  return createProxy(result);
}

export const BlazeJSON = {
  parse,
  stringify,
  from
};

export { compileSchema, restoreSchema, evaluateSchema };
