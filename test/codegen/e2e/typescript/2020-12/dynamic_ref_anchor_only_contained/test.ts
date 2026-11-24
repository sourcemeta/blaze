import { Root } from "./expected";

// Valid: the dynamic reference stands for every anchor of its name, and the
// one reached only by `contains` is among them
const leaf: Root = { child: "text" };

// Valid: the document carries that anchor too
const nested: Root = { child: { child: "text" } };

// Valid: what `contains` asks of the array says nothing about what it holds
const list: Root = { list: [ 1, "text", null ] };

// Invalid: a number is neither anchor
// @ts-expect-error
const number: Root = { child: 1 };

// Invalid: the document says an instance is an object
// @ts-expect-error
const text: Root = "text";
