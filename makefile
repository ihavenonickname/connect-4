.PHONY := clean tests

CPPC := clang++
CPPFLAGS := -std=c++11 -Werror -Wall -Wpedantic -Wconversion

LINTER = cppcheck
LINTERFLAGS =  --std=c++11 --enable=all  --error-exitcode=1

SRCS := $(wildcard src/*.cpp)
TSTS := $(wildcard test/*.cpp)
INCL := -Ivendor -Isrc

clean:
	@echo "Removing garbage..."
	rm -rf *.o run_test
	@echo "Ok"

tests:
	@echo "Checking code with linter..."
	${LINTER} ${LINTERFLAGS} ${SRCS} ${TSTS}
	@echo "Ok"

	@echo "Checking code with compiler..."
	${CPPC} ${CPPFLAGS} ${INCL} ${SRCS} -c
	@echo "Ok"

	@echo "Building test executable..."
	${CPPC} ${INCL} ${TSTS} ${SRCS} -o run_tests
	@echo "Ok"
