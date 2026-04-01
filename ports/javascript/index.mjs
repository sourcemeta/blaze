const DEPTH_LIMIT = 300;
const ANNOTATION_EMIT = 44;
const ANNOTATION_TO_PARENT = 45;
const ANNOTATION_BASENAME_TO_PARENT = 46;
const CONTROL_GROUP_START = 85;
const CONTROL_EVALUATE_END = 89;

function buildJsonPointer(tokens, length) {
  if (length === 0) return '';
  let result = '';
  for (let index = 0; index < length; index++) {
    const token = String(tokens[index]);
    result += '/' + token.replaceAll('~', '~0').replaceAll('/', '~1');
  }
  return result;
}

const Type = {
  Null: 0,
  Boolean: 1,
  Integer: 2,
  Real: 3,
  String: 4,
  Array: 5,
  Object: 6,
  Decimal: 7
};

function jsonTypeOf(value) {
  if (value === null) return Type.Null;
  switch (typeof value) {
    case 'boolean': return Type.Boolean;
    case 'number': return Number.isInteger(value) ? Type.Integer : Type.Real;
    case 'string': return Type.String;
    case 'object': return Array.isArray(value) ? Type.Array : Type.Object;
    default: return Type.Null;
  }
}

function isIntegral(value) {
  return typeof value === 'number' && Number.isFinite(value) && Math.floor(value) === value;
}

function resolveInstance(instance, relativeInstanceLocation) {
  if (relativeInstanceLocation.length === 0) return instance;
  let current = instance;
  for (let index = 0; index < relativeInstanceLocation.length; index++) {
    if (current === undefined || current === null) return undefined;
    current = current[relativeInstanceLocation[index]];
  }
  return current;
}

function prepareInstruction(instruction) {
  const wrapper = instruction[5];
  if (wrapper === undefined || wrapper === null) {
    instruction[5] = null;
  } else {
    const typeIndex = wrapper[0];
    if (typeIndex === 0 || wrapper.length === 1) {
      instruction[5] = null;
    } else {
      const payload = wrapper[1];
      switch (typeIndex) {
        case 4:
          instruction[5] = payload[0];
          break;
        case 9:
          try { instruction[5] = new RegExp(payload, 'u'); }
          catch { instruction[5] = new RegExp(payload); }
          break;
        case 13: {
          if (Array.isArray(payload)) {
            const object = Object.create(null);
            for (let index = 0; index < payload.length; index++) {
              object[payload[index][0]] = payload[index][1];
            }
            instruction[5] = object;
          } else {
            instruction[5] = payload;
          }
          break;
        }
        case 15: {
          if (Array.isArray(payload)) {
            const object = Object.create(null);
            for (let index = 0; index < payload.length; index++) {
              object[payload[index][0]] = payload[index][1];
            }
            instruction[5] = object;
          } else {
            instruction[5] = payload;
          }
          break;
        }
        case 16: {
          payload[0] = new Set(payload[0]);
          const regexes = payload[2];
          for (let index = 0; index < regexes.length; index++) {
            try { regexes[index] = new RegExp(regexes[index], 'u'); }
            catch { regexes[index] = new RegExp(regexes[index]); }
          }
          instruction[5] = payload;
          break;
        }
        default:
          instruction[5] = payload;
          break;
      }
    }
  }

  if (instruction.length < 7) {
    instruction.push(undefined);
  }

  instruction.push(handlers[instruction[0]] || null);

  const children = instruction[6];
  if (children) {
    for (let index = 0; index < children.length; index++) {
      prepareInstruction(children[index]);
    }
  }
}

function resolveJumpTargets(instructions, targets) {
  for (let index = 0; index < instructions.length; index++) {
    const instruction = instructions[index];
    if (instruction[0] === 91) {
      const targetIndex = instruction[5];
      if (targetIndex < targets.length) {
        instruction[5] = targets[targetIndex];
      }
    }
    const children = instruction[6];
    if (children) {
      resolveJumpTargets(children, targets);
    }
  }
}

const FNV_OFFSET = 14695981039346656037n;
const FNV_PRIME = 1099511628211n;
const MASK_53 = (1n << 53n) - 1n;

function blazeHash(resource, fragment) {
  let result = FNV_OFFSET & MASK_53;
  for (let index = 0; index < fragment.length; index++) {
    result ^= BigInt(fragment.charCodeAt(index));
    result = (result * FNV_PRIME) & MASK_53;
  }
  return Number((BigInt(resource) + result) & MASK_53);
}

function collectAnchorNames(targets, result) {
  for (let targetIndex = 0; targetIndex < targets.length; targetIndex++) {
    collectAnchorNamesFromInstructions(targets[targetIndex], result);
  }
}

function collectAnchorNamesFromInstructions(instructions, result) {
  for (let index = 0; index < instructions.length; index++) {
    const instruction = instructions[index];
    if (instruction[0] === 90 && typeof instruction[5] === 'string') {
      result.add(instruction[5]);
    }
    if (instruction[6]) {
      collectAnchorNamesFromInstructions(instruction[6], result);
    }
  }
}

function compile(template) {
  const targets = template[2];
  for (let targetIndex = 0; targetIndex < targets.length; targetIndex++) {
    const target = targets[targetIndex];
    for (let index = 0; index < target.length; index++) {
      prepareInstruction(target[index]);
    }
  }

  for (let targetIndex = 0; targetIndex < targets.length; targetIndex++) {
    resolveJumpTargets(targets[targetIndex], targets);
  }

  const labels = new Map();
  const rawLabels = template[3];
  for (let index = 0; index < rawLabels.length; index++) {
    const pair = rawLabels[index];
    labels.set(pair[0], pair[1]);
  }

  const anchors = new Map();
  if (template[0]) {
    const anchorNames = new Set();
    collectAnchorNames(targets, anchorNames);
    const resourceCount = targets.length;
    for (const anchor of anchorNames) {
      for (let resource = 0; resource <= resourceCount; resource++) {
        const hash = blazeHash(resource, anchor);
        const targetIndex = labels.get(hash);
        if (targetIndex !== undefined) {
          anchors.set(resource + ':' + anchor, targets[targetIndex]);
        }
      }
    }
  }

  template[4] = labels;
  template[5] = anchors;
  return template;
}

