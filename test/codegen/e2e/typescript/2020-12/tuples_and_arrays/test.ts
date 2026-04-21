import {
  DataPipeline,
  DataPipelinePipeline,
  DataPipelineStagesItems
} from "./expected";


// Valid: minimal required fields
const minimal: DataPipeline = {
  pipeline: {
    id: "pipeline-1",
    version: [ 1, 0, 0 ],
    coordinates: [ 0, 0, 0 ]
  },
  stages: [],
  connections: []
};

// Valid: version tuple
const validVersion: DataPipeline = {
  pipeline: {
    id: "p1",
    version: [ 1, 2, 3 ],
    coordinates: [ 0, 0, 0 ]
  },
  stages: [],
  connections: []
};

// Valid: coordinates can have more than 3 numbers (items: { type: number })
const validCoordinatesExtended: DataPipeline = {
  pipeline: {
    id: "p1",
    version: [ 1, 0, 0 ],
    coordinates: [ 1.5, 2.5, 3.5, 4.5, 5.5 ]
  },
  stages: [],
  connections: []
};

// Valid: stage with inputTypes tuple
const validStage: DataPipelineStagesItems = {
  name: "transform",
  inputTypes: [ "string", "required" ],
  outputType: [ "output", "sync" ]
};

// Valid: stage inputTypes with additional items
const validStageExtended: DataPipelineStagesItems = {
  name: "transform",
  inputTypes: [ "number", "optional", { typeName: "custom" } ],
  outputType: [ "result", "async" ]
};

// These would be valid in the generated TS but invalid per intended schema semantics:
const versionAsNumber: DataPipeline = {
  pipeline: {
    id: "p1",
    version: 100,  // Allowed because schema lacks type: "array"
    coordinates: [ 0, 0, 0 ]
  },
  stages: [],
  connections: []
};

const versionAsString: DataPipeline = {
  pipeline: {
    id: "p1",
    version: "1.0.0",  // Allowed because schema lacks type: "array"
    coordinates: [ 0, 0, 0 ]
  },
  stages: [],
  connections: []
};

// Invalid: missing required pipeline
// @ts-expect-error
const missingPipeline: DataPipeline = {
  stages: [],
  connections: []
};

// Invalid: missing required id in pipeline
const missingPipelineId: DataPipeline = {
  // @ts-expect-error
  pipeline: {
    version: [ 1, 0, 0 ],
    coordinates: [ 0, 0, 0 ]
  },
  stages: [],
  connections: []
};

// Invalid: extra property on pipeline (additionalProperties: false)
const invalidPipelineExtra: DataPipeline = {
  pipeline: {
    id: "p1",
    version: [ 1, 0, 0 ],
    coordinates: [ 0, 0, 0 ],
    // @ts-expect-error
    extra: "not allowed"
  },
  stages: [],
  connections: []
};

// Invalid: stage missing required name
// @ts-expect-error
const invalidStageMissingName: DataPipelineStagesItems = {
  inputTypes: [ "string", "required" ],
  outputType: [ "out", "sync" ]
};

// Invalid: extra property on stage (additionalProperties: false)
const invalidStageExtra: DataPipelineStagesItems = {
  name: "test",
  inputTypes: [ "string", "required" ],
  outputType: [ "out", "sync" ],
  // @ts-expect-error
  extra: "not allowed"
};

// Valid: full example
const fullExample: DataPipeline = {
  pipeline: {
    id: "data-etl",
    version: [ 2, 1, 0 ],
    coordinates: [ 10.5, 20.5, 30.5 ],
    tags: [ "production", "etl" ]
  },
  stages: [
    {
      name: "extract",
      inputTypes: [ "object", null ],
      outputType: [ "raw-data", "async" ],
      config: { timeout: 5000, retries: 3 }
    },
    {
      name: "transform",
      inputTypes: [ "string", "required", { typeName: "custom", nullable: false } ],
      outputType: [ "transformed", "sync" ],
      metrics: [ 1.0, 2.0, 3.0 ]
    }
  ],
  connections: [
    [ "extract", "transform", { weight: 1.0 } ],
    [ "transform", "load", { weight: 0.5, bidirectional: false } ]
  ],
  metadata: {
    createdAt: "2024-01-01",
    modifiedAt: "2024-06-01",
    authors: [
      [ "John", "Doe" ],
      [ "Jane", "Smith", "PhD" ]
    ],
    flags: [ true, false, true ]
  }
};
