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
const TRACE_SUITE_PATH = join(__dirname, '..', '..', 'test', 'evaluator', 'suite');

function resolveInstructionType(name) {
  const opcode = INSTRUCTION_NAMES[name];
  if (opcode === undefined) throw new Error(`Unknown instruction type: ${name}`);
  return opcode;
}

// A dialect that cannot declare itself, because its own meta-schema spares no
// `$schema` member, has to be named from the outside. A suite that stands for
// more than one of them runs once per dialect, the way the C++ suite does
const SUITE_DEFAULT_DIALECTS = {
  evaluator_openapi_3_0: [
    ['2024_10_18', 'tag:spec.openapis.org,2024-10-18:oas/3.0/dialect'],
    ['2021_09_28', 'tag:spec.openapis.org,2021-09-28:oas/3.0/dialect']
  ]
};

// This port is a JavaScript evaluator, not a compiler: it borrows the C++
// compiler to obtain a template. The `invalid` directory of a dialect asserts
// which schemas that compiler refuses, which exercises nothing here, so only
// the `valid` one is read
// What this port cannot run, and why.
//
// A skip with no reason is indistinguishable from a bug nobody noticed, so
// every one of them carries its own. Two mechanisms, because the reasons come
// at two different scales:
//
//   - A rule, for a whole class of fixture. Naming each of these individually
//     would mean hundreds of entries that all say the same thing.
//   - A name, for the one-offs that no rule describes.
//
// Either way the suite still reports the test, as skipped rather than passed,
// so nothing quietly disappears from the count.

// TODO: this port carries no string format validators, so every fixture that
// asks the compiler to turn `format` into an assertion is skipped. Drop this
// rule once the formats land
// The verdict itself turns on how a number was written, so these cannot run
const INTEGER_IS_LEXICAL =
  'draft 3 and 4 read `integer` as a number written without a fractional part';

// Only the described wording differs
const REAL_READS_AS_INTEGER =
  'a real written with a zero fractional part is indistinguishable from an ' +
  'integer here';

// A decimal of this length is rounded the moment it is read, and the fraction
// that settles the verdict, or that the wording quotes, rounds away with it
const DECIMAL_ROUNDS_AWAY =
  'a decimal of more digits than a double holds is rounded by `JSON.parse`';

const NO_FORMAT_VALIDATORS = 'this port carries no string format validators';

function skippedByRule(testCase) {
  if (testCase.tweaks && testCase.tweaks.formatAssertion) {
    return NO_FORMAT_VALIDATORS;
  }

  return null;
}

