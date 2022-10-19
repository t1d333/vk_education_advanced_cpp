.PHONY: all build check clean

all: check  build clean

clean:
	rm -rf build

check:
	cpplint --extensions=cpp,hpp project/include/* project/src/* 
	cppcheck project --enable=all --inconclusive --error-exitcode=1 -I project/include --suppress=missingIncludeSystem 
	clang-tidy project/src/* project/include/* -warnings-as-errors=* -- -x c++ -Iproject/include

build:
	cmake -S . -B build
	cmake --build build/
