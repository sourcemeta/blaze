#include <sourcemeta/blaze/documentation.h>

#include <sourcemeta/core/html.h>
#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/options.h>

#include <cstdlib>  // EXIT_SUCCESS, EXIT_FAILURE
#include <iostream> // std::cerr, std::cout
#include <sstream>  // std::ostringstream
#include <string>   // std::string
#include <vector>   // std::vector

static auto emit_schema(const sourcemeta::core::JSON &schema,
                        const std::string &heading, const bool divider)
    -> bool {
  try {
    const auto documentation{sourcemeta::blaze::to_documentation(
        schema, sourcemeta::core::schema_walker,
        sourcemeta::core::schema_resolver)};

    if (divider) {
      std::cout << "<hr>\n";
    }

    if (!heading.empty()) {
      std::string escaped_heading{heading};
      sourcemeta::core::html_escape(escaped_heading);
      std::cout << "<h2>" << escaped_heading << "</h2>\n";
    }

    std::cout << sourcemeta::blaze::to_html(documentation);

    std::ostringstream schema_stream;
    sourcemeta::core::prettify(schema, schema_stream);
    std::string schema_string{schema_stream.str()};
    sourcemeta::core::html_escape(schema_string);
    std::cout << "\n<details><summary>Source Schema</summary>\n<pre><code>"
              << schema_string << "</code></pre></details>\n";

    return true;
  } catch (const std::exception &error) {
    std::cerr << "Error";
    if (!heading.empty()) {
      std::cerr << " (" << heading << ")";
    }

    std::cerr << ": " << error.what() << "\n";
    return false;
  }
}

