#include <stdio.h>
#include <stdlib.h>
#include "include/lex.h"

int main(int argc, char **argv) {

  LEX_RESULT lex_result;

  if (argc == 1) {
    fprintf(stderr, "Please provide a source file!\n");
    exit(1);
  }

  lex_result = lex_file(argv[1]);

  printf("Exit code: %d, token count: %d\n",
    lex_result.exit_code, lex_result.token_count);

  for (int i = 0; i < lex_result.token_count; i++) {
    token_print(lex_result.token_list[i]);
    free(lex_result.token_list[i].value);
  }

}