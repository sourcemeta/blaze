export type DataPipelineStagesItemsOutputType_5 = number;

export type DataPipelineStagesItemsOutputType_4 = string;

export type DataPipelineStagesItemsOutputType_3_1 = "sync" | "async";

export type DataPipelineStagesItemsOutputType_3_0 = string;

export type DataPipelineStagesItemsOutputType_3Items = never;

export type DataPipelineStagesItemsOutputType_3 = [DataPipelineStagesItemsOutputType_3_0, DataPipelineStagesItemsOutputType_3_1, ...DataPipelineStagesItemsOutputType_3Items[]];

export type DataPipelineStagesItemsOutputType_2 = Record<string, unknown>;

export type DataPipelineStagesItemsOutputType_1 = boolean;

export type DataPipelineStagesItemsOutputType_0 = null;

export type DataPipelineStagesItemsOutputType =
  DataPipelineStagesItemsOutputType_0 |
  DataPipelineStagesItemsOutputType_1 |
  DataPipelineStagesItemsOutputType_2 |
  DataPipelineStagesItemsOutputType_3 |
  DataPipelineStagesItemsOutputType_4 |
  DataPipelineStagesItemsOutputType_5;

export type DataPipelineStagesItemsName = string;

export type DataPipelineStagesItemsMetrics_5 = number;

export type DataPipelineStagesItemsMetrics_4 = string;

export type DataPipelineStagesItemsMetrics_3_2 = number;

export type DataPipelineStagesItemsMetrics_3_1 = number;

export type DataPipelineStagesItemsMetrics_3_0 = number;

export type DataPipelineStagesItemsMetrics_3Items = never;

export type DataPipelineStagesItemsMetrics_3 = [DataPipelineStagesItemsMetrics_3_0, DataPipelineStagesItemsMetrics_3_1, DataPipelineStagesItemsMetrics_3_2, ...DataPipelineStagesItemsMetrics_3Items[]];

export type DataPipelineStagesItemsMetrics_2 = Record<string, unknown>;

export type DataPipelineStagesItemsMetrics_1 = boolean;

export type DataPipelineStagesItemsMetrics_0 = null;

export type DataPipelineStagesItemsMetrics =
  DataPipelineStagesItemsMetrics_0 |
  DataPipelineStagesItemsMetrics_1 |
  DataPipelineStagesItemsMetrics_2 |
  DataPipelineStagesItemsMetrics_3 |
  DataPipelineStagesItemsMetrics_4 |
  DataPipelineStagesItemsMetrics_5;

export type DataPipelineStagesItemsInputTypes_5 = number;

export type DataPipelineStagesItemsInputTypes_4 = string;

export type DataPipelineStagesItemsInputTypes_3_1_1 = null;

export type DataPipelineStagesItemsInputTypes_3_1_0 = "required" | "optional";

export type DataPipelineStagesItemsInputTypes_3_1 =
  DataPipelineStagesItemsInputTypes_3_1_0 |
  DataPipelineStagesItemsInputTypes_3_1_1;

export type DataPipelineStagesItemsInputTypes_3_0 = "string" | "number" | "boolean" | "object" | "array";

export type DataPipelineStagesItemsInputTypes_3ItemsTypeName = string;

export type DataPipelineStagesItemsInputTypes_3ItemsNullable = boolean;

export type DataPipelineStagesItemsInputTypes_3ItemsAdditionalProperties = never;

export interface DataPipelineStagesItemsInputTypes_3Items {
  "typeName"?: DataPipelineStagesItemsInputTypes_3ItemsTypeName;
  "nullable"?: DataPipelineStagesItemsInputTypes_3ItemsNullable;
}

export type DataPipelineStagesItemsInputTypes_3 = [DataPipelineStagesItemsInputTypes_3_0, DataPipelineStagesItemsInputTypes_3_1, ...DataPipelineStagesItemsInputTypes_3Items[]];

export type DataPipelineStagesItemsInputTypes_2 = Record<string, unknown>;

export type DataPipelineStagesItemsInputTypes_1 = boolean;

export type DataPipelineStagesItemsInputTypes_0 = null;

export type DataPipelineStagesItemsInputTypes =
  DataPipelineStagesItemsInputTypes_0 |
  DataPipelineStagesItemsInputTypes_1 |
  DataPipelineStagesItemsInputTypes_2 |
  DataPipelineStagesItemsInputTypes_3 |
  DataPipelineStagesItemsInputTypes_4 |
  DataPipelineStagesItemsInputTypes_5;

