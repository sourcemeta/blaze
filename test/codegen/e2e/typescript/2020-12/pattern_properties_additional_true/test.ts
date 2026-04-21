import { OpenExt } from "./expected";

const test1: OpenExt = {
  name: "hello",
  "x-custom": "value",
  other: 42
};

const test2: OpenExt = {
  name: "hello",
  // @ts-expect-error
  "x-custom": 123
};
