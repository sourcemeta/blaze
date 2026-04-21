export type StrictExtName = string;

export type StrictExtX = string;

export type StrictExtAdditionalProperties = never;

export interface StrictExt {
  "name"?: StrictExtName;
  [key: `x-${string}`]: StrictExtX;
}
