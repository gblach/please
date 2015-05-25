BIN=please
OBJ=${BIN}.o
MAN=${BIN}.1
PAM!=echo pam.d/${BIN}.`uname`

CC?=cc
CFLAGS?=-O2 -march=native
LDFLAGS?=
LIBS!=echo -n '-lpam'; if [ `uname` = Linux ]; then echo -n ' -lpam_misc'; fi
PREFIX?=/usr/local
PAMDIR!=if [ `uname` = FreeBSD ]; then echo -n ${PREFIX}; fi; echo /etc/pam.d


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

install-pam:
	install -m 0755 -o 0 -g 0 -d ${DESTDIR}${PAMDIR}
	install -m 0644 -o 0 -g 0 ${PAM} ${DESTDIR}${PAMDIR}/${BIN}

clean:
	rm -f ${BIN} *.o ${MAN}


${BIN}.o: ${BIN}.c
${MAN}: ${BIN}.rst
