export type PaymentCredit_card = string;

export type PaymentBilling_address = string;

export interface Payment {
  "credit_card": PaymentCredit_card;
  "billing_address": PaymentBilling_address;
  [key: string]: unknown | undefined;
}
