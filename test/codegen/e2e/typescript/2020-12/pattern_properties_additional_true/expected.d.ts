export type OpenExtName = string;

export type OpenExtX = string;

export type OpenExtAdditionalProperties = unknown;

export interface OpenExt {
  "name"?: OpenExtName;
  [key: `x-${string}`]: OpenExtX;
  [key: string]: unknown | undefined;
}
