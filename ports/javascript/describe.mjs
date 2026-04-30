import {
  ASSERTION_FAIL,
  ASSERTION_PROPERTY_DEPENDENCIES,
  LOGICAL_WHEN_TYPE,
  LOGICAL_WHEN_DEFINES,
  INSTRUCTION_NAMES
} from './opcodes.mjs';
import MESSAGES from './messages.json' with { type: 'json' };

const TYPE_NAMES = MESSAGES.types;
const TYPE_INTEGER = 2;
const TYPE_REAL = 3;
const TYPE_OBJECT = 6;

function jsonTypeOf(value) {
  if (value === null) return 0;
  if (typeof value === 'boolean') return 1;
  if (typeof value === 'bigint') return 2;
  if (typeof value === 'number') return Number.isInteger(value) ? 2 : 3;
  if (typeof value === 'string') return 4;
  if (Array.isArray(value)) return 5;
  return 6;
}

function valueTypeName(value) {
  if (typeof value === 'bigint') return 'integer';
  if (typeof value === 'number') return Number.isInteger(value) ? 'integer' : 'number';
  return TYPE_NAMES[jsonTypeOf(value)];
}

const escapeString = (input) => '"' + String(input).replaceAll('"', '\\"') + '"';

function stringifyValue(value) {
  if (typeof value === 'bigint') return String(value);
  return JSON.stringify(value, (key, current) =>
    typeof current === 'bigint' ? JSON.rawJSON(String(current)) : current);
}

function resolveTarget(instance, instanceLocation) {
  if (instanceLocation === '') return instance;
  let current = instance;
  for (const raw of instanceLocation.slice(1).split('/')) {
    const token = raw.replaceAll('~1', '/').replaceAll('~0', '~');
    current = Array.isArray(current) ? current[Number(token)] : current[token];
  }
  return current;
}

function extractKeyword(evaluatePath) {
  const match = evaluatePath.match(/\/([^/]+)$/);
  if (!match) return '';
  const token = match[1].replaceAll('~1', '/').replaceAll('~0', '~');
  return /^[0-9]+$/.test(token) ? '' : token;
}

const isWithinKeyword = (evaluatePath, keyword) =>
  evaluatePath.split('/').slice(1).some((segment) =>
    segment.replaceAll('~1', '/').replaceAll('~0', '~') === keyword);

function lastInstanceToken(instanceLocation) {
  if (instanceLocation === '') return null;
  return instanceLocation.slice(instanceLocation.lastIndexOf('/') + 1)
    .replaceAll('~1', '/').replaceAll('~0', '~');
}

const unicodeLength = (string) => [...string].length;

function jsonEqual(left, right) {
  if (left === right) return true;
  if (left === null || right === null) return left === right;
  if (typeof left !== typeof right) return false;
  if (typeof left !== 'object') return left === right;
  if (Array.isArray(left) !== Array.isArray(right)) return false;
  if (Array.isArray(left)) {
    if (left.length !== right.length) return false;
    for (let index = 0; index < left.length; index++) {
      if (!jsonEqual(left[index], right[index])) return false;
    }
    return true;
  }
  const leftKeys = Object.keys(left).sort();
  const rightKeys = Object.keys(right).sort();
  if (leftKeys.length !== rightKeys.length) return false;
  for (let index = 0; index < leftKeys.length; index++) {
    if (leftKeys[index] !== rightKeys[index]) return false;
    if (!jsonEqual(left[leftKeys[index]], right[rightKeys[index]])) return false;
  }
  return true;
}

function jsonCompare(left, right) {
  const leftType = jsonTypeOf(left);
  const rightType = jsonTypeOf(right);
  if (leftType !== rightType) return leftType - rightType;
  if (left === null) return 0;
  if (typeof left === 'boolean') return (left ? 1 : 0) - (right ? 1 : 0);
  if (typeof left === 'number' || typeof left === 'bigint') {
    if (left < right) return -1;
    if (left > right) return 1;
    return 0;
  }
  if (typeof left === 'string') return left < right ? -1 : left > right ? 1 : 0;
  const leftStr = JSON.stringify(left);
  const rightStr = JSON.stringify(right);
  return leftStr < rightStr ? -1 : leftStr > rightStr ? 1 : 0;
}

