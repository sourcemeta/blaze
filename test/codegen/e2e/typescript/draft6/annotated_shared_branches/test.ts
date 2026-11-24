import { Document } from "./expected";

// Valid: both branches of the choice say an instance is a string, and what
// stands beside them says nothing about what one looks like
const text: Document = "text";

// Invalid: a number is neither branch
// @ts-expect-error
const number: Document = 1;
