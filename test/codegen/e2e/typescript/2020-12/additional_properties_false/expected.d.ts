export type StrictPersonName = string;

export type StrictPersonAge = number;

export type StrictPersonAdditionalProperties = never;

export interface StrictPerson {
  "name": StrictPersonName;
  "age"?: StrictPersonAge;
}
