export type PatternStringThen = string;

export type PatternStringIf = string;

export type PatternStringElse = string;

// (if & then) | else approximation: the else branch is wider than what
// JSON Schema allows, as TypeScript cannot express type negation
export type PatternString =
  (PatternStringIf & PatternStringThen) | PatternStringElse;