class Blaze {
  constructor(template) {
    compile(template);
    this.template = template;
    this.callbackMode = false;
  }

  validate(instance, callback) {
    const template = this.template;
    const targets = template[2];
    if (targets.length === 0) return true;

    const track = template[1];
    const dynamic = template[0];
    this.trackMode = track;
    this.dynamicMode = dynamic;
    this.callbackMode = callback !== undefined;
    this.callback = callback;

    if (this.callbackMode) {
      this.evaluatePathLength = 0;
      this.evaluatePathTokens = [];
      this.instanceLocationLength = 0;
      this.instanceLocationTokens = [];
      this.resources = [];
      if (track || dynamic) {
        evaluateInstruction = evaluateInstructionTrackedCallback;
        if (track) {
          this.evaluated = [];
        }
      } else {
        evaluateInstruction = evaluateInstructionFastCallback;
      }
    } else if (track || dynamic) {
      evaluateInstruction = evaluateInstructionTracked;
      if (track) {
        this.evaluatePathLength = 0;
        this.evaluatePathTokens = [];
        this.evaluated = [];
      }
      if (dynamic) {
        this.resources = [];
      }
    } else {
      evaluateInstruction = evaluateInstructionFast;
    }

    const instructions = targets[0];
    let result = true;
    for (let index = 0; index < instructions.length; index++) {
      if (!evaluateInstruction(instructions[index], instance, 0, template, this)) {
        result = false;
        break;
      }
    }

    this.resources = undefined;
    this.evaluated = undefined;
    this.evaluatePathTokens = undefined;
    this.instanceLocationTokens = undefined;
    this.callback = undefined;
    this.callbackMode = false;
    return result;
  }

  snapshotPathTokens() {
    return this.evaluatePathTokens.slice(0, this.evaluatePathLength);
  }

  pushPath(relativeSchemaLocation) {
    for (let index = 0; index < relativeSchemaLocation.length; index++) {
      if (this.evaluatePathLength < this.evaluatePathTokens.length) {
        this.evaluatePathTokens[this.evaluatePathLength] = relativeSchemaLocation[index];
      } else {
        this.evaluatePathTokens.push(relativeSchemaLocation[index]);
      }
      this.evaluatePathLength++;
    }
  }

  popPath(count) {
    this.evaluatePathLength -= count;
  }

  callbackPush(instruction) {
    if (!this.trackMode) {
      this.pushPath(instruction[1]);
    }
    const relInstance = instruction[2];
    for (let index = 0; index < relInstance.length; index++) {
      this.pushInstanceToken(relInstance[index]);
    }
    this.callback("pre", true, instruction,
      buildJsonPointer(this.evaluatePathTokens, this.evaluatePathLength),
      buildJsonPointer(this.instanceLocationTokens, this.instanceLocationLength),
      null);
  }

  callbackPop(instruction, result) {
    const isAnnotation = instruction[0] >= ANNOTATION_EMIT &&
                         instruction[0] <= ANNOTATION_BASENAME_TO_PARENT;
    this.callback("post", result, instruction,
      buildJsonPointer(this.evaluatePathTokens, this.evaluatePathLength),
      buildJsonPointer(this.instanceLocationTokens, this.instanceLocationLength),
      isAnnotation ? instruction[5] : null);
    if (!this.trackMode) {
      this.popPath(instruction[1].length);
    }
    const relInstance = instruction[2];
    for (let index = 0; index < relInstance.length; index++) {
      this.popInstanceToken();
    }
  }

  callbackAnnotation(instruction) {
    if (!this.trackMode) {
      this.pushPath(instruction[1]);
    }
    const relInstance = instruction[2];
    for (let index = 0; index < relInstance.length; index++) {
      this.pushInstanceToken(relInstance[index]);
    }
    const evaluatePath = buildJsonPointer(this.evaluatePathTokens, this.evaluatePathLength);
    const opcode = instruction[0];
    let instanceLocation;
    if (opcode === ANNOTATION_EMIT) {
      instanceLocation = buildJsonPointer(this.instanceLocationTokens, this.instanceLocationLength);
    } else {
      const parentLength = this.instanceLocationLength > 0 ? this.instanceLocationLength - 1 : 0;
      instanceLocation = buildJsonPointer(this.instanceLocationTokens, parentLength);
    }
    let annotationValue = instruction[5];
    if (opcode === ANNOTATION_BASENAME_TO_PARENT && this.instanceLocationLength > 0) {
      annotationValue = this.instanceLocationTokens[this.instanceLocationLength - 1];
    }
    this.callback("pre", true, instruction, evaluatePath, instanceLocation, null);
    this.callback("post", true, instruction, evaluatePath, instanceLocation, annotationValue);
    if (!this.trackMode) {
      this.popPath(instruction[1].length);
    }
    for (let index = 0; index < relInstance.length; index++) {
      this.popInstanceToken();
    }
  }

  pushInstanceToken(token) {
    if (this.instanceLocationLength < this.instanceLocationTokens.length) {
      this.instanceLocationTokens[this.instanceLocationLength] = token;
    } else {
      this.instanceLocationTokens.push(token);
    }
    this.instanceLocationLength++;
  }

  popInstanceToken() {
    this.instanceLocationLength--;
  }

  markEvaluated(target, parent, key) {
    this.evaluated.push({
      instance: target,
      parent: parent,
      key: key,
      pathTokens: this.snapshotPathTokens(),
      pathLength: this.evaluatePathLength,
      skip: false
    });
  }

  isEvaluated(target, parent, key) {
    const pathLen = this.evaluatePathLength;
    const initialLen = pathLen <= 1 ? 0 : pathLen - 1;
    const initialTokens = this.evaluatePathTokens;
    const isPrimitive = target === null || typeof target !== 'object';
    const hasLocation = parent !== undefined;

    for (let index = this.evaluated.length - 1; index >= 0; index--) {
      const entry = this.evaluated[index];
      if (entry.skip) continue;

      if (isPrimitive && hasLocation && entry.parent !== undefined) {
        if (entry.parent !== parent || entry.key !== key) continue;
      } else {
        if (entry.instance !== target) continue;
      }

      if (initialLen === 0) return true;
      if (entry.pathLength < initialLen) continue;
      let match = true;
      for (let token = 0; token < initialLen; token++) {
        if (entry.pathTokens[token] !== initialTokens[token]) {
          match = false;
          break;
        }
      }
      if (match) return true;
    }
    return false;
  }

