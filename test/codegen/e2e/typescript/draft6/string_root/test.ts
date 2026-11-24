import { Document } from "./expected";

// Valid: the document says an instance is a string
const text: Document = "text";

// Invalid: a number is not a string
// @ts-expect-error
const number: Document = 1;
