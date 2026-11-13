import { describe, it } from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync, readdirSync, mkdirSync, mkdtempSync, writeFileSync, rmSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join, resolve, dirname, basename } from 'node:path';
import { fileURLToPath } from 'node:url';
import { compileSchema } from './compile.mjs';
import { Blaze } from './index.mjs';

const MODULE_DIR = dirname(fileURLToPath(import.meta.url));
const PROJECT_ROOT = resolve(MODULE_DIR, '../..');
const SUITE_PATH = join(PROJECT_ROOT, 'vendor/jsonschema-test-suite/validation/tests');

// Every schema a test case refers to is declared by the case itself, and all
// of them live under this one authority, so a single resolve directory does
const EXTERNAL_SCHEMA_PREFIX = 'http://localhost:1234/';

// The port has no format opcodes at all, so it cannot run a case that asks for
// format assertions. Upstream asks implementations to run a case only if they
// provide the behaviour that every one of its tags stands for
const SUPPORTED_TAGS = new Set(['format-annotation']);

const GROUPS = ['', 'optional'];

const DIALECTS = [
  { name: 'draft2020-12', uri: 'https://json-schema.org/draft/2020-12/schema', version: 2020 },
  { name: 'draft2019-09', uri: 'https://json-schema.org/draft/2019-09/schema', version: 2019 },
  { name: 'draft7', uri: 'http://json-schema.org/draft-07/schema#', version: 7 },
  { name: 'draft6', uri: 'http://json-schema.org/draft-06/schema#', version: 6 },
  { name: 'draft4', uri: 'http://json-schema.org/draft-04/schema#', version: 4 },
  { name: 'draft3', uri: 'http://json-schema.org/draft-03/schema#', version: 3 }
];

// The port cannot represent a decimal literal that no double can hold:
// `sourceToBigInt` returns null for a non-integral high-precision literal, so
// the value silently stays a lossy double. The C++ evaluator has no such gap,
// as core carries a decimal type of its own
// TODO: Represent high-precision decimals in the port
const HIGH_PRECISION_SKIPS = [
  'optional/bignum::const comparison with high precision::a slightly smaller decimal is invalid',
  'optional/bignum::const comparison with high precision::a slightly larger decimal is invalid',
  'optional/bignum::enum comparison with high precision::a slightly smaller decimal is invalid',
  'optional/bignum::enum comparison with high precision::a slightly larger decimal is invalid',
  'optional/bignum::float comparison with high precision::below the exclusive maximum is valid',
  'optional/bignum::float comparison with high precision (boolean)::below the exclusive maximum is valid',
  'optional/bignum::float comparison with high precision on negative numbers::above the exclusive minimum is valid',
  'optional/bignum::float comparison with high precision on negative numbers (boolean)::above the exclusive minimum is valid',
  'optional/bignum::uniqueItems comparison with high precision::distinct high-precision decimals are unique',
  'optional/bignum::uniqueItems comparison with high precision::arrays containing distinct decimals are unique',
  'optional/bignum::uniqueItems comparison with high precision::objects containing distinct decimals are unique',
  'optional/zero-terminated-floats::some languages do not distinguish between different types of numeric value::a float is not an integer even without fractional part'
];

// The compiler refuses to reference what the dialect in use does not consider
// a subschema
// TODO: Can we make this work?
const NON_SCHEMAS_SKIPS = [
  'optional/non-schemas::reference of a root arbitrary keyword',
  'optional/non-schemas::reference of a root arbitrary keyword with encoded ref',
  'optional/non-schemas::reference of an arbitrary keyword of a sub-schema',
  'optional/non-schemas::reference of an arbitrary keyword of a sub-schema with encoded ref',
  'optional/non-schemas::reference internals of known non-applicator'
];

// Draft 7 defines the content keywords as assertions rather than as the
// annotations that later dialects make of them
// TODO: Assert `contentEncoding` and `contentMediaType` on Draft 7
const CONTENT_SKIPS = [
  'optional/content::validation of string-encoded content based on media type::an invalid JSON document',
  'optional/content::validation of binary string-encoding::an invalid base64 string (% is not a valid character)',
  'optional/content::validation of binary-encoded media type documents::a validly-encoded invalid JSON document',
  'optional/content::validation of binary-encoded media type documents::an invalid base64 string that is valid JSON'
];

