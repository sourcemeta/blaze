export type SchemaX = string;

export interface Schema {
  [key: `x-${string}`]: SchemaX;
  [key: string]: unknown | undefined;
}
