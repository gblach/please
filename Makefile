BIN=please
OBJ=${BIN}.o

CC?=cc -c
LD?=cc
CFLAGS?=-O2 -march=native
CFLAGS+=-std=c99
LDFLAGS?=
PREFIX=/usr/local


${BIN}: ${OBJ}
	${LD} ${LDFLAGS} -o $@ ${OBJ}

.c.o:
	${CC} ${CFLAGS} -o $@ $<

install:
	install -d ${PREFIX}/bin
	install -m 6755 -s ${BIN} ${PREFIX}/bin

clean:
	rm -f ${BIN} ${OBJ}


please.o: please.c
