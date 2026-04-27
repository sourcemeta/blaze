export type Template = Array<unknown>;

export type EvaluationCallback = (
  type: "pre" | "post",
  valid: boolean,
  instruction: unknown[],
  evaluatePath: string,
  instanceLocation: string,
  annotation: unknown
) => void;

export type StandardOutputFormat = 'flag' | 'basic';

export interface StandardOutputErrorEntry {
  keywordLocation: string;
  absoluteKeywordLocation: string;
  instanceLocation: string;
  error: string;
}

export interface StandardOutputAnnotationEntry {
  keywordLocation: string;
  absoluteKeywordLocation: string;
  instanceLocation: string;
  annotation: unknown[];
}

export type StandardOutputResult =
  | { valid: true; annotations?: StandardOutputAnnotationEntry[] }
  | { valid: false; errors: StandardOutputErrorEntry[] };

export declare class Blaze {
  static reviver(
    key: string,
    value: unknown,
    context: { source: string }
  ): unknown;
  constructor(template: Template);
  validate(instance: unknown): boolean;
  validate(instance: unknown, callback: EvaluationCallback): boolean;
  validate(instance: unknown, format: StandardOutputFormat): StandardOutputResult;
}

export declare function describe(
  valid: boolean,
  instruction: unknown[],
  evaluatePath: string,
  instanceLocation: string,
  instance: unknown,
  annotation: unknown
): string;
