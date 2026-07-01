#include <sourcemeta/core/test.h>

#include <sourcemeta/blaze/test.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>

#include <filesystem> // std::filesystem::path

static const sourcemeta::core::PointerPositionTracker::Position STUB_POSITION{
    0, 0, 0, 0};

TEST(error_not_an_object) {
  const auto input{"[]"};
  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  try {
    sourcemeta::blaze::TestCase::parse(
        document, tracker, std::filesystem::path{STUBS_PATH},
        sourcemeta::core::empty_pointer, STUB_POSITION);
    FAIL();
  } catch (const sourcemeta::blaze::TestParseError &error) {
    EXPECT_STREQ(error.what(), "Test case documents must be objects");
  }
}

TEST(error_no_data_or_dataPath) {
  const auto input{R"JSON({
    "valid": true
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  try {
    sourcemeta::blaze::TestCase::parse(
        document, tracker, std::filesystem::path{STUBS_PATH},
        sourcemeta::core::empty_pointer, STUB_POSITION);
    FAIL();
  } catch (const sourcemeta::blaze::TestParseError &error) {
    EXPECT_STREQ(
        error.what(),
        "Test case documents must contain a `data` or `dataPath` property");
  }
}

TEST(error_both_data_and_dataPath) {
  const auto input{R"JSON({
    "data": {},
    "dataPath": "data.json",
    "valid": true
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  try {
    sourcemeta::blaze::TestCase::parse(
        document, tracker, std::filesystem::path{STUBS_PATH},
        sourcemeta::core::empty_pointer, STUB_POSITION);
    FAIL();
  } catch (const sourcemeta::blaze::TestParseError &error) {
    EXPECT_STREQ(error.what(), "Test case documents must contain either a "
                               "`data` or `dataPath` property, but not both");
  }
}

TEST(error_dataPath_not_string) {
  const auto input{R"JSON({
    "dataPath": 123,
    "valid": true
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  try {
    sourcemeta::blaze::TestCase::parse(
        document, tracker, std::filesystem::path{STUBS_PATH},
        sourcemeta::core::empty_pointer, STUB_POSITION);
    FAIL();
  } catch (const sourcemeta::blaze::TestParseError &error) {
    EXPECT_STREQ(
        error.what(),
        "Test case documents must set the `dataPath` property to a string");
  }
}

TEST(error_description_not_string) {
  const auto input{R"JSON({
    "data": {},
    "description": 123,
    "valid": true
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  try {
    sourcemeta::blaze::TestCase::parse(
        document, tracker, std::filesystem::path{STUBS_PATH},
        sourcemeta::core::empty_pointer, STUB_POSITION);
    FAIL();
  } catch (const sourcemeta::blaze::TestParseError &error) {
    EXPECT_STREQ(error.what(),
                 "If you set a test case description, it must be a string");
  }
}

TEST(error_no_valid) {
  const auto input{R"JSON({
    "data": {}
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  try {
    sourcemeta::blaze::TestCase::parse(
        document, tracker, std::filesystem::path{STUBS_PATH},
        sourcemeta::core::empty_pointer, STUB_POSITION);
    FAIL();
  } catch (const sourcemeta::blaze::TestParseError &error) {
    EXPECT_STREQ(error.what(),
                 "Test case documents must contain a `valid` property");
  }
}

TEST(error_valid_not_boolean) {
  const auto input{R"JSON({
    "data": {},
    "valid": "true"
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));

  try {
    sourcemeta::blaze::TestCase::parse(
        document, tracker, std::filesystem::path{STUBS_PATH},
        sourcemeta::core::empty_pointer, STUB_POSITION);
    FAIL();
  } catch (const sourcemeta::blaze::TestParseError &error) {
    EXPECT_STREQ(error.what(),
                 "The test case document `valid` property must be a boolean");
  }
}

TEST(valid_with_inline_data_true) {
  const auto input{R"JSON({
    "data": { "foo": 1 },
    "valid": true
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestCase::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::empty_pointer, STUB_POSITION)};

  EXPECT_TRUE(result.description.empty());
  EXPECT_TRUE(result.valid);
  EXPECT_EQ(result.data,
            sourcemeta::core::parse_json(R"JSON({ "foo": 1 })JSON"));
  EXPECT_EQ(result.position, STUB_POSITION);
}

TEST(valid_with_inline_data_false) {
  const auto input{R"JSON({
    "data": { "foo": 1 },
    "valid": false
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestCase::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::empty_pointer, STUB_POSITION)};

  EXPECT_TRUE(result.description.empty());
  EXPECT_FALSE(result.valid);
  EXPECT_EQ(result.data,
            sourcemeta::core::parse_json(R"JSON({ "foo": 1 })JSON"));
  EXPECT_EQ(result.position, STUB_POSITION);
}

TEST(valid_with_description) {
  const auto input{R"JSON({
    "data": {},
    "description": "My test case",
    "valid": true
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestCase::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::empty_pointer, STUB_POSITION)};

  EXPECT_EQ(result.description, "My test case");
  EXPECT_TRUE(result.valid);
  EXPECT_EQ(result.position, STUB_POSITION);
}

TEST(valid_with_dataPath_json) {
  const auto input{R"JSON({
    "dataPath": "data.json",
    "valid": true
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestCase::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::empty_pointer, STUB_POSITION)};

  EXPECT_TRUE(result.description.empty());
  EXPECT_TRUE(result.valid);
  EXPECT_EQ(result.data,
            sourcemeta::core::parse_json(R"JSON({ "foo": "bar" })JSON"));
  EXPECT_EQ(result.position, STUB_POSITION);
}

TEST(valid_with_dataPath_yaml) {
  const auto input{R"JSON({
    "dataPath": "data.yaml",
    "valid": true
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestCase::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::empty_pointer, STUB_POSITION)};

  EXPECT_TRUE(result.description.empty());
  EXPECT_TRUE(result.valid);
  EXPECT_EQ(result.data,
            sourcemeta::core::parse_json(R"JSON({ "foo": "bar" })JSON"));
  EXPECT_EQ(result.position, STUB_POSITION);
}

TEST(valid_with_dataPath_and_description) {
  const auto input{R"JSON({
    "dataPath": "data.json",
    "description": "External data test",
    "valid": false
  })JSON"};

  sourcemeta::core::PointerPositionTracker tracker;
  sourcemeta::core::JSON document{nullptr};
  sourcemeta::core::parse_json(input, document, std::ref(tracker));
  const auto result{sourcemeta::blaze::TestCase::parse(
      document, tracker, std::filesystem::path{STUBS_PATH},
      sourcemeta::core::empty_pointer, STUB_POSITION)};

  EXPECT_EQ(result.description, "External data test");
  EXPECT_FALSE(result.valid);
  EXPECT_EQ(result.data,
            sourcemeta::core::parse_json(R"JSON({ "foo": "bar" })JSON"));
  EXPECT_EQ(result.position, STUB_POSITION);
}
