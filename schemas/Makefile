SCHEMAS = canonical-draft4.json canonical-draft6.json
TESTS = canonical-draft4.test.json canonical-draft6.test.json
JSONSCHEMA ?= jsonschema

.PHONY: all
all:
	$(JSONSCHEMA) fmt $(SCHEMAS) $(TESTS)
	$(JSONSCHEMA) metaschema $(SCHEMAS)
	$(JSONSCHEMA) lint $(SCHEMAS)
	$(JSONSCHEMA) test $(TESTS)

.PHONY: ci
ci:
	$(JSONSCHEMA) fmt $(SCHEMAS) $(TESTS) --check
	$(JSONSCHEMA) metaschema $(SCHEMAS)
	$(JSONSCHEMA) lint $(SCHEMAS)
	$(JSONSCHEMA) test $(TESTS)
