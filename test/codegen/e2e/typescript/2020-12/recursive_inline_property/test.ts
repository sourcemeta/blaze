import { Chain, ChainHead } from "./expected";


// Valid: a chain of one link
const single: Chain = {
  head: {
    value: "only"
  }
};

// Valid: a chain that goes on
const several: Chain = {
  head: {
    value: "first",
    next: {
      value: "second",
      next: {
        value: "third"
      }
    }
  }
};

// Valid: a link on its own, named by the type the property declares
const link: ChainHead = {
  value: "link",
  next: {
    value: "next"
  }
};

// Invalid: the head is required
// @ts-expect-error - head is required
const headless: Chain = {};

// Invalid: wrong type for the value of a link
const wrongValueType: Chain = {
  head: {
    // @ts-expect-error - value must be string
    value: 123
  }
};

// Invalid: what follows a link is a link
const wrongNextType: Chain = {
  head: {
    value: "first",
    // @ts-expect-error - next must be a link
    next: "second"
  }
};

// Invalid: extra property on a link (additionalProperties: false)
const extraProperty: Chain = {
  head: {
    value: "first",
    // @ts-expect-error - extra property not allowed
    extra: true
  }
};
