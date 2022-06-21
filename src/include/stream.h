#ifndef STREAM_H

  #define STREAM_H

  #ifndef _INC_STDIO
    #include <stdio.h>
  #endif

  /**
   * Peeks the next character in the stream.
   * Does not move the cursor forward.
  **/
  int fpeekc(FILE *stream);

#endif
