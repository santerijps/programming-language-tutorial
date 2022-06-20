#ifndef _INC_STDIO
  #include <stdio.h>
#endif

#ifndef _INC_STDLIB
  #include <stdlib.h>
#endif

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
**/
char* token_type_name(TOKEN_TYPE t) {
  switch (t) {
    case T_WHITESPACE: return "WHITESPACE";
    case T_WORD: return "WORD";
    case T_EQ: return "EQ";
    case T_LT: return "LT";
    case T_GT: return "GT";
    case T_LPAREN: return "LPAR";
    case T_RPAREN: return "RPAR";
    case T_LBRACKET: return "LBRACKET";
    case T_RBRACKET: return "RBRACKET";
    case T_LBRACE: return "LBRACE";
    case T_RBRACE: return "RBRACE";
    case T_PUNCTUATION: return "PUNCTUATION";
    case T_OPERATOR: return "OPERATOR";
    case T_SYMBOL: return "SYMBOL";
    case T_NUM: return "NUM";
    case T_STR: return "STR";
    default: return "UNDEFINED";
  }
}

typedef struct {
  TOKEN_TYPE type;
  char *value;
} TOKEN;

TOKEN token_new(TOKEN_TYPE type, char *value) {
  TOKEN t;
  t.type = type;
  t.value = value;
  return t;
}

void token_print(TOKEN t) {
  printf("TOKEN{ %s, '", token_type_name(t.type));
  for (int i = 0; i < t.value[i] != '\0'; i++) {
    switch (t.value[i]) {
      case ' ':
        printf("\\s");
        break;
      case '\n':
        printf("\\n");
        break;
      case '\t':
        printf("\\t");
        break;
      case '\r':
        printf("\\r");
        break;
      default:
        printf("%c", t.value[i]);
    }
  }
  printf("' }\n");
}
