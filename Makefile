# Programs
CMAKE = cmake
CTEST = ctest

# Options
PRESET = Debug
SHARED = OFF

all: configure compile test

configure: .always
	$(CMAKE) -S . -B ./build \
		-DCMAKE_BUILD_TYPE:STRING=$(PRESET) \
		-DCMAKE_COMPILE_WARNING_AS_ERROR:BOOL=ON \
		-DBLAZE_TESTS:BOOL=ON \
		-DBLAZE_BENCHMARK:BOOL=ON \
		-DBLAZE_CONTRIB:BOOL=ON \
		-DBLAZE_DOCS:BOOL=ON \
		-DBUILD_SHARED_LIBS:BOOL=$(SHARED)

compile: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_format
	$(CMAKE) --build ./build --config $(PRESET) --parallel 4
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_core
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_core_dev
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_blaze
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_blaze_dev

test: .always
	$(CMAKE) -E env UBSAN_OPTIONS=print_stacktrace=1 \
		$(CTEST) --test-dir ./build --build-config $(PRESET) \
			--output-on-failure --parallel

benchmark: .always
	$(CMAKE) --build ./build --config $(PRESET) --target benchmark_all

doxygen: .always
	$(CMAKE) --build ./build --config $(PRESET) --target doxygen

clean: .always
	$(CMAKE) -E rm -R -f build

# For NMake, which doesn't support .PHONY
.always:
