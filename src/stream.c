#include "include/stream.h"

int fpeekc(FILE *stream) {
  int c = fgetc(stream);
  ungetc(c, stream);
  return c;
}