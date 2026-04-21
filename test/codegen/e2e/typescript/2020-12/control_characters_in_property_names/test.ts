import { Test } from "./expected";

// Valid: object with control characters in property names
const validObject: Test = {
  "normal": "hello",
  "with\bbackspace": "value1",
  "with\fformfeed": "value2",
  "with\u0000null": "value3",
  "with\u0001soh": "value4",
  "with\u001fus": "value5"
};

// Valid: empty object (all properties are optional)
const emptyObject: Test = {};

// Valid: partial object
const partialObject: Test = {
  "normal": "just normal"
};

// Invalid: extra property not allowed
const extraProp: Test = {
  "normal": "hello",
  // @ts-expect-error - extra property not allowed
  "extra": "not allowed"
};

// Invalid: wrong type for property
const wrongType: Test = {
  // @ts-expect-error - must be string
  "normal": 123
};
