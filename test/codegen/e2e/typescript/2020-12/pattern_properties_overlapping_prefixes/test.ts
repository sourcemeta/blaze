import { Overlap } from "./expected";

// Non-overlapping: only matches ^x-
const test1: Overlap = {
  "x-foo": "hello"
};

// Overlapping: matches both ^x- (string) and ^x-data- (number),
// so no value can satisfy both, which is correct per JSON Schema
const test2: Overlap = {
  // @ts-expect-error
  "x-data-id": 42
};

const test3: Overlap = {
  // @ts-expect-error
  "x-data-id": "hello"
};
