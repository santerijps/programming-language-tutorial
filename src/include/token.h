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

  typedef struct {
    TOKEN_TYPE type;
    char *value;
  } TOKEN;

  /**
   * Creates a new token.
  */
  TOKEN token_new(TOKEN_TYPE type, char *value);

  /**
   * Prints the specified token.
  */
  void token_print(TOKEN t);

#endif
