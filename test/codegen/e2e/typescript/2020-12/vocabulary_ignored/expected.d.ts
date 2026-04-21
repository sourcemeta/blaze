export type VocabTestValue = number;

export type VocabTestOptional = boolean;

export type VocabTestName = string;

export type VocabTestAdditionalProperties = never;

export interface VocabTest {
  "name": VocabTestName;
  "value": VocabTestValue;
  "optional"?: VocabTestOptional;
}
