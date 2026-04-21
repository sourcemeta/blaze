import {
  Response,
  ResponseUser,
  ResponseMetadata
} from "./expected";


// Valid: full response with all fields
const fullResponse: Response = {
  data: {
    id: 123,
    name: "John Doe"
  },
  meta: {
    timestamp: "2024-01-15T10:30:00Z",
    version: 1
  }
};

// Valid: minimal response (required fields only)
const minimalResponse: Response = {
  data: {
    id: 1,
    name: "Jane"
  },
  meta: {}
};

// Valid: user object directly
const user: ResponseUser = {
  id: 42,
  name: "Test User"
};

// Valid: metadata object
const metadata: ResponseMetadata = {
  timestamp: "2024-01-15",
  version: 2
};

// Invalid: missing required field 'data'
// @ts-expect-error - data is required
const missingData: Response = {
  meta: {}
};

// Invalid: missing required field 'meta'
// @ts-expect-error - meta is required
const missingMeta: Response = {
  data: { id: 1, name: "Test" }
};

// Invalid: user missing required 'id'
const userMissingId: Response = {
  // @ts-expect-error - id is required on user
  data: {
    name: "Test"
  },
  meta: {}
};

// Invalid: user missing required 'name'
const userMissingName: Response = {
  // @ts-expect-error - name is required on user
  data: {
    id: 1
  },
  meta: {}
};

// Invalid: extra property on user (additionalProperties: false)
const extraUserProp: Response = {
  data: {
    id: 1,
    name: "Test",
    // @ts-expect-error - extra property not allowed
    extra: "not allowed"
  },
  meta: {}
};
