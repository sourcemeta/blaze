import { Node } from "./expected";

const valid: Node = { name: "hello", value: 42 };

const nameOnly: Node = { name: "hello" };

// @ts-expect-error
const missingName: Node = { value: 42 };

// @ts-expect-error
const wrongNameType: Node = { name: 42 };

// additionalProperties: false
const extra: Node = {
  name: "hello",
  // @ts-expect-error
  other: "nope"
};
