BIN=please
OBJ=${BIN}.o

CC?=cc
CFLAGS?=-O2 -march=native
LDFLAGS?=
LIBS=-lpam $(shell if [ `uname` = Linux ]; then echo -lpam_misc; fi)
PREFIX=/usr/local


${BIN}: ${OBJ}
	${CC} ${LDFLAGS} -o $@ ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

install: ${BIN}
	install -d ${PREFIX}/bin
	install -m 6755 -s ${BIN} ${PREFIX}/bin

clean:
	rm -f ${BIN} *.o


please.o: please.c
