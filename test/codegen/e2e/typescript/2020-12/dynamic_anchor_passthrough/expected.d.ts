export type NodeValue = number;

export type NodeName = string;

export type NodeAdditionalProperties = never;

export interface Node {
  "name": NodeName;
  "value"?: NodeValue;
}
