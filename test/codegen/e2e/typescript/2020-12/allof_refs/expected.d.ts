export type Person_1 = PersonAged;

export type Person_0 = PersonNamed;

export type PersonNamedName = string;

export type PersonNamedAdditionalProperties = never;

export interface PersonNamed {
  "name": PersonNamedName;
}

export type PersonAgedAge = number;

export type PersonAgedAdditionalProperties = never;

export interface PersonAged {
  "age": PersonAgedAge;
}

export type Person =
  Person_0 &
  Person_1;
