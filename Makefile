BIN=please
OBJ=${BIN}.o

CC=gcc -c -std=c99
LD=gcc
CFLAGS?=-O2 -march=native
LDFLAGS?=
PREFIX=/usr/local


${BIN}: ${OBJ}
	${LD} ${LDFLAGS} -o $@ ${OBJ}

.c.o:
	${CC} ${CFLAGS} -o $@ $<

install:
	install -D -s -m 6755 ${BIN} ${PREFIX}/bin/${BIN}

clean:
	rm -f ${BIN} ${OBJ}


please.o: please.c
