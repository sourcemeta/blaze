export type MixedFallbackX = string;

export type MixedFallback_09 = number;

export interface MixedFallback {
  [key: `x-${string}`]: MixedFallbackX;
  [key: string]: unknown | undefined;
}