function normalizeTypes(bitmask) {
  let types = bitmask;
  const hasReal = (types & (1 << TYPE_REAL)) !== 0;
  const hasInteger = (types & (1 << TYPE_INTEGER)) !== 0;
  const hasDecimal = (types & (1 << 7)) !== 0;
  if (hasReal && hasInteger) types &= ~(1 << TYPE_INTEGER);
  if (hasReal && hasDecimal) types &= ~(1 << 7);
  if (hasInteger && hasDecimal) types &= ~(1 << 7);
  return types;
}

function describeTypeList(bitmask) {
  const types = normalizeTypes(bitmask);
  const names = [];
  for (let bit = 0; bit < 8; bit++) {
    if ((types & (1 << bit)) !== 0) names.push(TYPE_NAMES[bit]);
  }
  return names.length === 1 ? names[0] : formatList(names, 'or');
}

function formatList(items, conjunction) {
  if (items.length === 0) return '';
  if (items.length === 1) return conjunction + ' ' + items[0];
  return items.slice(0, -1).join(', ') + ', ' + conjunction + ' ' + items.at(-1);
}

function collectRequiredFromMap(target, valid, entries, all, present, withProperties, required) {
  for (const property in entries) {
    all.add(property);
    if (!Object.hasOwn(target, property)) continue;
    present.add(property);
    if (withProperties) withProperties.add(property);
    for (const dep of entries[property]) {
      if (valid || !Object.hasOwn(target, dep)) required.add(dep);
    }
  }
}

function analyzePropertyDependencies(ctx) {
  const all = new Set(), present = new Set(), required = new Set();
  collectRequiredFromMap(ctx.target, ctx.valid, ctx.value, all, present, null, required);
  return { all, present, required, withSchemas: new Set(), withProperties: new Set() };
}

function analyzeDependencies(ctx) {
  const all = new Set(), present = new Set(), withSchemas = new Set(),
        withProperties = new Set(), required = new Set();
  for (const child of ctx.children || []) {
    if (child[0] === LOGICAL_WHEN_DEFINES) {
      all.add(child[5]);
      if (Object.hasOwn(ctx.target, child[5])) {
        present.add(child[5]);
        withSchemas.add(child[5]);
      }
    } else if (child[0] === ASSERTION_PROPERTY_DEPENDENCIES) {
      collectRequiredFromMap(ctx.target, ctx.valid, child[5], all, present, withProperties, required);
    }
  }
  return { all, present, required, withSchemas, withProperties };
}

function analyzeDependentSchemas(ctx) {
  const all = new Set(), present = new Set();
  for (const child of ctx.children || []) {
    all.add(child[5]);
    if (Object.hasOwn(ctx.target, child[5])) present.add(child[5]);
  }
  return { all, present, required: new Set(), withSchemas: new Set(), withProperties: new Set() };
}

function ensureDepsAnalysis(ctx) {
  if (ctx.depsAnalysis !== undefined) return ctx.depsAnalysis;
  const raw = ctx.opcode === ASSERTION_PROPERTY_DEPENDENCIES ? analyzePropertyDependencies(ctx)
            : ctx.keyword === 'dependencies' ? analyzeDependencies(ctx)
            : analyzeDependentSchemas(ctx);
  return ctx.depsAnalysis = {
    allDependencies: [...raw.all].sort(),
    present: [...raw.present].sort(),
    presentWithSchemas: [...raw.withSchemas].sort(),
    presentWithProperties: [...raw.withProperties].sort(),
    required: [...raw.required].sort()
  };
}

function escapedList(items, conjunction) {
  return formatList(items.map(escapeString), conjunction);
}