// Keyed by `<dialect>/<fixture>`, since a fixture name repeats across dialects
const SKIPPED_FIXTURES = new Map([
  // A real this long is not recovered the way a truncated integer is: the
  // reviver reads `99999999999999999999999999999999999` back as a `BigInt`,
  // but `99999999999999999999999999999999999.1` has no such answer, so it
  // stays a double that rounded the fraction away and reads as an integer
  ['draft6/closed_integer_properties_reject_big_decimals_with_a_fraction', DECIMAL_ROUNDS_AWAY],
  ['draft6/items_integer_rejects_big_decimals_with_a_fraction', DECIMAL_ROUNDS_AWAY],
  ['draft6/prop_type_integer_rejects_a_big_decimal_with_a_fraction', DECIMAL_ROUNDS_AWAY],
  ['draft6/type_array_integer_string_rejects_a_big_decimal_with_a_fraction', DECIMAL_ROUNDS_AWAY],
  ['draft6/type_integer_rejects_a_big_decimal_with_a_fraction', DECIMAL_ROUNDS_AWAY],

  // A schema asks for the assertion itself with `x-format-assertion`,
  // rather than through the fixture's tweaks, so these are named one by
  // one. Reading the schema to find out would mistake a property called
  // `x-format-assertion` for the keyword
  ['2019_09/format_uri_x_assertion_true_invalid_no_tweak', NO_FORMAT_VALIDATORS],
  ['2019_09/format_uri_x_assertion_true_valid_no_tweak', NO_FORMAT_VALIDATORS],
  ['2020_12/format_uri_x_assertion_true_invalid_no_tweak', NO_FORMAT_VALIDATORS],
  ['2020_12/format_uri_x_assertion_true_valid_no_tweak', NO_FORMAT_VALIDATORS],
  ['2020_12/x_assertion_nested_selective_no_tweak', NO_FORMAT_VALIDATORS],
  ['2020_12/x_assertion_nested_selective_valid_no_tweak', NO_FORMAT_VALIDATORS],
  ['draft7/format_uri_x_assertion_true_invalid_no_tweak', NO_FORMAT_VALIDATORS],
  ['draft7/format_uri_x_assertion_true_valid_no_tweak', NO_FORMAT_VALIDATORS],

  // The older drafts ask whether a number was written with a fractional part,
  // which decides the verdict rather than only the wording. `JSON.parse` hands
  // back `1` for `1e0`, so the question cannot be put at all here
  ['draft3/disallow_integer_invalid_real_integer_valued', INTEGER_IS_LEXICAL],
  ['draft3/disallow_integer_valid_decimal_1e0', INTEGER_IS_LEXICAL],
  ['draft3/disallow_integer_valid_decimal_1e2', INTEGER_IS_LEXICAL],
  ['draft3/integer_type_with_integral_enum_real', INTEGER_IS_LEXICAL],
  ['draft3/type_array_integer_string_invalid_decimal_1_5e2', INTEGER_IS_LEXICAL],
  ['draft3/type_array_integer_string_invalid_decimal_1e0', INTEGER_IS_LEXICAL],
  ['draft3/type_array_integer_string_invalid_real_integer_valued', INTEGER_IS_LEXICAL],
  ['draft3/type_integer_beside_enum_rejects_an_integral_real', INTEGER_IS_LEXICAL],
  ['draft3/type_integer_invalid_decimal_1_5e1', INTEGER_IS_LEXICAL],
  ['draft3/type_integer_invalid_decimal_1_5e2', INTEGER_IS_LEXICAL],
  ['draft3/type_integer_invalid_decimal_1e0', INTEGER_IS_LEXICAL],
  ['draft3/type_integer_invalid_decimal_1e2', INTEGER_IS_LEXICAL],
  ['draft3/type_integer_invalid_decimal_30e_minus_1', INTEGER_IS_LEXICAL],
  ['draft3/type_integer_invalid_real_integer_valued', INTEGER_IS_LEXICAL],
  ['draft4/additional_properties_integer_or_string_rejects_a_big_decimal', INTEGER_IS_LEXICAL],
  ['draft4/closed_required_integer_properties_reject_a_big_decimal', INTEGER_IS_LEXICAL],
  ['draft4/enum_17', INTEGER_IS_LEXICAL],
  ['draft4/integer_type_with_integral_enum_real', INTEGER_IS_LEXICAL],
  ['draft4/items_closed_three_required_integer_properties_reject_a_big_decimal', INTEGER_IS_LEXICAL],
  ['draft4/items_closed_two_required_integer_properties_reject_a_big_decimal', INTEGER_IS_LEXICAL],
  ['draft4/items_integer_or_string_rejects_a_big_decimal_with_zero_fraction', INTEGER_IS_LEXICAL],
  ['draft4/items_integer_rejects_a_big_decimal_with_zero_fraction', INTEGER_IS_LEXICAL],
  ['draft4/prop_type_integer_bounded_strict_real_3_0_fails', INTEGER_IS_LEXICAL],
  ['draft4/prop_type_integer_lower_bound_strict_real_5_0_fails', INTEGER_IS_LEXICAL],
  ['draft4/prop_type_integer_rejects_a_big_decimal_with_zero_fraction', INTEGER_IS_LEXICAL],
  ['draft4/type_array_integer_string_invalid_decimal_1_5e2', INTEGER_IS_LEXICAL],
  ['draft4/type_array_integer_string_invalid_decimal_1e0', INTEGER_IS_LEXICAL],
  ['draft4/type_array_integer_string_invalid_real_integer_valued', INTEGER_IS_LEXICAL],
  ['draft4/type_array_integer_string_rejects_a_big_decimal_with_zero_fraction', INTEGER_IS_LEXICAL],
  ['draft4/type_integer_beside_enum_rejects_an_integral_real', INTEGER_IS_LEXICAL],
  ['draft4/type_integer_invalid_decimal_1_5e1', INTEGER_IS_LEXICAL],
  ['draft4/type_integer_invalid_decimal_1_5e2', INTEGER_IS_LEXICAL],
  ['draft4/type_integer_invalid_decimal_1e0', INTEGER_IS_LEXICAL],
  ['draft4/type_integer_invalid_decimal_1e2', INTEGER_IS_LEXICAL],
  ['draft4/type_integer_invalid_decimal_30e_minus_1', INTEGER_IS_LEXICAL],
  ['draft4/type_integer_invalid_real_integer_valued', INTEGER_IS_LEXICAL],
  ['draft4/type_integer_rejects_a_big_decimal_with_zero_fraction', INTEGER_IS_LEXICAL],
  ['draft4/typed_closed_long_named_integer_properties_reject_a_big_decimal', INTEGER_IS_LEXICAL],
  ['draft4/typed_closed_required_integer_properties_reject_a_big_decimal', INTEGER_IS_LEXICAL],
]);

