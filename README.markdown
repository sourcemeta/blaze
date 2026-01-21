Blaze
=====

The ultra high-performance JSON Schema validator for C++ with support for JSON
Schema Draft 4, Draft 6, Draft 7, 2019-09, and 2020-12.

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.14867298.svg)](https://doi.org/10.5281/zenodo.14867298)
![Supported Dialects](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fsupported_versions.json)

![Draft 2020-12](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fcompliance%2Fdraft2020-12.json)
![Draft 2019-09](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fcompliance%2Fdraft2019-09.json)
![Draft 7](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fcompliance%2Fdraft7.json)
![Draft 6](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fcompliance%2Fdraft6.json)
![Draft 4](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fcompliance%2Fdraft4.json)

Want to use Blaze without writing C++? Check out our [JSON Schema
CLI](https://github.com/sourcemeta/jsonschema), which is powered by Blaze, and
offers advanced functionality like [`validate
--trace`](https://github.com/sourcemeta/jsonschema/blob/main/docs/validate.markdown)
for debugging schema evaluation.

Benchmark
---------

The 2025 paper [Blaze: Compiling JSON Schema for 10x Faster
Validation](https://arxiv.org/abs/2503.02770) (also published on
[PVLDB](https://www.vldb.org/pvldb/vol19/p279-viotti.pdf)) presents a
reproducible benchmark comparing Blaze against a number of popular JSON Schema
validators, concluding that Blaze is on average _at least_ 10x faster than
competitors given a large set of representative schemas and instances.

[![](./assets/banner.png)](https://arxiv.org/abs/2503.02770)

Features
--------

- **Performance:** Blaze compiles JSON Schema into a lower-level intermediate
  language for ultra fast evaluation. It can achieve schema validation in the
  nano-second range, making it a perfect fit for low-latency gateways and
  validation of large datasets

- **Compliance:** Blaze achieves a 100% compliance score in the official
  [Bowtie](https://bowtie.report/#/implementations/cpp-blaze) benchmark, while
  popular validators like [AJV](https://bowtie.report/#/implementations/js-ajv)
  only achieve an average 85% compliance. It also supports the [Standard
  Output](https://json-schema.org/draft/2020-12/json-schema-core#name-output-formatting)
  format (Flag, and Basic). Furthermore, Blaze is built and maintained by a
  [JSON Schema TSC member](https://www.jviotti.com)

- **Extensibility:** Blaze supports the implementation of custom vocabularies
  of arbitrary complexity, and the ability to setup custom resolution of
  external schemas from arbitrary sources, like from HTTP, filesystem,
  databases, etc

- **Annotations:** Blaze is one of the few implementations that fully supports
  annotation extraction during evaluation to augment instances with semantic
  information, making it a great fit for data science scenarios. Blaze also
  adheres to the [annotations official test
  suite](https://github.com/json-schema-org/JSON-Schema-Test-Suite/tree/main/annotations)

- **Numerics:** Blaze supports high precision decimals. For performance
  reasons, these representations are only used if the numbers fail to be parsed
  at the JSON level using the 64-bit signed and IEEE 764 double precision
  representations or (as a heuristic) if the numbers explicitly opt-in to
  exponent scientific notation

Example
-------

Blaze is designed to be easy to use, while at the same time providing extensive
hooks for supporting custom vocabularies, resolving external schemas, and more.

```cpp
// (1) Get a JSON Schema
const auto schema{sourcemeta::core::parse(R"JSON({
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "type": "string"
})JSON")};

// (2) Compile the JSON Schema into an optimised representation
const auto compiled_schema{sourcemeta::blaze::compile(
  schema,

  // These options allow you tweak how Blaze works,
  // the JSON Schema vocabularies it understands,
  // and how to resolve references to external schemas
  sourcemeta::core::schema_walker,
  sourcemeta::core::schema_resolver,
  sourcemeta::blaze::default_schema_compiler,

  // Fast validation means getting to a boolean result
  // as fast as possible. Check out the documentation
  // for how to get detailed error information and/or
  // collect JSON Schema annotations
  sourcemeta::blaze::Mode::FastValidation)};

// (3) Get a JSON instance
const sourcemeta::core::JSON instance{"Hello Blaze!"};

// (4) Validate the instance against the schema
sourcemeta::blaze::Evaluator evaluator;
const auto result{evaluator.validate(compiled_schema, instance)};
if (result) {
  std::cout << "Success!\n";
}
```

Documentation
-------------

Refer to the project website for documentation:
[https://blaze.sourcemeta.com](https://blaze.sourcemeta.com).

Roadmap
-------

- Support running the validator on [simdjson](https://github.com/simdjson/simdjson)
- Provide bindings to more higher-level programming languages

Contributors
------------

Blaze was designed and developed by a team of passionate JSON Schema developers
and researchers.

<a href="https://github.com/sourcemeta/blaze/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=sourcemeta/blaze" />
</a>