export type DataPipelineStagesItemsConfig_1 = null;

export type DataPipelineStagesItemsConfig_0Timeout = number;

export type DataPipelineStagesItemsConfig_0Retries = number;

export type DataPipelineStagesItemsConfig_0AdditionalProperties = never;

export interface DataPipelineStagesItemsConfig_0 {
  "timeout"?: DataPipelineStagesItemsConfig_0Timeout;
  "retries"?: DataPipelineStagesItemsConfig_0Retries;
}

export type DataPipelineStagesItemsConfig =
  DataPipelineStagesItemsConfig_0 |
  DataPipelineStagesItemsConfig_1;

export type DataPipelineStagesItemsAdditionalProperties = never;

export interface DataPipelineStagesItems {
  "name": DataPipelineStagesItemsName;
  "inputTypes": DataPipelineStagesItemsInputTypes;
  "outputType": DataPipelineStagesItemsOutputType;
  "config"?: DataPipelineStagesItemsConfig;
  "metrics"?: DataPipelineStagesItemsMetrics;
}

export type DataPipelineStages = DataPipelineStagesItems[];

export type DataPipelinePipelineVersion_5 = number;

export type DataPipelinePipelineVersion_4 = string;

export type DataPipelinePipelineVersion_3_2 = number;

export type DataPipelinePipelineVersion_3_1 = number;

export type DataPipelinePipelineVersion_3_0 = number;

export type DataPipelinePipelineVersion_3Items = never;

export type DataPipelinePipelineVersion_3 = [DataPipelinePipelineVersion_3_0, DataPipelinePipelineVersion_3_1, DataPipelinePipelineVersion_3_2, ...DataPipelinePipelineVersion_3Items[]];

export type DataPipelinePipelineVersion_2 = Record<string, unknown>;

export type DataPipelinePipelineVersion_1 = boolean;

export type DataPipelinePipelineVersion_0 = null;

export type DataPipelinePipelineVersion =
  DataPipelinePipelineVersion_0 |
  DataPipelinePipelineVersion_1 |
  DataPipelinePipelineVersion_2 |
  DataPipelinePipelineVersion_3 |
  DataPipelinePipelineVersion_4 |
  DataPipelinePipelineVersion_5;

export type DataPipelinePipelineTagsItems = string;

export type DataPipelinePipelineTags = DataPipelinePipelineTagsItems[];

export type DataPipelinePipelineId = string;

export type DataPipelinePipelineCoordinates_5 = number;

export type DataPipelinePipelineCoordinates_4 = string;

export type DataPipelinePipelineCoordinates_3_2 = number;

export type DataPipelinePipelineCoordinates_3_1 = number;

export type DataPipelinePipelineCoordinates_3_0 = number;

export type DataPipelinePipelineCoordinates_3Items = number;

export type DataPipelinePipelineCoordinates_3 = [DataPipelinePipelineCoordinates_3_0, DataPipelinePipelineCoordinates_3_1, DataPipelinePipelineCoordinates_3_2, ...DataPipelinePipelineCoordinates_3Items[]];

export type DataPipelinePipelineCoordinates_2 = Record<string, unknown>;

export type DataPipelinePipelineCoordinates_1 = boolean;

export type DataPipelinePipelineCoordinates_0 = null;

export type DataPipelinePipelineCoordinates =
  DataPipelinePipelineCoordinates_0 |
  DataPipelinePipelineCoordinates_1 |
  DataPipelinePipelineCoordinates_2 |
  DataPipelinePipelineCoordinates_3 |
  DataPipelinePipelineCoordinates_4 |
  DataPipelinePipelineCoordinates_5;

export type DataPipelinePipelineAdditionalProperties = never;

export interface DataPipelinePipeline {
  "id": DataPipelinePipelineId;
  "version": DataPipelinePipelineVersion;
  "coordinates": DataPipelinePipelineCoordinates;
  "tags"?: DataPipelinePipelineTags;
}

export type DataPipelineMetadataModifiedAt_1 = null;

export type DataPipelineMetadataModifiedAt_0 = string;

export type DataPipelineMetadataModifiedAt =
  DataPipelineMetadataModifiedAt_0 |
  DataPipelineMetadataModifiedAt_1;

export type DataPipelineMetadataFlags_5 = number;

export type DataPipelineMetadataFlags_4 = string;

export type DataPipelineMetadataFlags_3_2 = boolean;

