Sourcemeta Extension Vocabulary
===============================

The Sourcemeta Extension vocabulary, identified by the URI
`tag:sourcemeta.com,2026:extension/v1`, defines the extension keywords listed
below.

In terms of compatibility, this vocabulary may receive backwards compatible
changes over time, such as new keywords. A breaking change results in a new
vocabulary published under a new major version.

Format assertion
----------------

| Keyword | Values | Applies To | Meaning |
|---------|--------|------------|---------|
| `x-format-assertion` | A boolean | any subschema | When `true` on a subschema that also declares `format`, that occurrence of `format` is evaluated as an assertion instead of an annotation. When `false` or absent, behavior is unchanged |

This is the per-subschema counterpart of the global format assertion
compilation option, and it only takes effect on evaluators that implement it,
such as Blaze.

JSON-LD
-------

These keywords map a valid instance to
[JSON-LD](https://www.w3.org/TR/json-ld11/), the JSON-based serialization of
[RDF](https://www.w3.org/RDF/). Each keyword may be placed on any subschema
and takes effect at the instance locations that subschema successfully
evaluates.

| Keyword | Values | Applies To | Meaning |
|---------|--------|------------|---------|
| `x-jsonld-id` | An absolute IRI | property subschema | The predicate IRI the property maps to |
| `x-jsonld-type` | An absolute IRI or array of absolute IRIs | object or reference subschema | The node `@type` |
| `x-jsonld-reverse` | An absolute IRI | property subschema | A reverse predicate IRI, emitting `@reverse` edges |
| `x-jsonld-datatype` | An absolute IRI | scalar subschema | A typed literal datatype IRI, such as `http://www.w3.org/2001/XMLSchema#date` |
| `x-jsonld-language` | A [BCP 47](https://www.rfc-editor.org/info/bcp47) language tag | string subschema | The language of language-tagged literals |
| `x-jsonld-direction` | `ltr` or `rtl` | string subschema | The base direction for internationalised literals |
| `x-jsonld-json` | A boolean | any subschema | Treat the value as an opaque `@json` literal |
| `x-jsonld-graph` | A boolean | object subschema | Wrap the node's edges in a named `@graph` |
| `x-jsonld-container` | `@list`, `@set`, `@language`, or `@index` | array or object property subschema | The container semantics of the property |
| `x-jsonld-self` | An [RFC 6570](https://www.rfc-editor.org/rfc/rfc6570) URI template | scalar or object subschema | Mint the node `@id` from instance values, such as `https://www.iso.org/iso-4217/{this}` |
