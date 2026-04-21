export type MyObjectFoo = string;

export interface MyObject {
  "foo"?: MyObjectFoo;
  [key: string]: unknown | undefined;
}
