import { Wrapper } from "./expected";

// Valid: single-element allOf acts as the element itself
const valid: Wrapper = {
  value: "hello"
};

// Invalid: missing required value
// @ts-expect-error
const missingValue: Wrapper = {};