  unevaluate() {
    const pathLen = this.evaluatePathLength;
    const tokens = this.evaluatePathTokens;
    for (let index = 0; index < this.evaluated.length; index++) {
      const entry = this.evaluated[index];
      if (entry.skip) continue;
      if (entry.pathLength < pathLen) continue;
      let match = true;
      for (let token = 0; token < pathLen; token++) {
        if (entry.pathTokens[token] !== tokens[token]) {
          match = false;
          break;
        }
      }
      if (match) entry.skip = true;
    }
  }
}

function evaluateInstructionFast(instruction, instance, depth, template, evaluator) {
  if (depth > DEPTH_LIMIT) {
    throw new Error('The evaluation path depth limit was reached likely due to infinite recursion');
  }
  const handler = instruction[7];
  if (!handler) return true;
  return handler(instruction, instance, depth, template, evaluator);
}

function evaluateInstructionTracked(instruction, instance, depth, template, evaluator) {
  if (depth > DEPTH_LIMIT) {
    throw new Error('The evaluation path depth limit was reached likely due to infinite recursion');
  }
  const handler = instruction[7];
  if (!handler) return true;

  const type = instruction[0];
  if (type < 85 || type > 89) {
    if (evaluator.trackMode) {
      evaluator.pushPath(instruction[1]);
    }
    if (evaluator.dynamicMode) {
      evaluator.resources.push(instruction[4]);
    }

    const result = handler(instruction, instance, depth, template, evaluator);

    if (evaluator.trackMode) {
      evaluator.popPath(instruction[1].length);
    }
    if (evaluator.dynamicMode) {
      evaluator.resources.pop();
    }
    return result;
  }

  return handler(instruction, instance, depth, template, evaluator);
}

function evaluateInstructionFastCallback(instruction, instance, depth, template, evaluator) {
  if (depth > DEPTH_LIMIT) {
    throw new Error('The evaluation path depth limit was reached likely due to infinite recursion');
  }
  const handler = instruction[7];
  if (!handler) return true;
  return handler(instruction, instance, depth, template, evaluator);
}

function evaluateInstructionTrackedCallback(instruction, instance, depth, template, evaluator) {
  if (depth > DEPTH_LIMIT) {
    throw new Error('The evaluation path depth limit was reached likely due to infinite recursion');
  }
  const handler = instruction[7];
  if (!handler) return true;

  const type = instruction[0];
  if (type < CONTROL_GROUP_START || type > CONTROL_EVALUATE_END) {
    if (evaluator.trackMode) {
      evaluator.pushPath(instruction[1]);
    }
    if (evaluator.dynamicMode) {
      evaluator.resources.push(instruction[4]);
    }

    const result = handler(instruction, instance, depth, template, evaluator);

    if (evaluator.trackMode) {
      evaluator.popPath(instruction[1].length);
    }
    if (evaluator.dynamicMode) {
      evaluator.resources.pop();
    }
    return result;
  }

  return handler(instruction, instance, depth, template, evaluator);
}

let evaluateInstruction = evaluateInstructionFast;

function effectiveTypeStrictReal(value) {
  const type = jsonTypeOf(value);
  if (type === Type.Real && Number.isInteger(value)) return Type.Integer;
  return type;
}

function typeSetTest(bitmask, typeIndex) {
  return (bitmask & (1 << typeIndex)) !== 0;
}

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
  const keysLeft = Object.keys(left);
  const keysRight = Object.keys(right);
  if (keysLeft.length !== keysRight.length) return false;
  for (let index = 0; index < keysLeft.length; index++) {
    const key = keysLeft[index];
    if (!Object.hasOwn(right, key)) return false;
    if (!jsonEqual(left[key], right[key])) return false;
  }
  return true;
}

function fastHash(value) {
  if (value === null) return 2;
  switch (typeof value) {
    case 'boolean': return value ? 1 : 0;
    case 'number': return 4 + ((value | 0) & 255);
    case 'string': return 3 + value.length;
    case 'object':
      if (Array.isArray(value)) {
        let hash = 6;
        for (let index = 0; index < value.length; index++) hash += 1 + fastHash(value[index]);
        return hash;
      } else {
        let hash = 7;
        for (const key in value) hash += 1 + key.length + fastHash(value[key]);
        return hash;
      }
    default: return 2;
  }
}

function isUnique(array) {
  if (array.length <= 1) return true;
  const hashes = new Array(array.length);
  for (let index = 0; index < array.length; index++) {
    hashes[index] = fastHash(array[index]);
  }
  for (let index = 1; index < array.length; index++) {
    for (let previous = 0; previous < index; previous++) {
      if (hashes[index] === hashes[previous] && jsonEqual(array[index], array[previous])) return false;
    }
  }
  return true;
}

function isDivisibleBy(value, divisor) {
  if (divisor === 0) return false;
  const remainder = value % divisor;
  if (remainder === 0) return true;
  return Math.abs(remainder) < 1e-9 || Math.abs(remainder - divisor) < 1e-9 ||
         Math.abs(remainder + divisor) < 1e-9;
}

function unicodeLength(string) {
  let count = 0;
  for (let index = 0; index < string.length; index++) {
    count++;
    if (string.charCodeAt(index) >= 0xD800 && string.charCodeAt(index) <= 0xDBFF) index++;
  }
  return count;
}

function objectSize(object) {
  let count = 0;
  for (const key in object) count++;
  return count;
}

function isObject(value) {
  return value !== null && typeof value === 'object' && !Array.isArray(value);
}

function AssertionFail(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
  return false;
};

