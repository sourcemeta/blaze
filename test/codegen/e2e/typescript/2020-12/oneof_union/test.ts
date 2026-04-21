import { OneOfTest } from "./expected";

// Valid: value as string
const withString: OneOfTest = {
  value: "hello"
};

// Valid: value as integer
const withInteger: OneOfTest = {
  value: 42
};

// Valid: value as boolean
const withBoolean: OneOfTest = {
  value: true
};

// Valid: with status from first enum
const withPendingStatus: OneOfTest = {
  value: "test",
  status: "pending"
};

// Valid: with status from second enum
const withCompletedStatus: OneOfTest = {
  value: 123,
  status: "completed"
};

// Invalid: value cannot be null
const invalidNull: OneOfTest = {
  // @ts-expect-error
  value: null
};

// Invalid: value cannot be object
const invalidObject: OneOfTest = {
  // @ts-expect-error
  value: { foo: "bar" }
};

// Invalid: status must be one of the allowed values
const invalidStatus: OneOfTest = {
  value: "test",
  // @ts-expect-error
  status: "unknown"
};

// Invalid: missing required value
// @ts-expect-error
const missingValue: OneOfTest = {
  status: "active"
};
