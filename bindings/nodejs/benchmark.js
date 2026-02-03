import Benchmark from 'benchmark';
import { readFileSync, readdirSync, statSync, existsSync } from 'fs';
import { join, dirname } from 'path';
import { fileURLToPath } from 'url';
import { compileSchema, evaluateSchema, BlazeJSON } from '@sourcemeta/blaze';
import { Ajv2020 } from 'ajv/dist/2020.js';
import { Ajv2019 } from 'ajv/dist/2019.js';
import Ajv from 'ajv';

const __dirname = dirname(fileURLToPath(import.meta.url));
const E2E_DIR = join(__dirname, '../../benchmark/e2e');

const BENCHMARKS = readdirSync(E2E_DIR)
  .filter(entry => {
    const entryPath = join(E2E_DIR, entry);
    return statSync(entryPath).isDirectory() &&
      existsSync(join(entryPath, 'schema.json')) &&
      existsSync(join(entryPath, 'instances.jsonl'));
  })
  .sort();

function formatName(name) {
  return name.replace(/-/g, '_');
}

const filterArg = process.argv[2];
const benchmarksToRun = filterArg
  ? BENCHMARKS.filter(name =>
    name.includes(filterArg) || formatName(name).includes(filterArg))
  : BENCHMARKS;
if (benchmarksToRun.length === 0) {
  console.error(`No benchmarks match filter: ${filterArg}`);
  process.exit(1);
}

const suite = new Benchmark.Suite();

for (const name of benchmarksToRun) {
  const schemaText = readFileSync(join(E2E_DIR, name, 'schema.json'), 'utf8');
  const instancesText = readFileSync(join(E2E_DIR, name, 'instances.jsonl'), 'utf8');

  const compiledSchema = compileSchema(BlazeJSON.parse(schemaText), { mode: 'fast' });
  const blazeInstances = instancesText.trim().split('\n').map(line => BlazeJSON.parse(line));
  suite.add(`E2E_Evaluator_${formatName(name)}`, () => {
    for (const instance of blazeInstances) {
      const result = evaluateSchema(compiledSchema, instance);
      if (!result.valid) {
        throw new Error(`Validation failed for ${name}`);
      }
    }
  });

  if (name != "krakend" && name != "ui5-manifest") {
    console.log(`Trying ${name}`);
    const AJV_DRAFTS = {
      "https://json-schema.org/draft/2020-12/schema": Ajv2020,
      "https://json-schema.org/draft/2020-12/schema#": Ajv2020,
      "https://json-schema.org/draft/2019-09/schema": Ajv2019,
      "https://json-schema.org/draft/2019-09/schema#": Ajv2019,
      "http://json-schema.org/draft-07/schema": Ajv,
      "http://json-schema.org/draft-07/schema#": Ajv
    };

    const schema = JSON.parse(schemaText);
    const AjvClass = AJV_DRAFTS[schema['$schema']];
    const ajv = new AjvClass({ strict: false });
    const validate = ajv.compile(schema);
    const ajvInstances = instancesText.trim().split('\n').map(line => JSON.parse(line));
    suite.add(`E2E_Evaluator_${formatName(name)}_ajv`, () => {
      for (const instance of ajvInstances) {
        if (!validate(instance)) {
          throw new Error(`Validation failed for ${name}`);
        }
      }
    });
  }
}

suite
  .on('cycle', (event) => {
    console.log(String(event.target));
  })
  .run();
