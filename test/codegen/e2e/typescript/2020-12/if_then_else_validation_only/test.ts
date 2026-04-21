import { PatternString } from "./expected";

// Valid: any string satisfies the type since all branches resolve to string
const short_value: PatternString = "short123";
const long_value: PatternString = "longstringvalue";
const empty_value: PatternString = "";

// Invalid: not a string
// @ts-expect-error
const number_value: PatternString = 42;

// Invalid: not a string
// @ts-expect-error
const boolean_value: PatternString = true;
