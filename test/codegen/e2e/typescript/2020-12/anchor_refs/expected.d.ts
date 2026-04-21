export type ColorSchemeSecondary = ColorSchemeColor;

export type ColorSchemePrimary = ColorSchemeColor;

export type ColorSchemeBackground = ColorSchemeColor;

export type ColorSchemeAdditionalProperties = never;

export type ColorSchemeColorR = number;

export type ColorSchemeColorG = number;

export type ColorSchemeColorB = number;

export type ColorSchemeColorAlpha = number;

export type ColorSchemeColorAdditionalProperties = never;

export interface ColorSchemeColor {
  "r": ColorSchemeColorR;
  "g": ColorSchemeColorG;
  "b": ColorSchemeColorB;
  "alpha"?: ColorSchemeColorAlpha;
}

export interface ColorScheme {
  "primary": ColorSchemePrimary;
  "secondary": ColorSchemeSecondary;
  "background"?: ColorSchemeBackground;
}
