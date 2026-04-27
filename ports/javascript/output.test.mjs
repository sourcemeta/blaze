import { describe, it } from 'node:test';
import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';
import { Blaze } from './index.mjs';
import { compileSchema } from './compile.mjs';

const __dirname = dirname(fileURLToPath(import.meta.url));
const SUITE_DIR = join(__dirname, '..', '..', 'test', 'output');

function runSuite(suiteName, fileName, format) {
  const filePath = join(SUITE_DIR, fileName);
  const tests = JSON.parse(readFileSync(filePath, 'utf8'), Blaze.reviver);
  describe(suiteName, () => {
    for (const [ index, testCase ] of tests.entries()) {
      for (const mode of [ 'fast', 'exhaustive' ]) {
        it(`${testCase.description}_${mode}`, () => {
          const template = compileSchema(filePath, {
            mode,
            path: `/${index}/schema`
          });
          const evaluator = new Blaze(template);
          const actual = evaluator.validate(testCase.instance, format);
          assert.deepStrictEqual(actual, testCase[mode]);
        });
      }
    }
  });
}

runSuite('output_standard_flag', 'output_standard_flag.json', 'flag');
runSuite('output_standard_basic', 'output_standard_basic.json', 'basic');
