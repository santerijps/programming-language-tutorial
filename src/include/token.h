#ifndef TOKEN_H

  #define TOKEN_H

  #ifndef _INC_STDIO
    #include <stdio.h>
  #endif

  #ifndef _INC_STDLIB
    #include <stdlib.h>
  #endif

  /**
   * Enumerator type for different types of tokens.
  */
  typedef enum TOKEN_TYPE {
    T_EOF,
    T_UNDEFINED,
    T_WHITESPACE,
    T_WORD,
    T_EQ,
    T_LT,
    T_GT,
    T_LPAREN,
    T_RPAREN,
    T_LBRACKET,
    T_RBRACKET,
    T_LBRACE,
    T_RBRACE,
    T_PUNCTUATION,
    T_OPERATOR,
    T_SYMBOL,
    T_NUM,
    T_STR,
  } TOKEN_TYPE;

  /**
   * Gets the name of the token type.
   * If not found, returns "UNDEFINED".
  */
  char* token_type_name(TOKEN_TYPE t);

  typedef struct TOKEN {
    TOKEN_TYPE type;
    char *value;
  } TOKEN;

  /**
   * Creates a new token.
  */
  TOKEN token_new(TOKEN_TYPE type, char *value);

  void token_destroy(TOKEN *t);

  /**
   * Prints the specified token.
  */
  void token_print(TOKEN t);

  typedef struct TOKEN_ITER {
    size_t cursor, size;
    TOKEN *items;
  } TOKEN_ITER;

  TOKEN_ITER token_iter_new(size_t size, TOKEN *items);
  int token_iter_has_next(TOKEN_ITER *iter);
  TOKEN token_iter_next(TOKEN_ITER *iter);
  TOKEN token_iter_peek(TOKEN_ITER *iter);

#endif
