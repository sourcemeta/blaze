export type OverlapXData = number;

export type OverlapX = string;

export type OverlapAdditionalProperties = never;

export interface Overlap {
  [key: `x-${string}`]: OverlapX;
  [key: `x-data-${string}`]: OverlapXData & OverlapX;
}
