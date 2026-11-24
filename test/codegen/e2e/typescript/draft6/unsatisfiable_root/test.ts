import { Document } from "./expected";

// Invalid: nothing satisfies a document no instance satisfies
// @ts-expect-error
const text: Document = "text";

// @ts-expect-error
const number: Document = 1;
