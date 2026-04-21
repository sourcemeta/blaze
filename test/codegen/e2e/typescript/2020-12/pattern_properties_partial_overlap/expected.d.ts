export type PartialId = number;

export type PartialY = number;

export type PartialXinternal = boolean;

export type PartialX = string;

export type PartialAdditionalProperties = never;

export interface Partial {
  "id": PartialId;
  [key: `x-${string}`]: PartialX;
  [key: `x-internal-${string}`]: PartialXinternal & PartialX;
  [key: `y-${string}`]: PartialY;
}
