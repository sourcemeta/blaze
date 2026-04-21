import { StrictPerson } from "./expected";

// Valid: required name only
const person1: StrictPerson = {
  name: "John Doe"
};

// Valid: name and optional age
const person2: StrictPerson = {
  name: "Jane Doe",
  age: 25
};

// Invalid: name must be string
const person3: StrictPerson = {
  // @ts-expect-error
  name: 123
};

// Invalid: age must be number
const person4: StrictPerson = {
  name: "John",
  // @ts-expect-error
  age: "twenty"
};

// Invalid: missing required name
// @ts-expect-error
const person5: StrictPerson = {
  age: 30
};

// Invalid: extra string property should be rejected
const person6: StrictPerson = {
  name: "John",
  // @ts-expect-error
  nickname: "Johnny"
};

// Invalid: extra number property should be rejected
const person7: StrictPerson = {
  name: "John",
  // @ts-expect-error
  score: 100
};

// Invalid: extra boolean property should be rejected
const person8: StrictPerson = {
  name: "John",
  // @ts-expect-error
  active: true
};

// Invalid: extra null property should be rejected
const person9: StrictPerson = {
  name: "John",
  // @ts-expect-error
  nothing: null
};

// Invalid: extra array property should be rejected
const person10: StrictPerson = {
  name: "John",
  // @ts-expect-error
  tags: [ "a", "b" ]
};

// Invalid: extra object property should be rejected
const person11: StrictPerson = {
  name: "John",
  // @ts-expect-error
  metadata: { foo: "bar" }
};
