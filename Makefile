PROJECT=carbon
WARN = -Wall -Wextra -pedantic

CFLAGS = -g ${WARN} -std=c11 -I. -I./cauterize -D_BSD_SOURCE

OBJS = carbon.o \
	cauterize/atom_api.o \
	cauterize/atom_api_message.o \
	cauterize/cauterize.o

OBJS_CLI = cli/connect.o \
	cli/sleep.o \
	cli/connected.o \
	cli/info.o \
	cli/send.o

all: lib${PROJECT}.a

lib${PROJECT}.a: ${OBJS}
	ar -rcs $@ ${OBJS}

${PROJECT}: ${OBJS_CLI} lib${PROJECT}.a cli/main.c
	${CC} -o $@ cli/main.c ${CFLAGS} ${OBJS_CLI} ${LDFLAGS} lib${PROJECT}.a

clean:
	rm -f ${OBJS} ${OBJS_CLI} ${PROJECT} *.a *.core
