# Compile Corpus

Seed corpus for fuzzing the `contrib/compile` binary with
[AFL++](https://aflplus.plus/) or similar tools. Each file is a small,
purposeful input that exercises a specific compiler path.

This corpus is designed for fuzzing and robustness testing, not as a
formal conformance test suite.

## Categories

| Directory          | Purpose                                          |
|--------------------|--------------------------------------------------|
| `valid/`           | Correct schemas across supported dialects         |
| `invalid_json/`    | Malformed JSON rejected by the parser             |
| `invalid_schema/`  | Valid JSON that violates JSON Schema constraints  |
| `unknown_dialect/` | Schemas with unsupported `$schema` values         |
| `edge_cases/`      | Unusual but possibly valid inputs and boundaries  |
| `stress/`          | Large schemas to test performance and scale       |

## Known Issues (Discovered via Corpus)

The following inputs trigger assertion failures (SIGABRT) inside the
compiler. They are kept in the corpus intentionally to document the
crashes and to serve as regression inputs once fixed.

| File | Input | Issue |
|------|-------|-------|
| `invalid_schema/additional_properties_as_number.json` | `"additionalProperties": 42` | Asserts on non-boolean/non-schema value |
| `invalid_schema/items_as_string.json` | `"items": "invalid"` | Asserts on non-schema items value |
| `invalid_schema/max_length_negative.json` | `"maxLength": -1` | Asserts on negative string constraint |
| `invalid_schema/multiple_of_negative.json` | `"multipleOf": -5` | Asserts on negative multipleOf |
| `edge_cases/empty_keyword_values.json` | `"allOf": [], "anyOf": []` | Asserts on empty applicator arrays |

Expected: graceful error (exception + exit 1). Actual: `assert()` failure.

## Fuzzing with AFL++

```sh
afl-fuzz -i test/corpus/compile/ -o findings/ -- \
  ./build/contrib/sourcemeta_blaze_contrib_compile @@
```

## Helper Script

An optional helper script is available at `contrib/run_corpus.sh` to run
the full corpus locally and detect crashes:

```sh
./contrib/run_corpus.sh ./build/contrib/sourcemeta_blaze_contrib_compile
```

## Adding New Files

Each file should be **small** and have a **single clear purpose**. Name files
descriptively (e.g., `type_as_integer.json`, `deeply_nested_allof.json`).
