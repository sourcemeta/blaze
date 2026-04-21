import { MixedFallback } from "./expected";

// Prefix pattern enforced: x- key must be string
const test1: MixedFallback = {
  "x-foo": "hello"
};

// Prefix pattern enforced even with [key: string]: unknown fallback
const test2: MixedFallback = {
  // @ts-expect-error
  "x-foo": 123
};

// Non-prefix pattern falls back to unknown, so any value works
const test3: MixedFallback = {
  "123": 42
};

const test4: MixedFallback = {
  "123": "also fine"
};

// Mixed together
const test5: MixedFallback = {
  "x-custom": "hello",
  "456": 99,
  other: true
};
