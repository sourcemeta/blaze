NPM = npm

all: configure compile test

configure: .always
	$(NPM) ci --prefix ../../

compile: .always
	$(NPM) run build --prefix ../../

test: .always
	$(NPM) test --prefix ../../

benchmark: .always
	$(NPM) run benchmark --prefix ../../

clean: .always
	$(NPM) run clean --prefix ../../

# For NMake, which doesn't support .PHONY
.always:
