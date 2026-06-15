import { Payment } from "./expected";

// Neither dependency is triggered
const empty: Payment = {};

// Only the "credit_card" dependency is triggered
const cardOnly: Payment = {
  credit_card: "4111-1111-1111-1111",
  billing_address: "123 Main Street",
  billing_zip: "90210"
};

// Only the "phone" dependency is triggered
const phoneOnly: Payment = {
  phone: "+1-555-0100",
  country_code: "US"
};

// Both dependencies are triggered
const everything: Payment = {
  credit_card: "4111-1111-1111-1111",
  billing_address: "123 Main Street",
  billing_zip: "90210",
  phone: "+1-555-0100",
  country_code: "US"
};

// @ts-expect-error "credit_card" requires "billing_address" and "billing_zip"
const cardMissingBoth: Payment = {
  credit_card: "4111-1111-1111-1111"
};

// @ts-expect-error "credit_card" still requires "billing_zip"
const cardMissingZip: Payment = {
  credit_card: "4111-1111-1111-1111",
  billing_address: "123 Main Street"
};

// @ts-expect-error "phone" requires "country_code"
const phoneMissingCountry: Payment = {
  phone: "+1-555-0100"
};

const wrongCreditCardType: Payment = {
  // @ts-expect-error
  credit_card: 123,
  billing_address: "123 Main Street",
  billing_zip: "90210"
};
