import { Partial } from "./expected";

// Named property only
const test1: Partial = {
  id: 1
};

// Non-overlapping x- prefix (string)
const test2: Partial = {
  id: 1,
  "x-foo": "hello"
};

// Non-overlapping y- prefix (integer)
const test3: Partial = {
  id: 1,
  "y-count": 42
};

// Overlapping x-internal- matches both ^x- and ^x-internal-,
// boolean & string = never, so no value satisfies both
const test4: Partial = {
  id: 1,
  // @ts-expect-error
  "x-internal-debug": true
};

const test5: Partial = {
  id: 1,
  // @ts-expect-error
  "x-internal-debug": "hello"
};

// Wrong type for x- prefix
const test6: Partial = {
  id: 1,
  // @ts-expect-error
  "x-foo": 42
};

// Wrong type for y- prefix
const test7: Partial = {
  id: 1,
  // @ts-expect-error
  "y-count": "not a number"
};

// Non-matching key rejected (additionalProperties: false)
const test8: Partial = {
  id: 1,
  // @ts-expect-error
  other: "value"
};
