BIN=please
OBJ=${BIN}.o
MAN=${BIN}.1
PAM=pam.d/${BIN}.$(shell echo `uname`)
PAM!=echo ${PAM}`uname`

CC?=cc
CFLAGS?=-O2 -march=native
LDFLAGS?=
LIBS=-lpam $(shell if [ `uname` = Linux ]; then echo -lpam_misc; fi)
PREFIX?=/usr/local
PAMDIR=$(shell if [ `uname` = FreeBSD ]; then echo -n ${PREFIX}; fi)/etc/pam.d
PAMDIR!=if [ `uname` = FreeBSD ]; then echo -n ${PREFIX}; fi; echo ${PAMDIR}


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
