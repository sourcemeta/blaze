import test from 'node:test';
import { dirname, resolve, extname } from 'path';
import { readdir, readFile } from 'fs/promises';
import { fileURLToPath } from 'url';
import { strict as assert } from 'node:assert';
import { compile, evaluate, remove } from './jsontoolkit.js';

test('simple 2020-12 pass', async (t) => {
  const schema = await compile({
    $schema: 'https://json-schema.org/draft/2020-12/schema',
    type: 'string'
  });

  const result = await evaluate(schema, "foo");
  assert.ok(result);
  await remove(schema);
});

test('simple 2020-12 fail', async (t) => {
  const schema = await compile({
    $schema: 'https://json-schema.org/draft/2020-12/schema',
    type: 'string'
  });

  const result = await evaluate(schema, 1);
  assert.ok(!result);
  await remove(schema);
});

const JSONSCHEMA_TEST_SUITE_PATH =
  resolve(dirname(dirname(dirname(fileURLToPath(import.meta.url)))),
    'vendor', 'jsonschema-test-suite');

const DEFAULT_DIALECT = {
  draft4: 'http://json-schema.org/draft-04/schema#',
  draft6: 'http://json-schema.org/draft-06/schema#',
  draft7: 'http://json-schema.org/draft-07/schema#',
  'draft2019-09': 'https://json-schema.org/draft/2019-09/schema',
  'draft2020-12': 'https://json-schema.org/draft/2020-12/schema'
};

for (const suite of [ 'draft4', 'draft6', 'draft7', 'draft2019-09', 'draft2020-12' ]) {
  const TEST_PATH = resolve(JSONSCHEMA_TEST_SUITE_PATH, 'tests', suite);
  console.error('-- Scanning', TEST_PATH);

  // TODO: Run optionals when possible
  for (const file of await readdir(TEST_PATH)) {
    if (extname(file).toLowerCase() !== '.json') {
      continue;
    }

    // TODO: Support remotes
    if ([ 'draft4', 'draft6', 'draft7', 'draft2019-09', 'draft2020-12' ].includes(suite) && file === 'refRemote.json') {
      continue;
    } else if ([ 'draft2019-09', 'draft2020-12' ].includes(suite) && file === 'vocabulary.json') {
      continue;
    } else if ([ 'draft2020-12' ].includes(suite) && file === 'dynamicRef.json') {
      continue;
    }

    const testPath = resolve(TEST_PATH, file);
    console.error('Reading', testPath);
    for (const entry of JSON.parse(await readFile(testPath, 'utf8'))) {
      for (const unit of entry.tests) {
        test(`${suite} (${file}) ${entry.description} => ${unit.description}`, async (t) => {
          const schema = await compile(entry.schema, DEFAULT_DIALECT[suite]);
          const result = await evaluate(schema, unit.data);

          if (unit.valid) {
            assert.ok(result);
          } else {
            assert.ok(!result);
          }

          await remove(schema);
        });
      }
    }
  }
}
