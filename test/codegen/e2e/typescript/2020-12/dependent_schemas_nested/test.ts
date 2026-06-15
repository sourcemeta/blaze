import { Record } from "./expected";

// The dependent schema does not apply when "category" is absent
const empty: Record = {};

// When "category" is present, "details" (with a numeric "code") is required
const withDetails: Record = {
  category: "invoice",
  details: {
    code: 42
  }
};

// @ts-expect-error "category" requires "details"
const categoryWithoutDetails: Record = {
  category: "invoice"
};

// @ts-expect-error "details.code" must be present
const detailsMissingCode: Record = {
  category: "invoice",
  details: {}
};

// @ts-expect-error "details.code" must be a number
const detailsWrongCodeType: Record = {
  category: "invoice",
  details: {
    code: "42"
  }
};
