import { describe, it } from 'node:test';
import assert from 'node:assert/strict';
import { isDeepStrictEqual } from 'node:util';
import { readFileSync, readdirSync } from 'node:fs';
import { join, dirname, basename } from 'node:path';
import { fileURLToPath } from 'node:url';
import { Blaze } from './index.mjs';
import { compileSchema } from './compile.mjs';

const __dirname = dirname(fileURLToPath(import.meta.url));
const TRACE_SUITE_PATH = join(__dirname, '..', '..', 'test', 'evaluator');

const INSTRUCTION_NAMES = {
  "AssertionFail": 0,
  "AssertionDefines": 1,
  "AssertionDefinesStrict": 2,
  "AssertionDefinesAll": 3,
  "AssertionDefinesAllStrict": 4,
  "AssertionDefinesExactly": 5,
  "AssertionDefinesExactlyStrict": 6,
  "AssertionDefinesExactlyStrictHash3": 7,
  "AssertionPropertyDependencies": 8,
  "AssertionType": 9,
  "AssertionTypeAny": 10,
  "AssertionTypeStrict": 11,
  "AssertionTypeStrictAny": 12,
  "AssertionTypeStringBounded": 13,
  "AssertionTypeStringUpper": 14,
  "AssertionTypeArrayBounded": 15,
  "AssertionTypeArrayUpper": 16,
  "AssertionTypeObjectBounded": 17,
  "AssertionTypeObjectUpper": 18,
  "AssertionRegex": 19,
  "AssertionStringSizeLess": 20,
  "AssertionStringSizeGreater": 21,
  "AssertionArraySizeLess": 22,
  "AssertionArraySizeGreater": 23,
  "AssertionObjectSizeLess": 24,
  "AssertionObjectSizeGreater": 25,
  "AssertionEqual": 26,
  "AssertionEqualsAny": 27,
  "AssertionEqualsAnyStringHash": 28,
  "AssertionGreaterEqual": 29,
  "AssertionLessEqual": 30,
  "AssertionGreater": 31,
  "AssertionLess": 32,
  "AssertionUnique": 33,
  "AssertionDivisible": 34,
  "AssertionStringType": 35,
  "AssertionPropertyType": 36,
  "AssertionPropertyTypeEvaluate": 37,
  "AssertionPropertyTypeStrict": 38,
  "AssertionPropertyTypeStrictEvaluate": 39,
  "AssertionPropertyTypeStrictAny": 40,
  "AssertionPropertyTypeStrictAnyEvaluate": 41,
  "AssertionArrayPrefix": 42,
  "AssertionArrayPrefixEvaluate": 43,
  "AnnotationEmit": 44,
  "AnnotationToParent": 45,
  "AnnotationBasenameToParent": 46,
  "Evaluate": 47,
  "LogicalNot": 48,
  "LogicalNotEvaluate": 49,
  "LogicalOr": 50,
  "LogicalAnd": 51,
  "LogicalXor": 52,
  "LogicalCondition": 53,
  "LogicalWhenType": 54,
  "LogicalWhenDefines": 55,
  "LogicalWhenArraySizeGreater": 56,
  "LoopPropertiesUnevaluated": 57,
  "LoopPropertiesUnevaluatedExcept": 58,
  "LoopPropertiesMatch": 59,
  "LoopPropertiesMatchClosed": 60,
  "LoopProperties": 61,
  "LoopPropertiesEvaluate": 62,
  "LoopPropertiesRegex": 63,
  "LoopPropertiesRegexClosed": 64,
  "LoopPropertiesStartsWith": 65,
  "LoopPropertiesExcept": 66,
  "LoopPropertiesType": 67,
  "LoopPropertiesTypeEvaluate": 68,
  "LoopPropertiesExactlyTypeStrict": 69,
  "LoopPropertiesExactlyTypeStrictHash": 70,
  "LoopPropertiesTypeStrict": 71,
  "LoopPropertiesTypeStrictEvaluate": 72,
  "LoopPropertiesTypeStrictAny": 73,
  "LoopPropertiesTypeStrictAnyEvaluate": 74,
  "LoopKeys": 75,
  "LoopItems": 76,
  "LoopItemsFrom": 77,
  "LoopItemsUnevaluated": 78,
  "LoopItemsType": 79,
  "LoopItemsTypeStrict": 80,
  "LoopItemsTypeStrictAny": 81,
  "LoopItemsPropertiesExactlyTypeStrictHash": 82,
  "LoopItemsPropertiesExactlyTypeStrictHash3": 83,
  "LoopContains": 84,
  "ControlGroup": 85,
  "ControlGroupWhenDefines": 86,
  "ControlGroupWhenDefinesDirect": 87,
  "ControlGroupWhenType": 88,
  "ControlEvaluate": 89,
  "ControlDynamicAnchorJump": 90,
  "ControlJump": 91,
  "Annotation": -1
};

