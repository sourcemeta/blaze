export type ApiResponseMeta = ApiResponseSchemasMetadata;

export type ApiResponseData = ApiResponseSchemasUser;

export type ApiResponseAdditionalProperties = never;

export type ApiResponseSchemasUserName = string;

export type ApiResponseSchemasUserId = number;

export type ApiResponseSchemasUserEmail = ApiResponseSchemasEmail;

export type ApiResponseSchemasUserAdditionalProperties = never;

export interface ApiResponseSchemasUser {
  "id": ApiResponseSchemasUserId;
  "name": ApiResponseSchemasUserName;
  "email"?: ApiResponseSchemasUserEmail;
}

export type ApiResponseSchemasMetadataVersion = number;

export type ApiResponseSchemasMetadataTimestamp = string;

export type ApiResponseSchemasMetadataAdditionalProperties = never;

export interface ApiResponseSchemasMetadata {
  "timestamp"?: ApiResponseSchemasMetadataTimestamp;
  "version"?: ApiResponseSchemasMetadataVersion;
}

export type ApiResponseSchemasEmail = string;

export interface ApiResponse {
  "data": ApiResponseData;
  "meta": ApiResponseMeta;
}
