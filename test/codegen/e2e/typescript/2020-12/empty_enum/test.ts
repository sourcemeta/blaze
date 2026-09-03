import { EmptyEnum, EmptyEnumImpossible } from "./expected";


// Valid: the property an empty enumeration describes can only be left out
const valid: EmptyEnum = {
  name: "foo"
};

// Valid: an absent property reads as undefined
const absent: EmptyEnum = {
  name: "foo",
  impossible: undefined
};

// Invalid: no value at all satisfies an empty enumeration
const withString: EmptyEnum = {
  name: "foo",
  // @ts-expect-error - nothing can be assigned to never
  impossible: "bar"
};

const withNull: EmptyEnum = {
  name: "foo",
  // @ts-expect-error - nothing can be assigned to never
  impossible: null
};

const withNumber: EmptyEnum = {
  name: "foo",
  // @ts-expect-error - nothing can be assigned to never
  impossible: 0
};

// Invalid: name is required
// @ts-expect-error - name is required
const missingName: EmptyEnum = {};

// Invalid: extra property (additionalProperties: false)
const extraProperty: EmptyEnum = {
  name: "foo",
  // @ts-expect-error - extra property not allowed
  extra: "not allowed"
};

// Test the standalone impossible type
// @ts-expect-error - nothing can be assigned to never
const impossible: EmptyEnumImpossible = "anything";
