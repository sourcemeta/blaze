export type MixedName = string;

export type MixedX = number;

export type MixedAdditionalProperties = boolean;

export interface Mixed {
  "name"?: MixedName;
  [key: `x-${string}`]: MixedX;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    MixedName |
    MixedX |
    MixedAdditionalProperties |
    undefined;
}
