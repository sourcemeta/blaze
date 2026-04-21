import { AllOfIntersection } from "./expected";

// Valid: satisfies both branches
const valid: AllOfIntersection = {
  name: "Alice",
  age: 30
};

// Invalid: missing age from second branch
// @ts-expect-error
const missingAge: AllOfIntersection = {
  name: "Bob"
};

// Invalid: missing name from first branch
// @ts-expect-error
const missingName: AllOfIntersection = {
  age: 25
};
