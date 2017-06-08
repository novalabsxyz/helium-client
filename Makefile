PROJECT=helium-client
WARN = -Werror -Wall -Wextra -pedantic

CFLAGS = -g ${WARN} -std=c11 -I. -I./cauterize -D_BSD_SOURCE -D_DEFAULT_SOURCE

OBJS = helium-client.o \
	cauterize/atom_api.o \
	cauterize/atom_api_message.o \
	cauterize/cauterize.o

all: lib${PROJECT}.a

lib${PROJECT}.a: ${OBJS}
	ar -rcs $@ ${OBJS}

clean:
	rm -f ${OBJS} ${PROJECT} *.a *.core
