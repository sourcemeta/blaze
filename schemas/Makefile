SCHEMAS = \
	canonical-draft2.json \
	canonical-draft3.json \
	canonical-draft4.json \
	canonical-draft6.json \
	canonical-draft7.json \
	canonical-2019-09.json \
	canonical-2020-12.json
TESTS = \
	canonical-draft2.test.json \
	canonical-draft3.test.json \
	canonical-draft4.test.json \
	canonical-draft6.test.json \
	canonical-draft7.test.json \
	canonical-2019-09.test.json \
	canonical-2020-12.test.json
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
