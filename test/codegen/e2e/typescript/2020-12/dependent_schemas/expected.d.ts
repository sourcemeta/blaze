export type Payment_1Credit_card = string;

export interface Payment_1 {
  "credit_card"?: Payment_1Credit_card;
  [key: string]: unknown | undefined;
}

export type Payment_0_1_1Billing_address = string;

export interface Payment_0_1_1 {
  "billing_address": Payment_0_1_1Billing_address;
  [key: string]: unknown | undefined;
}

export type Payment_0_1_0Credit_card = unknown;

export interface Payment_0_1_0 {
  "credit_card": Payment_0_1_0Credit_card;
  [key: string]: unknown | undefined;
}

export type Payment_0_1 =
  Payment_0_1_0 &
  Payment_0_1_1;

export type Payment_0_0Credit_card = never;

export interface Payment_0_0 {
  "credit_card"?: Payment_0_0Credit_card;
  [key: string]: unknown | undefined;
}

export type Payment_0 =
  Payment_0_0 |
  Payment_0_1;

export type Payment =
  Payment_0 &
  Payment_1;
