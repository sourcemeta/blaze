export type SameTypeXData = string;

export type SameTypeX = string;

export type SameTypeAdditionalProperties = never;

export interface SameType {
  [key: `x-${string}`]: SameTypeX;
  [key: `x-data-${string}`]: SameTypeXData & SameTypeX;
}
