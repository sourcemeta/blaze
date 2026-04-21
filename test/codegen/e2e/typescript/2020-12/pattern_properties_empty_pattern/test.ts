import { _EmptyPattern } from "./expected";

// Empty regex matches everything, so all keys go through [key: string]
// union (string | number | undefined)
const test1: _EmptyPattern = {
  name: "hello",
  anything: 42
};

const test2: _EmptyPattern = {
  name: "hello",
  anything: "also valid"
};

// Boolean is not in the union
const test3: _EmptyPattern = {
  name: "hello",
  // @ts-expect-error
  flag: true
};
