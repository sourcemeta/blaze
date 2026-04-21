export type FlexibleRecordName = string;

export type FlexibleRecordCount = number;

export type FlexibleRecordAdditionalProperties = unknown;

export interface FlexibleRecord {
  "name": FlexibleRecordName;
  "count"?: FlexibleRecordCount;
  [key: string]: unknown | undefined;
}
