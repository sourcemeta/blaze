import {
  ColorScheme,
  ColorSchemeColor
} from "./expected";

// Valid: minimal required fields
const minimal: ColorScheme = {
  primary: { r: 255, g: 0, b: 0 },
  secondary: { r: 0, g: 255, b: 0 }
};

// Valid: all fields including optional
const complete: ColorScheme = {
  primary: { r: 255, g: 0, b: 0, alpha: 1.0 },
  secondary: { r: 0, g: 255, b: 0, alpha: 0.8 },
  background: { r: 255, g: 255, b: 255, alpha: 1.0 }
};

// Valid: color with optional alpha
const colorWithAlpha: ColorSchemeColor = {
  r: 128,
  g: 128,
  b: 128,
  alpha: 0.5
};

// Valid: color without alpha
const colorWithoutAlpha: ColorSchemeColor = {
  r: 0,
  g: 0,
  b: 0
};

// Invalid: missing required r
// @ts-expect-error
const missingR: ColorSchemeColor = {
  g: 255,
  b: 255
};

// Invalid: missing required g
// @ts-expect-error
const missingG: ColorSchemeColor = {
  r: 255,
  b: 255
};

// Invalid: missing required b
// @ts-expect-error
const missingB: ColorSchemeColor = {
  r: 255,
  g: 255
};

// Invalid: r must be number
const invalidR: ColorSchemeColor = {
  // @ts-expect-error
  r: "255",
  g: 0,
  b: 0
};

// Invalid: alpha must be number
const invalidAlpha: ColorSchemeColor = {
  r: 255,
  g: 0,
  b: 0,
  // @ts-expect-error
  alpha: "1.0"
};

// Invalid: extra property on color (additionalProperties: false)
const invalidColorExtra: ColorSchemeColor = {
  r: 255,
  g: 0,
  b: 0,
  // @ts-expect-error
  name: "red"
};

// Invalid: missing required primary
// @ts-expect-error
const missingPrimary: ColorScheme = {
  secondary: { r: 0, g: 255, b: 0 }
};

// Invalid: missing required secondary
// @ts-expect-error
const missingSecondary: ColorScheme = {
  primary: { r: 255, g: 0, b: 0 }
};

// Invalid: extra property on root (additionalProperties: false)
const invalidRootExtra: ColorScheme = {
  primary: { r: 255, g: 0, b: 0 },
  secondary: { r: 0, g: 255, b: 0 },
  // @ts-expect-error
  accent: { r: 255, g: 255, b: 0 }
};

// Invalid: primary with wrong type
const invalidPrimaryType: ColorScheme = {
  // @ts-expect-error
  primary: "red",
  secondary: { r: 0, g: 255, b: 0 }
};