// TODO: Support bundling a Draft 7 schema whose top-level `$ref` sits next to
// other keywords
const CROSS_DRAFT_SKIPS = [
  'optional/cross-draft::refs to future drafts are processed as future drafts (2020)'
];

// These cases carry no tag of their own, yet they need real format assertions
// through a custom `$vocabulary` meta-schema. The whole file goes rather than
// the two tests that fail, because the others would pass only as a side effect
// of every format assertion evaluating as false
const FORMAT_ASSERTION_SKIPS = ['optional/format-assertion'];

// Keyed by the path of the test file relative to the suite directory,
// optionally followed by `::` and a case description, optionally followed by
// `::` and a test description
const SKIPS = {
  2020: new Set([...HIGH_PRECISION_SKIPS, ...NON_SCHEMAS_SKIPS, ...FORMAT_ASSERTION_SKIPS]),
  2019: new Set([...HIGH_PRECISION_SKIPS, ...NON_SCHEMAS_SKIPS]),
  7: new Set([...HIGH_PRECISION_SKIPS, ...CONTENT_SKIPS, ...CROSS_DRAFT_SKIPS]),
  6: new Set(HIGH_PRECISION_SKIPS),
  4: new Set(HIGH_PRECISION_SKIPS),
  3: new Set(HIGH_PRECISION_SKIPS)
};

// Whether a test case that declares the given `compatibility` applies to the
// release under test, as documented in
// vendor/jsonschema-test-suite/validation/README.md
function isCompatible(compatibility, version) {
  let result = true;
  let previous = 0;

  for (const constraint of compatibility.split(',')) {
    const match = /^(<=|=)?(\d+)$/.exec(constraint);
    if (match === null) {
      throw new Error(`Unsupported compatibility constraint: ${constraint}`);
    }

    const operator = match[1] ?? '';
    const target = Number(match[2]);
    if (target < previous) {
      throw new Error(`Unordered compatibility constraints: ${compatibility}`);
    }
    previous = target;

    if (operator === '<=') {
      result = version <= target;
    } else if (operator === '=') {
      result = version === target;
    } else {
      result = version >= target;
    }

    // The algorithm relies on the suite's requirement that constraints come
    // ordered from the smallest release to the largest one, as it stops at the
    // first constraint that covers the release under test
    if (version <= target) break;
  }

  return result;
}

function suiteFiles(group) {
  const directory = group ? join(SUITE_PATH, group) : SUITE_PATH;
  return readdirSync(directory, { withFileTypes: true })
    .filter(entry => entry.isFile() && entry.name.endsWith('.json'))
    .map(entry => entry.name)
    .sort()
    .map(name => ({
      name: basename(name, '.json'),
      relativePath: group ? `${group}/${basename(name, '.json')}` : basename(name, '.json'),
      filePath: join(directory, name)
    }));
}

function supportedTags(testCase) {
  if (testCase.tags === undefined) return true;
  return testCase.tags.every(tag => SUPPORTED_TAGS.has(tag));
}

// The compile CLI resolves a reference by looking for a file named after the
// rest of the URI, so each schema goes to its own path under a throwaway
// directory
function writeExternalSchemas(externalSchemas) {
  const directory = mkdtempSync(join(tmpdir(), 'blaze-official-suite-'));

  // The caller only learns about the directory once this returns, so whatever
  // goes wrong before that has to be cleaned up here
  try {
    for (const [identifier, schema] of Object.entries(externalSchemas)) {
      if (!identifier.startsWith(EXTERNAL_SCHEMA_PREFIX)) {
        throw new Error(`Unsupported external schema identifier: ${identifier}`);
      }

      const target = join(directory, identifier.slice(EXTERNAL_SCHEMA_PREFIX.length));
      mkdirSync(dirname(target), { recursive: true });
      writeFileSync(target, JSON.stringify(schema));
    }
  } catch (error) {
    rmSync(directory, { recursive: true, force: true });
    throw error;
  }

  return directory;
}

