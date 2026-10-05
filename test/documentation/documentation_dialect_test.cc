#include "documentation_test_utils.h"

TEST(draft4_an_exclusive_bound_without_its_bound_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "http://json-schema.org/draft-04/schema#",
    "type": "integer",
    "exclusiveMinimum": true
  })JSON",
      "The `exclusiveMinimum` keyword needs a `minimum` in Draft 4", "", "");
}

TEST(draft3_is_refused) {
  EXPECT_DOCUMENTATION_REFUSED(
      R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON",
      "This module describes JSON Schema Draft 4, 6 and 7, 2019-09 and "
      "2020-12, and not HyperSchema",
      "", "");
}
