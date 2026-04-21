import { StringArray } from "./expected";

const valid: StringArray = [ "hello", "world" ];

const empty: StringArray = [];

// @ts-expect-error
const invalidItem: StringArray = [ 42 ];

// @ts-expect-error
const notArray: StringArray = "hello";
