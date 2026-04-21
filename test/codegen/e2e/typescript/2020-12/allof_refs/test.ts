import { Person } from "./expected";

// Valid: satisfies both $ref branches
const valid: Person = {
  name: "Alice",
  age: 30
};

// Invalid: missing age
// @ts-expect-error
const missingAge: Person = {
  name: "Bob"
};

// Invalid: missing name
// @ts-expect-error
const missingName: Person = {
  age: 25
};
