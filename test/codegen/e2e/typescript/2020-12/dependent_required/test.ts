import { Payment } from "./expected";

// The dependency is not triggered when "credit_card" is absent
const empty: Payment = {};

const onlyBilling: Payment = {
  billing_address: "123 Main Street"
};

// When "credit_card" is present, "billing_address" must be present too
const both: Payment = {
  credit_card: "4111-1111-1111-1111",
  billing_address: "123 Main Street"
};

// @ts-expect-error "credit_card" requires "billing_address"
const creditWithoutBilling: Payment = {
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
