#!/usr/bin/env python3

"""Run a contrib program and check its exit code, its error output, and, for
the profiler, the JSON report that it writes.

Usage:
    python3 test/contrib/contrib_test.py --program <path> --exit <code>
        [--report <path>] [--stderr <regex>] [expectations...]
        -- <program arguments...>

When given a report path, the profiler is asked to write its report there and
the report is checked for its structure, its units, and the consistency of its
measurements, on top of whatever expectations the test asks for.
"""

import argparse
import json
import re
import subprocess
import sys


SUMMARY_KEYS = ("min_ns", "max_ns", "mean_ns", "p50_ns", "p95_ns", "p99_ns")


def reject_constant(name):
    """Refuse the non-standard constants that Python would otherwise accept."""
    raise ValueError(f"Non-standard JSON constant: {name}")


def is_integer(value):
    """Whether a JSON value is an integer, as Python counts booleans as one."""
    return isinstance(value, int) and not isinstance(value, bool)


class Checker:
    """Collect every failed check rather than stopping at the first one."""

    def __init__(self):
        self.failures = []

    def check(self, condition, message):
        if not condition:
            self.failures.append(message)


def check_summary(checker, name, summary):
    """A summary of zero samples is null throughout, never zero."""
    checker.check(is_integer(summary["count"]), f"{name}.count is an integer")
    checker.check(is_integer(summary["total_ns"]),
                  f"{name}.total_ns is an integer")
    if summary["count"] == 0:
        checker.check(all(summary[key] is None for key in SUMMARY_KEYS),
                      f"{name} uses null for an empty summary")
        checker.check(summary["total_ns"] == 0,
                      f"{name}.total_ns is zero for an empty summary")
        return

    checker.check(summary["min_ns"] <= summary["p50_ns"] <= summary["p95_ns"]
                  <= summary["p99_ns"] <= summary["max_ns"],
                  f"{name} percentiles are ordered")
    checker.check(summary["min_ns"] <= summary["mean_ns"] <= summary["max_ns"],
                  f"{name}.mean_ns is within range")


def check_hardware(checker, hardware):
    """Hardware counters may or may not be available on the machine running
    the tests, so either outcome passes as long as it is reported honestly."""
    if not hardware["available"]:
        checker.check(isinstance(hardware["unavailable_reason"], str) and
                      hardware["unavailable_reason"],
                      "unavailable hardware counters carry a reason")
        checker.check(hardware["scopes"] is None,
                      "unavailable hardware counters have no scopes")
        return

    checker.check(hardware["unavailable_reason"] is None,
                  "available hardware counters carry no reason")
    for name, scope in (hardware["scopes"] or {}).items():
        if scope is None:
            continue
        checker.check(scope["time_running_ns"] <= scope["time_enabled_ns"],
                      f"{name} runs no longer than it is enabled")
        for counter, value in scope["values"].items():
            checker.check(value is None or is_integer(value),
                          f"{name}.{counter} is an integer or null")
            checker.check((value is None) == (counter in
                                              scope["unavailable_counters"]),
                          f"{name}.{counter} is null only when unavailable")


def check_compilation(checker, compilation):
    phases = compilation["phases"]
    checker.check(compilation["wall_time_ns"] == phases["bundle_ns"] +
                  phases["frame_ns"] + phases["compile_body_ns"],
                  "compilation wall time is the sum of its phases")
    checker.check(compilation["template_instruction_count"] ==
                  sum(compilation["template_instruction_counts_by_type"]
                      .values()),
                  "instruction counts by type add up to the total")
    checker.check(compilation["template_size_bytes"] is None,
                  "template size is reported as not measured")
    check_summary(checker, "compile_body_repeated",
                  compilation["compile_body_repeated"])

    # Without repeated compilations there is nothing to profile keywords on
    profile = compilation["keyword_profile"]
    if compilation["compile_body_repeated"]["count"] == 0:
        checker.check(profile is None,
                      "no keyword profile without repeated compilations")
        return
    checker.check(profile is not None,
                  "repeated compilations produce a keyword profile")
    if profile is None:
        return

    for key, value in profile["accounting"].items():
        checker.check(value is True, f"keyword accounting: {key}")
    checker.check(profile["self_ns_total"] ==
                  profile["keyword_compilers_top_level_ns"],
                  "keyword self time adds up to top-level inclusive time")
    checker.check(profile["outside_keyword_compilers_ns"] ==
                  profile["instrumented_compile_body_ns"] -
                  profile["keyword_compilers_top_level_ns"],
                  "time outside keyword compilers is the remainder")
    checker.check(profile["outside_keyword_compilers_ns"] >= 0,
                  "time outside keyword compilers is not negative")
    checker.check(len(profile["keywords"]) > 0, "keywords were profiled")
    for keyword, entry in profile["keywords"].items():
        checker.check(entry["inclusive_ns"] >= entry["self_ns"] >= 0,
                      f"keyword {keyword}: inclusive >= self >= 0")
        checker.check(entry["calls"] >= entry["calls_without_instructions"],
                      f"keyword {keyword}: call counts are consistent")


