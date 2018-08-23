BIN=please
OBJ=${BIN}.o

CC?=cc
CFLAGS?=-O2 -march=native -flto -fPIE -fstack-protector-strong -pipe
LDFLAGS?=-flto -pie -Wl,-z,relro,-z,now
LIBS!=echo -n '-lpam'; if [ `uname` = Linux ]; then echo -n ' -lpam_misc'; fi
PREFIX?=/usr/local


all: ${BIN} ${BIN}.1.gz

${BIN}: ${OBJ}
	${CC} ${LDFLAGS} -o $@ ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

${BIN}.1.gz: ${BIN}.1
	gzip -k -9 $<

${BIN}.1: ${BIN}.rst
	rst2man $> $@

install: all
	install -d ${DESTDIR}${PREFIX}/bin
	install -m 4555 -s ${BIN} ${DESTDIR}${PREFIX}/bin
	install -d ${DESTDIR}${PREFIX}/man/man1
	install -m 0444 ${BIN}.1.gz ${DESTDIR}${PREFIX}/man/man1

clean:
	rm -f ${BIN} ${OBJ} ${BIN}.1.gz


${BIN}.o: ${BIN}.c
