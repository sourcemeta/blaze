find_package(Python3 COMPONENTS Interpreter)
if(NOT Python3_FOUND)
  message(STATUS "Skipping the contrib tests, as Python 3 was not found")
  return()
endif()

set(CONTRIB_TEST_DRIVER "${CMAKE_CURRENT_SOURCE_DIR}/contrib_test.py")
set(PROFILER_FIXTURES "${CMAKE_CURRENT_SOURCE_DIR}/profiler")
set(PROFILER_REPORTS "${CMAKE_CURRENT_BINARY_DIR}/reports")
file(MAKE_DIRECTORY "${PROFILER_REPORTS}")

# Keep the repeated passes short, as these tests check the report rather than
# the measurements themselves
set(PROFILER_QUICK --warmup 1 --iterations 2 --compile-iterations 2)

function(blaze_contrib_profiler_test name)
  cmake_parse_arguments(TEST "" "EXIT" "EXPECT;ARGUMENTS" ${ARGN})
  add_test(NAME "contrib.profiler.${name}" COMMAND
    "${Python3_EXECUTABLE}" "${CONTRIB_TEST_DRIVER}"
    --program "$<TARGET_FILE:sourcemeta_blaze_contrib_profiler>"
    --exit "${TEST_EXIT}"
    --report "${PROFILER_REPORTS}/${name}.json"
    ${TEST_EXPECT} -- ${TEST_ARGUMENTS})
endfunction()

# A real workload, with its default number of passes
blaze_contrib_profiler_test(geojson EXIT 0
  EXPECT --instances 500 --valid 500 --trace
  ARGUMENTS --trace-steps
    "${PROJECT_SOURCE_DIR}/benchmark/e2e/geojson/schema.json"
    "${PROJECT_SOURCE_DIR}/benchmark/e2e/geojson/instances.jsonl")

# The fast validation template of this schema fuses its properties into an
# instruction whose children the evaluation callback never observes, which is
# what the trace coverage report exists to flag
blaze_contrib_profiler_test(valid_and_invalid_fast EXIT 0
  EXPECT --instances 5 --valid 3 --trace --coverage incomplete
    --hidden-subtrees 1
  ARGUMENTS ${PROFILER_QUICK} --trace-steps
    "${PROFILER_FIXTURES}/person.json" "${PROFILER_FIXTURES}/person.jsonl")
# The exhaustive template hides no subtree, but still groups instructions in a
# container that never reports itself
blaze_contrib_profiler_test(valid_and_invalid_exhaustive EXIT 0
  EXPECT --instances 5 --valid 3 --trace --coverage incomplete
    --hidden-subtrees 0
  ARGUMENTS ${PROFILER_QUICK} --trace-steps --exhaustive
    "${PROFILER_FIXTURES}/person.json" "${PROFILER_FIXTURES}/person.jsonl")
blaze_contrib_profiler_test(complete_trace EXIT 0
  EXPECT --instances 3 --valid 2 --trace --coverage complete
    --hidden-subtrees 0
  ARGUMENTS ${PROFILER_QUICK} --trace-steps
    "${PROFILER_FIXTURES}/string.json" "${PROFILER_FIXTURES}/string.jsonl")
blaze_contrib_profiler_test(single_json_instance EXIT 0
  EXPECT --instances 1 --valid 1
  ARGUMENTS ${PROFILER_QUICK}
    "${PROFILER_FIXTURES}/person.json"
    "${PROFILER_FIXTURES}/person_single.json")
blaze_contrib_profiler_test(empty_instances EXIT 0
  EXPECT --instances 0 --valid 0
  ARGUMENTS ${PROFILER_QUICK}
    "${PROFILER_FIXTURES}/person.json" "${PROFILER_FIXTURES}/empty.jsonl")
blaze_contrib_profiler_test(compile_failure EXIT 1
  EXPECT --compile failure
  ARGUMENTS ${PROFILER_QUICK}
    "${PROFILER_FIXTURES}/broken.json" "${PROFILER_FIXTURES}/person.jsonl")
blaze_contrib_profiler_test(unevaluated_marks EXIT 0
  EXPECT --instances 4 --valid 3 --trace --marks
  ARGUMENTS ${PROFILER_QUICK} --trace-steps
    "${PROFILER_FIXTURES}/unevaluated.json"
    "${PROFILER_FIXTURES}/unevaluated.jsonl")
blaze_contrib_profiler_test(no_compile_iterations EXIT 0
  EXPECT --instances 5 --valid 3
  ARGUMENTS --warmup 1 --iterations 2 --compile-iterations 0
    "${PROFILER_FIXTURES}/person.json" "${PROFILER_FIXTURES}/person.jsonl")
blaze_contrib_profiler_test(no_hardware_counters EXIT 0
  EXPECT --instances 5 --valid 3 --no-hardware
  ARGUMENTS ${PROFILER_QUICK} --no-hardware-counters
    "${PROFILER_FIXTURES}/person.json" "${PROFILER_FIXTURES}/person.jsonl")

add_test(NAME contrib.profiler.missing_arguments COMMAND
  "${Python3_EXECUTABLE}" "${CONTRIB_TEST_DRIVER}"
  --program "$<TARGET_FILE:sourcemeta_blaze_contrib_profiler>"
  --exit 1 --stderr "^Usage: ")
add_test(NAME contrib.profiler.negative_count COMMAND
  "${Python3_EXECUTABLE}" "${CONTRIB_TEST_DRIVER}"
  --program "$<TARGET_FILE:sourcemeta_blaze_contrib_profiler>"
  --exit 1 --stderr "warmup expects a non-negative integer, got: -1"
  -- --warmup -1
    "${PROFILER_FIXTURES}/person.json" "${PROFILER_FIXTURES}/person.jsonl")
add_test(NAME contrib.profiler.unwritable_output COMMAND
  "${Python3_EXECUTABLE}" "${CONTRIB_TEST_DRIVER}"
  --program "$<TARGET_FILE:sourcemeta_blaze_contrib_profiler>"
  --exit 1 --stderr "Could not write the report to "
  -- ${PROFILER_QUICK}
    --output "${PROFILER_REPORTS}/missing-directory/report.json"
    "${PROFILER_FIXTURES}/person.json" "${PROFILER_FIXTURES}/person.jsonl")

# Hardware counters may well be unavailable where the tests run, in which case
# the program has to carry on validating and say why
if(TARGET sourcemeta_blaze_contrib_perf)
  add_test(NAME contrib.perf.geojson COMMAND
    "${Python3_EXECUTABLE}" "${CONTRIB_TEST_DRIVER}"
    --program "$<TARGET_FILE:sourcemeta_blaze_contrib_perf>"
    --exit 0 --stderr "Cold\\n=+\\n(.|\\n)*Warm\\n=+\\n"
    -- "${PROJECT_SOURCE_DIR}/benchmark/e2e/geojson/schema.json"
       "${PROJECT_SOURCE_DIR}/benchmark/e2e/geojson/instances.jsonl")
  add_test(NAME contrib.perf.invalid_instance COMMAND
    "${Python3_EXECUTABLE}" "${CONTRIB_TEST_DRIVER}"
    --program "$<TARGET_FILE:sourcemeta_blaze_contrib_perf>"
    --exit 1 --stderr "Error validating instance 3"
    -- "${PROFILER_FIXTURES}/person.json" "${PROFILER_FIXTURES}/person.jsonl")
endif()
