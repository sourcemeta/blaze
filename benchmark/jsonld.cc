#include <benchmark/benchmark.h>

#include <cassert>       // assert
#include <cstddef>       // std::size_t
#include <string>        // std::string, std::to_string
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move
#include <variant>       // std::holds_alternative

#include <sourcemeta/blaze/foundation.h>
#include <sourcemeta/core/json.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>
#include <sourcemeta/blaze/output.h>

// The number of books in the catalog and how many authors each one carries.
// Together they set how many annotations the run emits, so they are the knobs
// to turn when using this benchmark as a basis for further research.
static constexpr std::size_t catalog_member_count{256};
static constexpr std::size_t authors_per_book{3};

// A string value that never risks the const char* to bool constructor selection
static auto string_value(std::string value) -> sourcemeta::core::JSON {
  return sourcemeta::core::JSON{std::move(value)};
}

static auto make_person(const std::size_t index) -> sourcemeta::core::JSON {
  auto person{sourcemeta::core::JSON::make_object()};
  person.assign("id", string_value("person-" + std::to_string(index)));
  person.assign("name", string_value("Person " + std::to_string(index)));
  return person;
}

static auto make_organization(const std::size_t index)
    -> sourcemeta::core::JSON {
  auto organization{sourcemeta::core::JSON::make_object()};
  organization.assign("id", string_value("org-" + std::to_string(index)));
  organization.assign("name",
                      string_value("Organization " + std::to_string(index)));
  organization.assign(
      "url", string_value("https://example.com/org/" + std::to_string(index)));
  return organization;
}

static auto make_price(const std::size_t index) -> sourcemeta::core::JSON {
  auto price{sourcemeta::core::JSON::make_object()};
  const auto code{index % 3 == 0 ? "USD" : index % 3 == 1 ? "EUR" : "GBP"};
  price.assign("currency", string_value(code));
  price.assign("value",
               sourcemeta::core::JSON{static_cast<double>(index) + 0.99});
  return price;
}

static auto make_series(const std::size_t index) -> sourcemeta::core::JSON {
  auto series{sourcemeta::core::JSON::make_object()};
  series.assign("id", string_value("series-" + std::to_string(index)));
  series.assign("name", string_value("Series " + std::to_string(index)));
  return series;
}

static auto make_provenance(const std::size_t index) -> sourcemeta::core::JSON {
  auto provenance{sourcemeta::core::JSON::make_object()};
  provenance.assign("id", string_value("prov-" + std::to_string(index)));
  provenance.assign("generatedBy",
                    string_value("Importer " + std::to_string(index)));
  return provenance;
}

static auto make_title(const std::size_t index) -> sourcemeta::core::JSON {
  auto title{sourcemeta::core::JSON::make_object()};
  title.assign("en", string_value("Title " + std::to_string(index)));
  title.assign("es", string_value("Titulo " + std::to_string(index)));
  title.assign("fr", string_value("Titre " + std::to_string(index)));
  return title;
}

static auto make_identifiers(const std::size_t index)
    -> sourcemeta::core::JSON {
  auto identifiers{sourcemeta::core::JSON::make_object()};
  identifiers.assign("isbn", string_value("978-" + std::to_string(index)));
  identifiers.assign("doi", string_value("10.1000/" + std::to_string(index)));
  identifiers.assign("oclc", string_value("oclc-" + std::to_string(index)));
  return identifiers;
}

static auto make_metadata(const std::size_t index) -> sourcemeta::core::JSON {
  auto metadata{sourcemeta::core::JSON::make_object()};
  metadata.assign("source", string_value("registry"));
  metadata.assign("batch", string_value("batch-" + std::to_string(index)));
  return metadata;
}

static auto make_keywords() -> sourcemeta::core::JSON {
  auto keywords{sourcemeta::core::JSON::make_array()};
  keywords.push_back(string_value("reference"));
  keywords.push_back(string_value("standards"));
  keywords.push_back(string_value("linked-data"));
  return keywords;
}

static auto make_book(const std::size_t index) -> sourcemeta::core::JSON {
  auto book{sourcemeta::core::JSON::make_object()};
  book.assign("isbn", string_value("978-0-" + std::to_string(index)));
  book.assign("title", make_title(index));
  book.assign("abstract", string_value("Abstract " + std::to_string(index)));
  book.assign("datePublished", string_value("2020-05-15"));

  auto authors{sourcemeta::core::JSON::make_array()};
  for (std::size_t offset = 0; offset < authors_per_book; offset += 1) {
    authors.push_back(make_person(index * 10 + offset));
  }
  book.assign("authors", std::move(authors));

  book.assign("keywords", make_keywords());
  book.assign("identifiers", make_identifiers(index));
  book.assign("price", make_price(index));
  book.assign("publisher", make_organization(index));
  book.assign("series", make_series(index));
  book.assign("metadata", make_metadata(index));
  book.assign("provenance", make_provenance(index));
  return book;
}

