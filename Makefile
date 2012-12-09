CC ?= gcc
# CFLAGS ?= -std=c99
CFDEBUG = -pedantic -Wall -g

EXEC = vector
SRCS = vector.c main.c
OBJS = ${SRCS:.c=.o}

all: ${EXEC}

.c.o:
	${CC} ${CFLAGS} -o $@ -c $<

${EXEC}: ${OBJS}
	${CC} ${LDFLAGS} -g -o ${EXEC} ${OBJS}

lib: ${OBJS}
	${CC} -c hash.c -o hash.o
	ar rcs libhash.a hash.o

debug: ${EXEC}
debug: CC += ${CFDEBUG}

test: debug
	./${EXEC}

clean:
	rm -rf ./*.o
	rm -rf ./*.a
	rm -rf ./${EXEC}

.PHONY: all debug clean
