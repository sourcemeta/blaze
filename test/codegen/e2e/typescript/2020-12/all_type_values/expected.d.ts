export type AllTypesStringField = string;

export type AllTypesObjectFieldNested = string;

export type AllTypesObjectFieldAdditionalProperties = never;

export interface AllTypesObjectField {
  "nested"?: AllTypesObjectFieldNested;
}

export type AllTypesNumberField = number;

export type AllTypesNullField = null;

export type AllTypesNestedTypesDeepNull = null;

export type AllTypesNestedTypesDeepInteger = number;

export type AllTypesNestedTypesDeepBoolean = boolean;

export type AllTypesNestedTypesAdditionalProperties = never;

export interface AllTypesNestedTypes {
  "deepBoolean"?: AllTypesNestedTypesDeepBoolean;
  "deepNull"?: AllTypesNestedTypesDeepNull;
  "deepInteger"?: AllTypesNestedTypesDeepInteger;
}

export type AllTypesMultiType_2 = null;

export type AllTypesMultiType_1 = number;

export type AllTypesMultiType_0 = string;

export type AllTypesMultiType =
  AllTypesMultiType_0 |
  AllTypesMultiType_1 |
  AllTypesMultiType_2;

export type AllTypesIntegerField = number;

export type AllTypesBooleanField = boolean;

export type AllTypesArrayFieldItems = string;

export type AllTypesArrayField = AllTypesArrayFieldItems[];

export type AllTypesAdditionalProperties = never;

export interface AllTypes {
  "stringField": AllTypesStringField;
  "numberField": AllTypesNumberField;
  "integerField": AllTypesIntegerField;
  "booleanField": AllTypesBooleanField;
  "nullField": AllTypesNullField;
  "arrayField": AllTypesArrayField;
  "objectField": AllTypesObjectField;
  "multiType"?: AllTypesMultiType;
  "nestedTypes"?: AllTypesNestedTypes;
}