static auto make_catalog(const std::size_t count) -> sourcemeta::core::JSON {
  auto members{sourcemeta::core::JSON::make_array()};
  for (std::size_t index = 0; index < count; index += 1) {
    members.push_back(make_book(index));
  }

  auto catalog{sourcemeta::core::JSON::make_object()};
  catalog.assign("members", std::move(members));
  return catalog;
}

static auto JSONLD_Catalog(benchmark::State &state) -> void {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/catalog",
    "$defs": {
      "person": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/Person",
        "x-jsonld-self": "https://example.com/people/{id}",
        "properties": {
          "id": { "type": "string" },
          "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" }
        }
      },
      "organization": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/Organization",
        "x-jsonld-self": "https://example.com/orgs/{id}",
        "properties": {
          "id": { "type": "string" },
          "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" },
          "url": { "type": "string", "x-jsonld-id": "https://schema.org/url" }
        }
      },
      "price": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/MonetaryAmount",
        "properties": {
          "currency": {
            "type": "string",
            "x-jsonld-id": "https://schema.org/currency",
            "x-jsonld-type": "https://schema.org/Currency",
            "x-jsonld-self": "https://www.iso.org/iso-4217/{this}"
          },
          "value": {
            "type": "number",
            "x-jsonld-id": "https://schema.org/value",
            "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#decimal"
          }
        }
      },
      "series": {
        "type": "object",
        "x-jsonld-self": "https://example.com/series/{id}",
        "properties": {
          "id": { "type": "string" },
          "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" }
        }
      },
      "provenance": {
        "type": "object",
        "x-jsonld-self": "https://example.com/prov/{id}",
        "x-jsonld-graph": true,
        "properties": {
          "id": { "type": "string" },
          "generatedBy": {
            "type": "string",
            "x-jsonld-id": "https://schema.org/creator"
          }
        }
      },
      "book": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/Book",
        "x-jsonld-self": "urn:isbn:{isbn}",
        "properties": {
          "isbn": { "type": "string", "x-jsonld-id": "https://schema.org/isbn" },
          "title": {
            "type": "object",
            "x-jsonld-id": "https://schema.org/name",
            "x-jsonld-container": "@language"
          },
          "abstract": {
            "type": "string",
            "x-jsonld-id": "https://schema.org/abstract",
            "x-jsonld-language": "ar",
            "x-jsonld-direction": "rtl"
          },
          "datePublished": {
            "type": "string",
            "x-jsonld-id": "https://schema.org/datePublished",
            "x-jsonld-datatype": "http://www.w3.org/2001/XMLSchema#date"
          },
          "authors": {
            "type": "array",
            "x-jsonld-id": "https://schema.org/author",
            "x-jsonld-container": "@list",
            "items": { "$ref": "#/$defs/person" }
          },
          "keywords": {
            "type": "array",
            "x-jsonld-id": "https://schema.org/keywords",
            "items": { "type": "string" }
          },
          "identifiers": {
            "type": "object",
            "x-jsonld-id": "https://schema.org/identifier",
            "x-jsonld-container": "@index",
            "additionalProperties": { "type": "string" }
          },
          "price": {
            "$ref": "#/$defs/price",
            "x-jsonld-id": "https://schema.org/offers"
          },
          "publisher": {
            "$ref": "#/$defs/organization",
            "x-jsonld-id": "https://schema.org/publisher"
          },
          "series": {
            "$ref": "#/$defs/series",
            "x-jsonld-reverse": "https://schema.org/hasPart"
          },
          "metadata": {
            "type": "object",
            "x-jsonld-id": "https://schema.org/additionalProperty",
            "x-jsonld-json": true
          },
          "provenance": {
            "$ref": "#/$defs/provenance",
            "x-jsonld-id": "https://schema.org/isBasedOn"
          }
        }
      }
    },
    "type": "object",
    "x-jsonld-type": "https://schema.org/ItemList",
    "properties": {
      "members": {
        "type": "array",
        "x-jsonld-id": "https://schema.org/itemListElement",
        "items": { "$ref": "#/$defs/book" }
      }
    }
  })JSON")};

  const auto instance{make_catalog(catalog_member_count)};

  sourcemeta::blaze::Tweaks tweaks;
  tweaks.annotations = std::unordered_set<sourcemeta::core::JSON::StringView>{
      sourcemeta::blaze::JSONLD_KEYWORDS.begin(),
      sourcemeta::blaze::JSONLD_KEYWORDS.end()};
  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::blaze::schema_walker,
      sourcemeta::blaze::schema_resolver,
      sourcemeta::blaze::default_schema_compiler,
      sourcemeta::blaze::Mode::FastValidation, "", "", "", tweaks)};

  sourcemeta::blaze::Evaluator evaluator;
  for (auto _ : state) {
    auto outcome{
        sourcemeta::blaze::jsonld(evaluator, schema_template, instance)};
    assert(std::holds_alternative<sourcemeta::core::JSON>(outcome));
    benchmark::DoNotOptimize(outcome);
  }
}

BENCHMARK(JSONLD_Catalog);
