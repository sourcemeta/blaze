export type FallbackName = string;

export type FallbackAZ_id = number;

export interface Fallback {
  "name"?: FallbackName;
  [key: string]: unknown | undefined;
}
