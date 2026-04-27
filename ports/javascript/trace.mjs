import { describe, it } from 'node:test';
import assert from 'node:assert/strict';
import { isDeepStrictEqual } from 'node:util';
import { readFileSync, readdirSync } from 'node:fs';
import { join, dirname, basename } from 'node:path';
import { fileURLToPath } from 'node:url';
import { Blaze, describe as describeInstruction } from './index.mjs';
const reviver = Blaze.reviver;
import { compileSchema } from './compile.mjs';
import { INSTRUCTION_NAMES, ANNOTATION_OPCODES } from './opcodes.mjs';

const __dirname = dirname(fileURLToPath(import.meta.url));
const TRACE_SUITE_PATH = join(__dirname, '..', '..', 'test', 'evaluator');

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
              tracePost.push({ valid, opcode: instruction[0], evaluatePath, keywordLocation: instruction[3], instanceLocation, annotation, instruction });
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

          const expectedDescriptions = modeData.descriptions || [];
          assert.equal(tracePost.length, expectedDescriptions.length,
            `Description count: expected ${expectedDescriptions.length}, got ${tracePost.length}`);
          for (let index = 0; index < expectedDescriptions.length; index++) {
            const post = tracePost[index];
            const actual = describeInstruction(
              post.valid, post.instruction,
              post.evaluatePath, post.instanceLocation,
              testCase.instance, post.annotation
            );
            assert.equal(actual, expectedDescriptions[index],
              `Description[${index}]: expected ${JSON.stringify(expectedDescriptions[index])}, got ${JSON.stringify(actual)}`);
          }
        });
      }
    }
  });
}
