import { Hybrid } from "./expected";

// All features together
const test1: Hybrid = {
  name: "hello",
  age: 30,
  "x-custom": "extension",
  "123_id": 42,
  flag: true
};

// Required name only
const test2: Hybrid = {
  name: "hello"
};

// Missing required name
// @ts-expect-error
const test3: Hybrid = {
  age: 30
};

// Prefix pattern enforced: x- must be string, not number
const test4: Hybrid = {
  name: "hello",
  // @ts-expect-error
  "x-custom": 42
};

// Array is not in the union
const test5: Hybrid = {
  name: "hello",
  // @ts-expect-error
  extra: [ 1, 2, 3 ]
};

// Additional property with boolean (additionalProperties type)
const test6: Hybrid = {
  name: "hello",
  flag: true
};

// JSON Schema would reject this (additionalProperties is boolean, not
// number), but TypeScript allows it because the [key: string] union must
// include all member and pattern types (number from "age" and the non-prefix
// pattern). The generated types are always a superset of what JSON Schema
// allows, never a subset.
const test7: Hybrid = {
  name: "hello",
  extra: 42
};

// Template literal takes priority over permissive [key: string] union:
// boolean is in the union but x- keys must be string
const test8: Hybrid = {
  name: "hello",
  // @ts-expect-error
  "x-custom": true
};
