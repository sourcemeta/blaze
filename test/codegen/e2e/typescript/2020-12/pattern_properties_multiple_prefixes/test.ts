import { MultiPattern } from "./expected";

const test1: MultiPattern = {
  "x-foo": "hello"
};

const test2: MultiPattern = {
  "data-id": 42
};

const test3: MultiPattern = {
  "x-foo": "hello",
  "data-id": 42
};

const test4: MultiPattern = {
  // @ts-expect-error
  "x-foo": 123
};

const test5: MultiPattern = {
  // @ts-expect-error
  "data-id": "not a number"
};
