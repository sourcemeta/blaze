import { Document } from "./expected";

// Valid: what `contains` asks of an array says nothing about what it holds
const items: Document = [ 1, "text", null ];

// Valid: an array of anything includes an empty one
const empty: Document = [];

// Invalid: the document still says an instance is an array
// @ts-expect-error
const text: Document = "text";
