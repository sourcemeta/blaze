export type ApiResponseStatus = "success" | "error" | "pending";

export type ApiResponseMeta = ApiResponseResponseMeta;

export type ApiResponseErrorCode_1 = null;

export type ApiResponseErrorCode_0 = string;

export type ApiResponseErrorCode =
  ApiResponseErrorCode_0 |
  ApiResponseErrorCode_1;

export type ApiResponseData = ApiResponsePaginatedResult;

export type ApiResponseAdditionalProperties = never;

export type ApiResponseResponseMetaVersion = string;

export type ApiResponseResponseMetaTimestamp = string;

export type ApiResponseResponseMetaRequestId = string;

export type ApiResponseResponseMetaDeprecationWarningsItemsSuggestedAlternative_1 = null;

export type ApiResponseResponseMetaDeprecationWarningsItemsSuggestedAlternative_0 = string;

export type ApiResponseResponseMetaDeprecationWarningsItemsSuggestedAlternative =
  ApiResponseResponseMetaDeprecationWarningsItemsSuggestedAlternative_0 |
  ApiResponseResponseMetaDeprecationWarningsItemsSuggestedAlternative_1;

export type ApiResponseResponseMetaDeprecationWarningsItemsMessage = string;

export type ApiResponseResponseMetaDeprecationWarningsItemsField = string;

export type ApiResponseResponseMetaDeprecationWarningsItemsAdditionalProperties = never;

export interface ApiResponseResponseMetaDeprecationWarningsItems {
  "message": ApiResponseResponseMetaDeprecationWarningsItemsMessage;
  "field": ApiResponseResponseMetaDeprecationWarningsItemsField;
  "suggestedAlternative"?: ApiResponseResponseMetaDeprecationWarningsItemsSuggestedAlternative;
}

export type ApiResponseResponseMetaDeprecationWarnings = ApiResponseResponseMetaDeprecationWarningsItems[];

export type ApiResponseResponseMetaAdditionalProperties = never;

export interface ApiResponseResponseMeta {
  "requestId": ApiResponseResponseMetaRequestId;
  "timestamp": ApiResponseResponseMetaTimestamp;
  "version"?: ApiResponseResponseMetaVersion;
  "deprecationWarnings"?: ApiResponseResponseMetaDeprecationWarnings;
}

export type ApiResponsePaginationInfoTotalPages = number;

export type ApiResponsePaginationInfoTotalItems = number;

export type ApiResponsePaginationInfoPageSize = number;

export type ApiResponsePaginationInfoPage = number;

export type ApiResponsePaginationInfoHasPreviousPage = boolean;

export type ApiResponsePaginationInfoHasNextPage = boolean;

export type ApiResponsePaginationInfoAdditionalProperties = never;

export interface ApiResponsePaginationInfo {
  "page": ApiResponsePaginationInfoPage;
  "pageSize": ApiResponsePaginationInfoPageSize;
  "totalItems": ApiResponsePaginationInfoTotalItems;
  "totalPages": ApiResponsePaginationInfoTotalPages;
  "hasNextPage"?: ApiResponsePaginationInfoHasNextPage;
  "hasPreviousPage"?: ApiResponsePaginationInfoHasPreviousPage;
}

export type ApiResponsePaginatedResultPagination = ApiResponsePaginationInfo;

export type ApiResponsePaginatedResultItemsItems = ApiResponseEntity;

export type ApiResponsePaginatedResultItems = ApiResponsePaginatedResultItemsItems[];

export type ApiResponsePaginatedResultFilters = ApiResponseAppliedFilters;

export type ApiResponsePaginatedResultAdditionalProperties = never;

export interface ApiResponsePaginatedResult {
  "items": ApiResponsePaginatedResultItems;
  "pagination": ApiResponsePaginatedResultPagination;
  "filters"?: ApiResponsePaginatedResultFilters;
}

export type ApiResponseEntityReferenceType = string;

export type ApiResponseEntityReferenceId = string;

export type ApiResponseEntityReferenceAdditionalProperties = never;

export interface ApiResponseEntityReference {
  "id": ApiResponseEntityReferenceId;
  "type": ApiResponseEntityReferenceType;
}

export type ApiResponseEntityAttributesUpdatedAt_1 = null;

export type ApiResponseEntityAttributesUpdatedAt_0 = string;

export type ApiResponseEntityAttributesUpdatedAt =
  ApiResponseEntityAttributesUpdatedAt_0 |
  ApiResponseEntityAttributesUpdatedAt_1;

export type ApiResponseEntityAttributesTagsItems = string;

export type ApiResponseEntityAttributesTags = ApiResponseEntityAttributesTagsItems[];