function registerTests(dialect, group, registered) {
  const skips = SKIPS[dialect.version];

  for (const file of suiteFiles(group)) {
    if (skips.has(file.relativePath)) continue;

    console.error(`Loading ${dialect.name}/${file.relativePath}`);
    const contents = readFileSync(file.filePath, 'utf-8');
    const suite = JSON.parse(contents, Blaze.reviver);
    // `JSON.stringify` throws on the big integers that the reviver produces,
    // so the external schemas come from a copy parsed without it
    const plainSuite = JSON.parse(contents);

    describe(`${dialect.name}/${file.relativePath}`, () => {
      for (let caseIndex = 0; caseIndex < suite.tests.length; caseIndex++) {
        const testCase = suite.tests[caseIndex];
        const caseKey = `${file.relativePath}::${testCase.description}`;
        if (skips.has(caseKey)) continue;

        if (testCase.compatibility !== undefined &&
            !isCompatible(testCase.compatibility, dialect.version)) {
          continue;
        }

        if (!supportedTags(testCase)) continue;

        const externalSchemas = plainSuite.tests[caseIndex].externalSchemas;
        const directory = externalSchemas === undefined
          ? null
          : writeExternalSchemas(externalSchemas);

        registered.count += 1;

        try {
          for (const mode of ['fast', 'exhaustive']) {
            let evaluator;
            try {
              evaluator = new Blaze(compileSchema(file.filePath, {
                mode,
                defaultDialect: dialect.uri,
                resolveDirectory: directory === null
                  ? undefined
                  : `${EXTERNAL_SCHEMA_PREFIX},${directory}`,
                path: `/tests/${caseIndex}/schema`
              }));
            } catch (error) {
              it(`[${mode}] ${testCase.description} (compile error)`, () => {
                assert.fail(`Compilation failed: ${error.message}`);
              });
              continue;
            }

            for (const test of testCase.tests) {
              if (skips.has(`${caseKey}::${test.description}`)) continue;

              it(`[${mode}] ${testCase.description} - ${test.description}`, () => {
                const result = evaluator.validate(test.data);
                assert.equal(result, test.valid,
                  `Expected ${test.valid} but got ${result}`);
              });
            }
          }
        } finally {
          if (directory !== null) {
            rmSync(directory, { recursive: true, force: true });
          }
        }
      }
    });
  }
}

const REGISTERED = new Map();

for (const dialect of DIALECTS) {
  const registered = { count: 0 };
  for (const group of GROUPS) {
    registerTests(dialect, group, registered);
  }
  REGISTERED.set(dialect.name, registered.count);
}

describe('coverage', () => {
  for (const dialect of DIALECTS) {
    it(`registers test cases for ${dialect.name}`, () => {
      assert.ok(REGISTERED.get(dialect.name) > 0,
        `No test cases were registered for ${dialect.name}`);
    });
  }
});

describe('reviver', () => {
  it('does not crash when the third argument is undefined', () => {
    assert.doesNotThrow(() => {
      Blaze.reviver('key', 42, undefined);
    });
  });

  it('returns the value unchanged when context is missing', () => {
    assert.equal(Blaze.reviver('key', 42, undefined), 42);
  });

  it('handles uppercase E in exponential notation', () => {
    const result = Blaze.reviver('key', 1e+35, { source: '9.9999999999999999999999999999999999E+34' });
    assert.equal(result, 99999999999999999999999999999999999n);
  });
});

describe('version', () => {
  it('rejects a template with an unsupported version', () => {
    const template = [15, false, false, [[]], [], [], []];
    assert.throws(() => new Blaze(template), {
      message: 'Only version 16 of the compiled template is supported by this version of the evaluator'
    });
  });

  it('rejects a template that is not an array', () => {
    assert.throws(() => new Blaze({}), {
      message: 'Only version 16 of the compiled template is supported by this version of the evaluator'
    });
  });
});
