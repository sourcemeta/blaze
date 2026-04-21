import { Shape } from "./expected";

// Valid: satisfies the if condition (kind="circle") and then branch (radius)
const circle: Shape = {
  kind: "circle",
  radius: 5
};

// Valid: does not satisfy the if condition, satisfies else branch (sides)
const polygon: Shape = {
  sides: 6
};

// Invalid: satisfies if (kind="circle") but missing then's required radius
// @ts-expect-error
const circleWithoutRadius: Shape = {
  kind: "circle"
};

// Invalid: does not satisfy if, and missing else's required sides
// @ts-expect-error
const emptyObject: Shape = {};

// NOTE: This passes TypeScript but would fail JSON Schema validation.
// The if condition matches (kind is "circle"), so the then branch should
// apply (requiring radius). But our (If & Then) | Else approximation
// allows the else branch to also match when if holds.
const circleMatchingElse: Shape = {
  kind: "circle",
  sides: 4
};
