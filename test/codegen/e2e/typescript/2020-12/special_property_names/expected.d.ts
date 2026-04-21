export type SchemaSayhello = string;

export type SchemaPathtofile = string;

export type SchemaMypropertyname = string;

export type SchemaLine1line2 = string;

export type SchemaCol1col2 = string;

export type SchemaClass = string;

export type Schema_123abc = string;

export type Schema$specialchars = string;

export type SchemaAdditionalProperties = never;

export interface Schema {
  "say \"hello\""?: SchemaSayhello;
  "path\\to\\file"?: SchemaPathtofile;
  "line1\nline2"?: SchemaLine1line2;
  "col1\tcol2"?: SchemaCol1col2;
  "$special@chars"?: Schema$specialchars;
  "my property name"?: SchemaMypropertyname;
  "123abc"?: Schema_123abc;
  "class"?: SchemaClass;
}
