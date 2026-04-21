export type PersonName = string;

export type PersonAge = number;

export type PersonAdditionalProperties = string;

export interface Person {
  "name": PersonName;
  "age"?: PersonAge;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    PersonName |
    PersonAge |
    PersonAdditionalProperties |
    undefined;
}
