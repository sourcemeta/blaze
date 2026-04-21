import {
  ComplexEnum,
  ComplexEnumStatus,
  ComplexEnumCoordinates,
  ComplexEnumFixedConfig,
  ComplexEnumFixedList
} from "./expected";


// Valid: empty object (all optional)
const empty: ComplexEnum = {};

// Valid: status with each enum value
const status200: ComplexEnum = {
  status: { code: 200, message: "OK" }
};

const status404: ComplexEnum = {
  status: { code: 404, message: "Not Found" }
};

const status500: ComplexEnum = {
  status: { code: 500, message: "Internal Server Error" }
};

// Valid: coordinates with each enum value
const coordsOrigin: ComplexEnum = {
  coordinates: [ 0, 0 ]
};

const coordsPositive: ComplexEnum = {
  coordinates: [ 1, 1 ]
};

const coordsNegative: ComplexEnum = {
  coordinates: [ -1, -1 ]
};

// Valid: fixedConfig with exact const value
const withFixedConfig: ComplexEnum = {
  fixedConfig: { enabled: true, maxRetries: 3 }
};

// Valid: fixedList with exact const value
const withFixedList: ComplexEnum = {
  fixedList: [ "read", "write", "execute" ]
};

// Valid: all fields
const complete: ComplexEnum = {
  status: { code: 200, message: "OK" },
  coordinates: [ 0, 0 ],
  fixedConfig: { enabled: true, maxRetries: 3 },
  fixedList: [ "read", "write", "execute" ]
};

// Invalid: status with wrong code
const invalidStatusCode: ComplexEnum = {
  // @ts-expect-error - status must be one of the enum objects
  status: { code: 201, message: "Created" }
};

// Invalid: status with mismatched code/message
const invalidStatusMismatch: ComplexEnum = {
  // @ts-expect-error - code 200 must have message "OK"
  status: { code: 200, message: "Not Found" }
};

// Invalid: coordinates not in enum
const invalidCoords: ComplexEnum = {
  // @ts-expect-error - coordinates must be [0,0], [1,1], or [-1,-1]
  coordinates: [ 2, 2 ]
};

// Invalid: coordinates with mixed values
const invalidCoordsMixed: ComplexEnum = {
  // @ts-expect-error - coordinates must be exactly one of the enum values
  coordinates: [ 0, 1 ]
};

// Invalid: fixedConfig with wrong enabled value
const invalidFixedConfigEnabled: ComplexEnum = {
  // @ts-expect-error - fixedConfig must be exactly {enabled: true, maxRetries: 3}
  fixedConfig: { enabled: false, maxRetries: 3 }
};

// Invalid: fixedConfig with wrong maxRetries value
const invalidFixedConfigRetries: ComplexEnum = {
  // @ts-expect-error - fixedConfig must be exactly {enabled: true, maxRetries: 3}
  fixedConfig: { enabled: true, maxRetries: 5 }
};

// Invalid: fixedList with wrong values
const invalidFixedListValues: ComplexEnum = {
  // @ts-expect-error - fixedList must be exactly ["read", "write", "execute"]
  fixedList: [ "read", "write", "delete" ]
};

// Invalid: fixedList with wrong order
const invalidFixedListOrder: ComplexEnum = {
  // @ts-expect-error - fixedList must be exactly ["read", "write", "execute"]
  fixedList: [ "write", "read", "execute" ]
};

// Invalid: fixedList with different length
const invalidFixedListLength: ComplexEnum = {
  // @ts-expect-error - fixedList must be exactly 3 elements
  fixedList: [ "read", "write" ]
};

// Invalid: extra property (additionalProperties: false)
const extraProperty: ComplexEnum = {
  status: { code: 200, message: "OK" },
  // @ts-expect-error - extra property not allowed
  extra: "not allowed"
};

// Test standalone types
const validStatus1: ComplexEnumStatus = { code: 200, message: "OK" };
const validStatus2: ComplexEnumStatus = { code: 404, message: "Not Found" };
const validStatus3: ComplexEnumStatus = { code: 500, message: "Internal Server Error" };
// @ts-expect-error - must be one of the enum values
const invalidStatusStandalone: ComplexEnumStatus = { code: 201, message: "Created" };

const validCoords1: ComplexEnumCoordinates = [ 0, 0 ];
const validCoords2: ComplexEnumCoordinates = [ 1, 1 ];
const validCoords3: ComplexEnumCoordinates = [ -1, -1 ];
// @ts-expect-error - must be one of the enum values
const invalidCoordsStandalone: ComplexEnumCoordinates = [ 0, 1 ];

const validConfig: ComplexEnumFixedConfig = { enabled: true, maxRetries: 3 };
// @ts-expect-error - must match const exactly
const invalidConfig: ComplexEnumFixedConfig = { enabled: true, maxRetries: 10 };

const validList: ComplexEnumFixedList = [ "read", "write", "execute" ];
// @ts-expect-error - must match const exactly
const invalidList: ComplexEnumFixedList = [ "read", "write" ];
