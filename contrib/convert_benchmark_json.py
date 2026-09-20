#!/usr/bin/env python3

"""Converter from the Sourcemeta Core benchmark JSON output to the shape that
benchmark-action/github-action-benchmark reads as `customSmallerIsBetter`.

Usage:
    python3 contrib/convert_benchmark_json.py build/benchmark.json
"""

import json
import sys


FORMAT_VERSION = 1


def convert(document):
    """Turn a Core benchmark document into benchmark action entries."""
    return [
        {
            "name": benchmark["name"],
            "unit": "ns",
            "value": benchmark["realTime"],
        }
        for benchmark in document["benchmarks"]
    ]


def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <benchmark.json>", file=sys.stderr)
        sys.exit(1)

    with open(sys.argv[1]) as handle:
        document = json.load(handle)

    version = document.get("version")
    if version != FORMAT_VERSION:
        print(f"Unsupported benchmark format version: {version}",
              file=sys.stderr)
        sys.exit(1)

    print(json.dumps(convert(document), indent=2))


if __name__ == "__main__":
    main()
