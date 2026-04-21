import {
  ApiResponse,
  ApiResponseSchemasUser,
  ApiResponseSchemasMetadata,
  ApiResponseSchemasEmail
} from "./expected";


// Valid: full API response with all fields
const fullResponse: ApiResponse = {
  data: {
    id: 123,
    name: "John Doe",
    email: "john@example.com"
  },
  meta: {
    timestamp: "2024-01-15T10:30:00Z",
    version: 1
  }
};

// Valid: minimal response (required fields only)
const minimalResponse: ApiResponse = {
  data: {
    id: 1,
    name: "Jane"
  },
  meta: {}
};

// Valid: user object directly
const user: ApiResponseSchemasUser = {
  id: 42,
  name: "Test User"
};

// Valid: user with email
const userWithEmail: ApiResponseSchemasUser = {
  id: 42,
  name: "Test User",
  email: "test@example.com"
};

// Valid: metadata object
const metadata: ApiResponseSchemasMetadata = {
  timestamp: "2024-01-15",
  version: 2
};

// Valid: email is just a string
const email: ApiResponseSchemasEmail = "user@domain.com";

// Invalid: missing required field 'data'
// @ts-expect-error - data is required
const missingData: ApiResponse = {
  meta: {}
};

// Invalid: missing required field 'meta'
// @ts-expect-error - meta is required
const missingMeta: ApiResponse = {
  data: { id: 1, name: "Test" }
};

// Invalid: user missing required 'id'
const userMissingId: ApiResponse = {
  // @ts-expect-error - id is required on user
  data: {
    name: "Test"
  },
  meta: {}
};

// Invalid: user missing required 'name'
const userMissingName: ApiResponse = {
  // @ts-expect-error - name is required on user
  data: {
    id: 1
  },
  meta: {}
};

// Invalid: wrong type for user id
const wrongIdType: ApiResponse = {
  data: {
    // @ts-expect-error - id must be number
    id: "not-a-number",
    name: "Test"
  },
  meta: {}
};

// Invalid: extra property on user (additionalProperties: false)
const extraUserProp: ApiResponse = {
  data: {
    id: 1,
    name: "Test",
    // @ts-expect-error - extra property not allowed
    extra: "not allowed"
  },
  meta: {}
};