def check_evaluation(checker, report, evaluation):
    count = evaluation["instance_count"]
    checker.check(count == report["workload"]["instance_count"],
                  "instance counts agree")
    checker.check(evaluation["valid_count"] + evaluation["invalid_count"] ==
                  count, "valid and invalid instances add up")
    checker.check(evaluation["result_mismatches"] == 0,
                  "repeated validations agree")
    checker.check(evaluation["cold"]["count"] == count,
                  "one cold sample per instance")
    iterations = report["workload"]["configuration"]["measured_iterations"]
    checker.check(evaluation["warm_per_instance"]["count"] ==
                  count * iterations,
                  "one warm sample per instance per iteration")
    checker.check(evaluation["warm_whole_pass"]["count"] == iterations,
                  "one whole-pass sample per iteration")
    for name in ("cold", "warm_per_instance", "warm_whole_pass"):
        check_summary(checker, name, evaluation[name])

    trace = evaluation["trace_step_counts"]
    if trace is not None:
        checker.check(trace["total"] == sum(trace["by_type"].values()),
                      "trace steps by type add up to the total")
        checker.check(trace["result_mismatches"] == 0,
                      "validation agrees with and without the callback")
        coverage = trace["coverage"]
        checker.check(coverage["complete"] ==
                      (coverage["hidden_subtree_roots"] == 0 and
                       not coverage["never_reported_types"]),
                      "trace coverage flag matches what the trace misses")


def check_report(checker, report, options):
    checker.check(report["report_version"] == 1, "report_version is 1")
    run = report["run"]
    for key in ("id", "timestamp", "platform", "build", "profiling_mode"):
        checker.check(key in run, f"run.{key} is present")
    checker.check(re.fullmatch(r"\d{4}-\d\d-\d\dT\d\d:\d\d:\d\dZ",
                               run["timestamp"]) is not None,
                  "timestamp is UTC ISO-8601")
    workload = report["workload"]
    for entry in ("schema", "instances"):
        checker.check(re.fullmatch(r"[0-9a-f]{64}",
                                   workload[entry]["sha256"]) is not None,
                      f"workload.{entry}.sha256 is a SHA-256 digest")
    checker.check(isinstance(report["notes"], list), "notes is a list")
    checker.check(report["timer"]["mean_timer_pair_ns"] > 0,
                  "the timer cost was measured")
    checker.check(report["timer"]["mean_empty_region_ns"] >= 0,
                  "the timer bias was measured")
    check_hardware(checker, report["hardware_counters"])

    compilation = report["compilation"]
    if options.compile == "failure":
        checker.check(compilation["success"] is False, "compilation fails")
        checker.check(isinstance(compilation.get("error"), str) and
                      compilation["error"],
                      "a failed compilation carries its error")
        checker.check(report["evaluation"] is None,
                      "nothing is evaluated after a failed compilation")
        return

    checker.check(compilation["success"] is True, "compilation succeeds")
    check_compilation(checker, compilation)
    evaluation = report["evaluation"]
    check_evaluation(checker, report, evaluation)

    if options.instances is not None:
        checker.check(evaluation["instance_count"] == options.instances,
                      f"instance_count is {options.instances}")
    if options.valid is not None:
        checker.check(evaluation["valid_count"] == options.valid,
                      f"valid_count is {options.valid}")
    trace = evaluation["trace_step_counts"]
    checker.check((trace is not None) == options.trace,
                  "trace_step_counts is present only when requested")
    if options.coverage is not None and trace is not None:
        checker.check(trace["coverage"]["complete"] ==
                      (options.coverage == "complete"),
                      f"trace coverage is {options.coverage}")
    if options.hidden_subtrees is not None and trace is not None:
        checker.check(trace["coverage"]["hidden_subtree_roots"] ==
                      options.hidden_subtrees,
                      f"trace hides {options.hidden_subtrees} subtrees")
    if options.marks:
        checker.check(evaluation["final_evaluation_marks"] is not None and
                      evaluation["final_evaluation_marks"]["total"] > 0,
                      "evaluation marks were recorded")
    if options.no_hardware:
        hardware = report["hardware_counters"]
        checker.check(hardware["requested"] is False and
                      hardware["available"] is False and
                      hardware["unavailable_reason"] == "Not requested",
                      "hardware counters are reported as not requested")
        checker.check(run["profiling_mode"] == "software",
                      "profiling mode is software only")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--program", required=True)
    parser.add_argument("--exit", type=int, required=True)
    parser.add_argument("--report")
    parser.add_argument("--stderr")
    parser.add_argument("--compile", choices=("success", "failure"),
                        default="success")
    parser.add_argument("--instances", type=int)
    parser.add_argument("--valid", type=int)
    parser.add_argument("--trace", action="store_true")
    parser.add_argument("--coverage", choices=("complete", "incomplete"))
    parser.add_argument("--hidden-subtrees", type=int)
    parser.add_argument("--marks", action="store_true")
    parser.add_argument("--no-hardware", action="store_true")
    parser.add_argument("arguments", nargs=argparse.REMAINDER)
    options = parser.parse_args()
    arguments = options.arguments
    if arguments and arguments[0] == "--":
        arguments = arguments[1:]

    command = [options.program]
    if options.report:
        command += ["--output", options.report]
    command += arguments
    result = subprocess.run(command, capture_output=True, text=True)

    checker = Checker()
    checker.check(result.returncode == options.exit,
                  f"exit code is {options.exit}, got {result.returncode}")
    if options.stderr:
        checker.check(re.search(options.stderr, result.stderr) is not None,
                      f"error output matches {options.stderr!r}")
    if options.report and not checker.failures:
        with open(options.report) as handle:
            report = json.load(handle, parse_constant=reject_constant)
        check_report(checker, report, options)

    if checker.failures:
        print("Command:", " ".join(command))
        print("Error output:", result.stderr, sep="\n")
        for failure in checker.failures:
            print(f"FAIL: {failure}")
        sys.exit(1)
    print(f"PASS: {' '.join(command)}")


if __name__ == "__main__":
    main()
