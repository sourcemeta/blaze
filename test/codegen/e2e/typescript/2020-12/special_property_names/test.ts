import { Schema } from "./expected";


// Valid: object with special property names
const valid: Schema = {
  "say \"hello\"": "greeting",
  "path\\to\\file": "/usr/local/bin",
  "line1\nline2": "multiline",
  "col1\tcol2": "tabbed",
  "$special@chars": "special",
  "my property name": "spaced",
  "123abc": "starts with number",
  "class": "reserved word"
};

// Valid: partial object
const partial: Schema = {
  "class": "only class property"
};

// Valid: empty object (all properties optional)
const empty: Schema = {};

// Invalid: extra property (additionalProperties: false)
const extraProperty: Schema = {
  "class": "valid",
  // @ts-expect-error - extra property not allowed
  extra: "not allowed"
};

// Invalid: wrong type for property
const wrongType: Schema = {
  // @ts-expect-error - class must be string
  "class": 123
};
