export type ShapeThenRadius = number;

export interface ShapeThen {
  "radius": ShapeThenRadius;
  [key: string]: unknown | undefined;
}

export type ShapeIfKind = "circle";

export interface ShapeIf {
  "kind": ShapeIfKind;
  [key: string]: unknown | undefined;
}

export type ShapeElseSides = number;

export interface ShapeElse {
  "sides": ShapeElseSides;
  [key: string]: unknown | undefined;
}

// (if & then) | else approximation: the else branch is wider than what
// JSON Schema allows, as TypeScript cannot express type negation
export type Shape =
  (ShapeIf & ShapeThen) | ShapeElse;
