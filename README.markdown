Blaze
=====

The ultra high-performance JSON Schema validator for C++ with support for JSON
Schema Draft 4, Draft 6, Draft 7, 2019-09, and 2020-12. Built on top of the
powerful [JSON Toolkit](https://github.com/sourcemeta/jsontoolkit) library.

![Supported Dialects](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fsupported_versions.json)

![Draft 2020-12](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fcompliance%2Fdraft2020-12.json)
![Draft 2019-09](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fcompliance%2Fdraft2019-09.json)
![Draft 7](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fcompliance%2Fdraft7.json)
![Draft 6](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fcompliance%2Fdraft6.json)
![Draft 4](https://img.shields.io/endpoint?url=https%3A%2F%2Fbowtie.report%2Fbadges%2Fc%2B%2B-blaze%2Fcompliance%2Fdraft4.json)

***

> [!IMPORTANT]
> We are working hard to get Blaze to its first stable release. This includes:
>
> - Improving the documentation to include a basic getting started guide
> - Bindings to higher-level programming languages, starting with Node.js
> - Publishing an academic paper along with a reproducible benchmark
> - Landing various other in-progress optimizations
>
> Please star the project to show us your support!

Features
--------

- **Performance:** Blaze compiles JSON Schema into a lower-level intermediate
  language for ultra fast evaluation. It can achieve schema validation in the
  nano-second range, making it a perfect fit for low-latency gateways and
  validation of large datasets

- **Compliance:** Blaze achieves a 100% compliance score in the official
  [Bowtie](https://bowtie.report/#/implementations/cpp-blaze) benchmark, while
  popular validators like [AJV](https://bowtie.report/#/implementations/js-ajv)
  only achieve an average 85% compliance. Furthermore, Blaze is built and
  maintained by a [JSON Schema TSC member](https://www.jviotti.com)

- **Extensibility:** Blaze supports the implementation of custom vocabularies
  of arbitrary complexity, and the ability to setup custom resolution of
  external schemas from arbitrary sources, like from HTTP, filesystem,
  databases, etc

- **Annotations:** Blaze is one of the few implementations that fully supports
  annotation extraction during evaluation to augment instances with semantic
  information, making it a great fit for data science scenarios

Documentation
-------------

Refer to the project website for documentation and tutorials:
[https://blaze.sourcemeta.com](https://blaze.sourcemeta.com).
