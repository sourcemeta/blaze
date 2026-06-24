export type TestWithUs = string;

export type TestWithFormfeed = string;

export type TestWithBackspace = string;

export type TestWithSoh = string;

export type TestWithNull = string;

export type TestNormal = string;

export type TestAdditionalProperties = never;

export interface Test {
  "normal"?: TestNormal;
  "with\bbackspace"?: TestWithBackspace;
  "with\fformfeed"?: TestWithFormfeed;
  "with\u0000null"?: TestWithNull;
  "with\u0001soh"?: TestWithSoh;
  "with\u001fus"?: TestWithUs;
}
