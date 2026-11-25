#!/usr/bin/env python3

"""Formatter for Blaze JSON test files (evaluator traces and output suites).

A file holding an array is formatted as a suite of test entries, and a file
holding a single object as one entry. A directory is walked for the JSON files
it holds, so a suite of one fixture per file needs no argument of its own.

Usage:
    python3 contrib/format_trace_json.py test/evaluator/suite
    python3 contrib/format_trace_json.py test/output/output_standard_basic.json
"""

import json
import pathlib
import sys


MAX_LINE_LENGTH = 80

TRACE_ENTRY_KEYS = (
    "comment", "description", "schema", "resolve", "instance", "valid",
    "defaultDialect", "entrypoint", "tweaks", "fast", "exhaustive"
)
ERROR_ENTRY_KEYS = (
    "comment", "description", "schema", "resolve", "instance",
    "defaultDialect", "entrypoint", "tweaks", "error"
)


class RawNumber:
    """A number held as the document spells it.

    How a number is written is part of what a fixture asks: `1e0` and `1.0`
    are the same value but not the same test, and reading one into a Python
    float and writing it back loses the difference.
    """

    __slots__ = ("text",)

    def __init__(self, text):
        self.text = text

    def __eq__(self, other):
        return isinstance(other, RawNumber) and self.text == other.text

    def __hash__(self):
        return hash(self.text)


def dump(value):
    """One JSON value on a single line, numbers spelled as they were written.

    Lays out exactly as `json.dumps` does, so formatting a file that holds no
    reformatted number leaves it alone.
    """
    if isinstance(value, RawNumber):
        return value.text
    if isinstance(value, dict):
        pairs = ", ".join(f"{json.dumps(key)}: {dump(inner)}"
                          for key, inner in value.items())
        return "{" + pairs + "}"
    if isinstance(value, list):
        return "[" + ", ".join(dump(element) for element in value) + "]"
    return json.dumps(value)


def compact_json(value):
    """Try to produce a compact single-line JSON representation."""
    if isinstance(value, dict):
        if not value:
            return "{}"
        pairs = ", ".join(
            f"{json.dumps(k)}: {compact_json(v)}"
            for k, v in value.items()
        )
        return "{ " + pairs + " }"
    if isinstance(value, list):
        if not value:
            return "[]"
        inner = ", ".join(compact_json(element) for element in value)
        return "[ " + inner + " ]"
    return dump(value)


def format_json_value(value, indent_level):
    """Format a JSON value with standard indentation."""
    spaces = "  " * indent_level
    current_indent = len(spaces)

    # Try compact single-line first
    one_line = compact_json(value)
    if "\n" not in one_line and current_indent + len(one_line) <= MAX_LINE_LENGTH:
        return one_line

    if isinstance(value, dict):
        if not value:
            return "{}"
        lines = ["{"]
        entries = list(value.items())
        for index, (key, val) in enumerate(entries):
            comma = "," if index < len(entries) - 1 else ""
            formatted = format_json_value(val, indent_level + 1)
            lines.append(f"{spaces}  {json.dumps(key)}: {formatted}{comma}")
        lines.append(f"{spaces}}}")
        return "\n".join(lines)
    if isinstance(value, list):
        if not value:
            return "[]"
        # Check if all elements are primitives (not dicts or lists)
        all_primitive = all(
            not isinstance(element, (dict, list)) for element in value
        )
        if all_primitive:
            inner = ", ".join(dump(element) for element in value)
            return f"[ {inner} ]"
        lines = ["["]
        for index, element in enumerate(value):
            comma = "," if index < len(value) - 1 else ""
            formatted = format_json_value(element, indent_level + 1)
            lines.append(f"{spaces}  {formatted}{comma}")
        lines.append(f"{spaces}]")
        return "\n".join(lines)
    return dump(value)


def format_trace_array(entries, indent_level):
    """Format a pre/post trace array with one entry per line."""
    spaces = "  " * indent_level
    if not entries:
        return f"{spaces}[]"
    lines = [f"{spaces}["]
    for index, entry in enumerate(entries):
        inner = ", ".join(dump(value) for value in entry)
        comma = "," if index < len(entries) - 1 else ""
        lines.append(f"{spaces}  [ {inner} ]{comma}")
    lines.append(f"{spaces}]")
    return "\n".join(lines)


