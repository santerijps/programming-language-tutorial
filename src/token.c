#include "include/token.h"

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

TOKEN token_new(TOKEN_TYPE type, char *value) {
  TOKEN t;
  t.type = type;
  t.value = value;
  return t;
}

void token_destroy(TOKEN *t) {
  free(t->value);
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

inline TOKEN_ITER token_iter_new(size_t size, TOKEN *items) {
  TOKEN_ITER iter;
  iter.cursor = 0;
  iter.size = size;
  iter.items = items;
  return iter;
}

int token_iter_has_next(TOKEN_ITER *iter) {
  return (iter->cursor) < (iter->size);
}

TOKEN token_iter_next(TOKEN_ITER *iter) {
  return (iter->items)[(iter->cursor)++];
}

TOKEN token_iter_peek(TOKEN_ITER *iter) {
  TOKEN token;
  if (token_iter_has_next(iter)) {
    token = token_iter_next(iter);
    (iter->cursor)--;
  } else {
    token.type = T_EOF;
    token.value = NULL;
  }
  return token;
}
