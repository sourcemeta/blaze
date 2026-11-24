import { spawnSync } from 'node:child_process';
import { existsSync } from 'node:fs';
import { resolve, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';
import { Blaze } from './index.mjs';

const MODULE_DIR = dirname(fileURLToPath(import.meta.url));
const PROJECT_ROOT = resolve(MODULE_DIR, '../..');
const BINARY_NAME = 'sourcemeta_blaze_contrib_compile';

const CANDIDATES = [
  resolve(PROJECT_ROOT, 'build/contrib', BINARY_NAME),
  resolve(PROJECT_ROOT, 'build/bin/Release', BINARY_NAME + '.exe'),
  resolve(PROJECT_ROOT, 'build/bin/Debug', BINARY_NAME + '.exe')
];

const COMPILE_BIN = CANDIDATES.find(existsSync);
if (COMPILE_BIN) {
  process.stderr.write(`Found compile CLI: ${COMPILE_BIN}\n`);
} else {
  throw new Error('Could not find compile CLI. Searched:\n' + CANDIDATES.join('\n'));
}

export function compileSchema(schemaPath, options) {
  const args = [];

  if (options && options.mode === 'fast') {
    args.push('--fast');
  }

  if (options && options.defaultDialect) {
    args.push('--default-dialect', options.defaultDialect);
  }

  if (options && options.resolveDirectory) {
    args.push('--resolve-directory', options.resolveDirectory);
  }

  // The schemas a suite directory supplies for the URIs its fixtures reference
  if (options && options.resolveMap) {
    args.push('--resolve-map', options.resolveMap);
  }

  if (options && options.path) {
    args.push('--path', options.path);
  }

  // Where the schema itself starts, which is not the same question as where the
  // schema sits in the file `--path` reads it out of
  if (options && options.entrypoint) {
    args.push('--entrypoint', options.entrypoint);
  }

  // The fixtures name compiler knobs, and this port borrows the C++ compiler,
  // so they have to travel as flags rather than being applied here
  if (options && options.tweaks) {
    if (options.tweaks.formatAssertion) {
      args.push('--format-assertion');
    }

    // An allowlist that is present but empty says to emit no annotation at
    // all, which is not what leaving the option out means, so it travels as a
    // flag of its own
    const annotations = options.tweaks.annotations;
    if (annotations !== undefined) {
      if (annotations.length === 0) {
        args.push('--no-annotations');
      }

      for (const keyword of annotations) {
        args.push('--annotations', keyword);
      }
    }
  }

  args.push(schemaPath);

  const result = spawnSync(COMPILE_BIN, args, {
    encoding: 'utf-8',
    maxBuffer: 256 * 1024 * 1024
  });
  // A spawn that never ran captures no output, so reading its stderr would
  // report a type error rather than the reason it could not run, such as the
  // process limit this suite reaches when it runs beside a busy build
  if (result.error !== undefined) {
    throw new Error(`Could not run the compiler: ${result.error.message}`);
  }

  if (result.status !== 0) {
    throw new Error((result.stderr ?? '').trim() ||
      `The compiler exited with status ${result.status}`);
  }

  return JSON.parse(result.stdout, Blaze.reviver);
}
