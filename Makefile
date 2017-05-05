PROJECT = carbon
WARN = -Wall -Wextra -pedantic

CFLAGS = -g ${WARN} -std=c11 -I./cauterize

OBJS = carbon.o \
	cauterize/atom_api.o \
	cauterize/atom_api_message.o \
	cauterize/cauterize.o

all: lib${PROJECT}.a

lib${PROJECT}.a: ${OBJS}
	ar -rcs lib${PROECT}.a ${OBJS}

clean:
	rm -f ${OBJS} *.a *.core