// Fixtures whose describe wording this port cannot reproduce, though it agrees
// on everything else. Only the description check stands down, so the verdict
// and the trace are still held to the same expectations
const SKIPPED_DESCRIPTIONS = new Map([
  // A real written as `3.0` comes back from `JSON.parse` as `3`, and nothing
  // afterwards distinguishes it from the integer `3`, so the described value
  // reads as an integer where the C++ evaluator reads a number
  ['2020_12/prop_type_integer_bounded_6_exhaustive_annotations_none', REAL_READS_AS_INTEGER],
  ['2020_12/prop_type_integer_bounded_6_exhaustive_annotations_selected', REAL_READS_AS_INTEGER],
  ['2019_09/type_integer_beside_enum_accepts_an_integral_real', REAL_READS_AS_INTEGER],
  ['2020_12/multiple_of_real_two_bounded_1', REAL_READS_AS_INTEGER],
  ['2020_12/type_integer_beside_enum_accepts_an_integral_real', REAL_READS_AS_INTEGER],
  ['draft3/enum_real_value_equals_integer_member', REAL_READS_AS_INTEGER],
  ['draft4/items_integer_bounded_large_decimal_in_range', DECIMAL_ROUNDS_AWAY],
  ['draft4/exclusiveMaximum_8', REAL_READS_AS_INTEGER],
  ['draft4/exclusiveMinimum_8', REAL_READS_AS_INTEGER],
  ['draft4/maximum_11', REAL_READS_AS_INTEGER],
  ['draft4/maximum_12', REAL_READS_AS_INTEGER],
  ['draft4/maximum_21', REAL_READS_AS_INTEGER],
  ['draft4/minimum_12', REAL_READS_AS_INTEGER],
  ['draft4/minimum_13', REAL_READS_AS_INTEGER],
  ['draft4/minimum_22', REAL_READS_AS_INTEGER],
  ['draft4/multipleOf_11', REAL_READS_AS_INTEGER],
  ['draft4/multipleOf_12', REAL_READS_AS_INTEGER],
  ['draft4/multipleOf_21', REAL_READS_AS_INTEGER],
  ['draft4/multipleOf_5', REAL_READS_AS_INTEGER],
  ['draft6/const_8', REAL_READS_AS_INTEGER],
  ['draft6/enum_14', REAL_READS_AS_INTEGER],
  ['draft6/type_8', REAL_READS_AS_INTEGER],
  ['draft6/type_integer_beside_enum_accepts_an_integral_real', REAL_READS_AS_INTEGER],
  ['draft7/type_integer_beside_enum_accepts_an_integral_real', REAL_READS_AS_INTEGER],
  ['2020_12/multiple_of_real_one_bounded_1', REAL_READS_AS_INTEGER],
  ['2020_12/multiple_of_real_one_bounded_2', REAL_READS_AS_INTEGER],
  ['2020_12/multiple_of_real_one_bounded_3', REAL_READS_AS_INTEGER],
  ['2020_12/multiple_of_real_one_exclusive_bounded_1', REAL_READS_AS_INTEGER],
  ['2020_12/prop_type_integer_bounded_6', REAL_READS_AS_INTEGER],
  ['2020_12/prop_type_integer_lower_bound_4', REAL_READS_AS_INTEGER],
  ['2020_12/type_integer_bounded_5', REAL_READS_AS_INTEGER],
  ['2020_12/type_integer_lower_bound_3', REAL_READS_AS_INTEGER],
  ['draft6/prop_type_integer_bounded_6', REAL_READS_AS_INTEGER],
  ['draft6/prop_type_integer_lower_bound_4', REAL_READS_AS_INTEGER],
  ['draft6/type_integer_bounded_5', REAL_READS_AS_INTEGER],
  ['draft6/type_integer_lower_bound_3', REAL_READS_AS_INTEGER],
]);

