BIN=please
OBJ=${BIN}.o
MAN=${BIN}.1

CC?=cc
CFLAGS?=-O2 -march=native
LDFLAGS?=
LIBS=-lpam $(shell if [ `uname` = Linux ]; then echo -lpam_misc; fi)
PREFIX?=/usr/local


all: ${BIN} ${MAN}

${BIN}: ${OBJ}
	${CC} ${LDFLAGS} -o $@ ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

${MAN}:
	rst2man ${BIN}.rst $@

install: all
	install -m 0755 -o 0 -g 0 -d ${DESTDIR}${PREFIX}/bin
	install -m 6555 -o 0 -g 0 -s ${BIN} ${DESTDIR}${PREFIX}/bin
	install -m 0755 -o 0 -g 0 -d ${DESTDIR}${PREFIX}/man/man1
	install -m 0444 -o 0 -g 0 ${MAN} ${DESTDIR}${PREFIX}/man/man1

clean:
	rm -f ${BIN} *.o ${MAN}


${BIN}.o: ${BIN}.c
${MAN}: ${BIN}.rst
