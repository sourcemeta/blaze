import { Payment } from "./expected";

// Because "credit_card" is already required, the dependency folds into a
// plain object where both properties are unconditionally required
const both: Payment = {
  credit_card: "4111-1111-1111-1111",
  billing_address: "123 Main Street"
};

// @ts-expect-error "credit_card" is required
const empty: Payment = {};

// @ts-expect-error "billing_address" is required
const onlyCard: Payment = {
  credit_card: "4111-1111-1111-1111"
};

const wrongCreditCardType: Payment = {
  // @ts-expect-error
  credit_card: 123,
  billing_address: "123 Main Street"
};

const wrongBillingType: Payment = {
  credit_card: "4111-1111-1111-1111",
  // @ts-expect-error
  billing_address: 456
};
