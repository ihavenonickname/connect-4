.PHONY := clean

CPPC := clang++
CPPFLAGS := -std=c++11 -Werror -Wall -Wpedantic -Wconversion

SRCS := $(wildcard src/*.cpp)
TSTS := $(wildcard test/*.cpp)
BINS := $(SRCS:%.cpp=%) + $(TSTS:%.cpp=%)
INCL := -Ivendor -Isrc

build/main: ${SRCS}
	@echo "Compiling ${SRCS}"
	${CPPC} ${CPPFLAGS} ${INCL} ${SRCS} -o build/main

clean:
	@echo "Removing garbage"
	rm -rf run_test

run_test: ${TSTS} ${SRCS}
	${CPPC} -std=c++11 ${INCL} ${TSTS} ${SRCS} -o run_test
