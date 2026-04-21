import { SameType } from "./expected";

// x-data-* satisfies both ^x- and ^x-data-, both string, so string works
const test1: SameType = {
  "x-data-id": "hello"
};

// Non-overlapping x- key
const test2: SameType = {
  "x-foo": "world"
};

// Both together
const test3: SameType = {
  "x-foo": "hello",
  "x-data-id": "world"
};

// Wrong type on overlapping key
const test4: SameType = {
  // @ts-expect-error
  "x-data-id": 42
};

// Wrong type on non-overlapping key
const test5: SameType = {
  // @ts-expect-error
  "x-foo": 42
};
