import { VocabTest } from "./expected";

// additionalProperties: false

// Valid: minimal required fields
const minimal: VocabTest = {
  name: "test",
  value: 42
};

// Valid: all fields
const complete: VocabTest = {
  name: "test",
  value: 42,
  optional: true
};

// Valid: optional as false
const optionalFalse: VocabTest = {
  name: "test",
  value: 42,
  optional: false
};

// Invalid: missing required name
// @ts-expect-error
const missingName: VocabTest = {
  value: 42
};

// Invalid: missing required value
// @ts-expect-error
const missingValue: VocabTest = {
  name: "test"
};

// Invalid: name must be string
const invalidName: VocabTest = {
  // @ts-expect-error
  name: 123,
  value: 42
};

// Invalid: value must be number
const invalidValue: VocabTest = {
  name: "test",
  // @ts-expect-error
  value: "42"
};

// Invalid: optional must be boolean
const invalidOptional: VocabTest = {
  name: "test",
  value: 42,
  // @ts-expect-error
  optional: "yes"
};

// Invalid: extra property (additionalProperties: false)
const invalidExtra: VocabTest = {
  name: "test",
  value: 42,
  // @ts-expect-error
  extra: "not allowed"
};
