import { Fallback } from "./expected";

const test1: Fallback = {
  name: "hello",
  "user_id": 42
};

// Name wrong type
const test2: Fallback = {
  // @ts-expect-error
  name: 123
};

// Any extra key is allowed (additionalProperties defaults to true)
const test3: Fallback = {
  name: "hello",
  extra: true
};
