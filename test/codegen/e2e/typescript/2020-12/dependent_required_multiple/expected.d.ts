export type Payment_2Phone = string;

export type Payment_2Credit_card = string;

export type Payment_2Country_code = string;

export type Payment_2Billing_zip = string;

export type Payment_2Billing_address = string;

export interface Payment_2 {
  "credit_card"?: Payment_2Credit_card;
  "billing_address"?: Payment_2Billing_address;
  "billing_zip"?: Payment_2Billing_zip;
  "phone"?: Payment_2Phone;
  "country_code"?: Payment_2Country_code;
  [key: string]: unknown | undefined;
}

export type Payment_1_1Phone = unknown;

export type Payment_1_1Country_code = unknown;

export interface Payment_1_1 {
  "phone": Payment_1_1Phone;
  "country_code": Payment_1_1Country_code;
  [key: string]: unknown | undefined;
}

export type Payment_1_0Phone = never;

export interface Payment_1_0 {
  "phone"?: Payment_1_0Phone;
  [key: string]: unknown | undefined;
}

export type Payment_1 =
  Payment_1_0 |
  Payment_1_1;

export type Payment_0_1Credit_card = unknown;

export type Payment_0_1Billing_zip = unknown;

export type Payment_0_1Billing_address = unknown;

export interface Payment_0_1 {
  "credit_card": Payment_0_1Credit_card;
  "billing_address": Payment_0_1Billing_address;
  "billing_zip": Payment_0_1Billing_zip;
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
  Payment_1 &
  Payment_2;