function equalsAnyValues(ctx) {
  return ctx.equalsAnyValues ??= Array.isArray(ctx.value)
    ? ctx.value : (ctx.value.values || []);
}

function missingProperties(ctx) {
  return ctx.missingProperties ??= ctx.value
    .filter((property) => !Object.hasOwn(ctx.target, property))
    .sort();
}

function duplicateItems(ctx) {
  if (ctx.duplicateItems !== undefined) return ctx.duplicateItems;
  const duplicates = new Set();
  for (let index = 0; index < ctx.target.length; index++) {
    for (let other = index + 1; other < ctx.target.length; other++) {
      if (jsonEqual(ctx.target[index], ctx.target[other])) {
        duplicates.add(stringifyValue(ctx.target[index]));
      }
    }
  }
  return ctx.duplicateItems = [...duplicates].sort();
}

// Slot dispatch table. Each entry is a pure function from ctx to string.
// Templates in messages.json reference slots by integer ID (their index here).
const SLOTS = [
  (ctx) => TYPE_NAMES[ctx.targetType],                                                   // 0  targetTypeName
  (ctx) => valueTypeName(ctx.target),                                                    // 1  targetValueTypeName
  (ctx) => TYPE_NAMES[ctx.value],                                                        // 2  valueTypeName
  (ctx) => TYPE_NAMES[ctx.value[0]],                                                     // 3  firstValueTypeName
  (ctx) => valueTypeName(ctx.value),                                                     // 4  valueValueTypeName
  (ctx) => TYPE_NAMES[jsonTypeOf(ctx.value)],                                            // 5  valueOfTypeName
  (ctx) => describeTypeList(ctx.value),                                                  // 6  valueTypeList
  (ctx) => escapeString(ctx.value),                                                      // 7  escapedValue
  (ctx) => escapeString(ctx.target),                                                     // 8  escapedTarget
  (ctx) => escapeString(ctx.keyword),                                                    // 9  escapedKeyword
  (ctx) => escapeString(ctx.annotation),                                                 // 10 escapedAnnotation
  (ctx) => escapeString(ctx.value.source),                                               // 11 escapedRegexSource
  (ctx) => escapeString(lastInstanceToken(ctx.instanceLocation)),                        // 12 escapedPropertyName
  (ctx) => stringifyValue(ctx.target),                                                   // 13 stringifiedTarget
  (ctx) => stringifyValue(ctx.value),                                                    // 14 stringifiedValue
  (ctx) => stringifyValue(ctx.annotation),                                               // 15 stringifiedAnnotation
  (ctx) => String(ctx.value),                                                            // 16 rawValue
  (ctx) => ctx.value.source,                                                             // 17 regexSource
  (ctx) => lastInstanceToken(ctx.instanceLocation),                                      // 18 rawLastInstanceToken
  (ctx) => ctx.instanceLocation,                                                         // 19 instanceLocation
  (ctx) => String(ctx.children ? ctx.children.length : 0),                               // 20 childCount
  (ctx) => String((ctx.children ? ctx.children.length : 0) - 1),                         // 21 childCountMinusOne
  (ctx) => String(ctx.annotation + 1),                                                   // 22 prefixItemsCountPlusOne
  (ctx) => String(ctx.value[0]),                                                         // 23 min
  (ctx) => String(ctx.value[1]),                                                         // 24 max
  (ctx) => String(ctx.value - 1),                                                        // 25 valueMinusOne
  (ctx) => String(ctx.value + 1),                                                        // 26 valuePlusOne
  (ctx) => String(ctx.target.length),                                                    // 27 targetLengthString
  (ctx) => String(Object.keys(ctx.target).length),                                       // 28 objectSizeString
  (ctx) => String(unicodeLength(ctx.target)),                                            // 29 unicodeLengthString
  (ctx) => String(unicodeLength(lastInstanceToken(ctx.instanceLocation))),               // 30 propertyUnicodeLengthString
  (ctx) => formatList(ctx.annotation.map(stringifyValue), 'and'),                        // 31 examplesList
  (ctx) => TYPE_NAMES[Math.log2(normalizeTypes(ctx.value))],                             // 32 firstTypeNameInBitmask
  (ctx) => escapedList(ctx.value, 'and'),                                                // 33 valueListAnd
  (ctx) => escapedList([...ctx.value].sort(), 'and'),                                    // 34 sortedValueListAnd
  (ctx) => String(ctx.value[0].length),                                                  // 35 firstValueLength
  (ctx) => escapedList(missingProperties(ctx), 'and'),                                   // 36 missingPropertiesList
  (ctx) => escapeString(missingProperties(ctx)[0]),                                      // 37 missingPropertySingle
  (ctx) => duplicateItems(ctx)[0],                                                       // 38 duplicateItemSingle
  (ctx) => formatList(duplicateItems(ctx), 'and'),                                       // 39 duplicateItemsList
  (ctx) => escapeString(Object.keys(ctx.target)[0]),                                     // 40 firstObjectKeyEscaped
  (ctx) => escapedList(Object.keys(ctx.target), 'and'),                                  // 41 objectKeysList
  (ctx) => escapedList(Object.keys(ctx.target).sort(), 'and'),                           // 42 sortedObjectKeysList
  (ctx) => TYPE_NAMES[jsonTypeOf(equalsAnyValues(ctx)[0])],                              // 43 firstEqualsAnyValueTypeName
  (ctx) => stringifyValue(equalsAnyValues(ctx)[0]),                                      // 44 firstEqualsAnyValueStringified
  (ctx) => String(equalsAnyValues(ctx).length),                                          // 45 equalsAnyValuesLength
  (ctx) => formatList([...equalsAnyValues(ctx)].sort(jsonCompare).map(stringifyValue), 'and'), // 46 equalsAnySortedList
  (ctx) => String(ctx.target.length - ctx.value),                                        // 47 additionalItemCount
  (ctx) => escapeString(ensureDepsAnalysis(ctx).allDependencies[0]),                     // 48 depsAllDependenciesSingle
  (ctx) => escapedList(ensureDepsAnalysis(ctx).allDependencies, 'or'),                   // 49 depsAllDependenciesListOr
  (ctx) => escapeString(ensureDepsAnalysis(ctx).present[0]),                             // 50 depsPresentSingle
  (ctx) => escapedList(ensureDepsAnalysis(ctx).present, 'and'),                          // 51 depsPresentListAnd
  (ctx) => escapeString(ensureDepsAnalysis(ctx).required[0]),                            // 52 depsRequiredSingle
  (ctx) => escapedList(ensureDepsAnalysis(ctx).required, 'and'),                         // 53 depsRequiredListAnd
  (ctx) => escapeString(ensureDepsAnalysis(ctx).presentWithSchemas[0]),                  // 54 depsPresentSchemasSingle
  (ctx) => escapedList(ensureDepsAnalysis(ctx).presentWithSchemas, 'and')                // 55 depsPresentSchemasListAnd
];

