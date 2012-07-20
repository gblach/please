BIN=please
OBJ=${BIN}.o pam.o

CC?=cc
CFLAGS?=-O2 -march=native
LDFLAGS?=
LIBS=-lpam
PREFIX=/usr/local


${BIN}: ${OBJ}
	${CC} ${LDFLAGS} ${LIBS} -o $@ ${OBJ}

.c.o:
	${CC} -c -std=c99 ${CFLAGS} -o $@ $<

install: ${BIN}
	install -d ${PREFIX}/bin
	install -m 6755 -s ${BIN} ${PREFIX}/bin

clean:
	rm -f ${BIN} *.o


please.o: please.c pam.h
pam.o: pam.c pam.h
