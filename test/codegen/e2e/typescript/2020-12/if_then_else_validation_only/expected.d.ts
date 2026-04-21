export type PatternString_1 = string;

export type PatternString_0Then = string;

export type PatternString_0If = string;

export type PatternString_0Else = string;

// (if & then) | else approximation: the else branch is wider than what
// JSON Schema allows, as TypeScript cannot express type negation
export type PatternString_0 =
  (PatternString_0If & PatternString_0Then) | PatternString_0Else;

export type PatternString =
  PatternString_0 &
  PatternString_1;
