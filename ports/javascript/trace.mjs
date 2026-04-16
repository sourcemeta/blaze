import { describe, it } from 'node:test';
import assert from 'node:assert/strict';
import { isDeepStrictEqual } from 'node:util';
import { readFileSync, readdirSync } from 'node:fs';
import { join, dirname, basename } from 'node:path';
import { fileURLToPath } from 'node:url';
import { Blaze } from './index.mjs';
const reviver = Blaze.reviver;
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
  "AssertionTypeIntegerBounded": 35,
  "AssertionTypeIntegerBoundedStrict": 36,
  "AssertionTypeIntegerLowerBound": 37,
  "AssertionTypeIntegerLowerBoundStrict": 38,
  "AssertionStringType": 39,
  "AssertionPropertyType": 40,
  "AssertionPropertyTypeEvaluate": 41,
  "AssertionPropertyTypeStrict": 42,
  "AssertionPropertyTypeStrictEvaluate": 43,
  "AssertionPropertyTypeStrictAny": 44,
  "AssertionPropertyTypeStrictAnyEvaluate": 45,
  "AssertionArrayPrefix": 46,
  "AssertionArrayPrefixEvaluate": 47,
  "AssertionObjectPropertiesSimple": 48,
  "AnnotationEmit": 49,
  "AnnotationToParent": 50,
  "AnnotationBasenameToParent": 51,
  "Evaluate": 52,
  "LogicalNot": 53,
  "LogicalNotEvaluate": 54,
  "LogicalOr": 55,
  "LogicalAnd": 56,
  "LogicalXor": 57,
  "LogicalCondition": 58,
  "LogicalWhenType": 59,
  "LogicalWhenDefines": 60,
  "LogicalWhenArraySizeGreater": 61,
  "LoopPropertiesUnevaluated": 62,
  "LoopPropertiesUnevaluatedExcept": 63,
  "LoopPropertiesMatch": 64,
  "LoopPropertiesMatchClosed": 65,
  "LoopProperties": 66,
  "LoopPropertiesEvaluate": 67,
  "LoopPropertiesRegex": 68,
  "LoopPropertiesRegexClosed": 69,
  "LoopPropertiesStartsWith": 70,
  "LoopPropertiesExcept": 71,
  "LoopPropertiesType": 72,
  "LoopPropertiesTypeEvaluate": 73,
  "LoopPropertiesExactlyTypeStrict": 74,
  "LoopPropertiesExactlyTypeStrictHash": 75,
  "LoopPropertiesTypeStrict": 76,
  "LoopPropertiesTypeStrictEvaluate": 77,
  "LoopPropertiesTypeStrictAny": 78,
  "LoopPropertiesTypeStrictAnyEvaluate": 79,
  "LoopKeys": 80,
  "LoopItems": 81,
  "LoopItemsFrom": 82,
  "LoopItemsUnevaluated": 83,
  "LoopItemsType": 84,
  "LoopItemsTypeStrict": 85,
  "LoopItemsTypeStrictAny": 86,
  "LoopItemsPropertiesExactlyTypeStrictHash": 87,
  "LoopItemsPropertiesExactlyTypeStrictHash3": 88,
  "LoopItemsIntegerBounded": 89,
  "LoopItemsIntegerBoundedSized": 90,
  "LoopItemsObjectProperties": 91,
  "LoopContains": 92,
  "ControlGroup": 93,
  "ControlGroupWhenDefines": 94,
  "ControlGroupWhenDefinesDirect": 95,
  "ControlGroupWhenType": 96,
  "ControlEvaluate": 97,
  "ControlDynamicAnchorJump": 98,
  "ControlJump": 99,
  "Annotation": -1
};

const ANNOTATION_OPCODES = new Set([49, 50, 51]);

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
  const tests = JSON.parse(readFileSync(filePath, 'utf8'), reviver);
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
