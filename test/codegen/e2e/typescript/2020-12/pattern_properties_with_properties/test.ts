import { Extensible } from "./expected";

const test1: Extensible = {
  name: "hello"
};

const test2: Extensible = {
  name: "hello",
  "x-custom": "value"
};

const test3: Extensible = {
  // @ts-expect-error
  name: 123
};

const test4: Extensible = {
  name: "hello",
  // @ts-expect-error
  "x-custom": 42
};

// Missing required property
// @ts-expect-error
const test5: Extensible = {
  "x-custom": "value"
};
