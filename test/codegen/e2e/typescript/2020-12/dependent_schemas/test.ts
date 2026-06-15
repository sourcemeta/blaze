import { Payment } from "./expected";

// The dependent schema does not apply when "credit_card" is absent
const empty: Payment = {};

// When "credit_card" is present, the dependent schema requires
// "billing_address" to be a string
const both: Payment = {
  credit_card: "4111-1111-1111-1111",
  billing_address: "123 Main Street"
};

// @ts-expect-error "credit_card" triggers the dependent schema
const creditWithoutBilling: Payment = {
  credit_card: "4111-1111-1111-1111"
};

// @ts-expect-error "billing_address" must be a string
const wrongBillingType: Payment = {
  credit_card: "4111-1111-1111-1111",
  billing_address: 456
};

const wrongCreditCardType: Payment = {
  // @ts-expect-error
  credit_card: 123,
  billing_address: "123 Main Street"
};
