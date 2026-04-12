SCHEMAS = canonical-draft4.json
TESTS = canonical-draft4.test.json

.PHONY: all
all:
	jsonschema fmt $(SCHEMAS) $(TESTS) --default-dialect "https://json-schema.org/draft/2020-12/schema"
	jsonschema metaschema $(SCHEMAS)
	jsonschema lint $(SCHEMAS)
	jsonschema test $(TESTS)