auto main(int argc, char *argv[]) -> int {
  sourcemeta::core::Options options;
  options.option("pointer", {"p"});
  options.option("title", {"t"});
  options.parse(argc, argv);

  const auto &files{options.positional()};
  if (files.empty()) {
    std::cerr << "Usage: " << argv[0]
              << " [-p /pointer] [-t /title] <file> [file...]\n";
    return EXIT_FAILURE;
  }

  const auto has_pointer{options.contains("pointer")};
  const auto has_title{options.contains("title")};
  const std::string pointer_key{
      has_pointer ? std::string{options.at("pointer").front().substr(1)} : ""};
  const std::string title_key{
      has_title ? std::string{options.at("title").front().substr(1)} : ""};

  std::cout << R"HTML(<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Schema Documentation</title>
<style>
  body {
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto,
                 Helvetica, Arial, sans-serif;
    margin: 2rem;
    color: #1a1a1a;
    background: #fff;
  }

  .sourcemeta-blaze-documentation {
    width: 100%;
    border-collapse: collapse;
    font-size: 0.9rem;
    line-height: 1.4;
    table-layout: fixed;
  }

  .sourcemeta-blaze-documentation th:nth-child(1),
  .sourcemeta-blaze-documentation td:nth-child(1) { width: 20%; }
  .sourcemeta-blaze-documentation th:nth-child(2),
  .sourcemeta-blaze-documentation td:nth-child(2) { width: 20%; }
  .sourcemeta-blaze-documentation th:nth-child(3),
  .sourcemeta-blaze-documentation td:nth-child(3) { width: 8%; }
  .sourcemeta-blaze-documentation th:nth-child(4),
  .sourcemeta-blaze-documentation td:nth-child(4) { width: 20%; }
  .sourcemeta-blaze-documentation th:nth-child(5),
  .sourcemeta-blaze-documentation td:nth-child(5) { width: 32%; }

  .sourcemeta-blaze-documentation th,
  .sourcemeta-blaze-documentation td {
    border: 1px solid #d0d7de;
    padding: 0.5rem 0.75rem;
    text-align: left;
    vertical-align: top;
  }

  .sourcemeta-blaze-documentation thead th {
    background: #f6f8fa;
    font-weight: 600;
  }

  .sourcemeta-blaze-documentation code {
    font-family: ui-monospace, SFMono-Regular, "SF Mono", Menlo,
                 Consolas, monospace;
    font-size: 0.85em;
    background: #f0f3f6;
    padding: 0.15em 0.35em;
    border-radius: 3px;
  }

  .sourcemeta-blaze-documentation em {
    color: #656d76;
    font-style: italic;
  }

  .sourcemeta-blaze-documentation strong {
    font-weight: 600;
  }

  .sourcemeta-blaze-documentation p {
    margin: 0.25rem 0 0 0;
    color: #656d76;
    font-size: 0.85em;
  }

  .sourcemeta-blaze-documentation span {
    display: inline-block;
    font-size: 0.8em;
    padding: 0.15em 0.5em;
    margin: 0.15em 0.15em 0.15em 0;
    border-radius: 3px;
    background: #e8ecf0;
    color: #1a1a1a;
  }

  .sourcemeta-blaze-documentation a {
    color: #0969da;
    text-decoration: none;
  }

  .sourcemeta-blaze-documentation a:hover {
    text-decoration: underline;
  }

  .sourcemeta-blaze-documentation details:not(.schema-source) {
    display: inline;
  }

  .sourcemeta-blaze-documentation summary {
    display: inline;
    cursor: pointer;
    color: #656d76;
    font-size: 0.85em;
  }

  .sourcemeta-blaze-documentation table {
    width: 100%;
    border-collapse: collapse;
    font-size: inherit;
    line-height: inherit;
  }

  .sourcemeta-blaze-documentation table th,
  .sourcemeta-blaze-documentation table td {
    border: 1px solid #d0d7de;
    padding: 0.5rem 0.75rem;
    text-align: left;
    vertical-align: top;
  }

  .sourcemeta-blaze-documentation table thead th {
    background: #f6f8fa;
    font-weight: 600;
  }

  .sourcemeta-blaze-documentation tr > td[colspan="5"] {
    padding: 0.75rem;
    background: #f6f8fa;
  }

  .sourcemeta-blaze-documentation tr > td[colspan="5"] > div > div:first-child {
    font-weight: 600;
    font-size: 0.85em;
    color: #656d76;
    text-transform: uppercase;
    letter-spacing: 0.03em;
    margin-bottom: 0.5rem;
  }

  .sourcemeta-blaze-documentation tr > td[colspan="5"] > div > div + div {
    border: 1px solid #d0d7de;
    border-radius: 4px;
    background: #fff;
    padding: 0.5rem;
    margin-bottom: 0.5rem;
  }

  h2 {
    margin-top: 2rem;
    font-size: 1.1rem;
    font-weight: 600;
  }

  hr {
    border: none;
    border-top: 3px solid #d0d7de;
    margin: 2.5rem 0;
  }

  details.schema-source {
    margin-top: 0.5rem;
  }

  details.schema-source summary {
    cursor: pointer;
    font-size: 0.85rem;
    color: #656d76;
  }

  pre {
    background: #f6f8fa;
    border: 1px solid #d0d7de;
    border-radius: 6px;
    padding: 1rem;
    overflow-x: auto;
    font-size: 0.85rem;
    line-height: 1.5;
  }

  pre code {
    font-family: ui-monospace, SFMono-Regular, "SF Mono", Menlo,
                 Consolas, monospace;
    background: none;
    padding: 0;
  }
</style>
</head>
<body>
)HTML";

  bool any_failed{false};
  bool first{true};

  for (const auto &file : files) {
    const auto document{sourcemeta::core::read_json(std::string{file})};

    if (has_pointer && document.is_array()) {
      std::size_t index{0};
      for (const auto &entry : document.as_array()) {
        const auto &schema{entry.at(pointer_key)};

        std::string heading;
        if (has_title && entry.defines(title_key)) {
          const auto &title_value{entry.at(title_key)};
          if (title_value.is_string()) {
            heading = title_value.to_string();
          }
        }

        if (heading.empty()) {
          heading = std::string{file} + "[" + std::to_string(index) + "]";
        }

        if (!emit_schema(schema, heading, !first)) {
          any_failed = true;
        }

        first = false;
        index++;
      }
    } else {
      std::string heading;
      if (files.size() > 1) {
        heading = std::string{file};
      }

      if (!emit_schema(document, heading, !first)) {
        any_failed = true;
      }

      first = false;
    }
  }

  std::cout << R"HTML(
</body>
</html>
)HTML";

  return any_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