function skipReason(dialect, fixtureName, testCase) {
  return SKIPPED_FIXTURES.get(`${dialect}/${fixtureName}`) ??
    skippedByRule(testCase);
}

function skipDescriptions(dialect, fixtureName) {
  return SKIPPED_DESCRIPTIONS.get(`${dialect}/${fixtureName}`) ?? null;
}

const suiteDialects = readdirSync(TRACE_SUITE_PATH, { withFileTypes: true })
  .filter(entry => entry.isDirectory())
  .map(entry => entry.name)
  .sort();

for (const dialect of suiteDialects) {
  const suiteName = `evaluator_${dialect}`;
  const directory = join(TRACE_SUITE_PATH, dialect, 'valid');
  const fixtures = readdirSync(directory)
    .filter(file => file.endsWith('.json'))
    .sort();

  // A directory that holds none is a mistake rather than an empty suite, the
  // same way the C++ suite refuses one: a fixture left in the wrong place
  // would otherwise never run, and nobody would notice
  if (fixtures.length === 0) {
    throw new Error(`No fixtures found at ${directory}`);
  }

  console.log(`-- Loading: ${dialect} (${fixtures.length} fixtures)`);

  const dialects = SUITE_DEFAULT_DIALECTS[suiteName] ?? [[null, undefined]];

  for (const [label, defaultDialect] of dialects) {
    describe(label === null ? suiteName : `${suiteName}_${label}`, () => {
      for (const fixture of fixtures) {
        const filePath = join(directory, fixture);
        const fixtureName = basename(fixture, '.json');
        const testCase = JSON.parse(readFileSync(filePath, 'utf8'), reviver);

        for (const mode of ['fast', 'exhaustive']) {
          if (!testCase[mode]) continue;
          const modeData = testCase[mode];
          const testName = `${fixtureName}_${mode}`;
          const skip = skipReason(dialect, fixtureName, testCase) ?? false;
          // The count of described steps is still checked above, so a fixture
          // standing down from the wording is not standing down from the shape

          it(testName, { skip }, (context) => {
            const template = compileSchema(filePath, {
              mode,
              path: '/schema',
              defaultDialect,
              tweaks: testCase.tweaks
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
            // Saying so in the output is the point of the reason: a check that
            // stands down without a word looks the same as one that passed
            const describeSkip = skipDescriptions(dialect, fixtureName);
            if (describeSkip) {
              context.diagnostic(`descriptions not checked: ${describeSkip}`);
            }

            for (let index = 0;
                 index < (describeSkip ? 0 : expectedDescriptions.length);
                 index++) {
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

          if (mode === 'fast') {
            it(`${testName}_callbackless`, { skip }, () => {
              const template = compileSchema(filePath, {
                mode,
                path: '/schema',
                defaultDialect,
                tweaks: testCase.tweaks
              });

              const evaluator = new Blaze(template);
              const result = evaluator.validate(testCase.instance);
              assert.equal(result, testCase.valid, `Callbackless validation result mismatch`);
            });
          }
        }
      }
    });
  }
}
