import {
  Record,
  RecordTimestamp,
  RecordFullName,
  RecordLocation,
  RecordItemsItems,
  RecordEntity
} from "./expected";


// Valid: Timestamp with all required fields
const timestamp: RecordTimestamp = {
  rawValue: "2024-01-15",
  year: 2024,
  month: 1,
  day: 15
};

// Valid: Timestamp with optional isoFormat
const timestampWithIso: RecordTimestamp = {
  rawValue: "2024-01-15",
  year: 2024,
  month: 1,
  day: 15,
  isoFormat: "2024-01-15T00:00:00Z"
};

// Invalid: Timestamp missing required rawValue
// @ts-expect-error - rawValue is required
const timestampMissingRaw: RecordTimestamp = {
  year: 2024,
  month: 1,
  day: 15
};

// Valid: FullName with required fields only
const fullNameMinimal: RecordFullName = {
  givenName: "John",
  familyName: "Doe"
};

// Valid: FullName with all fields
const fullNameComplete: RecordFullName = {
  rawValue: "Dr. John Michael Doe Jr.",
  givenName: "John",
  middleName: "Michael",
  familyName: "Doe",
  suffix: "Jr.",
  prefix: "Dr."
};

// Valid: FullName with null nullable fields (type: ["string", "null"])
const fullNameNulls: RecordFullName = {
  givenName: "Jane",
  familyName: "Smith",
  middleName: null,
  suffix: null,
  prefix: null
};

// Invalid: FullName missing required givenName
// @ts-expect-error - givenName is required
const fullNameMissingGiven: RecordFullName = {
  familyName: "Doe"
};

// Valid: Location with all required fields
const location: RecordLocation = {
  rawValue: "123 Main St, City, Region 12345, Country",
  line1: "123 Main St",
  city: "City",
  region: "Region",
  postalCode: "12345",
  country: "Country"
};

// Valid: Location with all fields including nullable line2
const locationComplete: RecordLocation = {
  rawValue: "123 Main St, Apt 4, City, District, Region 12345, Country",
  line1: "123 Main St",
  line2: "Apt 4",
  city: "City",
  district: "District",
  region: "Region",
  postalCode: "12345",
  country: "Country"
};

// Valid: Location with null line2
const locationNullLine2: RecordLocation = {
  rawValue: "123 Main St, City, Region 12345, Country",
  line1: "123 Main St",
  line2: null,
  city: "City",
  region: "Region",
  postalCode: "12345",
  country: "Country"
};

// Valid: Entity with required fields
const entity: RecordEntity = {
  fullName: { givenName: "John", familyName: "Doe" },
  birthDate: { rawValue: "1990-05-15", year: 1990, month: 5, day: 15 },
  locations: [
    {
      rawValue: "123 Main St",
      line1: "123 Main St",
      city: "City",
      region: "Region",
      postalCode: "12345",
      country: "US"
    }
  ]
};

// Valid: Entity with optional fields
const entityComplete: RecordEntity = {
  fullName: { givenName: "John", familyName: "Doe" },
  birthDate: { rawValue: "1990-05-15", year: 1990, month: 5, day: 15 },
  category: "individual",
  classification: "standard",
  locations: []
};

// Invalid: Entity missing required fullName
// @ts-expect-error - fullName is required
const entityMissingFullName: RecordEntity = {
  birthDate: { rawValue: "1990-05-15", year: 1990, month: 5, day: 15 },
  locations: []
};

// Valid: Item with required fields
const item: RecordItemsItems = {
  itemId: "item-001",
  sequenceNumber: "001",
  description: "Test item",
  occurredAt: { rawValue: "2024-01-15", year: 2024, month: 1, day: 15 },
  severity: "high"
};

// Valid: Item with nullable fields as strings
const itemWithStrings: RecordItemsItems = {
  itemId: "item-002",
  sequenceNumber: "002",
  description: "Another item",
  code: "ABC123",
  occurredAt: { rawValue: "2024-01-15", year: 2024, month: 1, day: 15 },
  severity: "medium",
  resolution: "Resolved",
  remarks: "Some remarks"
};

// Valid: Item with nullable fields as null
const itemWithNulls: RecordItemsItems = {
  itemId: "item-003",
  sequenceNumber: "003",
  description: "Item with nulls",
  code: null,
  occurredAt: { rawValue: "2024-01-15", year: 2024, month: 1, day: 15 },
  severity: "low",
  resolution: null,
  remarks: null
};

// Valid: Item with resolvedAt as Timestamp (anyOf [$ref, null])
const itemResolved: RecordItemsItems = {
  itemId: "item-004",
  sequenceNumber: "004",
  description: "Resolved item",
  occurredAt: { rawValue: "2024-01-15", year: 2024, month: 1, day: 15 },
  severity: "high",
  resolvedAt: { rawValue: "2024-01-20", year: 2024, month: 1, day: 20 }
};

