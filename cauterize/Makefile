CC=clang
CFLAGS=-O3 -Werror -Wall -Wextra -std=c11 -pedantic
CLIENT_PROG=test_client

CFILES := cauterize.c atom_api.c atom_api_message.c
HFILES := cauterize.h atom_api.h atom_api_message.h

all: $(CLIENT_PROG)
clean:
	rm $(CLIENT_PROG)

$(CLIENT_PROG): $(HFILES) $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) test_client.c -o $@
