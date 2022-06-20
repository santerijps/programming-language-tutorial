#ifndef _INC_STDIO
  #include <stdio.h>
#endif

/**
 * Peeks the next character in the stream.
 * Does not move the cursor forward.
**/
int fpeekc(FILE *stream) {
  int c = fgetc(stream);
  ungetc(c, stream);
  return c;
}
