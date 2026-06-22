export type SchemaSimpleEnum = "foo" | "bar" | "baz";

export type SchemaMixedEnum_3 = null;

export type SchemaMixedEnum_2 = true;

export type SchemaMixedEnum_1 = 42;

export type SchemaMixedEnum_0 = "active";

export type SchemaMixedEnum =
  SchemaMixedEnum_0 |
  SchemaMixedEnum_1 |
  SchemaMixedEnum_2 |
  SchemaMixedEnum_3;

export type SchemaEnumWithObject_1 = {
  "type": "complex",
  "value": 123
};

export type SchemaEnumWithObject_0 = "simple";

export type SchemaEnumWithObject =
  SchemaEnumWithObject_0 |
  SchemaEnumWithObject_1;

export type SchemaEnumWithArray_1 = [ 1, 2, 3 ];

export type SchemaEnumWithArray_0 = 1;

export type SchemaEnumWithArray =
  SchemaEnumWithArray_0 |
  SchemaEnumWithArray_1;

export type SchemaAdditionalProperties = never;

export interface Schema {
  "simpleEnum"?: SchemaSimpleEnum;
  "mixedEnum"?: SchemaMixedEnum;
  "enumWithObject"?: SchemaEnumWithObject;
  "enumWithArray"?: SchemaEnumWithArray;
}