// Selector dispatch table. Each entry is a tiny pure function from ctx to a
// non-negative integer. The compiler does
// `variants[Math.min(selectorFn(ctx), variants.length - 1)]`, so the last
// variant in any array is the catch-all "otherwise". Selector 0 is `byKeyword`,
// which is special: it pairs with a sibling `keys` array on its descriptor.
const SELECTORS = [
  null,                                                                                              // 0  byKeyword (special)
  (ctx) => ctx.valid ? 1 : 0,                                                                        // 1  validity
  (ctx) => ctx.instanceLocation === '' ? 0 : 1,                                                      // 2  instanceLocation: 0 empty, 1 present
  (ctx) => ctx.annotation ? 1 : 0,                                                                   // 3  annotation truthy
  (ctx) => ctx.targetType === TYPE_OBJECT ? 1 : 0,                                                   // 4  target is object
  (ctx) => isWithinKeyword(ctx.evaluatePath, 'propertyNames') ? 1 : 0,                               // 5  is within propertyNames
  (ctx) => ctx.targetType === TYPE_INTEGER ? 1 : 0,                                                  // 6  target is integer
  (ctx) => ctx.targetType === TYPE_REAL ? 1 : 0,                                                     // 7  target is real
  (ctx) => (ctx.value & (1 << TYPE_REAL)) !== 0 ? 1 : 0,                                             // 8  bitmask has real bit
  (ctx) => { const t = normalizeTypes(ctx.value); return (t & (t - 1)) === 0 ? 1 : 0; },             // 9  bitmask popcount is 1
  (ctx) => { const c = ctx.children; return c && c.length > 0 && c[0][0] === ASSERTION_FAIL ? 1 : 0; }, // 10 first child is fail
  (ctx) => { const c = ctx.children; return c && c.length === 1 && c[0][0] === ASSERTION_FAIL ? 1 : 0; }, // 11 first child is fail and child count is 1
  (ctx) => jsonEqual(ctx.target, ctx.value) ? 1 : 0,                                                 // 12 target equals value
  (ctx) => ctx.annotation === true ? 1 : 0,                                                          // 13 annotation === true
  (ctx) => typeof ctx.annotation === 'number' ? 1 : 0,                                               // 14 annotation is number
  (ctx) => ctx.annotation === 0 ? 1 : 0,                                                             // 15 annotation === 0
  (ctx) => ctx.value[1] === null ? 1 : 0,                                                            // 16 max (value[1]) is null
  (ctx) => ctx.value[0] === 0 ? 1 : 0,                                                               // 17 min (value[0]) is zero
  (ctx) => ctx.value[0] === ctx.value[1] ? 1 : 0,                                                    // 18 min equals max
  (ctx) => ensureDepsAnalysis(ctx).present.length === 0 ? 1 : 0,                                     // 19 no present deps
  (ctx) => { const d = ensureDepsAnalysis(ctx); return d.presentWithSchemas.length === 0 && d.presentWithProperties.length === 0 ? 1 : 0; }, // 20 no schemas-or-properties present deps
  (ctx) => ctx.target.length > ctx.value ? 1 : 0,                                                    // 21 target.length > value
  (ctx) => (ctx.children ? ctx.children.length : 0) > 1 ? 1 : 0,                                     // 22 child count > 1
  (ctx) => (ctx.children ? ctx.children.length : 0) <= 2 ? 1 : 0,                                    // 23 child count <= 2
  (ctx) => (ctx.children ? ctx.children.length : 0) === 1 ? 1 : 0,                                   // 24 child count === 1
  (ctx) => ctx.value === 1 ? 1 : 0,                                                                  // 25 value === 1
  (ctx) => (ctx.value - 1) === 1 ? 1 : 0,                                                            // 26 value - 1 === 1
  (ctx) => (ctx.value + 1) === 1 ? 1 : 0,                                                            // 27 value + 1 === 1
  (ctx) => ctx.value[0] === 1 ? 1 : 0,                                                               // 28 min === 1
  (ctx) => ctx.value[1] === 1 ? 1 : 0,                                                               // 29 max === 1
  (ctx) => ctx.target.length === 1 ? 1 : 0,                                                          // 30 target.length === 1
  (ctx) => unicodeLength(ctx.target) === 1 ? 1 : 0,                                                  // 31 unicodeLength(target) === 1
  (ctx) => unicodeLength(lastInstanceToken(ctx.instanceLocation)) === 1 ? 1 : 0,                     // 32 propertyName unicodeLength === 1
  (ctx) => (ctx.target.length - ctx.value) === 1 ? 1 : 0,                                            // 33 additional item count === 1
  (ctx) => missingProperties(ctx).length === 1 ? 1 : 0,                                              // 34 missing properties count === 1
  (ctx) => duplicateItems(ctx).length === 1 ? 1 : 0,                                                 // 35 duplicate items count === 1
  (ctx) => equalsAnyValues(ctx).length === 1 ? 1 : 0,                                                // 36 equalsAnyValues count === 1
  (ctx) => ctx.value[0].length === 1 ? 1 : 0,                                                        // 37 value[0].length === 1
  (ctx) => ensureDepsAnalysis(ctx).present.length === 1 ? 1 : 0,                                    // 38 present deps count === 1
  (ctx) => ensureDepsAnalysis(ctx).required.length === 1 ? 1 : 0,                                   // 39 required deps count === 1
  (ctx) => ensureDepsAnalysis(ctx).presentWithSchemas.length === 1 ? 1 : 0,                         // 40 presentWithSchemas count === 1
  (ctx) => ensureDepsAnalysis(ctx).allDependencies.length === 1 ? 1 : 0,                            // 41 allDependencies count === 1
  (ctx) => Math.min(ensureDepsAnalysis(ctx).required.length, 2),                                    // 42 required count clamped to 2 (3-way)
  (ctx) => Math.min(ensureDepsAnalysis(ctx).presentWithSchemas.length, 2),                          // 43 presentWithSchemas count clamped to 2 (3-way)
  (ctx) => Math.min(Object.keys(ctx.target).length, 2),                                              // 44 object size clamped to 2 (3-way)
  (ctx) => ctx.value === 1 ? 1 : ctx.value > 0 ? 2 : 0                                               // 45 loop items from (0=all, 1=one, 2=many)
];

