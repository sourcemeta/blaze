import Benchmark from 'benchmark';
import { readFileSync, readdirSync, statSync, existsSync } from 'fs';
import { join, dirname } from 'path';
import { fileURLToPath } from 'url';
import { compileSchema, evaluateSchema, BlazeJSON } from '@sourcemeta/blaze';

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
const benchmarkData = new Map();
for (const name of benchmarksToRun) {
  benchmarkData.set(name, {
    schema:
      compileSchema(
        BlazeJSON.parse(readFileSync(join(E2E_DIR, name, 'schema.json'), 'utf8')), {
          mode: 'fast'
        }),
    instances: readFileSync(join(E2E_DIR, name, 'instances.jsonl'), 'utf8')
      .trim()
      .split('\n')
      .map(line => BlazeJSON.parse(line))
  });
}

for (const name of benchmarksToRun) {
  const { schema, instances } = benchmarkData.get(name);
  suite.add(`E2E_Evaluator_${formatName(name)}`, () => {
    for (const instance of instances) {
      const result = evaluateSchema(schema, instance);
      if (!result.valid) {
        throw new Error(`Validation failed for ${name}`);
      }
    }
  });
}

suite
  .on('cycle', (event) => {
    console.log(String(event.target));
  })
  .run();
