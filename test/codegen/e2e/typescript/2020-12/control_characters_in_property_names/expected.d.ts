export type TestWithus = string;

export type TestWithformfeed = string;

export type TestWithbackspace = string;

export type TestWithsoh = string;

export type TestWithnull = string;

export type TestNormal = string;

export type TestAdditionalProperties = never;

export interface Test {
  "normal"?: TestNormal;
  "with\bbackspace"?: TestWithbackspace;
  "with\fformfeed"?: TestWithformfeed;
  "with\u0000null"?: TestWithnull;
  "with\u0001soh"?: TestWithsoh;
  "with\u001fus"?: TestWithus;
}
