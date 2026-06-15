export type Record_1Category = string;

export interface Record_1 {
  "category"?: Record_1Category;
  [key: string]: unknown | undefined;
}

export type Record_0_1_1DetailsCode = number;

export interface Record_0_1_1Details {
  "code": Record_0_1_1DetailsCode;
  [key: string]: unknown | undefined;
}

export interface Record_0_1_1 {
  "details": Record_0_1_1Details;
  [key: string]: unknown | undefined;
}

export type Record_0_1_0Category = unknown;

export interface Record_0_1_0 {
  "category": Record_0_1_0Category;
  [key: string]: unknown | undefined;
}

export type Record_0_1 =
  Record_0_1_0 &
  Record_0_1_1;

export type Record_0_0Category = never;

export interface Record_0_0 {
  "category"?: Record_0_0Category;
  [key: string]: unknown | undefined;
}

export type Record_0 =
  Record_0_0 |
  Record_0_1;

export type Record =
  Record_0 &
  Record_1;