function compileDescriptor(descriptor) {
  if (Array.isArray(descriptor)) {
    const segments = descriptor.map((seg, index) =>
      index % 2 === 0 ? seg : SLOTS[seg]);
    return (ctx) => {
      let result = '';
      for (let index = 0; index < segments.length; index++) {
        const segment = segments[index];
        result += typeof segment === 'string' ? segment : segment(ctx);
      }
      return result;
    };
  }

  const handlers = descriptor.variants.map(compileDescriptor);
  const lastIndex = handlers.length - 1;

  if (descriptor.select === 0) {
    const keys = descriptor.keys;
    return (ctx) => {
      const index = keys.indexOf(ctx.keyword);
      return handlers[index === -1 ? lastIndex : index](ctx);
    };
  }

  const selectorFn = SELECTORS[descriptor.select];
  return (ctx) => handlers[Math.min(selectorFn(ctx), lastIndex)](ctx);
}

// Sanity-check the JSON metadata against the in-memory implementation.
if (MESSAGES.slots.length !== SLOTS.length) {
  throw new Error('Slot count mismatch: ' + MESSAGES.slots.length + ' vs ' + SLOTS.length);
}
if (MESSAGES.selectors.length !== SELECTORS.length) {
  throw new Error('Selector count mismatch: ' + MESSAGES.selectors.length + ' vs ' + SELECTORS.length);
}

const OPCODE_COUNT = Math.max(...Object.values(INSTRUCTION_NAMES)) + 1;
const HANDLERS = new Array(OPCODE_COUNT);

for (const name in MESSAGES.messages) {
  const opcode = INSTRUCTION_NAMES[name];
  if (opcode === undefined || opcode < 0) {
    throw new Error('Unknown instruction name in messages.json: ' + name);
  }
  HANDLERS[opcode] = compileDescriptor(MESSAGES.messages[name]);
}

export function describe(valid, instruction, evaluatePath,
                         instanceLocation, instance, annotation) {
  const opcode = instruction[0];
  const handler = HANDLERS[opcode];
  if (handler === undefined) return '<unknown>';
  const target = resolveTarget(instance, instanceLocation);
  return handler({
    valid, instruction, evaluatePath, instanceLocation, instance, annotation,
    opcode, value: instruction[5], children: instruction[6],
    keyword: extractKeyword(evaluatePath),
    target, targetType: jsonTypeOf(target)
  });
}
