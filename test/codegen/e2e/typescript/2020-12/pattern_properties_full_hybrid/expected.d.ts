export type HybridName = string;

export type HybridAge = number;

export type HybridX = string;

export type Hybrid_09_id = number;

export type HybridAdditionalProperties = boolean;

export interface Hybrid {
  "name": HybridName;
  "age"?: HybridAge;
  [key: `x-${string}`]: HybridX;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    HybridName |
    HybridAge |
    HybridX |
    Hybrid_09_id |
    HybridAdditionalProperties |
    undefined;
}
