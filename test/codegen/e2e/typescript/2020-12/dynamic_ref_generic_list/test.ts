import { StringList } from "./expected";

// At runtime, the dynamic ref resolves to the string anchor (the parent
// schema overrides the default). But the codegen emits a union of ALL possible
// targets: the unconstrained default (all JSON types) plus the string anchor.
// So the generated type allows any JSON value as items. The generated types
// are always a superset of what JSON Schema allows, never a subset.
const strings: StringList = [ "hello", "world" ];

const numbers: StringList = [ 1, 2, 3 ];

const mixed: StringList = [ "hello", 42, true, null ];

const objects: StringList = [ { key: "value" } ];

const empty: StringList = [];

// @ts-expect-error
const notArray: StringList = "hello";

// undefined is not a JSON type and is not in any anchor's type union
// @ts-expect-error
const undefinedItem: StringList = [ undefined ];
