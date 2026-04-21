export type RecordRegion = string;

export type RecordReferenceCode = string;

export type RecordRecordId = string;

export type RecordOrganizationName = string;

export type RecordNotes = string;

export type RecordMetaOriginId = string;

export type RecordMetaOrigin = string;

export type RecordMetaAdditionalProperties = never;

export interface RecordMeta {
  "origin"?: RecordMetaOrigin;
  "originId"?: RecordMetaOriginId;
}

export type RecordLocationInfoStateCode = string;

export type RecordLocationInfoAreaCode = string;

export type RecordLocationInfoAdditionalProperties = never;

export interface RecordLocationInfo {
  "stateCode"?: RecordLocationInfoStateCode;
  "areaCode"?: RecordLocationInfoAreaCode;
}

export type RecordItemsItemsSubCategory = string;

export type RecordItemsItemsSeverity = string;

export type RecordItemsItemsSequenceNumber = string;

export type RecordItemsItemsResolvedAt_1 = null;

export type RecordItemsItemsResolvedAt_0 = RecordTimestamp;

export type RecordItemsItemsResolvedAt =
  RecordItemsItemsResolvedAt_0 |
  RecordItemsItemsResolvedAt_1;

export type RecordItemsItemsResolution_1 = null;

export type RecordItemsItemsResolution_0 = string;

export type RecordItemsItemsResolution =
  RecordItemsItemsResolution_0 |
  RecordItemsItemsResolution_1;

export type RecordItemsItemsRemarks_1 = null;

export type RecordItemsItemsRemarks_0 = string;

export type RecordItemsItemsRemarks =
  RecordItemsItemsRemarks_0 |
  RecordItemsItemsRemarks_1;

export type RecordItemsItemsOutcome = string;

export type RecordItemsItemsOccurredAt = RecordTimestamp;

export type RecordItemsItemsMetaOriginId = string;

export type RecordItemsItemsMetaOrigin = string;

export type RecordItemsItemsMetaAdditionalProperties = never;

export interface RecordItemsItemsMeta {
  "origin"?: RecordItemsItemsMetaOrigin;
  "originId"?: RecordItemsItemsMetaOriginId;
}

export type RecordItemsItemsItemId = string;

export type RecordItemsItemsDescription = string;

export type RecordItemsItemsCode_1 = null;

export type RecordItemsItemsCode_0 = string;

export type RecordItemsItemsCode =
  RecordItemsItemsCode_0 |
  RecordItemsItemsCode_1;

export type RecordItemsItemsCategory = string;

export type RecordItemsItemsAdditionalProperties = never;

export interface RecordItemsItems {
  "itemId": RecordItemsItemsItemId;
  "sequenceNumber": RecordItemsItemsSequenceNumber;
  "description": RecordItemsItemsDescription;
  "code"?: RecordItemsItemsCode;
  "occurredAt": RecordItemsItemsOccurredAt;
  "severity": RecordItemsItemsSeverity;
  "resolution"?: RecordItemsItemsResolution;
  "resolvedAt"?: RecordItemsItemsResolvedAt;
  "outcome"?: RecordItemsItemsOutcome;
  "remarks"?: RecordItemsItemsRemarks;
  "category"?: RecordItemsItemsCategory;
  "subCategory"?: RecordItemsItemsSubCategory;
  "meta"?: RecordItemsItemsMeta;
}

export type RecordItems = RecordItemsItems[];

export type RecordEntityLocationsItems = RecordLocation;

export type RecordEntityLocations = RecordEntityLocationsItems[];

export type RecordEntityFullName = RecordFullName;

export type RecordEntityClassification = string;

export type RecordEntityCategory = string;

export type RecordEntityBirthDate = RecordTimestamp;

export type RecordEntityAdditionalProperties = never;

export interface RecordEntity {
  "fullName": RecordEntityFullName;
  "birthDate": RecordEntityBirthDate;
  "category"?: RecordEntityCategory;
  "classification"?: RecordEntityClassification;
  "locations": RecordEntityLocations;
}

export type RecordCreatedAt = RecordTimestamp;

export type RecordAdditionalProperties = never;

export type RecordTimestampYear = number;

export type RecordTimestampRawValue = string;

export type RecordTimestampMonth = number;

export type RecordTimestampIsoFormat = string;

export type RecordTimestampDay = number;

export type RecordTimestampAdditionalProperties = never;

export interface RecordTimestamp {
  "rawValue": RecordTimestampRawValue;
  "year": RecordTimestampYear;
  "month": RecordTimestampMonth;
  "day": RecordTimestampDay;
  "isoFormat"?: RecordTimestampIsoFormat;
}

export type RecordLocationRegion = string;

export type RecordLocationRawValue = string;

export type RecordLocationPostalCode = string;

export type RecordLocationLine2_1 = null;

export type RecordLocationLine2_0 = string;

export type RecordLocationLine2 =
  RecordLocationLine2_0 |
  RecordLocationLine2_1;

export type RecordLocationLine1 = string;

export type RecordLocationDistrict = string;

export type RecordLocationCountry = string;

export type RecordLocationCity = string;

export type RecordLocationAdditionalProperties = never;

export interface RecordLocation {
  "rawValue": RecordLocationRawValue;
  "line1": RecordLocationLine1;
  "line2"?: RecordLocationLine2;
  "city": RecordLocationCity;
  "district"?: RecordLocationDistrict;
  "region": RecordLocationRegion;
  "postalCode": RecordLocationPostalCode;
  "country": RecordLocationCountry;
}

export type RecordFullNameSuffix_1 = null;

export type RecordFullNameSuffix_0 = string;

export type RecordFullNameSuffix =
  RecordFullNameSuffix_0 |
  RecordFullNameSuffix_1;

export type RecordFullNameRawValue = string;

export type RecordFullNamePrefix_1 = null;

export type RecordFullNamePrefix_0 = string;

export type RecordFullNamePrefix =
  RecordFullNamePrefix_0 |
  RecordFullNamePrefix_1;

export type RecordFullNameMiddleName_1 = null;

export type RecordFullNameMiddleName_0 = string;

export type RecordFullNameMiddleName =
  RecordFullNameMiddleName_0 |
  RecordFullNameMiddleName_1;

export type RecordFullNameGivenName = string;

export type RecordFullNameFamilyName = string;

export type RecordFullNameAdditionalProperties = never;

export interface RecordFullName {
  "rawValue"?: RecordFullNameRawValue;
  "givenName": RecordFullNameGivenName;
  "middleName"?: RecordFullNameMiddleName;
  "familyName": RecordFullNameFamilyName;
  "suffix"?: RecordFullNameSuffix;
  "prefix"?: RecordFullNamePrefix;
}

export interface Record {
  "recordId": RecordRecordId;
  "referenceCode"?: RecordReferenceCode;
  "organizationName": RecordOrganizationName;
  "createdAt"?: RecordCreatedAt;
  "region": RecordRegion;
  "locationInfo"?: RecordLocationInfo;
  "entity": RecordEntity;
  "notes"?: RecordNotes;
  "items": RecordItems;
  "meta"?: RecordMeta;
}
