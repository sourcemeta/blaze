export type StrictFallbackName = string;

export type StrictFallbackAZ_id = number;

export type StrictFallbackAdditionalProperties = never;

export interface StrictFallback {
  "name"?: StrictFallbackName;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    StrictFallbackName |
    StrictFallbackAZ_id |
    undefined;
}
