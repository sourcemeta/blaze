import { NonPrefix } from "./expected";

// Any key, any value (falls back to [key: string]: unknown)
const test1: NonPrefix = {
  "user_id": 42
};

const test2: NonPrefix = {
  "user_id": 42,
  other: "hello"
};

const test3: NonPrefix = {};
