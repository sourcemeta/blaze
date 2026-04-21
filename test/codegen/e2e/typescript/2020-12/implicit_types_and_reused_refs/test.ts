import {
  DocSystem,
  DocSystemUser,
  DocSystemTimestamp,
  DocSystemDocument,
  DocSystemPermissions,
  DocSystemHistoryItems
} from "./expected";


// Valid: minimal required fields
const minimal: DocSystem = {
  document: {
    id: "doc-uuid-1",
    title: "Test Document",
    content: {
      format: "markdown",
      body: "# Hello"
    },
    author: {
      id: "user-uuid-1",
      email: "author@example.com"
    }
  },
  permissions: {
    owner: { id: "user-uuid-1", email: "owner@example.com" },
    readers: [],
    editors: []
  },
  history: []
};

// Valid: User with all fields including role enum
const userWithRole: DocSystemUser = {
  id: "user-123",
  email: "user@example.com",
  displayName: "John Doe",
  role: "admin"
};

// Valid: User with null displayName (anyOf [string, null])
const userNullDisplay: DocSystemUser = {
  id: "user-123",
  email: "user@example.com",
  displayName: null
};

// Invalid: User role must be from enum
const invalidRole: DocSystemUser = {
  id: "user-123",
  email: "user@example.com",
  // @ts-expect-error - role must be admin|editor|viewer|guest
  role: "superuser"
};

// Valid: Timestamp with all fields
const timestamp: DocSystemTimestamp = {
  unix: 1704067200,
  iso: "2024-01-01T00:00:00Z",
  timezone: "UTC"
};

// Valid: Timestamp with null timezone
const timestampNullTz: DocSystemTimestamp = {
  unix: 1704067200,
  iso: "2024-01-01T00:00:00Z",
  timezone: null
};

// Invalid: Timestamp missing required unix
// @ts-expect-error - unix is required
const timestampMissingUnix: DocSystemTimestamp = {
  iso: "2024-01-01T00:00:00Z"
};

// Valid: Document with format enum values
const docMarkdown: DocSystemDocument = {
  id: "doc-1",
  title: "Markdown Doc",
  content: { format: "markdown", body: "# Title" },
  author: { id: "user-1", email: "a@b.com" }
};

const docHtml: DocSystemDocument = {
  id: "doc-2",
  title: "HTML Doc",
  content: { format: "html", body: "<h1>Title</h1>" },
  author: { id: "user-1", email: "a@b.com" }
};

const docPlaintext: DocSystemDocument = {
  id: "doc-3",
  title: "Plain Doc",
  content: { format: "plaintext", body: "Title" },
  author: { id: "user-1", email: "a@b.com" }
};

// Invalid: format must be from enum
const invalidFormat: DocSystemDocument = {
  id: "doc-1",
  title: "Doc",
  content: {
    // @ts-expect-error - format must be markdown|html|plaintext
    format: "rtf",
    body: "text"
  },
  author: { id: "user-1", email: "a@b.com" }
};

// Valid: permissions with isPublic boolean enum
const permissionsPublic: DocSystemPermissions = {
  owner: { id: "user-1", email: "owner@a.com" },
  readers: [],
  editors: [],
  isPublic: true
};

const permissionsPrivate: DocSystemPermissions = {
  owner: { id: "user-1", email: "owner@a.com" },
  readers: [],
  editors: [],
  isPublic: false
};

// Valid: permissions with expiresAt as Timestamp
const permissionsWithExpiry: DocSystemPermissions = {
  owner: { id: "user-1", email: "owner@a.com" },
  readers: [],
  editors: [],
  expiresAt: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" }
};

// Valid: permissions with expiresAt as null
const permissionsNoExpiry: DocSystemPermissions = {
  owner: { id: "user-1", email: "owner@a.com" },
  readers: [],
  editors: [],
  expiresAt: null
};

// Valid: history item with all action enum values
const historyCreated: DocSystemHistoryItems = {
  action: "created",
  actor: { id: "user-1", email: "a@b.com" },
  timestamp: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" }
};

