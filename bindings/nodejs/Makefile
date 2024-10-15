# For greater flexibility, this Makefile requires GNU Make
# and various other UNIX utilities.
# If you are on Windows, please use the WSL instead of NMAKE.

# Programs
EMCC ?= emcc
MKDIR ?= mkdir
SED ?= sed
NODE ?= node
CMAKE ?= cmake

# Misc
ROOT := ../..

# Flags
CFLAGS ?= -O3 -std=c11 -flto
CXXFLAGS ?= -O3 -std=c++20 -flto \
	-I$(ROOT)/vendor/uriparser/include \
	-I$(ROOT)/src/uri/include \
	-I$(ROOT)/src/json/include \
	-I$(ROOT)/src/jsonpointer/include \
	-I$(ROOT)/src/evaluator/include \
	-I$(ROOT)/src/jsonschema/include \
	-DSOURCEMETA_JSONTOOLKIT_URI_EXPORT= \
	-DSOURCEMETA_JSONTOOLKIT_JSON_EXPORT= \
	-DSOURCEMETA_JSONTOOLKIT_JSONPOINTER_EXPORT= \
	-DSOURCEMETA_JSONTOOLKIT_EVALUATOR_EXPORT= \
	-DSOURCEMETA_JSONTOOLKIT_JSONSCHEMA_EXPORT=

# See https://emscripten.org/docs/tools_reference/settings_reference.html
LDFLAGS ?= -lembind -s EXPORT_NAME=jsontoolkit \
					 -s EVAL_CTORS=2 -s WASM=1 -s NO_EXIT_RUNTIME=1 -s ASSERTIONS=0 \
					 -s MODULARIZE=1 -s EXPORT_ES6=1 -s ENVIRONMENT=node

.PHONY: all
all: compile test
.PHONY: compile
compile: build/wrapper.js
.PHONY: test
test: test.js
	$(NODE) $<

build: ; $(MKDIR) $@
build/uri: | build; $(MKDIR) $@
build/json: | build; $(MKDIR) $@
build/jsonpointer: | build; $(MKDIR) $@
build/evaluator: | build; $(MKDIR) $@
build/jsonschema: | build; $(MKDIR) $@

# URIParser
build/uriparser: | build; $(MKDIR) $@
build/uriparser/UriConfig.h: $(ROOT)/vendor/uriparser/src/UriConfig.h.in | build/uriparser
	$(SED) -e 's/@PROJECT_VERSION@/0.0.0/g' -e 's/#cmakedefine/#undef/g' $< > $@
build/uriparser/%.o: $(ROOT)/vendor/uriparser/src/%.c build/uriparser/UriConfig.h | build/uriparser
	$(EMCC) $(CFLAGS) -o $@ $< -I$(ROOT)/vendor/uriparser/include -I$(dir $(word 2,$^)) -c

build/jsonschema/official_resolver.in.cc: \
	$(ROOT)/src/jsonschema/official_resolver.cmake \
	$(ROOT)/src/jsonschema/official_resolver.in.cc \
	| build/jsonschema
	$(CMAKE) \
		-DPROJECT_SOURCE_DIR=$(ROOT)/ \
		-DOFFICIAL_RESOLVER_INPUT=$(ROOT)/src/jsonschema/official_resolver.in.cc \
		-DOFFICIAL_RESOLVER_OUTPUT=$@ -P $<

build/%.o: build/%.cc \
	| build/uri build/json build/jsonpointer build/evaluator build/jsonschema
	$(EMCC) $(CXXFLAGS) -o $@ -c $<
build/%.o: $(ROOT)/src/%.cc \
	| build/uri build/json build/jsonpointer build/evaluator build/jsonschema
	$(EMCC) $(CXXFLAGS) -o $@ -c $<

build/%.js: %.cc \
	$(patsubst ../../vendor/uriparser/src/%.c,build/uriparser/%.o,$(wildcard $(ROOT)/vendor/uriparser/src/*.c)) \
	$(patsubst ../../src/%.cc,build/%.o,$(wildcard $(ROOT)/src/uri/*.cc)) \
	$(patsubst ../../src/%.cc,build/%.o,$(wildcard $(ROOT)/src/json/*.cc)) \
	$(patsubst ../../src/%.cc,build/%.o,$(wildcard $(ROOT)/src/jsonpointer/*.cc)) \
	$(patsubst ../../src/%.cc,build/%.o,$(wildcard $(ROOT)/src/evaluator/*.cc)) \
	$(patsubst ../../src/%.cc,build/%.o,$(wildcard $(ROOT)/src/jsonschema/*.cc)) \
	| build
	$(EMCC) $(CXXFLAGS) $(LDFLAGS) -o $@ $^
