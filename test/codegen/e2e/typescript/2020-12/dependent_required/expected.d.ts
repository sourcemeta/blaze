export type Payment_1Credit_card = string;

export type Payment_1Billing_address = string;

export interface Payment_1 {
  "credit_card"?: Payment_1Credit_card;
  "billing_address"?: Payment_1Billing_address;
  [key: string]: unknown | undefined;
}

export type Payment_0_1Credit_card = unknown;

export type Payment_0_1Billing_address = unknown;

export interface Payment_0_1 {
  "credit_card": Payment_0_1Credit_card;
  "billing_address": Payment_0_1Billing_address;
  [key: string]: unknown | undefined;
}

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