export type ApiResponseEntityAttributesName = string;

export type ApiResponseEntityAttributesMetadataAdditionalProperties_2 = boolean;

export type ApiResponseEntityAttributesMetadataAdditionalProperties_1 = number;

export type ApiResponseEntityAttributesMetadataAdditionalProperties_0 = string;

export type ApiResponseEntityAttributesMetadataAdditionalProperties =
  ApiResponseEntityAttributesMetadataAdditionalProperties_0 |
  ApiResponseEntityAttributesMetadataAdditionalProperties_1 |
  ApiResponseEntityAttributesMetadataAdditionalProperties_2;

export type ApiResponseEntityAttributesMetadata = Record<string, ApiResponseEntityAttributesMetadataAdditionalProperties>;

export type ApiResponseEntityAttributesDescription_1 = null;

export type ApiResponseEntityAttributesDescription_0 = string;

export type ApiResponseEntityAttributesDescription =
  ApiResponseEntityAttributesDescription_0 |
  ApiResponseEntityAttributesDescription_1;

export type ApiResponseEntityAttributesCreatedAt = string;

export type ApiResponseEntityAttributesAdditionalProperties = never;

export interface ApiResponseEntityAttributes {
  "name": ApiResponseEntityAttributesName;
  "description"?: ApiResponseEntityAttributesDescription;
  "createdAt": ApiResponseEntityAttributesCreatedAt;
  "updatedAt"?: ApiResponseEntityAttributesUpdatedAt;
  "tags"?: ApiResponseEntityAttributesTags;
  "metadata"?: ApiResponseEntityAttributesMetadata;
}

export type ApiResponseEntityType = "user" | "organization" | "resource";

export type ApiResponseEntityRelationshipsParent = ApiResponseEntityReference;

export type ApiResponseEntityRelationshipsChildrenItems = ApiResponseEntityReference;

export type ApiResponseEntityRelationshipsChildren = ApiResponseEntityRelationshipsChildrenItems[];

export type ApiResponseEntityRelationshipsAdditionalProperties = ApiResponseEntityReference;

export interface ApiResponseEntityRelationships {
  "parent"?: ApiResponseEntityRelationshipsParent;
  "children"?: ApiResponseEntityRelationshipsChildren;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    ApiResponseEntityRelationshipsParent |
    ApiResponseEntityRelationshipsChildren |
    ApiResponseEntityRelationshipsAdditionalProperties |
    undefined;
}

export type ApiResponseEntityId = string;

export type _ApiResponseEntityAttributes = ApiResponseEntityAttributes;

export type ApiResponseEntityAdditionalProperties = never;

export interface ApiResponseEntity {
  "id": ApiResponseEntityId;
  "type": ApiResponseEntityType;
  "attributes": _ApiResponseEntityAttributes;
  "relationships"?: ApiResponseEntityRelationships;
}

export type ApiResponseAppliedFiltersTypesItems = "user" | "organization" | "resource";

export type ApiResponseAppliedFiltersTypes = ApiResponseAppliedFiltersTypesItems[];

export type ApiResponseAppliedFiltersSortOrder = "asc" | "desc";

export type ApiResponseAppliedFiltersSortBy = "name" | "createdAt" | "updatedAt" | null;

export type ApiResponseAppliedFiltersSearch_1 = null;

export type ApiResponseAppliedFiltersSearch_0 = string;

export type ApiResponseAppliedFiltersSearch =
  ApiResponseAppliedFiltersSearch_0 |
  ApiResponseAppliedFiltersSearch_1;

export type ApiResponseAppliedFiltersDateRangeStart = string;

export type ApiResponseAppliedFiltersDateRangeEnd = string;

export type ApiResponseAppliedFiltersDateRangeAdditionalProperties = never;

export interface ApiResponseAppliedFiltersDateRange {
  "start": ApiResponseAppliedFiltersDateRangeStart;
  "end": ApiResponseAppliedFiltersDateRangeEnd;
}

export type ApiResponseAppliedFiltersAdditionalProperties = never;

export interface ApiResponseAppliedFilters {
  "search"?: ApiResponseAppliedFiltersSearch;
  "dateRange"?: ApiResponseAppliedFiltersDateRange;
  "types"?: ApiResponseAppliedFiltersTypes;
  "sortBy"?: ApiResponseAppliedFiltersSortBy;
  "sortOrder"?: ApiResponseAppliedFiltersSortOrder;
}

export interface ApiResponse {
  "status": ApiResponseStatus;
  "errorCode"?: ApiResponseErrorCode;
  "data": ApiResponseData;
  "meta": ApiResponseMeta;
}
