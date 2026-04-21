import { StrictExt } from "./expected";

const test1: StrictExt = {
  name: "hello"
};

const test2: StrictExt = {
  name: "hello",
  "x-custom": "value"
};

// Wrong type for pattern property
const test3: StrictExt = {
  name: "hello",
  // @ts-expect-error
  "x-custom": 42
};

// Non-matching key should be rejected (additionalProperties: false)
const test4: StrictExt = {
  name: "hello",
  // @ts-expect-error
  other: "value"
};

// Edge case: key is exactly the prefix with empty suffix
const test5: StrictExt = {
  name: "hello",
  "x-": "value"
};
