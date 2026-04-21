export type TreeNodeParent = TreeNode;

export type TreeNodeName = string;

export type TreeNodeChildrenItems = TreeNode;

export type TreeNodeChildren = TreeNodeChildrenItems[];

export type TreeNodeAdditionalProperties = never;

export interface TreeNode {
  "name": TreeNodeName;
  "children"?: TreeNodeChildren;
  "parent"?: TreeNodeParent;
}
