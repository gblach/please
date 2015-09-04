BIN=please
OBJ=${BIN}.o
MAN=${BIN}.1
RST=${BIN}.rst
PAM!=echo pam.d/${BIN}.`uname`

CC?=cc
CFLAGS?=-O2 -march=native
LDFLAGS?=
LIBS!=echo -n '-lpam'; if [ `uname` = Linux ]; then echo -n ' -lpam_misc'; fi
PREFIX?=/usr/local
PAMDIR!=if [ `uname` = FreeBSD ]; then echo -n ${PREFIX}; fi; echo /etc/pam.d


all: ${BIN}

${BIN}: ${OBJ}
	${CC} ${LDFLAGS} -o $@ ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

install: all
	install -d ${DESTDIR}${PREFIX}/bin
	install -m 6555 -s ${BIN} ${DESTDIR}${PREFIX}/bin
	install -d ${DESTDIR}${PREFIX}/man/man1
	install -m 0444 ${MAN} ${DESTDIR}${PREFIX}/man/man1

clean:
	rm -rf ${BIN} ${OBJ}

man: ${MAN}

${MAN}: ${RST}
	rst2man $> $@

man-clean:
	rm -f ${MAN}


${BIN}.o: ${BIN}.c
