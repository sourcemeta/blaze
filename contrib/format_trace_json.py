#!/usr/bin/env python3

"""Formatter for Blaze JSON test files (evaluator traces and output suites).

Usage:
    python3 contrib/format_trace_json.py test/evaluator/evaluator_*.json
    python3 contrib/format_trace_json.py test/output/output_standard_basic.json
"""

import json
import sys


MAX_LINE_LENGTH = 80


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
    return json.dumps(value)


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
            inner = ", ".join(json.dumps(element) for element in value)
            return f"[ {inner} ]"
        lines = ["["]
        for index, element in enumerate(value):
            comma = "," if index < len(value) - 1 else ""
            formatted = format_json_value(element, indent_level + 1)
            lines.append(f"{spaces}  {formatted}{comma}")
        lines.append(f"{spaces}]")
        return "\n".join(lines)
    return json.dumps(value)


def format_trace_array(entries, indent_level):
    """Format a pre/post trace array with one entry per line."""
    spaces = "  " * indent_level
    if not entries:
        return f"{spaces}[]"
    lines = [f"{spaces}["]
    for index, entry in enumerate(entries):
        inner = ", ".join(json.dumps(value) for value in entry)
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
    return "pre" in fast or "post" in fast


def format_test_entry(test):
    """Format a single test entry."""
    if is_trace_format(test):
        fmt = format_trace_mode_section
    else:
        fmt = format_output_mode_section

    lines = []
    lines.append("  {")
    lines.append(
        f"    \"description\": {json.dumps(test['description'])},"
    )
    lines.append(
        f"    \"schema\": {format_json_value(test['schema'], 2)},"
    )
    lines.append(
        f"    \"instance\": {format_json_value(test['instance'], 2)},"
    )
    lines.append(
        f"    \"valid\": {json.dumps(test['valid'])},"
    )
    lines.append(
        f"    \"fast\": {fmt(test['fast'], 2)},"
    )
    lines.append(
        f"    \"exhaustive\": {fmt(test['exhaustive'], 2)}"
    )
    lines.append("  }")
    return "\n".join(lines)


def format_file(filepath):
    """Format a trace JSON test file in place."""
    with open(filepath) as handle:
        data = json.load(handle)

    entries = []
    for test in data:
        entries.append(format_test_entry(test))

    result = "[\n" + ",\n".join(entries) + "\n]\n"

    with open(filepath, "w") as handle:
        handle.write(result)


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <file.json>...", file=sys.stderr)
        sys.exit(1)

    for filepath in sys.argv[1:]:
        print(f"Formatting {filepath}")
        format_file(filepath)


if __name__ == "__main__":
    main()
