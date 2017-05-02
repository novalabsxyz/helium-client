#include "test_client.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>

bool read_exactly(FILE * fd, void * buf, size_t nbyte, size_t * rbyte);
int run_client(FILE * si, FILE * so);

int main(int argc, char * argv[]) {
  (void)argc;
  (void)argv;

  return run_client(stdin, stdout);
}

int run_client(FILE * si, FILE * so) {
  MESSAGE_HEADER_T * h = malloc(sizeof(*h));
  MESSAGE_T * d = malloc(sizeof(*d));
  void * buffer = malloc(MESSAGE_MAX_SIZE);

  struct caut_decode_iter decode;
  struct caut_encode_iter encode;

  size_t rlen = 0;

  enum caut_status status;

  /* Read and decode header. */
  if (!read_exactly(si, buffer, MESSAGE_OVERHEAD, &rlen)) {
    fprintf(stderr, "Not enough data available for header: expected %d bytes but only got %lu bytes.",
      MESSAGE_OVERHEAD,
      rlen);
    return 1;
  }
  caut_decode_iter_init(&decode, buffer, rlen);
  if (caut_status_ok != (status = DECODE_HEADER(&decode, h))) {
    fprintf(stderr, "Failed to decode the header: %d.", status);
    return 2;
  }

  /* Read the remaining data as described by the header. */
  if (!read_exactly(si, buffer, h->length, &rlen)) {
    fprintf(stderr, "Not enough data available: expected %d bytes but only got %lu bytes.",
      (int)h->length,
      rlen);
    return 3;
  }
  caut_decode_iter_init(&decode, buffer, rlen);
  if (caut_status_ok != (status = DECODE_MESSAGE(&decode, h, d))) {
    fprintf(stderr, "Unable to decode payload: %d.", status);
    return 4;
  }

  memset(buffer, 0, MESSAGE_MAX_SIZE);

  caut_encode_iter_init(&encode, buffer, MESSAGE_MAX_SIZE);

  if (caut_status_ok != (status = ENCODE_MESSAGE(&encode, d))) {
    fprintf(stderr, "Unable to encode response: %d.", status);
    return 5;
  }

  fwrite(buffer, 1, encode.position, so);

  return 0;
}

/*
 * read_exactly
 *
 *    Automatically re-reads a file descriptor until an error occurs or the
 *    expected number of bytes has been read.
 *
 *    fd - the file descriptor to read from.
 *    buf - the buffer to read into.
 *    nbyte - the number of bytes to read into the buffer.
 *    rbyte - the actual number of bytes read into the buffer. Will always
 *    equal nbyte if all reads were successful.
 *
 *    Returns true when no errors occurred and the proper number of bytes was
 *    read. Returns false otherwise.
 */
bool read_exactly(FILE * fd, void * buf, size_t nbyte, size_t * rbyte) {
  uint8_t * bbuf = buf;
  size_t r = 0;

  while(r < nbyte) {
    uint8_t * next_pos = &(bbuf[r]);
    size_t l = fread(next_pos, 1, nbyte - r, fd);

    if (l == 0) {
      break;
    } else {
      r += (size_t)l;
    }
  }

  if (rbyte) {
    *rbyte = r;
  }

  return (r == nbyte);
}
