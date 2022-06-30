#include "include/lex.h"
#include "include/validators.h"
#include "include/stream.h"

LEX_RESULT lex_file(char *src_file) {

  FILE *stream;
  LEX_RESULT result;
  size_t token_list_size = 1000;
  char c, *token_value;
  TOKEN_TYPE token_type;

  result.token_list = (TOKEN*) calloc(token_list_size, sizeof(TOKEN));
  result.token_count = 0;
  result.exit_code = 0;

  if ((stream = fopen(src_file, "r")) == NULL) {
    printf("Failed to open source file!\n");
    result.exit_code = 1;
    return result;
  }

  // Begin reading single characters from the file
  while ((c = fpeekc(stream)) != EOF) {

    token_type = T_UNDEFINED;
    token_value = NULL;

    // Whitespaces
    if (char_is_whitespace(c)) {
      token_value = _read_single_char_token(stream);
      token_type = T_WHITESPACE;
    }

    // Words
    else if (char_is_alpha(c) || c == '_') {
      token_value = _read_token_until_invalid(stream, char_is_word);
      token_type = T_WORD;
    }

    // Numbers
    else if (char_is_digit(c)) {
      token_value = _read_token_until_invalid(stream, char_is_number);
      token_type = T_NUM;
    }

    // Equals sign, one
    else if (c == '=') {
      token_value = _read_single_char_token(stream);
      token_type = T_EQ;
    }

    // Less than sign, one
    else if (c == '<') {
      token_value = _read_single_char_token(stream);
      token_type = T_LT;
    }

    // Greater than sign, one
    else if (c == '>') {
      token_value = _read_single_char_token(stream);
      token_type = T_GT;
    }

    // Left parenthesis, one
    else if (c == '(') {
      token_value = _read_single_char_token(stream);
      token_type = T_LPAREN;
    }

    // Right parenthesis, one
    else if (c == ')') {
      token_value = _read_single_char_token(stream);
      token_type = T_RPAREN;
    }

    // Left bracket, one
    else if (c == '[') {
      token_value = _read_single_char_token(stream);
      token_type = T_LBRACKET;
    }

    // Right bracket, one
    else if (c == ']') {
      token_value = _read_single_char_token(stream);
      token_type = T_RBRACKET;
    }

    // Left brace, one
    else if (c == '{') {
      token_value = _read_single_char_token(stream);
      token_type = T_LBRACE;
    }

    // Right brace, one
    else if (c == '}') {
      token_value = _read_single_char_token(stream);
      token_type = T_RBRACE;
    }

    // Operators
    else if (char_is_operator(c)) {
      token_value = _read_single_char_token(stream);
      token_type = T_OPERATOR;
    }

    // Punctuation
    else if (char_is_punctuation(c)) {
      token_value = _read_single_char_token(stream);
      token_type = T_PUNCTUATION;
    }

    // Symbols
    else if (char_is_symbol(c)) {
      token_value = _read_single_char_token(stream);
      token_type = T_SYMBOL;
    }

    // Strings (inside quotes)
    else if (c == '"') {
      token_value = _read_string_token(stream);
      token_type = T_STR;
    }

    if (token_type == T_UNDEFINED) {
      token_value = _read_single_char_token(stream);
    }

    TOKEN token = token_new(token_type, token_value);
    result.token_list[result.token_count++] = token;

    if (result.token_count == token_list_size) {
      token_list_size *= 2;
      result.token_list = (TOKEN*) realloc(result.token_list, sizeof(TOKEN) * token_list_size);
    }

  }

  if (ferror(stream) > 0) {
    printf("Stream reading finished with error code: %d\n", ferror(stream));
    result.exit_code = ferror(stream);
  }

  if (fclose(stream)) {
    printf("Could not close the file successfully!\n");
    result.exit_code = 1;
  }

  return result;
}


char* _read_token_until_invalid(FILE *stream, int char_validator(char)) {

  unsigned int i = 0, j, size = 10;
  char c, *token = (char*) malloc(sizeof(char) * size);
  memset(token, '\0', size);

  while ((c = fpeekc(stream)) != EOF && char_validator(c)) {

    token[i++] = fgetc(stream);

    // Increase memory for the token string if needed
    if (i == size) {
      size *= 2;
      token = (char*) realloc(token, sizeof(char) * size);
      for (j = i; j < size; j++) token[j] = '\0';
    }

  }

  // Make sure the token string ends with a null terminator
  if (token[size - 1] != '\0') {
    size++;
    token = (char*) realloc(token, sizeof(char) * size);
    token[size - 1] = '\0';
  }

  // TODO: realloc the char* to only be as big as it needs to be?
  // It may be larger than necessary due to previosu reallocs.

  return token;
}


char* _read_string_token(FILE *stream) {

  unsigned int i = 0, j, size = 10, backslash = 0;
  char c, *token = (char*) malloc(sizeof(char) * size);
  memset(token, '\0', size);

  // Ignore the opening quote
  fgetc(stream);

  while ((c = fgetc(stream)) != EOF) {

    // Remove backslashes from the front of double quotes.
    // All other backslashes are kept in the string.
    if (c == '"') {
      if (backslash) {
        token[i - 1] = '"';
        backslash = 0;
        continue;
      } else {
        break;
      }
    }

    backslash = c == '\\';
    token[i++] = c;

    // Increase memory for the token string if needed
    if (i == size) {
      size *= 2;
      token = (char*) realloc(token, sizeof(char) * size);
      for (j = i; j < size; j++) token[j] = '\0';
    }

  }

  return token;
}


char* _read_single_char_token(FILE *stream) {
  char *token = (char*) malloc(sizeof(char) * 2);
  if (token != NULL) {
    token[0] = fgetc(stream);
    token[1] = '\0';
  }
  return token;
}
