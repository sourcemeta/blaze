export type DocSystemRelatedDocumentsItemsTitle_1 = null;

export type DocSystemRelatedDocumentsItemsTitle_0 = string;

export type DocSystemRelatedDocumentsItemsTitle =
  DocSystemRelatedDocumentsItemsTitle_0 |
  DocSystemRelatedDocumentsItemsTitle_1;

export type DocSystemRelatedDocumentsItemsRelationship = "parent" | "child" | "sibling" | "reference";

export type DocSystemRelatedDocumentsItemsId = DocSystemUUID;

export type DocSystemRelatedDocumentsItemsAdditionalProperties = never;

export interface DocSystemRelatedDocumentsItems {
  "id": DocSystemRelatedDocumentsItemsId;
  "relationship": DocSystemRelatedDocumentsItemsRelationship;
  "title"?: DocSystemRelatedDocumentsItemsTitle;
}

export type DocSystemRelatedDocuments = DocSystemRelatedDocumentsItems[];

export type DocSystemPermissionsReadersItems = DocSystemUser;

export type DocSystemPermissionsReaders = DocSystemPermissionsReadersItems[];

export type DocSystemPermissionsOwner = DocSystemUser;

export type DocSystemPermissionsIsPublic = boolean;

export type DocSystemPermissionsExpiresAt_1 = null;

export type DocSystemPermissionsExpiresAt_0 = DocSystemTimestamp;

export type DocSystemPermissionsExpiresAt =
  DocSystemPermissionsExpiresAt_0 |
  DocSystemPermissionsExpiresAt_1;

export type DocSystemPermissionsEditorsItems = DocSystemUser;

export type DocSystemPermissionsEditors = DocSystemPermissionsEditorsItems[];

export type DocSystemPermissionsAdditionalProperties = never;

export interface DocSystemPermissions {
  "owner": DocSystemPermissionsOwner;
  "readers": DocSystemPermissionsReaders;
  "editors": DocSystemPermissionsEditors;
  "isPublic"?: DocSystemPermissionsIsPublic;
  "expiresAt"?: DocSystemPermissionsExpiresAt;
}

export type DocSystemHistoryItemsTimestamp = DocSystemTimestamp;

export type DocSystemHistoryItemsDetails_1 = null;

export type DocSystemHistoryItemsDetails_0OldValue_2 = null;

export type DocSystemHistoryItemsDetails_0OldValue_1 = number;

export type DocSystemHistoryItemsDetails_0OldValue_0 = string;

export type DocSystemHistoryItemsDetails_0OldValue =
  DocSystemHistoryItemsDetails_0OldValue_0 |
  DocSystemHistoryItemsDetails_0OldValue_1 |
  DocSystemHistoryItemsDetails_0OldValue_2;

export type DocSystemHistoryItemsDetails_0NewValue_2 = null;

export type DocSystemHistoryItemsDetails_0NewValue_1 = number;

export type DocSystemHistoryItemsDetails_0NewValue_0 = string;

export type DocSystemHistoryItemsDetails_0NewValue =
  DocSystemHistoryItemsDetails_0NewValue_0 |
  DocSystemHistoryItemsDetails_0NewValue_1 |
  DocSystemHistoryItemsDetails_0NewValue_2;

export type DocSystemHistoryItemsDetails_0Field = string;

export type DocSystemHistoryItemsDetails_0AdditionalProperties = never;

export interface DocSystemHistoryItemsDetails_0 {
  "field"?: DocSystemHistoryItemsDetails_0Field;
  "oldValue"?: DocSystemHistoryItemsDetails_0OldValue;
  "newValue"?: DocSystemHistoryItemsDetails_0NewValue;
}

export type DocSystemHistoryItemsDetails =
  DocSystemHistoryItemsDetails_0 |
  DocSystemHistoryItemsDetails_1;

export type DocSystemHistoryItemsActor = DocSystemUser;

export type DocSystemHistoryItemsAction = "created" | "updated" | "deleted" | "restored" | "shared";

export type DocSystemHistoryItemsAdditionalProperties = never;

export interface DocSystemHistoryItems {
  "action": DocSystemHistoryItemsAction;
  "actor": DocSystemHistoryItemsActor;
  "timestamp": DocSystemHistoryItemsTimestamp;
  "details"?: DocSystemHistoryItemsDetails;
}

