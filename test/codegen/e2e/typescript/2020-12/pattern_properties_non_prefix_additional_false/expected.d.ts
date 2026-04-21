export type StrictFallbackName = string;

export type StrictFallbackAz_id = number;

export type StrictFallbackAdditionalProperties = never;

export interface StrictFallback {
  "name"?: StrictFallbackName;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    StrictFallbackName |
    StrictFallbackAz_id |
    undefined;
}