const historyUpdated: DocSystemHistoryItems = {
  action: "updated",
  actor: { id: "user-1", email: "a@b.com" },
  timestamp: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" },
  details: { field: "title", oldValue: "Old", newValue: "New" }
};

const historyDeleted: DocSystemHistoryItems = {
  action: "deleted",
  actor: { id: "user-1", email: "a@b.com" },
  timestamp: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" }
};

const historyRestored: DocSystemHistoryItems = {
  action: "restored",
  actor: { id: "user-1", email: "a@b.com" },
  timestamp: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" }
};

const historyShared: DocSystemHistoryItems = {
  action: "shared",
  actor: { id: "user-1", email: "a@b.com" },
  timestamp: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" }
};

// Invalid: action must be from enum
const historyInvalidAction: DocSystemHistoryItems = {
  // @ts-expect-error - action must be created|updated|deleted|restored|shared
  action: "archived",
  actor: { id: "user-1", email: "a@b.com" },
  timestamp: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" }
};

// Valid: history with details having number oldValue/newValue
const historyNumericChange: DocSystemHistoryItems = {
  action: "updated",
  actor: { id: "user-1", email: "a@b.com" },
  timestamp: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" },
  details: { field: "version", oldValue: 1, newValue: 2 }
};

// Valid: history with details as null
const historyNullDetails: DocSystemHistoryItems = {
  action: "created",
  actor: { id: "user-1", email: "a@b.com" },
  timestamp: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" },
  details: null
};

// Valid: full example with relatedDocuments
const fullExample: DocSystem = {
  document: {
    id: "doc-main",
    title: "Main Document",
    content: {
      format: "markdown",
      body: "# Main\n\nContent here",
      summary: "A summary"
    },
    author: { id: "author-1", email: "author@example.com", displayName: "Author", role: "editor" },
    reviewers: [
      { id: "reviewer-1", email: "r1@example.com", role: "viewer" },
      { id: "reviewer-2", email: "r2@example.com", displayName: null }
    ],
    tags: [
      { name: "important", color: "red" },
      { name: "draft", color: null }
    ],
    metadata: {
      createdAt: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" },
      updatedAt: { unix: 1706745600, iso: "2024-02-01T00:00:00Z", timezone: "America/New_York" },
      version: 3
    }
  },
  permissions: {
    owner: { id: "author-1", email: "author@example.com" },
    readers: [ { id: "reader-1", email: "reader@example.com" } ],
    editors: [ { id: "editor-1", email: "editor@example.com", role: "editor" } ],
    isPublic: false,
    expiresAt: { unix: 1735689600, iso: "2025-01-01T00:00:00Z" }
  },
  history: [
    { action: "created", actor: { id: "author-1", email: "author@example.com" }, timestamp: { unix: 1704067200, iso: "2024-01-01T00:00:00Z" } },
    { action: "updated", actor: { id: "editor-1", email: "editor@example.com" }, timestamp: { unix: 1706745600, iso: "2024-02-01T00:00:00Z" }, details: { field: "title", oldValue: "Draft", newValue: "Main Document" } }
  ],
  relatedDocuments: [
    { id: "related-1", relationship: "parent", title: "Parent Doc" },
    { id: "related-2", relationship: "child" },
    { id: "related-3", relationship: "sibling", title: null },
    { id: "related-4", relationship: "reference", title: "Referenced Doc" }
  ]
};

// Invalid: relationship must be from enum
const invalidRelationship: DocSystem = {
  document: {
    id: "doc-1",
    title: "Doc",
    content: { format: "markdown", body: "text" },
    author: { id: "user-1", email: "a@b.com" }
  },
  permissions: { owner: { id: "user-1", email: "a@b.com" }, readers: [], editors: [] },
  history: [],
  relatedDocuments: [
    // @ts-expect-error - relationship must be parent|child|sibling|reference
    { id: "rel-1", relationship: "linked" }
  ]
};