export type DocSystemHistory = DocSystemHistoryItems[];

export type DocSystemDocumentTitle = string;

export type DocSystemDocumentTagsItemsName = string;

export type DocSystemDocumentTagsItemsColor_1 = null;

export type DocSystemDocumentTagsItemsColor_0 = string;

export type DocSystemDocumentTagsItemsColor =
  DocSystemDocumentTagsItemsColor_0 |
  DocSystemDocumentTagsItemsColor_1;

export type DocSystemDocumentTagsItemsAdditionalProperties = never;

export interface DocSystemDocumentTagsItems {
  "name": DocSystemDocumentTagsItemsName;
  "color"?: DocSystemDocumentTagsItemsColor;
}

export type DocSystemDocumentTags = DocSystemDocumentTagsItems[];

export type DocSystemDocumentReviewersItems = DocSystemUser;

export type DocSystemDocumentReviewers = DocSystemDocumentReviewersItems[];

export type DocSystemDocumentMetadataVersion = number;

export type DocSystemDocumentMetadataUpdatedAt = DocSystemTimestamp;

export type DocSystemDocumentMetadataCreatedAt = DocSystemTimestamp;

export type DocSystemDocumentMetadataAdditionalProperties = never;

export interface DocSystemDocumentMetadata {
  "createdAt"?: DocSystemDocumentMetadataCreatedAt;
  "updatedAt"?: DocSystemDocumentMetadataUpdatedAt;
  "version"?: DocSystemDocumentMetadataVersion;
}

export type DocSystemDocumentId = DocSystemUUID;

export type DocSystemDocumentContentSummary_1 = null;

export type DocSystemDocumentContentSummary_0 = string;

export type DocSystemDocumentContentSummary =
  DocSystemDocumentContentSummary_0 |
  DocSystemDocumentContentSummary_1;

export type DocSystemDocumentContentFormat = "markdown" | "html" | "plaintext";

export type DocSystemDocumentContentBody = string;

export type DocSystemDocumentContentAdditionalProperties = never;

export interface DocSystemDocumentContent {
  "format": DocSystemDocumentContentFormat;
  "body": DocSystemDocumentContentBody;
  "summary"?: DocSystemDocumentContentSummary;
}

export type DocSystemDocumentAuthor = DocSystemUser;

export type DocSystemDocumentAdditionalProperties = never;

export interface DocSystemDocument {
  "id": DocSystemDocumentId;
  "title": DocSystemDocumentTitle;
  "content": DocSystemDocumentContent;
  "author": DocSystemDocumentAuthor;
  "reviewers"?: DocSystemDocumentReviewers;
  "tags"?: DocSystemDocumentTags;
  "metadata"?: DocSystemDocumentMetadata;
}

export type DocSystemAdditionalProperties = never;

export type DocSystemUserRole = "admin" | "editor" | "viewer" | "guest";

export type DocSystemUserId = DocSystemUUID;

export type DocSystemUserEmail = string;

export type DocSystemUserDisplayName_1 = null;

export type DocSystemUserDisplayName_0 = string;

export type DocSystemUserDisplayName =
  DocSystemUserDisplayName_0 |
  DocSystemUserDisplayName_1;

export type DocSystemUserAdditionalProperties = never;

export interface DocSystemUser {
  "id": DocSystemUserId;
  "email": DocSystemUserEmail;
  "displayName"?: DocSystemUserDisplayName;
  "role"?: DocSystemUserRole;
}

export type DocSystemUUID = string;

export type DocSystemTimestampUnix = number;

export type DocSystemTimestampTimezone_1 = null;

export type DocSystemTimestampTimezone_0 = string;

export type DocSystemTimestampTimezone =
  DocSystemTimestampTimezone_0 |
  DocSystemTimestampTimezone_1;

export type DocSystemTimestampIso = string;

export type DocSystemTimestampAdditionalProperties = never;

export interface DocSystemTimestamp {
  "unix": DocSystemTimestampUnix;
  "iso": DocSystemTimestampIso;
  "timezone"?: DocSystemTimestampTimezone;
}

export interface DocSystem {
  "document": DocSystemDocument;
  "permissions": DocSystemPermissions;
  "history": DocSystemHistory;
  "relatedDocuments"?: DocSystemRelatedDocuments;
}
