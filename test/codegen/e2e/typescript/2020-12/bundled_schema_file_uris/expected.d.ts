export type ResponseMeta = ResponseMetadata;

export type ResponseData = ResponseUser;

export type ResponseAdditionalProperties = never;

export type ResponseUserName = string;

export type ResponseUserId = number;

export type ResponseUserAdditionalProperties = never;

export interface ResponseUser {
  "id": ResponseUserId;
  "name": ResponseUserName;
}

export type ResponseMetadataVersion = number;

export type ResponseMetadataTimestamp = string;

export type ResponseMetadataAdditionalProperties = never;

export interface ResponseMetadata {
  "timestamp"?: ResponseMetadataTimestamp;
  "version"?: ResponseMetadataVersion;
}

export interface Response {
  "data": ResponseData;
  "meta": ResponseMeta;
}
