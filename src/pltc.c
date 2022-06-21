#include <stdio.h>
#include <stdlib.h>
#include "include/lex.h"

int main(int argc, char **argv) {

  LEX_RESULT lex_result;
  TOKEN_ITER token_iter;
  TOKEN token;

  if (argc == 1) {
    fprintf(stderr, "Please provide a source file!\n");
    exit(1);
  }

  lex_result = lex_file(argv[1]);

  printf("Exit code: %d, token count: %d\n",
    lex_result.exit_code, lex_result.token_count);

  if (lex_result.exit_code != 0) {
    exit(1);
  }

  token_iter = token_iter_new(lex_result.token_count, lex_result.token_list);

  while (token_iter_has_next(&token_iter)) {
    token = token_iter_next(&token_iter);
    token_print(token);
    token_destroy(&token);
  }

}