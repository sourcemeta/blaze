export type ExtensibleName = string;

export type ExtensibleX = string;

export interface Extensible {
  "name": ExtensibleName;
  [key: `x-${string}`]: ExtensibleX;
  [key: string]: unknown | undefined;
}
