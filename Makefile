.PHONY: all build check clean rebuild

all: check  build clean rebuild

clean:
	rm -rf build 
check:
	./scripts/lint.sh
build:
	cmake -S . -B build
	cmake --build build/

rebuild: clean build


test: rebuild
	cd build && ctest -V -R
