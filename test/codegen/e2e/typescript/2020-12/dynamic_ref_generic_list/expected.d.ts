export type StringList_0 = StringListGenericList;

export type StringListStringItem = string;

export type StringListGenericListItems =
  StringListGenericListDefaultItem |
  StringListStringItem;

export type StringListGenericListDefaultItem_5 = number;

export type StringListGenericListDefaultItem_4 = string;

export type StringListGenericListDefaultItem_3Items = unknown;

export type StringListGenericListDefaultItem_3 = StringListGenericListDefaultItem_3Items[];

export type StringListGenericListDefaultItem_2 = Record<string, unknown>;

export type StringListGenericListDefaultItem_1 = boolean;

export type StringListGenericListDefaultItem_0 = null;

export type StringListGenericListDefaultItem =
  StringListGenericListDefaultItem_0 |
  StringListGenericListDefaultItem_1 |
  StringListGenericListDefaultItem_2 |
  StringListGenericListDefaultItem_3 |
  StringListGenericListDefaultItem_4 |
  StringListGenericListDefaultItem_5;

export type StringListGenericList = StringListGenericListItems[];

export type StringList = StringList_0;
