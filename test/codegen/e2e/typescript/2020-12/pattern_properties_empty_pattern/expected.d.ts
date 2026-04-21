export type EmptyPatternName = string;

export type EmptyPattern = number;

export type EmptyPatternAdditionalProperties = never;

export interface _EmptyPattern {
  "name"?: EmptyPatternName;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    EmptyPatternName |
    EmptyPattern |
    undefined;
}
