import { Schema } from "./expected";

const test1: Schema = {
  "x-foo": "hello"
};

const test2: Schema = {
  "x-foo": "hello",
  "x-bar": "world"
};

const test3: Schema = {
  "x-foo": "hello",
  other: "value"
};

const test4: Schema = {
  // @ts-expect-error
  "x-foo": 123
};
