export type RootListItems = unknown;

export type RootList = RootListItems[];

export type RootChild =
  RootLeaf |
  Root;

export type RootLeaf = string;

export interface Root {
  "child"?: RootChild;
  "list"?: RootList;
  [key: string]: unknown | undefined;
}
