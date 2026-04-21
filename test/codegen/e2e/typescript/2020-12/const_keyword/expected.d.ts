export type ConstTestVersion = "1.0.0";

export type ConstTestOptionalFlag = false;

export type ConstTestNothing = null;

export type ConstTestNestedFixedValue = "fixed";

export type ConstTestNestedFixedNumber = 100;

export type ConstTestNestedAdditionalProperties = never;

export interface ConstTestNested {
  "fixedValue"?: ConstTestNestedFixedValue;
  "fixedNumber"?: ConstTestNestedFixedNumber;
}

export type ConstTestMode = "production";

export type ConstTestEnabled = true;

export type ConstTestCount = 42;

export type ConstTestAdditionalProperties = never;

export interface ConstTest {
  "version": ConstTestVersion;
  "enabled": ConstTestEnabled;
  "mode": ConstTestMode;
  "count": ConstTestCount;
  "nothing": ConstTestNothing;
  "optionalFlag"?: ConstTestOptionalFlag;
  "nested"?: ConstTestNested;
}
