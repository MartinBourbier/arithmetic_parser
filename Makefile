CC = g++
CFLAGS = -Wall -Wextra -pedantic -O3
LDFLAGS = -lcriterion

SRC = src/main.cpp \
	  src/monomial.cpp \
	  src/polynomial.cpp \
	  src/token.cpp \
	  src/lexer.cpp \
	  src/ast.cpp \
	  src/parser.cpp \
	  src/evaluator.cpp \
	  src/reducto.cpp
OBJ = ${SRC:.cpp=.o}

SRC_TESTS = tests/sanity.cpp \
			tests/test_monomial.cpp \
			tests/test_polynomial.cpp \
			tests/test_token.cpp \
			tests/test_step0.cpp
OBJ_TESTS = ${SRC_TESTS:.cpp=.o}

all: build check

build: ${OBJ}
	${CC} ${CFLAGS} $^ -o $@

check: ${OBJ_TESTS} \
	src/monomial.o \
	src/polynomial.o \
	src/token.o \
	src/ast.o \
	src/lexer.o \
	src/parser.o \
	src/evaluator.o \
	src/reducto.o
	${CC} ${CFLAGS} $^ -o $@ ${LDFLAGS}

clean:
	${RM} build
	${RM} check
	${RM} ${OBJ}
	${RM} ${OBJ_TESTS}

.PHONY: all clean
