BIN=please
OBJ=${BIN}.o
PAM!=echo pam.d/${BIN}.`uname`

CC?=cc
CFLAGS?=-O2 -march=native
LDFLAGS?=
LIBS!=echo -n '-lpam'; if [ `uname` = Linux ]; then echo -n ' -lpam_misc'; fi
PREFIX?=/usr/local


all: ${BIN}

${BIN}: ${OBJ}
	${CC} ${LDFLAGS} -o $@ ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

install: all
	install -d ${DESTDIR}${PREFIX}/bin
	install -m 6555 -s ${BIN} ${DESTDIR}${PREFIX}/bin
	install -d ${DESTDIR}${PREFIX}/man/man1
	install -m 0444 ${BIN}.1 ${DESTDIR}${PREFIX}/man/man1

clean:
	rm -f ${BIN} ${OBJ}


man: ${BIN}.1

${BIN}.1: ${BIN}.rst
	rst2man $> $@

man-clean:
	rm -f ${BIN}.1


${BIN}.o: ${BIN}.c
