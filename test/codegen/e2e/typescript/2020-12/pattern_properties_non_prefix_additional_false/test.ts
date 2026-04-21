import { StrictFallback } from "./expected";

const test1: StrictFallback = {
  name: "hello",
  "user_id": 42
};

// JSON Schema would reject this (additionalProperties: false and "other"
// does not match the pattern), but TypeScript allows it because the
// [key: string] union must include all member types (string from "name"),
// so any string value passes. The generated types are always a superset
// of what JSON Schema allows, never a subset.
const test2: StrictFallback = {
  name: "hello",
  other: "also string"
};

// Boolean is not in the union (string | number | undefined)
const test3: StrictFallback = {
  name: "hello",
  // @ts-expect-error
  flag: true
};

// Array is not in the union
const test4: StrictFallback = {
  name: "hello",
  // @ts-expect-error
  items: [ 1, 2, 3 ]
};
