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
	${CC} -c vector.c -o vector.o
	ar rcs libvector.a vector.o

debug: ${EXEC}
debug: CC += ${CFDEBUG}

test: debug
	./${EXEC}

clean:
	rm -rf ./*.o
	rm -rf ./*.a
	rm -rf ./${EXEC}

.PHONY: all debug clean
