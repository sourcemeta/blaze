import { ConstTest, ConstTestNested } from "./expected";


// Valid: all required fields with exact const values
const valid: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  nothing: null
};

// Valid: with optional fields
const complete: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  nothing: null,
  optionalFlag: false,
  nested: {
    fixedValue: "fixed",
    fixedNumber: 100
  }
};

// Valid: nested with partial fields (all are optional in nested)
const partialNested: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  nothing: null,
  nested: {}
};

// Invalid: version must be exactly "1.0.0"
const invalidVersion: ConstTest = {
  // @ts-expect-error - version must be literal "1.0.0"
  version: "2.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  nothing: null
};

// Invalid: enabled must be exactly true
const invalidEnabled: ConstTest = {
  version: "1.0.0",
  // @ts-expect-error - enabled must be literal true
  enabled: false,
  mode: "production",
  count: 42,
  nothing: null
};

// Invalid: mode must be exactly "production"
const invalidMode: ConstTest = {
  version: "1.0.0",
  enabled: true,
  // @ts-expect-error - mode must be literal "production"
  mode: "development",
  count: 42,
  nothing: null
};

// Invalid: count must be exactly 42
const invalidCount: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  // @ts-expect-error - count must be literal 42
  count: 100,
  nothing: null
};

// Invalid: nothing must be exactly null (not string)
const invalidNothingString: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  // @ts-expect-error
  nothing: "not null"
};

const invalidNothingUndefined: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  // @ts-expect-error
  nothing: undefined
};

// Invalid: optionalFlag must be exactly false
const invalidOptionalFlag: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  nothing: null,
  // @ts-expect-error - optionalFlag must be literal false
  optionalFlag: true
};

// Invalid: nested.fixedValue must be exactly "fixed"
const invalidNestedValue: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  nothing: null,
  nested: {
    // @ts-expect-error - fixedValue must be literal "fixed"
    fixedValue: "other"
  }
};

// Invalid: nested.fixedNumber must be exactly 100
const invalidNestedNumber: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  nothing: null,
  nested: {
    // @ts-expect-error - fixedNumber must be literal 100
    fixedNumber: 200
  }
};

// Invalid: missing required field
// @ts-expect-error - version is required
const missingVersion: ConstTest = {
  enabled: true,
  mode: "production",
  count: 42,
  nothing: null
};

// Invalid: extra property (additionalProperties: false)
const extraProperty: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  nothing: null,
  // @ts-expect-error - extra property not allowed
  extra: "not allowed"
};

// Invalid: extra property on nested (additionalProperties: false)
const nestedExtraProperty: ConstTest = {
  version: "1.0.0",
  enabled: true,
  mode: "production",
  count: 42,
  nothing: null,
  nested: {
    fixedValue: "fixed",
    // @ts-expect-error - extra property not allowed
    extra: "not allowed"
  }
};

// Test standalone nested type
const nested1: ConstTestNested = {};
const nested2: ConstTestNested = { fixedValue: "fixed" };
const nested3: ConstTestNested = { fixedNumber: 100 };
const nested4: ConstTestNested = { fixedValue: "fixed", fixedNumber: 100 };
// @ts-expect-error - fixedValue must be "fixed"
const invalidNested: ConstTestNested = { fixedValue: "wrong" };
