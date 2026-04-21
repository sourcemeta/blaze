import { Mixed } from "./expected";

const test1: Mixed = {
  name: "hello",
  "x-count": 42,
  extra: true
};

// Wrong type on pattern property (string instead of number)
const test2: Mixed = {
  name: "hello",
  // @ts-expect-error
  "x-count": "not a number"
};

// Template literal signature takes priority over the permissive
// [key: string] union, so boolean is rejected even though the
// union includes boolean
const test3: Mixed = {
  name: "hello",
  // @ts-expect-error
  "x-count": true
};

// Additional property with wrong type (array is not in the union)
const test4: Mixed = {
  name: "hello",
  // @ts-expect-error
  extra: [ 1, 2, 3 ]
};
