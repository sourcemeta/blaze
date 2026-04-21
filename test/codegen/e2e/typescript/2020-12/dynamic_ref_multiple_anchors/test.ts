import { Root } from "./expected";

const strings: Root = [ "hello", "world" ];

// JSON Schema would reject this (the dynamic scope resolves to the root's
// string anchor at runtime, so only strings are valid). But the codegen emits
// a union of ALL possible dynamic anchor targets (string | number), because
// the actual target depends on the runtime evaluation path. The generated
// types are always a superset of what JSON Schema allows, never a subset.
const numbers: Root = [ 1, 2, 3 ];

const mixed: Root = [ "hello", 42 ];

const empty: Root = [];

// @ts-expect-error
const notArray: Root = "hello";

// Boolean is not in the union (string | number)
// @ts-expect-error
const invalidItem: Root = [ true ];

// Null is not in the union
// @ts-expect-error
const nullItem: Root = [ null ];

// Object is not in the union
// @ts-expect-error
const objectItem: Root = [ { key: "value" } ];
