export type EmptyEnumName = string;

export type EmptyEnumImpossible = never;

export type EmptyEnumAdditionalProperties = never;

export interface EmptyEnum {
  "name": EmptyEnumName;
  "impossible"?: EmptyEnumImpossible;
}
