export type OverlapXdata = number;

export type OverlapX = string;

export type OverlapAdditionalProperties = never;

export interface Overlap {
  [key: `x-${string}`]: OverlapX;
  [key: `x-data-${string}`]: OverlapXdata & OverlapX;
}
