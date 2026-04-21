import { TreeNode } from "./expected";


// Valid: minimal node with just name
const leaf: TreeNode = {
  name: "leaf"
};

// Valid: node with children
const parent: TreeNode = {
  name: "parent",
  children: [
    { name: "child1" },
    { name: "child2" }
  ]
};

// Valid: deeply nested structure
const root: TreeNode = {
  name: "root",
  children: [
    {
      name: "branch1",
      children: [
        { name: "leaf1" },
        { name: "leaf2" }
      ]
    },
    {
      name: "branch2",
      children: []
    }
  ]
};

// Valid: node with parent reference
const childWithParent: TreeNode = {
  name: "child",
  parent: { name: "myParent" }
};

// Valid: complex tree with parent references
const complexTree: TreeNode = {
  name: "root",
  children: [
    {
      name: "child",
      parent: { name: "root" },
      children: [
        { name: "grandchild" }
      ]
    }
  ]
};

// Invalid: missing required name
// @ts-expect-error - name is required
const missingName: TreeNode = {
  children: []
};

// Invalid: wrong type for name
const wrongNameType: TreeNode = {
  // @ts-expect-error - name must be string
  name: 123
};

// Invalid: children must be array of TreeNode
const wrongChildrenType: TreeNode = {
  name: "node",
  // @ts-expect-error - children must be array of TreeNode
  children: "not an array"
};

// Invalid: extra property (additionalProperties: false)
const extraProperty: TreeNode = {
  name: "node",
  // @ts-expect-error - extra property not allowed
  extra: "not allowed"
};
