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

// The number of top-level people in the catalog and how many acquaintances each
// one carries. Together they set how many annotations the run emits, so they
// are the knobs to turn when using this benchmark as a basis for further
// research.
static constexpr std::size_t catalog_member_count{256};
static constexpr std::size_t relations_per_member{3};

// A string value that never risks the const char* to bool constructor selection
static auto string_value(std::string value) -> sourcemeta::core::JSON {
  return sourcemeta::core::JSON{std::move(value)};
}

static auto make_person(const std::size_t index, const bool include_relations)
    -> sourcemeta::core::JSON {
  auto person{sourcemeta::core::JSON::make_object()};
  person.assign("name", string_value("Person " + std::to_string(index)));
  person.assign(
      "email", string_value("person" + std::to_string(index) + "@example.com"));
  person.assign("jobTitle", string_value("Title " + std::to_string(index)));
  if (!include_relations) {
    return person;
  }

  auto telephone{sourcemeta::core::JSON::make_array()};
  telephone.push_back(string_value("+1-555-000-" + std::to_string(index)));
  telephone.push_back(string_value("+1-555-100-" + std::to_string(index)));
  person.assign("telephone", std::move(telephone));

  auto address{sourcemeta::core::JSON::make_object()};
  address.assign("streetAddress",
                 string_value(std::to_string(index) + " Main Street"));
  address.assign("addressLocality", string_value("Springfield"));
  address.assign("postalCode", string_value("00000"));
  address.assign("addressCountry", string_value("US"));
  person.assign("address", std::move(address));

  auto organization{sourcemeta::core::JSON::make_object()};
  organization.assign("name",
                      string_value("Organization " + std::to_string(index)));
  organization.assign(
      "url", string_value("https://example.com/org/" + std::to_string(index)));
  person.assign("worksFor", std::move(organization));

  auto knows{sourcemeta::core::JSON::make_array()};
  for (std::size_t offset = 1; offset <= relations_per_member; offset += 1) {
    knows.push_back(make_person(index * 10 + offset, false));
  }
  person.assign("knows", std::move(knows));

  return person;
}

static auto make_catalog(const std::size_t count) -> sourcemeta::core::JSON {
  auto members{sourcemeta::core::JSON::make_array()};
  for (std::size_t index = 0; index < count; index += 1) {
    members.push_back(make_person(index, true));
  }

  auto catalog{sourcemeta::core::JSON::make_object()};
  catalog.assign("members", std::move(members));
  return catalog;
}

static auto Micro_JSONLD_Catalog(benchmark::State &state) -> void {
  const auto schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/catalog",
    "$defs": {
      "postalAddress": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/PostalAddress",
        "properties": {
          "streetAddress": {
            "type": "string",
            "x-jsonld-id": "https://schema.org/streetAddress"
          },
          "addressLocality": {
            "type": "string",
            "x-jsonld-id": "https://schema.org/addressLocality"
          },
          "postalCode": {
            "type": "string",
            "x-jsonld-id": "https://schema.org/postalCode"
          },
          "addressCountry": {
            "type": "string",
            "x-jsonld-id": "https://schema.org/addressCountry"
          }
        }
      },
      "organization": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/Organization",
        "properties": {
          "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" },
          "url": { "type": "string", "x-jsonld-id": "https://schema.org/url" }
        }
      },
      "person": {
        "type": "object",
        "x-jsonld-type": "https://schema.org/Person",
        "properties": {
          "name": { "type": "string", "x-jsonld-id": "https://schema.org/name" },
          "email": {
            "type": "string",
            "x-jsonld-id": "https://schema.org/email"
          },
          "jobTitle": {
            "type": "string",
            "x-jsonld-id": "https://schema.org/jobTitle"
          },
          "telephone": {
            "type": "array",
            "x-jsonld-id": "https://schema.org/telephone",
            "items": { "type": "string" }
          },
          "address": {
            "$ref": "#/$defs/postalAddress",
            "x-jsonld-id": "https://schema.org/address"
          },
          "worksFor": {
            "$ref": "#/$defs/organization",
            "x-jsonld-id": "https://schema.org/worksFor"
          },
          "knows": {
            "type": "array",
            "x-jsonld-id": "https://schema.org/knows",
            "items": { "$ref": "#/$defs/person" }
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
        "items": { "$ref": "#/$defs/person" }
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

BENCHMARK(Micro_JSONLD_Catalog);
