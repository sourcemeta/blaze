import { Person } from "./expected";

const test1: Person = {
  name: "John Doe"
};

const test2: Person = {
  // @ts-expect-error
  name: 123
};

const test3: Person = {
  name: "John Doe",
  age: 30
};

const test4: Person = {
  name: "John Doe",
  age: 30,
  extra: "foo"
};

// @ts-expect-error name is required
const test5: Person = {
  extra: "foo"
};

const test6: Person = {
  name: "John Doe",
  age: 30,
  // @ts-expect-error
  extra: true
};
