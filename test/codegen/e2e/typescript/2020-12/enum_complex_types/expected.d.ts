export type ComplexEnumStatus = {
  "code": 200,
  "message": "OK"
} | {
  "code": 404,
  "message": "Not Found"
} | {
  "code": 500,
  "message": "Internal Server Error"
};

export type ComplexEnumFixedList = [ "read", "write", "execute" ];

export type ComplexEnumFixedConfig = {
  "enabled": true,
  "maxRetries": 3
};

export type ComplexEnumCoordinates = [ 0, 0 ] | [ 1, 1 ] | [ -1, -1 ];

export type ComplexEnumAdditionalProperties = never;

export interface ComplexEnum {
  "status"?: ComplexEnumStatus;
  "coordinates"?: ComplexEnumCoordinates;
  "fixedConfig"?: ComplexEnumFixedConfig;
  "fixedList"?: ComplexEnumFixedList;
}