export type DataPipelineMetadataFlags_3_1 = boolean;

export type DataPipelineMetadataFlags_3_0 = boolean;

export type DataPipelineMetadataFlags_3Items = never;

export type DataPipelineMetadataFlags_3 = [DataPipelineMetadataFlags_3_0, DataPipelineMetadataFlags_3_1, DataPipelineMetadataFlags_3_2, ...DataPipelineMetadataFlags_3Items[]];

export type DataPipelineMetadataFlags_2 = Record<string, unknown>;

export type DataPipelineMetadataFlags_1 = boolean;

export type DataPipelineMetadataFlags_0 = null;

export type DataPipelineMetadataFlags =
  DataPipelineMetadataFlags_0 |
  DataPipelineMetadataFlags_1 |
  DataPipelineMetadataFlags_2 |
  DataPipelineMetadataFlags_3 |
  DataPipelineMetadataFlags_4 |
  DataPipelineMetadataFlags_5;

export type DataPipelineMetadataCreatedAt = string;

export type DataPipelineMetadataAuthorsItems_5 = number;

export type DataPipelineMetadataAuthorsItems_4 = string;

export type DataPipelineMetadataAuthorsItems_3_1 = string;

export type DataPipelineMetadataAuthorsItems_3_0 = string;

export type DataPipelineMetadataAuthorsItems_3Items = string;

export type DataPipelineMetadataAuthorsItems_3 = [DataPipelineMetadataAuthorsItems_3_0, DataPipelineMetadataAuthorsItems_3_1, ...DataPipelineMetadataAuthorsItems_3Items[]];

export type DataPipelineMetadataAuthorsItems_2 = Record<string, unknown>;

export type DataPipelineMetadataAuthorsItems_1 = boolean;

export type DataPipelineMetadataAuthorsItems_0 = null;

export type DataPipelineMetadataAuthorsItems =
  DataPipelineMetadataAuthorsItems_0 |
  DataPipelineMetadataAuthorsItems_1 |
  DataPipelineMetadataAuthorsItems_2 |
  DataPipelineMetadataAuthorsItems_3 |
  DataPipelineMetadataAuthorsItems_4 |
  DataPipelineMetadataAuthorsItems_5;

export type DataPipelineMetadataAuthors = DataPipelineMetadataAuthorsItems[];

export type DataPipelineMetadataAdditionalProperties = never;

export interface DataPipelineMetadata {
  "createdAt"?: DataPipelineMetadataCreatedAt;
  "modifiedAt"?: DataPipelineMetadataModifiedAt;
  "authors"?: DataPipelineMetadataAuthors;
  "flags"?: DataPipelineMetadataFlags;
}

export type DataPipelineConnectionsItems_5 = number;

export type DataPipelineConnectionsItems_4 = string;

export type DataPipelineConnectionsItems_3_2Weight = number;

export type DataPipelineConnectionsItems_3_2Bidirectional = boolean;

export type DataPipelineConnectionsItems_3_2AdditionalProperties = never;

export interface DataPipelineConnectionsItems_3_2 {
  "weight": DataPipelineConnectionsItems_3_2Weight;
  "bidirectional"?: DataPipelineConnectionsItems_3_2Bidirectional;
}

export type DataPipelineConnectionsItems_3_1 = string;

export type DataPipelineConnectionsItems_3_0 = string;

export type DataPipelineConnectionsItems_3Items = never;

export type DataPipelineConnectionsItems_3 = [DataPipelineConnectionsItems_3_0, DataPipelineConnectionsItems_3_1, DataPipelineConnectionsItems_3_2, ...DataPipelineConnectionsItems_3Items[]];

export type DataPipelineConnectionsItems_2 = Record<string, unknown>;

export type DataPipelineConnectionsItems_1 = boolean;

export type DataPipelineConnectionsItems_0 = null;

export type DataPipelineConnectionsItems =
  DataPipelineConnectionsItems_0 |
  DataPipelineConnectionsItems_1 |
  DataPipelineConnectionsItems_2 |
  DataPipelineConnectionsItems_3 |
  DataPipelineConnectionsItems_4 |
  DataPipelineConnectionsItems_5;

export type DataPipelineConnections = DataPipelineConnectionsItems[];

export type DataPipelineAdditionalProperties = never;

export interface DataPipeline {
  "pipeline": DataPipelinePipeline;
  "stages": DataPipelineStages;
  "connections": DataPipelineConnections;
  "metadata"?: DataPipelineMetadata;
}
