export type SchemaSayHello = string;

export type SchemaPathToFile = string;

export type SchemaMyPropertyName = string;

export type SchemaLine1Line2 = string;

export type SchemaCol1Col2 = string;

export type SchemaClass = string;

export type Schema_123abc = string;

export type Schema$specialChars = string;

export type SchemaAdditionalProperties = never;

export interface Schema {
  "say \"hello\""?: SchemaSayHello;
  "path\\to\\file"?: SchemaPathToFile;
  "line1\nline2"?: SchemaLine1Line2;
  "col1\tcol2"?: SchemaCol1Col2;
  "$special@chars"?: Schema$specialChars;
  "my property name"?: SchemaMyPropertyName;
  "123abc"?: Schema_123abc;
  "class"?: SchemaClass;
}
