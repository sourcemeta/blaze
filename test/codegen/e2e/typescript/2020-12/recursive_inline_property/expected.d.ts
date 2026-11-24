export type ChainHeadValue = string;

export type ChainHeadNext = ChainHead;

export type ChainHeadAdditionalProperties = never;

export interface ChainHead {
  "value": ChainHeadValue;
  "next"?: ChainHeadNext;
}

export type ChainAdditionalProperties = never;

export interface Chain {
  "head": ChainHead;
}
