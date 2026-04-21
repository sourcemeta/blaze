import { FlexibleRecord } from "./expected";

// Valid: required name only
const record1: FlexibleRecord = {
  name: "test"
};

// Valid: name and optional count
const record2: FlexibleRecord = {
  name: "test",
  count: 42
};

// Valid: with string additional property
const record3: FlexibleRecord = {
  name: "test",
  extra: "some string"
};

// Valid: with number additional property
const record4: FlexibleRecord = {
  name: "test",
  extra: 123
};

// Valid: with boolean additional property
const record5: FlexibleRecord = {
  name: "test",
  flag: true
};

// Valid: with null additional property
const record6: FlexibleRecord = {
  name: "test",
  nothing: null
};

// Valid: with array additional property
const record7: FlexibleRecord = {
  name: "test",
  items: [ 1, 2, 3 ]
};

// Valid: with object additional property
const record8: FlexibleRecord = {
  name: "test",
  nested: { foo: "bar" }
};

// Valid: multiple additional properties of different types
const record9: FlexibleRecord = {
  name: "test",
  count: 10,
  label: "my label",
  active: false,
  data: [ "a", "b" ]
};

// Invalid: name must be string
const record10: FlexibleRecord = {
  // @ts-expect-error
  name: 123
};

// Invalid: missing required name
// @ts-expect-error
const record11: FlexibleRecord = {
  count: 5
};
