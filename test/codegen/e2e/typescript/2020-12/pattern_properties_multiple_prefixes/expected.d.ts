export type MultiPatternX = string;

export type MultiPatternData = number;

export interface MultiPattern {
  [key: `x-${string}`]: MultiPatternX;
  [key: `data-${string}`]: MultiPatternData;
  [key: string]: unknown | undefined;
}
