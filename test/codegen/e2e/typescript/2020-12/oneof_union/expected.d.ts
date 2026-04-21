export type OneOfTestValue_2 = boolean;

export type OneOfTestValue_1 = number;

export type OneOfTestValue_0 = string;

export type OneOfTestValue =
  OneOfTestValue_0 |
  OneOfTestValue_1 |
  OneOfTestValue_2;

export type OneOfTestStatus_1 = "completed" | "cancelled";

export type OneOfTestStatus_0 = "pending" | "active";

export type OneOfTestStatus =
  OneOfTestStatus_0 |
  OneOfTestStatus_1;

export type OneOfTestAdditionalProperties = never;

export interface OneOfTest {
  "value": OneOfTestValue;
  "status"?: OneOfTestStatus;
}