const ANNOTATION_OPCODES = new Set([44, 45, 46]);

function resolveInstructionType(name) {
  const opcode = INSTRUCTION_NAMES[name];
  if (opcode === undefined) throw new Error(`Unknown instruction type: ${name}`);
  return opcode;
}

const suiteFiles = readdirSync(TRACE_SUITE_PATH)
  .filter(file => file.startsWith('evaluator_') && file.endsWith('.json'))
  .sort();

for (const file of suiteFiles) {
  const suiteName = basename(file, '.json');
  const filePath = join(TRACE_SUITE_PATH, file);
  console.log(`-- Loading: ${file} (${suiteName})`);
  const tests = JSON.parse(readFileSync(filePath, 'utf8'));
  console.log(`   ${tests.length} test entries`);

  describe(suiteName, () => {
    for (let testIndex = 0; testIndex < tests.length; testIndex++) {
      const testCase = tests[testIndex];

      for (const mode of ['fast', 'exhaustive']) {
        if (!testCase[mode]) continue;
        const modeData = testCase[mode];
        const testName = `${testCase.description}_${mode}`;

        it(testName, () => {
          const template = compileSchema(filePath, {
            mode,
            path: `/${testIndex}/schema`
          });

          const evaluator = new Blaze(template);
          const tracePre = [];
          const tracePost = [];

          const result = evaluator.validate(testCase.instance, (type, valid, instruction, evaluatePath, instanceLocation, annotation) => {
            if (type === 'pre') {
              tracePre.push({ opcode: instruction[0], evaluatePath, keywordLocation: instruction[3], instanceLocation });
            } else {
              tracePost.push({ valid, opcode: instruction[0], evaluatePath, keywordLocation: instruction[3], instanceLocation, annotation });
            }
          });

          assert.equal(result, testCase.valid, `Validation result mismatch`);

          const expectedPre = modeData.pre || [];
          const expectedPost = modeData.post || [];

          assert.equal(tracePre.length, expectedPre.length,
            `Pre trace count: expected ${expectedPre.length}, got ${tracePre.length}`);
          assert.equal(tracePost.length, expectedPost.length,
            `Post trace count: expected ${expectedPost.length}, got ${tracePost.length}`);

          for (let index = 0; index < expectedPre.length; index++) {
            const expected = expectedPre[index];
            const actual = tracePre[index];
            const expectedType = resolveInstructionType(expected[0]);

            if (expectedType === -1) {
              assert.ok(ANNOTATION_OPCODES.has(actual.opcode),
                `Pre[${index}] type: expected Annotation, got opcode ${actual.opcode}`);
            } else {
              assert.equal(actual.opcode, expectedType,
                `Pre[${index}] type: expected ${expected[0]} (${expectedType}), got ${actual.opcode}`);
            }

            assert.equal(actual.evaluatePath, expected[1],
              `Pre[${index}] evaluatePath: expected "${expected[1]}", got "${actual.evaluatePath}"`);
            assert.equal(actual.keywordLocation, expected[2],
              `Pre[${index}] keywordLocation: expected "${expected[2]}", got "${actual.keywordLocation}"`);
            assert.equal(actual.instanceLocation, expected[3],
              `Pre[${index}] instanceLocation: expected "${expected[3]}", got "${actual.instanceLocation}"`);
          }

          for (let index = 0; index < expectedPost.length; index++) {
            const expected = expectedPost[index];
            const actual = tracePost[index];
            const expectedValid = expected[0];
            const expectedType = resolveInstructionType(expected[1]);

            assert.equal(actual.valid, expectedValid,
              `Post[${index}] valid: expected ${expectedValid}, got ${actual.valid}`);

            if (expectedType === -1) {
              assert.ok(ANNOTATION_OPCODES.has(actual.opcode),
                `Post[${index}] type: expected Annotation, got opcode ${actual.opcode}`);
            } else {
              assert.equal(actual.opcode, expectedType,
                `Post[${index}] type: expected ${expected[1]} (${expectedType}), got ${actual.opcode}`);
            }

            assert.equal(actual.evaluatePath, expected[2],
              `Post[${index}] evaluatePath: expected "${expected[2]}", got "${actual.evaluatePath}"`);
            assert.equal(actual.keywordLocation, expected[3],
              `Post[${index}] keywordLocation: expected "${expected[3]}", got "${actual.keywordLocation}"`);
            assert.equal(actual.instanceLocation, expected[4],
              `Post[${index}] instanceLocation: expected "${expected[4]}", got "${actual.instanceLocation}"`);

            if (expected.length > 5) {
              assert.ok(isDeepStrictEqual(actual.annotation, expected[5]),
                `Post[${index}] annotation: expected ${JSON.stringify(expected[5])}, got ${JSON.stringify(actual.annotation)}`);
            }
          }
        });
      }
    }
  });
}
