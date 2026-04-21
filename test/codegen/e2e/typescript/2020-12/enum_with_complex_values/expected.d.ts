export type SchemaSimpleEnum = "foo" | "bar" | "baz";

export type SchemaMixedEnum = "active" | 42 | true | null;

export type SchemaEnumWithObject = "simple" | {
  "type": "complex",
  "value": 123
};

export type SchemaEnumWithArray = 1 | [ 1, 2, 3 ];

export type SchemaAdditionalProperties = never;

export interface Schema {
  "simpleEnum"?: SchemaSimpleEnum;
  "mixedEnum"?: SchemaMixedEnum;
  "enumWithObject"?: SchemaEnumWithObject;
  "enumWithArray"?: SchemaEnumWithArray;
}