def format_descriptions(descriptions, indent_level):
    """Format a descriptions array with one string per line."""
    spaces = "  " * indent_level
    if not descriptions:
        return f"{spaces}[]"
    lines = [f"{spaces}["]
    for index, description in enumerate(descriptions):
        comma = "," if index < len(descriptions) - 1 else ""
        lines.append(f"{spaces}  {json.dumps(description)}{comma}")
    lines.append(f"{spaces}]")
    return "\n".join(lines)


def format_trace_mode_section(mode_data, indent_level):
    """Format a fast/exhaustive section containing trace data."""
    spaces = "  " * indent_level
    if not mode_data:
        return "{}"
    lines = ["{"]

    pre_formatted = format_trace_array(mode_data["pre"], indent_level + 1)
    # Put "pre": [ on the same line
    pre_lines = pre_formatted.split("\n")
    lines.append(f"{spaces}  \"pre\": {pre_lines[0].lstrip()}")
    lines.extend(pre_lines[1:])
    lines[-1] += ","

    post_formatted = format_trace_array(mode_data["post"], indent_level + 1)
    post_lines = post_formatted.split("\n")
    lines.append(f"{spaces}  \"post\": {post_lines[0].lstrip()}")
    lines.extend(post_lines[1:])
    lines[-1] += ","

    desc_formatted = format_descriptions(
        mode_data["descriptions"], indent_level + 1
    )
    desc_lines = desc_formatted.split("\n")
    lines.append(f"{spaces}  \"descriptions\": {desc_lines[0].lstrip()}")
    lines.extend(desc_lines[1:])

    lines.append(f"{spaces}}}")
    return "\n".join(lines)


def format_output_mode_section(mode_data, indent_level):
    """Format a fast/exhaustive section containing standard output data."""
    if not mode_data:
        return "{}"
    return format_json_value(mode_data, indent_level)


def is_trace_format(test):
    """Detect whether a test entry uses trace format or output format."""
    fast = test.get("fast", {})
    exhaustive = test.get("exhaustive", {})
    return ("pre" in fast or "post" in fast
            or "pre" in exhaustive or "post" in exhaustive)


def format_entry_value(test, key, indent_level):
    """Format the value one key of a test entry holds."""
    value = test[key]
    if key in ("description", "valid"):
        return dump(value)
    if key in ("fast", "exhaustive"):
        if is_trace_format(test):
            return format_trace_mode_section(value, indent_level)
        return format_output_mode_section(value, indent_level)
    return format_json_value(value, indent_level)


def format_test_entry(test, indent_level):
    """Format a single test entry, keeping its keys in their canonical order."""
    spaces = "  " * indent_level
    order = ERROR_ENTRY_KEYS if "error" in test else TRACE_ENTRY_KEYS
    keys = [key for key in order if key in test]

    # Formatting rewrites each entry from its known keys, so a key this does not
    # know about would be dropped rather than kept. Refusing is the only safe
    # answer: silently discarding one leaves a fixture asserting the behaviour
    # of something it no longer asks for
    unknown = [key for key in test if key not in order]
    if unknown:
        raise ValueError(
            f"unknown key(s) {', '.join(sorted(unknown))}; "
            f"add them to {'ERROR' if 'error' in test else 'TRACE'}_ENTRY_KEYS"
        )

    lines = [f"{spaces}{{"]
    for index, key in enumerate(keys):
        comma = "," if index < len(keys) - 1 else ""
        formatted = format_entry_value(test, key, indent_level + 1)
        lines.append(f"{spaces}  {json.dumps(key)}: {formatted}{comma}")
    lines.append(f"{spaces}}}")
    return "\n".join(lines)


def format_file(filepath):
    """Format a trace JSON test file in place."""
    with open(filepath) as handle:
        data = json.load(handle, parse_float=RawNumber,
                         parse_int=RawNumber)

    if isinstance(data, list):
        entries = [format_test_entry(test, 1) for test in data]
        result = "[\n" + ",\n".join(entries) + "\n]\n"
    else:
        result = format_test_entry(data, 0) + "\n"

    with open(filepath, "w") as handle:
        handle.write(result)


def json_files(path):
    """The JSON files a command line argument names."""
    target = pathlib.Path(path)
    if target.is_dir():
        return sorted(target.rglob("*.json"))
    if target.is_file():
        return [target]
    raise FileNotFoundError(path)


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <file.json|directory>...", file=sys.stderr)
        sys.exit(1)

    for path in sys.argv[1:]:
        print(f"Formatting {path}")
        for filepath in json_files(path):
            try:
                format_file(filepath)
            except ValueError as error:
                print(f"{filepath}: {error}", file=sys.stderr)
                sys.exit(1)


if __name__ == "__main__":
    main()