// Valid: Item with resolvedAt as null
const itemUnresolved: RecordItemsItems = {
  itemId: "item-005",
  sequenceNumber: "005",
  description: "Unresolved item",
  occurredAt: { rawValue: "2024-01-15", year: 2024, month: 1, day: 15 },
  severity: "high",
  resolvedAt: null
};

// Invalid: Item missing required fields
// @ts-expect-error - itemId is required
const itemMissingId: RecordItemsItems = {
  sequenceNumber: "001",
  description: "Missing ID",
  occurredAt: { rawValue: "2024-01-15", year: 2024, month: 1, day: 15 },
  severity: "high"
};

// Valid: minimal Record
const minimalRecord: Record = {
  recordId: "rec-001",
  organizationName: "Acme Corp",
  region: "US-WEST",
  entity: {
    fullName: { givenName: "John", familyName: "Doe" },
    birthDate: { rawValue: "1990-01-01", year: 1990, month: 1, day: 1 },
    locations: []
  },
  items: [
    {
      itemId: "item-001",
      sequenceNumber: "001",
      description: "First item",
      occurredAt: { rawValue: "2024-01-01", year: 2024, month: 1, day: 1 },
      severity: "low"
    }
  ]
};

// Valid: complete Record with all fields
const completeRecord: Record = {
  recordId: "rec-002",
  referenceCode: "REF-12345",
  organizationName: "Acme Corp",
  createdAt: { rawValue: "2024-01-01", year: 2024, month: 1, day: 1 },
  region: "US-EAST",
  locationInfo: {
    stateCode: "NY",
    areaCode: "212"
  },
  entity: {
    fullName: {
      rawValue: "John Michael Doe",
      givenName: "John",
      middleName: "Michael",
      familyName: "Doe",
      prefix: null,
      suffix: null
    },
    birthDate: { rawValue: "1985-06-15", year: 1985, month: 6, day: 15 },
    category: "individual",
    classification: "premium",
    locations: [
      {
        rawValue: "123 Main St, New York, NY 10001, US",
        line1: "123 Main St",
        line2: null,
        city: "New York",
        district: "Manhattan",
        region: "NY",
        postalCode: "10001",
        country: "US"
      }
    ]
  },
  notes: "Important client",
  items: [
    {
      itemId: "i-001",
      sequenceNumber: "001",
      description: "Initial item",
      code: "CODE-A",
      occurredAt: { rawValue: "2024-01-10", year: 2024, month: 1, day: 10 },
      severity: "high",
      resolution: "Addressed",
      resolvedAt: { rawValue: "2024-01-15", year: 2024, month: 1, day: 15 },
      outcome: "success",
      remarks: "Handled promptly",
      category: "support",
      subCategory: "billing",
      meta: { origin: "web", originId: "web-123" }
    },
    {
      itemId: "i-002",
      sequenceNumber: "002",
      description: "Follow-up item",
      code: null,
      occurredAt: { rawValue: "2024-01-20", year: 2024, month: 1, day: 20 },
      severity: "low",
      resolution: null,
      resolvedAt: null,
      remarks: null
    }
  ],
  meta: {
    origin: "api",
    originId: "api-456"
  }
};

// Invalid: Record missing required recordId
// @ts-expect-error - recordId is required
const recordMissingId: Record = {
  organizationName: "Acme",
  region: "US",
  entity: {
    fullName: { givenName: "John", familyName: "Doe" },
    birthDate: { rawValue: "1990-01-01", year: 1990, month: 1, day: 1 },
    locations: []
  },
  items: []
};

// Invalid: extra property on Record (additionalProperties: false)
const recordExtraProperty: Record = {
  recordId: "rec-001",
  organizationName: "Acme",
  region: "US",
  entity: {
    fullName: { givenName: "John", familyName: "Doe" },
    birthDate: { rawValue: "1990-01-01", year: 1990, month: 1, day: 1 },
    locations: []
  },
  items: [],
  // @ts-expect-error - extra property not allowed
  customField: "not allowed"
};

// Invalid: extra property on nested meta (additionalProperties: false)
const recordMetaExtra: Record = {
  recordId: "rec-001",
  organizationName: "Acme",
  region: "US",
  entity: {
    fullName: { givenName: "John", familyName: "Doe" },
    birthDate: { rawValue: "1990-01-01", year: 1990, month: 1, day: 1 },
    locations: []
  },
  items: [],
  meta: {
    origin: "test",
    // @ts-expect-error - extra property not allowed on meta
    extra: "not allowed"
  }
};
