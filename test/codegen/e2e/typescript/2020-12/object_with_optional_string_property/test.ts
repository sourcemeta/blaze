import { MyObject } from "./expected";

// Valid: empty object
const empty: MyObject = {};

// Valid: with optional foo
const withFoo: MyObject = {
  foo: "hello"
};

// Invalid: foo must be string
const invalidFoo: MyObject = {
  // @ts-expect-error
  foo: 123
};

// Valid: with extra properties (additionalProperties not set means any allowed)
const withExtra: MyObject = {
  foo: "hello",
  bar: "extra"
};

// Assignment from variable should work (TypeScript allows this)
const extraData = { foo: "hello", bar: "extra", count: 42 };
const assignedFromVariable: MyObject = extraData;
