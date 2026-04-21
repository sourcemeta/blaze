import {
  Schema,
  SchemaSimpleEnum,
  SchemaMixedEnum,
  SchemaEnumWithObject,
  SchemaEnumWithArray
} from "./expected";


// Valid: simple string enum values
const simple1: SchemaSimpleEnum = "foo";
const simple2: SchemaSimpleEnum = "bar";
const simple3: SchemaSimpleEnum = "baz";

// Invalid: wrong string for simple enum
// @ts-expect-error - must be "foo" | "bar" | "baz"
const simpleInvalid: SchemaSimpleEnum = "invalid";

// Valid: mixed enum values
const mixed1: SchemaMixedEnum = "active";
const mixed2: SchemaMixedEnum = 42;
const mixed3: SchemaMixedEnum = true;
const mixed4: SchemaMixedEnum = null;

// Invalid: wrong value for mixed enum
// @ts-expect-error - must be "active" | 42 | true | null
const mixedInvalid: SchemaMixedEnum = "inactive";

// Valid: enum with object value
const withObj1: SchemaEnumWithObject = "simple";
const withObj2: SchemaEnumWithObject = { type: "complex", value: 123 };

// Invalid: completely wrong type for enum with object
// @ts-expect-error - must be "simple" or the exact object literal
const withObjInvalid: SchemaEnumWithObject = "wrong";

// Valid: enum with array value
const withArr1: SchemaEnumWithArray = 1;
const withArr2: SchemaEnumWithArray = [ 1, 2, 3 ];

// Invalid: wrong array
// @ts-expect-error - must be exactly [1, 2, 3]
const withArrInvalid: SchemaEnumWithArray = [ 1, 2 ];

// Valid: full schema object
const fullSchema: Schema = {
  simpleEnum: "foo",
  mixedEnum: 42,
  enumWithObject: { type: "complex", value: 123 },
  enumWithArray: [ 1, 2, 3 ]
};

// Valid: partial schema
const partialSchema: Schema = {
  simpleEnum: "bar"
};

// Valid: empty schema (all optional)
const emptySchema: Schema = {};
