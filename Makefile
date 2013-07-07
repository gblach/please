BIN=please
OBJ=${BIN}.o
MAN=${BIN}.1

CC?=cc
CFLAGS?=-O2 -march=native
LDFLAGS?=
LIBS=-lpam $(shell if [ `uname` = Linux ]; then echo -lpam_misc; fi)
PREFIX?=/usr/local


all: ${BIN} ${MAN}.gz

${BIN}: ${OBJ}
	${CC} ${LDFLAGS} -o $@ ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

${MAN}.gz:
	rst2man ${BIN}.rst > ${MAN}
	gzip -f -9 ${MAN}

install: all
	install -m 0755 -o 0 -g 0 -d ${PREFIX}/bin
	install -m 6555 -o 0 -g 0 -s ${BIN} ${PREFIX}/bin
	install -m 0755 -o 0 -g 0 -d ${PREFIX}/man/man1
	install -m 0444 -o 0 -g 0 ${MAN}.gz ${PREFIX}/man/man1

clean:
	rm -f ${BIN} *.o ${MAN} ${MAN}.gz


${BIN}.o: ${BIN}.c
${MAN}.gz: ${BIN}.rst