function AssertionDefines(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = Object.hasOwn(target, instruction[5]);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionDefinesStrict(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const __result = Object.hasOwn(target, instruction[5]);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionDefinesAll(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const strings = instruction[5];
  for (let index = 0; index < strings.length; index++) {
    if (!Object.hasOwn(target, strings[index])) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function AssertionDefinesAllStrict(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const strings = instruction[5];
  for (let index = 0; index < strings.length; index++) {
    if (!Object.hasOwn(target, strings[index])) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function AssertionDefinesExactly(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  let targetSize = 0;
  for (const key in target) targetSize++;
  const strings = instruction[5];
  if (targetSize !== strings.length) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  for (let index = 0; index < strings.length; index++) {
    if (!Object.hasOwn(target, strings[index])) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function AssertionDefinesExactlyStrict(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  let targetSize = 0;
  for (const key in target) targetSize++;
  const strings = instruction[5];
  if (targetSize !== strings.length) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  for (let index = 0; index < strings.length; index++) {
    if (!Object.hasOwn(target, strings[index])) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function AssertionDefinesExactlyStrictHash3(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const entries = instruction[5][0];
  let count = 0;
  for (const key in target) count++;
  if (count !== 3) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const __result = Object.hasOwn(target, entries[0][1]) &&
    Object.hasOwn(target, entries[1][1]) &&
    Object.hasOwn(target, entries[2][1]);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionPropertyDependencies(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const value = instruction[5];
  for (const property in value) {
    if (!Object.hasOwn(target, property)) continue;
    const dependencies = value[property];
    for (let index = 0; index < dependencies.length; index++) {
      if (!Object.hasOwn(target, dependencies[index])) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
        return false;
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function AssertionType(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  const expected = instruction[5];
  const actual = jsonTypeOf(target);
  if (actual === expected) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  if (expected === Type.Integer && isIntegral(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
  return false;
};

function AssertionTypeAny(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  const bitmask = instruction[5];
  const typeIndex = jsonTypeOf(target);
  if (typeSetTest(bitmask, typeIndex)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  if (typeSetTest(bitmask, Type.Integer) && isIntegral(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
  return false;
};

function AssertionTypeStrict(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  const __result = effectiveTypeStrictReal(target) === instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionTypeStrictAny(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  const __result = typeSetTest(instruction[5], effectiveTypeStrictReal(target));
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionTypeStringBounded(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (typeof target !== 'string') {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const range = instruction[5];
  const length = unicodeLength(target);
  if (length < range[0]) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  if (range[1] !== null && length > range[1]) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function AssertionTypeStringUpper(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  const __result = typeof target === 'string' && unicodeLength(target) <= instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionTypeArrayBounded(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const range = instruction[5];
  if (target.length < range[0]) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  if (range[1] !== null && target.length > range[1]) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function AssertionTypeArrayUpper(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  const __result = Array.isArray(target) && target.length <= instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionTypeObjectBounded(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const range = instruction[5];
  const size = objectSize(target);
  if (size < range[0]) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  if (range[1] !== null && size > range[1]) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function AssertionTypeObjectUpper(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const __result = objectSize(target) <= instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionRegex(instruction, instance, depth, template, evaluator) {
  const target = evaluator.propertyTarget !== undefined
    ? evaluator.propertyTarget : resolveInstance(instance, instruction[2]);
  if (typeof target !== 'string') return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = instruction[5].test(target);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionStringSizeLess(instruction, instance, depth, template, evaluator) {
  const target = evaluator.propertyTarget !== undefined
    ? evaluator.propertyTarget : resolveInstance(instance, instruction[2]);
  if (typeof target !== 'string') return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = unicodeLength(target) < instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionStringSizeGreater(instruction, instance, depth, template, evaluator) {
  const target = evaluator.propertyTarget !== undefined
    ? evaluator.propertyTarget : resolveInstance(instance, instruction[2]);
  if (typeof target !== 'string') return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = unicodeLength(target) > instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionArraySizeLess(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = target.length < instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionArraySizeGreater(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = target.length > instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionObjectSizeLess(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = objectSize(target) < instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionObjectSizeGreater(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = objectSize(target) > instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionEqual(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  let __result;
  if (evaluator.propertyTarget !== undefined) {
    const value = instruction[5];
    __result = typeof value === 'string' && value === evaluator.propertyTarget;
  } else {
    __result = jsonEqual(resolveInstance(instance, instruction[2]), instruction[5]);
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionEqualsAny(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  if (evaluator.propertyTarget !== undefined) {
    const values = instruction[5];
    for (let index = 0; index < values.length; index++) {
      if (jsonEqual(evaluator.propertyTarget, values[index])) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
        return true;
      }
    }
  } else {
    const target = resolveInstance(instance, instruction[2]);
    const values = instruction[5];
    for (let index = 0; index < values.length; index++) {
      if (jsonEqual(target, values[index])) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
        return true;
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
  return false;
};

function AssertionEqualsAnyStringHash(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = evaluator.propertyTarget !== undefined
    ? evaluator.propertyTarget
    : resolveInstance(instance, instruction[2]);
  if (typeof target !== 'string') {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }

  const value = instruction[5];
  const entries = value[0];
  const tableOfContents = value[1];

  const stringSize = target.length;
  if (stringSize < tableOfContents.length) {
    const hint = tableOfContents[stringSize];
    if (hint[1] === 0) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
    for (let index = hint[0] - 1; index < hint[1]; index++) {
      if (entries[index][1] === target) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
        return true;
      }
    }
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }

  if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
  return false;
};

function AssertionGreaterEqual(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (typeof target !== 'number') return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = target >= instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionLessEqual(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (typeof target !== 'number') return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = target <= instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionGreater(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (typeof target !== 'number') return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = target > instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionLess(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (typeof target !== 'number') return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = target < instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionUnique(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = isUnique(target);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionDivisible(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (typeof target !== 'number') return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = isDivisibleBy(target, instruction[5]);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionStringType(instruction, instance, depth, template, evaluator) {
  const target = evaluator.propertyTarget !== undefined
    ? evaluator.propertyTarget : resolveInstance(instance, instruction[2]);
  if (typeof target !== 'string') return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  try {
    new URL(target);
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  } catch {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
};

function AssertionPropertyType(instruction, instance, depth, template, evaluator) {
  if (!isObject(instance)) return true;
  const target = resolveInstance(instance, instruction[2]);
  if (target === undefined) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const expected = instruction[5];
  const actual = jsonTypeOf(target);
  const __result = actual === expected || (expected === Type.Integer && isIntegral(target));
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionPropertyTypeEvaluate(instruction, instance, depth, template, evaluator) {
  if (!isObject(instance)) return true;
  const target = resolveInstance(instance, instruction[2]);
  if (target === undefined) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const expected = instruction[5];
  const actual = jsonTypeOf(target);
  const result = actual === expected || (expected === Type.Integer && isIntegral(target));
  if (result && evaluator.trackMode) {
    const location = instruction[2];
    evaluator.markEvaluated(target, instance, location.length > 0 ? location[location.length - 1] : undefined);
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, result);
  return result;
};

function AssertionPropertyTypeStrict(instruction, instance, depth, template, evaluator) {
  if (!isObject(instance)) return true;
  const target = resolveInstance(instance, instruction[2]);
  if (target === undefined) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = effectiveTypeStrictReal(target) === instruction[5];
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionPropertyTypeStrictEvaluate(instruction, instance, depth, template, evaluator) {
  if (!isObject(instance)) return true;
  const target = resolveInstance(instance, instruction[2]);
  if (target === undefined) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const result = effectiveTypeStrictReal(target) === instruction[5];
  if (result && evaluator.trackMode) {
    const location = instruction[2];
    evaluator.markEvaluated(target, instance, location.length > 0 ? location[location.length - 1] : undefined);
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, result);
  return result;
};

function AssertionPropertyTypeStrictAny(instruction, instance, depth, template, evaluator) {
  if (!isObject(instance)) return true;
  const target = resolveInstance(instance, instruction[2]);
  if (target === undefined) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const __result = typeSetTest(instruction[5], effectiveTypeStrictReal(target));
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function AssertionPropertyTypeStrictAnyEvaluate(instruction, instance, depth, template, evaluator) {
  if (!isObject(instance)) return true;
  const target = resolveInstance(instance, instruction[2]);
  if (target === undefined) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const result = typeSetTest(instruction[5], effectiveTypeStrictReal(target));
  if (result && evaluator.trackMode) {
    const location = instruction[2];
    evaluator.markEvaluated(target, instance, location.length > 0 ? location[location.length - 1] : undefined);
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, result);
  return result;
};

function AssertionArrayPrefix(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  if (target.length === 0) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  const children = instruction[6];
  const prefixes = children.length - 1;
  const pointer = target.length === prefixes ? prefixes : Math.min(target.length, prefixes) - 1;
  const entry = children[pointer];
  const entryChildren = entry[6];
  if (entryChildren) {
    for (let index = 0; index < entryChildren.length; index++) {
      if (!evaluateInstruction(entryChildren[index], target, depth + 1, template, evaluator)) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
        return false;
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function AssertionArrayPrefixEvaluate(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  if (target.length === 0) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  const children = instruction[6];
  const prefixes = children.length - 1;
  const pointer = target.length === prefixes ? prefixes : Math.min(target.length, prefixes) - 1;
  const entry = children[pointer];
  const entryChildren = entry[6];
  if (entryChildren) {
    for (let index = 0; index < entryChildren.length; index++) {
      if (!evaluateInstruction(entryChildren[index], target, depth + 1, template, evaluator)) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
        return false;
      }
    }
  }
  if (evaluator.trackMode) {
    if (target.length === prefixes) {
      evaluator.markEvaluated(target);
    } else {
      for (let cursor = 0; cursor <= pointer; cursor++) {
        evaluator.markEvaluated(target[cursor], target, cursor);
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function AnnotationEmit(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackAnnotation(instruction);
  return true;
}
function AnnotationToParent(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackAnnotation(instruction);
  return true;
}
function AnnotationBasenameToParent(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackAnnotation(instruction);
  return true;
}

function Evaluate(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  if (evaluator.trackMode) {
    const target = resolveInstance(instance, instruction[2]);
    evaluator.markEvaluated(target);
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LogicalNot(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  const children = instruction[6];
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (!evaluateInstruction(children[index], target, depth + 1, template, evaluator)) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
        return true;
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
  return false;
};

function LogicalNotEvaluate(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  const children = instruction[6];
  let result = false;
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (!evaluateInstruction(children[index], target, depth + 1, template, evaluator)) {
        result = true;
        break;
      }
    }
  }
  if (evaluator.trackMode) evaluator.unevaluate();
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, result);
  return result;
};

function LogicalOr(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  if (!children || children.length === 0) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  const target = resolveInstance(instance, instruction[2]);
  const exhaustive = instruction[5];
  let result = false;
  if (exhaustive) {
    for (let index = 0; index < children.length; index++) {
      if (evaluateInstruction(children[index], target, depth + 1, template, evaluator)) {
        result = true;
      }
    }
  } else {
    for (let index = 0; index < children.length; index++) {
      if (evaluateInstruction(children[index], target, depth + 1, template, evaluator)) {
        result = true;
        break;
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, result);
  return result;
};

function LogicalAnd(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  const children = instruction[6];
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (!evaluateInstruction(children[index], target, depth + 1, template, evaluator)) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
        return false;
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LogicalXor(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  const exhaustive = instruction[5];
  const children = instruction[6];
  let result = true;
  let hasMatched = false;
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (evaluateInstruction(children[index], target, depth + 1, template, evaluator)) {
        if (hasMatched) {
          result = false;
          if (!exhaustive) break;
        } else {
          hasMatched = true;
        }
      }
    }
  }
  const __result = result && hasMatched;
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function LogicalCondition(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const value = instruction[5];
  const thenStart = value[0];
  const elseStart = value[1];
  const children = instruction[6];
  const childrenSize = children ? children.length : 0;

  let conditionEnd = childrenSize;
  if (thenStart > 0) conditionEnd = thenStart;
  else if (elseStart > 0) conditionEnd = elseStart;

  const target = resolveInstance(instance, instruction[2]);

  let conditionResult = true;
  for (let cursor = 0; cursor < conditionEnd; cursor++) {
    if (!evaluateInstruction(children[cursor], target, depth + 1, template, evaluator)) {
      conditionResult = false;
      break;
    }
  }

  const consequenceStart = conditionResult ? thenStart : elseStart;
  const consequenceEnd = (conditionResult && elseStart > 0) ? elseStart : childrenSize;

  if (consequenceStart > 0) {
    if (evaluator.trackMode || evaluator.callbackMode) {
      evaluator.popPath(instruction[1].length);
    }

    let result = true;
    for (let cursor = consequenceStart; cursor < consequenceEnd; cursor++) {
      if (!evaluateInstruction(children[cursor], target, depth + 1, template, evaluator)) {
        result = false;
        break;
      }
    }

    if (evaluator.trackMode || evaluator.callbackMode) {
      evaluator.pushPath(instruction[1]);
    }

    if (evaluator.callbackMode) evaluator.callbackPop(instruction, result);
    return result;
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LogicalWhenType(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (jsonTypeOf(target) !== instruction[5]) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (!evaluateInstruction(children[index], target, depth + 1, template, evaluator)) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
        return false;
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LogicalWhenDefines(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (!Object.hasOwn(target, instruction[5])) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (!evaluateInstruction(children[index], target, depth + 1, template, evaluator)) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
        return false;
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LogicalWhenArraySizeGreater(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target) || target.length <= instruction[5]) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (!evaluateInstruction(children[index], target, depth + 1, template, evaluator)) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
        return false;
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesUnevaluated(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  if (evaluator.trackMode && evaluator.isEvaluated(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  const children = instruction[6];
  for (const key in target) {
    if (evaluator.trackMode && evaluator.isEvaluated(target[key], target, key)) continue;
    if (evaluator.callbackMode) evaluator.pushInstanceToken(key);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[key], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  if (evaluator.trackMode) evaluator.markEvaluated(target);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesUnevaluatedExcept(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  if (evaluator.trackMode && evaluator.isEvaluated(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  const filter = instruction[5];
  const filterStrings = filter[0];
  const filterPrefixes = filter[1];
  const filterRegexes = filter[2];
  const children = instruction[6];
  for (const key in target) {
    if (filterStrings.has(key)) continue;
    let matched = false;
    for (let index = 0; index < filterPrefixes.length; index++) {
      if (key.startsWith(filterPrefixes[index])) { matched = true; break; }
    }
    if (matched) continue;
    for (let index = 0; index < filterRegexes.length; index++) {
      filterRegexes[index].lastIndex = 0;
      if (filterRegexes[index].test(key)) { matched = true; break; }
    }
    if (matched) continue;
    if (evaluator.trackMode && evaluator.isEvaluated(target[key], target, key)) continue;
    if (evaluator.callbackMode) evaluator.pushInstanceToken(key);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[key], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  if (evaluator.trackMode) evaluator.markEvaluated(target);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesMatch(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  for (const key in target) {
    const index = instruction[5][key];
    if (index === undefined) continue;
    const subinstruction = children[index];
    const subchildren = subinstruction[6];
    if (subchildren) {
      for (let childIndex = 0; childIndex < subchildren.length; childIndex++) {
        if (!evaluateInstruction(subchildren[childIndex], target, depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesMatchClosed(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  for (const key in target) {
    const index = instruction[5][key];
    if (index === undefined) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
    const subinstruction = children[index];
    const subchildren = subinstruction[6];
    if (subchildren) {
      for (let childIndex = 0; childIndex < subchildren.length; childIndex++) {
        if (!evaluateInstruction(subchildren[childIndex], target, depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopProperties(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  for (const key in target) {
    evaluator.propertyParent = target;
    evaluator.propertyKey = key;
    if (evaluator.callbackMode) evaluator.pushInstanceToken(key);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[key], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  evaluator.propertyParent = undefined;
  evaluator.propertyKey = undefined;
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesEvaluate(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  for (const key in target) {
    evaluator.propertyParent = target;
    evaluator.propertyKey = key;
    if (evaluator.callbackMode) evaluator.pushInstanceToken(key);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[key], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  evaluator.propertyParent = undefined;
  evaluator.propertyKey = undefined;
  if (evaluator.trackMode) evaluator.markEvaluated(target);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesRegex(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const regex = instruction[5];
  const children = instruction[6];
  for (const key in target) {
    regex.lastIndex = 0;
    if (!regex.test(key)) continue;
    evaluator.propertyParent = target;
    evaluator.propertyKey = key;
    if (evaluator.callbackMode) evaluator.pushInstanceToken(key);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[key], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  evaluator.propertyParent = undefined;
  evaluator.propertyKey = undefined;
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesRegexClosed(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const regex = instruction[5];
  const children = instruction[6];
  for (const key in target) {
    regex.lastIndex = 0;
    if (!regex.test(key)) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
    evaluator.propertyParent = target;
    evaluator.propertyKey = key;
    if (evaluator.callbackMode) evaluator.pushInstanceToken(key);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[key], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  evaluator.propertyParent = undefined;
  evaluator.propertyKey = undefined;
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesStartsWith(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const prefix = instruction[5];
  const children = instruction[6];
  for (const key in target) {
    if (!key.startsWith(prefix)) continue;
    evaluator.propertyParent = target;
    evaluator.propertyKey = key;
    if (evaluator.callbackMode) evaluator.pushInstanceToken(key);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[key], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  evaluator.propertyParent = undefined;
  evaluator.propertyKey = undefined;
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesExcept(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const filter = instruction[5];
  const filterStrings = filter[0];
  const filterPrefixes = filter[1];
  const filterRegexes = filter[2];
  const children = instruction[6];
  for (const key in target) {
    if (filterStrings.has(key)) continue;
    let matched = false;
    for (let index = 0; index < filterPrefixes.length; index++) {
      if (key.startsWith(filterPrefixes[index])) { matched = true; break; }
    }
    if (matched) continue;
    for (let index = 0; index < filterRegexes.length; index++) {
      filterRegexes[index].lastIndex = 0;
      if (filterRegexes[index].test(key)) { matched = true; break; }
    }
    if (matched) continue;
    evaluator.propertyParent = target;
    evaluator.propertyKey = key;
    if (evaluator.callbackMode) evaluator.pushInstanceToken(key);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[key], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  evaluator.propertyParent = undefined;
  evaluator.propertyKey = undefined;
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesType(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const expected = instruction[5];
  for (const key in target) {
    const actual = jsonTypeOf(target[key]);
    if (actual !== expected && !(expected === Type.Integer && isIntegral(target[key]))) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesTypeEvaluate(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const expected = instruction[5];
  for (const key in target) {
    const actual = jsonTypeOf(target[key]);
    if (actual !== expected && !(expected === Type.Integer && isIntegral(target[key]))) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.trackMode) evaluator.markEvaluated(target);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesExactlyTypeStrict(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const value = instruction[5];
  let count = 0;
  for (const key in target) {
    count++;
    if (effectiveTypeStrictReal(target[key]) !== value[0]) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  const __result = count === value[1].length;
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, __result);
  return __result;
};

function LoopPropertiesExactlyTypeStrictHash(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const value = instruction[5];
  const entries = value[1][0];
  const expectedCount = entries.length;
  let count = 0;
  for (const key in target) {
    count++;
    if (effectiveTypeStrictReal(target[key]) !== value[0]) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (count !== expectedCount) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  for (let index = 0; index < expectedCount; index++) {
    if (!Object.hasOwn(target, entries[index][1])) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesTypeStrict(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const expected = instruction[5];
  for (const key in target) {
    if (effectiveTypeStrictReal(target[key]) !== expected) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesTypeStrictEvaluate(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const expected = instruction[5];
  for (const key in target) {
    if (effectiveTypeStrictReal(target[key]) !== expected) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.trackMode) evaluator.markEvaluated(target);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesTypeStrictAny(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const bitmask = instruction[5];
  for (const key in target) {
    if (!typeSetTest(bitmask, effectiveTypeStrictReal(target[key]))) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopPropertiesTypeStrictAnyEvaluate(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const bitmask = instruction[5];
  for (const key in target) {
    if (!typeSetTest(bitmask, effectiveTypeStrictReal(target[key]))) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.trackMode) evaluator.markEvaluated(target);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopKeys(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  for (const key in target) {
    if (evaluator.callbackMode) evaluator.pushInstanceToken(key);
    const previousPropertyTarget = evaluator.propertyTarget;
    evaluator.propertyTarget = key;
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], null, depth + 1, template, evaluator)) {
          evaluator.propertyTarget = previousPropertyTarget;
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    evaluator.propertyTarget = previousPropertyTarget;
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopItems(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  for (let index = 0; index < target.length; index++) {
    if (evaluator.callbackMode) evaluator.pushInstanceToken(index);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[index], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopItemsFrom(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  const startIndex = instruction[5];
  if (!Array.isArray(target) || startIndex >= target.length) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const children = instruction[6];
  for (let index = startIndex; index < target.length; index++) {
    if (evaluator.callbackMode) evaluator.pushInstanceToken(index);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[index], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopItemsUnevaluated(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  if (evaluator.trackMode && evaluator.isEvaluated(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  const children = instruction[6];
  for (let index = 0; index < target.length; index++) {
    if (evaluator.trackMode && evaluator.isEvaluated(target[index], target, index)) continue;
    if (evaluator.callbackMode) evaluator.pushInstanceToken(index);
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[index], depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.popInstanceToken();
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
  }
  if (evaluator.trackMode) evaluator.markEvaluated(target);
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopItemsType(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const expected = instruction[5];
  for (let index = 0; index < target.length; index++) {
    const actual = jsonTypeOf(target[index]);
    if (actual !== expected && !(expected === Type.Integer && isIntegral(target[index]))) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopItemsTypeStrict(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const expected = instruction[5];
  for (let index = 0; index < target.length; index++) {
    if (effectiveTypeStrictReal(target[index]) !== expected) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopItemsTypeStrictAny(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const bitmask = instruction[5];
  for (let index = 0; index < target.length; index++) {
    if (!typeSetTest(bitmask, effectiveTypeStrictReal(target[index]))) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

function LoopItemsPropertiesExactlyTypeStrictHash(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }
  const expectedType = instruction[5][0];
  const entries = instruction[5][1][0];
  const expectedCount = entries.length;
  for (let index = 0; index < target.length; index++) {
    const item = target[index];
    if (!isObject(item)) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
    let count = 0;
    for (const key in item) {
      count++;
      if (effectiveTypeStrictReal(item[key]) !== expectedType) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
        return false;
      }
    }
    if (count !== expectedCount) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
    for (let entry = 0; entry < expectedCount; entry++) {
      if (!Object.hasOwn(item, entries[entry][1])) {
        if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
        return false;
      }
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};
function LoopContains(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!Array.isArray(target)) return true;
  const range = instruction[5];
  const minimum = range[0];
  const maximum = range[1];
  const isExhaustive = range[2];
  if (minimum === 0 && target.length === 0) return true;
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);

  const children = instruction[6];
  let result = false;
  let matchCount = 0;
  for (let index = 0; index < target.length; index++) {
    if (evaluator.callbackMode) evaluator.pushInstanceToken(index);
    let subresult = true;
    if (children) {
      for (let childIndex = 0; childIndex < children.length; childIndex++) {
        if (!evaluateInstruction(children[childIndex], target[index], depth + 1, template, evaluator)) {
          subresult = false;
          break;
        }
      }
    }
    if (evaluator.callbackMode) evaluator.popInstanceToken();
    if (subresult) {
      matchCount++;
      if (maximum !== null && matchCount > maximum) {
        result = false;
        break;
      }
      if (matchCount >= minimum) {
        result = true;
        if (maximum === null && !isExhaustive) break;
      }
    }
  }

  if (evaluator.callbackMode) evaluator.callbackPop(instruction, result);
  return result;
};

function ControlGroup(instruction, instance, depth, template, evaluator) {
  const children = instruction[6];
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (!evaluateInstruction(children[index], instance, depth + 1, template, evaluator)) return false;
    }
  }
  return true;
};

function ControlGroupWhenDefines(instruction, instance, depth, template, evaluator) {
  const target = resolveInstance(instance, instruction[2]);
  if (!isObject(target)) return true;
  if (!Object.hasOwn(target, instruction[5])) return true;
  const children = instruction[6];
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (!evaluateInstruction(children[index], instance, depth + 1, template, evaluator)) return false;
    }
  }
  return true;
};

function ControlGroupWhenDefinesDirect(instruction, instance, depth, template, evaluator) {
  if (!isObject(instance)) return true;
  if (!Object.hasOwn(instance, instruction[5])) return true;
  const children = instruction[6];
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (!evaluateInstruction(children[index], instance, depth + 1, template, evaluator)) return false;
    }
  }
  return true;
};

function ControlGroupWhenType(instruction, instance, depth, template, evaluator) {
  if (jsonTypeOf(instance) !== instruction[5]) return true;
  const children = instruction[6];
  if (children) {
    for (let index = 0; index < children.length; index++) {
      if (!evaluateInstruction(children[index], instance, depth + 1, template, evaluator)) return false;
    }
  }
  return true;
};

function ControlEvaluate(instruction, instance, depth, template, evaluator) {
  if (evaluator.trackMode) {
    const target = resolveInstance(instance, instruction[5]);
    evaluator.markEvaluated(target, evaluator.propertyParent, evaluator.propertyKey);
  }
  return true;
};

function ControlDynamicAnchorJump(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const resolved = resolveInstance(instance, instruction[2]);
  const anchor = instruction[5];

  if (!evaluator.resources) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
    return false;
  }

  const anchors = template[5];
  for (let index = 0; index < evaluator.resources.length; index++) {
    const jumpTarget = anchors.get(evaluator.resources[index] + ':' + anchor);
    if (jumpTarget !== undefined) {
      for (let childIndex = 0; childIndex < jumpTarget.length; childIndex++) {
        if (!evaluateInstruction(jumpTarget[childIndex], resolved, depth + 1, template, evaluator)) {
          if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
          return false;
        }
      }
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
      return true;
    }
  }

  if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
  return false;
};

function ControlJump(instruction, instance, depth, template, evaluator) {
  if (evaluator.callbackMode) evaluator.callbackPush(instruction);
  const jumpTarget = instruction[5];
  if (!jumpTarget) {
    if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
    return true;
  }
  const resolved = resolveInstance(instance, instruction[2]);
  for (let index = 0; index < jumpTarget.length; index++) {
    if (!evaluateInstruction(jumpTarget[index], resolved, depth + 1, template, evaluator)) {
      if (evaluator.callbackMode) evaluator.callbackPop(instruction, false);
      return false;
    }
  }
  if (evaluator.callbackMode) evaluator.callbackPop(instruction, true);
  return true;
};

const handlers = [
  AssertionFail,                              // 0
  AssertionDefines,                           // 1
  AssertionDefinesStrict,                     // 2
  AssertionDefinesAll,                        // 3
  AssertionDefinesAllStrict,                  // 4
  AssertionDefinesExactly,                    // 5
  AssertionDefinesExactlyStrict,              // 6
  AssertionDefinesExactlyStrictHash3,         // 7
  AssertionPropertyDependencies,              // 8
  AssertionType,                              // 9
  AssertionTypeAny,                           // 10
  AssertionTypeStrict,                        // 11
  AssertionTypeStrictAny,                     // 12
  AssertionTypeStringBounded,                 // 13
  AssertionTypeStringUpper,                   // 14
  AssertionTypeArrayBounded,                  // 15
  AssertionTypeArrayUpper,                    // 16
  AssertionTypeObjectBounded,                 // 17
  AssertionTypeObjectUpper,                   // 18
  AssertionRegex,                             // 19
  AssertionStringSizeLess,                    // 20
  AssertionStringSizeGreater,                 // 21
  AssertionArraySizeLess,                     // 22
  AssertionArraySizeGreater,                  // 23
  AssertionObjectSizeLess,                    // 24
  AssertionObjectSizeGreater,                 // 25
  AssertionEqual,                             // 26
  AssertionEqualsAny,                         // 27
  AssertionEqualsAnyStringHash,               // 28
  AssertionGreaterEqual,                      // 29
  AssertionLessEqual,                         // 30
  AssertionGreater,                           // 31
  AssertionLess,                              // 32
  AssertionUnique,                            // 33
  AssertionDivisible,                         // 34
  AssertionStringType,                        // 35
  AssertionPropertyType,                      // 36
  AssertionPropertyTypeEvaluate,              // 37
  AssertionPropertyTypeStrict,                // 38
  AssertionPropertyTypeStrictEvaluate,        // 39
  AssertionPropertyTypeStrictAny,             // 40
  AssertionPropertyTypeStrictAnyEvaluate,     // 41
  AssertionArrayPrefix,                       // 42
  AssertionArrayPrefixEvaluate,               // 43
  AnnotationEmit,                             // 44
  AnnotationToParent,                         // 45
  AnnotationBasenameToParent,                 // 46
  Evaluate,                                   // 47
  LogicalNot,                                 // 48
  LogicalNotEvaluate,                         // 49
  LogicalOr,                                  // 50
  LogicalAnd,                                 // 51
  LogicalXor,                                 // 52
  LogicalCondition,                           // 53
  LogicalWhenType,                            // 54
  LogicalWhenDefines,                         // 55
  LogicalWhenArraySizeGreater,                // 56
  LoopPropertiesUnevaluated,                  // 57
  LoopPropertiesUnevaluatedExcept,            // 58
  LoopPropertiesMatch,                        // 59
  LoopPropertiesMatchClosed,                  // 60
  LoopProperties,                             // 61
  LoopPropertiesEvaluate,                     // 62
  LoopPropertiesRegex,                        // 63
  LoopPropertiesRegexClosed,                  // 64
  LoopPropertiesStartsWith,                   // 65
  LoopPropertiesExcept,                       // 66
  LoopPropertiesType,                         // 67
  LoopPropertiesTypeEvaluate,                 // 68
  LoopPropertiesExactlyTypeStrict,            // 69
  LoopPropertiesExactlyTypeStrictHash,        // 70
  LoopPropertiesTypeStrict,                   // 71
  LoopPropertiesTypeStrictEvaluate,           // 72
  LoopPropertiesTypeStrictAny,                // 73
  LoopPropertiesTypeStrictAnyEvaluate,        // 74
  LoopKeys,                                   // 75
  LoopItems,                                  // 76
  LoopItemsFrom,                              // 77
  LoopItemsUnevaluated,                       // 78
  LoopItemsType,                              // 79
  LoopItemsTypeStrict,                        // 80
  LoopItemsTypeStrictAny,                     // 81
  LoopItemsPropertiesExactlyTypeStrictHash,   // 82
  LoopItemsPropertiesExactlyTypeStrictHash,   // 83
  LoopContains,                               // 84
  ControlGroup,                               // 85
  ControlGroupWhenDefines,                    // 86
  ControlGroupWhenDefinesDirect,              // 87
  ControlGroupWhenType,                       // 88
  ControlEvaluate,                            // 89
  ControlDynamicAnchorJump,                   // 90
  ControlJump                                 // 91
];

export { Blaze };
