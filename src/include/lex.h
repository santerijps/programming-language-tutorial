#ifndef LEX_H

  #ifndef _INC_STDIO
    #include <stdio.h>
  #endif

  #ifndef _INC_STDLIB
    #include <stdlib.h>
  #endif

  #ifndef _INC_STRING
    #include <string.h>
  #endif

  #ifndef TOKEN_H
    #include "token.h"
  #endif

  #define LEX_H

  typedef struct LEX_RESULT {
    TOKEN *token_list;
    size_t token_count;
    int exit_code;
  } LEX_RESULT;

  /**
   * Generic function for reading tokens.
   * Stops reading once the char_validator function returns false or EOF.
  */
  char* _read_token_until_invalid(FILE*, int(char));

  /**
   * Reads a token with type T_STR.
  */
  char* _read_string_token(FILE*);

  /**
   * Allocates memory for a one-character string.
   * Appends a null terminator.
  */
  char* _read_single_char_token(FILE*);

  /**
   * Reads a file and produces a list of tokens.
  */
  LEX_RESULT lex_file(char *src_file);

#endif
