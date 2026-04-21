import {
  ApiResponse,
  ApiResponseEntity,
  ApiResponseEntityAttributes,
  ApiResponsePaginationInfo,
  ApiResponseAppliedFilters
} from "./expected";


// Valid: minimal response
const minimal: ApiResponse = {
  status: "success",
  data: {
    items: [],
    pagination: {
      page: 1,
      pageSize: 10,
      totalItems: 0,
      totalPages: 0
    }
  },
  meta: {
    requestId: "req-123",
    timestamp: "2024-01-01T00:00:00Z"
  }
};

// Valid: with error status
const errorResponse: ApiResponse = {
  status: "error",
  errorCode: "NOT_FOUND",
  data: {
    items: [],
    pagination: { page: 1, pageSize: 10, totalItems: 0, totalPages: 0 }
  },
  meta: { requestId: "req-456", timestamp: "2024-01-01T00:00:00Z" }
};

// Valid: errorCode can be null
const errorCodeNull: ApiResponse = {
  status: "pending",
  errorCode: null,
  data: {
    items: [],
    pagination: { page: 1, pageSize: 10, totalItems: 0, totalPages: 0 }
  },
  meta: { requestId: "req-789", timestamp: "2024-01-01T00:00:00Z" }
};

// Invalid: status must be one of the enum values
const invalidStatus: ApiResponse = {
  // @ts-expect-error - status must be success|error|pending
  status: "unknown",
  data: {
    items: [],
    pagination: { page: 1, pageSize: 10, totalItems: 0, totalPages: 0 }
  },
  meta: { requestId: "req", timestamp: "ts" }
};

// Valid: Entity with type enum
const validEntity: ApiResponseEntity = {
  id: "user-1",
  type: "user",
  attributes: {
    name: "John Doe",
    createdAt: "2024-01-01"
  }
};

// Invalid: Entity type must be from enum
const invalidEntityType: ApiResponseEntity = {
  id: "e1",
  // @ts-expect-error - type must be user|organization|resource
  type: "admin",
  attributes: { name: "test", createdAt: "2024-01-01" }
};

// Valid: Entity with relationships including additionalProperties
const entityWithRelationships: ApiResponseEntity = {
  id: "org-1",
  type: "organization",
  attributes: { name: "Acme Corp", createdAt: "2024-01-01" },
  relationships: {
    parent: { id: "parent-1", type: "organization" },
    children: [
      { id: "child-1", type: "user" },
      { id: "child-2", type: "resource" }
    ],
    // Additional properties should be allowed (additionalProperties: EntityReference)
    manager: { id: "manager-1", type: "user" },
    subsidiary: { id: "sub-1", type: "organization" }
  }
};

// Valid: EntityAttributes with metadata (additionalProperties: string|number|boolean)
const attributesWithMetadata: ApiResponseEntityAttributes = {
  name: "Test Entity",
  createdAt: "2024-01-01",
  description: "A test entity",
  updatedAt: "2024-06-01",
  tags: [ "tag1", "tag2" ],
  metadata: {
    stringValue: "hello",
    numberValue: 42,
    booleanValue: true
  }
};

// Invalid: metadata values must be string|number|boolean, not object
const invalidMetadata: ApiResponseEntityAttributes = {
  name: "test",
  createdAt: "2024-01-01",
  metadata: {
    // @ts-expect-error - must be string|number|boolean, not object
    nested: { foo: "bar" }
  }
};

// Invalid: metadata values must be string|number|boolean, not array
const invalidMetadataArray: ApiResponseEntityAttributes = {
  name: "test",
  createdAt: "2024-01-01",
  metadata: {
    // @ts-expect-error - must be string|number|boolean, not array
    list: [ 1, 2, 3 ]
  }
};

// Valid: PaginationInfo with boolean enum fields
const pagination: ApiResponsePaginationInfo = {
  page: 1,
  pageSize: 20,
  totalItems: 100,
  totalPages: 5,
  hasNextPage: true,
  hasPreviousPage: false
};

// Valid: AppliedFilters with sortBy enum including null
const filters: ApiResponseAppliedFilters = {
  search: "query",
  sortBy: "name",
  sortOrder: "asc"
};

// Valid: sortBy can be null (it's in the enum)
const filtersWithNullSort: ApiResponseAppliedFilters = {
  sortBy: null,
  sortOrder: "desc"
};

// Invalid: sortBy must be from enum
const invalidSortBy: ApiResponseAppliedFilters = {
  // @ts-expect-error - sortBy must be name|createdAt|updatedAt|null
  sortBy: "id"
};

// Invalid: sortOrder must be asc or desc
const invalidSortOrder: ApiResponseAppliedFilters = {
  // @ts-expect-error - sortOrder must be asc|desc
  sortOrder: "random"
};

// Valid: types array with enum items
const filtersWithTypes: ApiResponseAppliedFilters = {
  types: [ "user", "organization" ]
};

// Invalid: types must be from enum
const invalidTypes: ApiResponseAppliedFilters = {
  // @ts-expect-error - type items must be user|organization|resource
  types: [ "user", "admin" ]
};

// Valid: full response with all features
const fullResponse: ApiResponse = {
  status: "success",
  errorCode: null,
  data: {
    items: [
      {
        id: "user-1",
        type: "user",
        attributes: {
          name: "Alice",
          description: "Developer",
          createdAt: "2024-01-01",
          updatedAt: "2024-06-01",
          tags: [ "developer", "team-a" ],
          metadata: { department: "Engineering", level: 5, active: true }
        },
        relationships: {
          parent: { id: "org-1", type: "organization" },
          children: [],
          mentor: { id: "user-2", type: "user" }
        }
      }
    ],
    pagination: {
      page: 1,
      pageSize: 10,
      totalItems: 1,
      totalPages: 1,
      hasNextPage: false,
      hasPreviousPage: false
    },
    filters: {
      search: "alice",
      dateRange: { start: "2024-01-01", end: "2024-12-31" },
      types: [ "user" ],
      sortBy: "createdAt",
      sortOrder: "desc"
    }
  },
  meta: {
    requestId: "req-abc",
    timestamp: "2024-06-15T12:00:00Z",
    version: "2.0",
    deprecationWarnings: [
      { message: "Field deprecated", field: "oldField", suggestedAlternative: "newField" },
      { message: "Another warning", field: "anotherField", suggestedAlternative: null }
    ]
  }
};
