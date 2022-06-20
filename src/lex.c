#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/token.h"
#include "include/validators.h"
#include "include/stream.h"

char* read_token_until_invalid(int(char));
char* read_string_token();
char* read_single_char_token();

FILE *stream;

int main(int argc, char** argv) {

  size_t n, token_list_size = 100, token_list_index = 0;
  char c, *token_value, *src_file, *dst_file = NULL;
  TOKEN_TYPE token_type;
  TOKEN *token_list = (TOKEN*) calloc(token_list_size, sizeof(TOKEN));

  if (argc == 1) {
    printf("Please provide a source file!\n");
    return 1;
  }

  src_file = argv[1];

  if (argc >= 3) {
    dst_file = argv[2];
  }

  if ((stream = fopen(src_file, "r")) == NULL) {
    printf("Failed to open source file!\n");
    return 1;
  }

  // Begin reading single characters from the file
  while ((c = fpeekc(stream)) != EOF) {

    token_type = T_UNDEFINED;
    token_value = NULL;

    // Whitespaces
    if (char_is_whitespace(c)) {
      token_value = read_single_char_token();
      token_type = T_WHITESPACE;
    }

    // Words
    else if (char_is_alpha(c)) {
      token_value = read_token_until_invalid(char_is_word);
      token_type = T_WORD;
    }

    // Numbers
    else if (char_is_digit(c)) {
      token_value = read_token_until_invalid(char_is_number);
      token_type = T_NUM;
    }

    // Equals sign, one
    else if (c == '=') {
      token_value = read_single_char_token();
      token_type = T_EQ;
    }

    // Less than sign, one
    else if (c == '<') {
      token_value = read_single_char_token();
      token_type = T_LT;
    }

    // Greater than sign, one
    else if (c == '>') {
      token_value = read_single_char_token();
      token_type = T_GT;
    }

    // Left parenthesis, one
    else if (c == '(') {
      token_value = read_single_char_token();
      token_type = T_LPAREN;
    }

    // Right parenthesis, one
    else if (c == ')') {
      token_value = read_single_char_token();
      token_type = T_RPAREN;
    }

    // Left bracket, one
    else if (c == '[') {
      token_value = read_single_char_token();
      token_type = T_LBRACKET;
    }

    // Right bracket, one
    else if (c == ']') {
      token_value = read_single_char_token();
      token_type = T_RBRACKET;
    }

    // Left brace, one
    else if (c == '{') {
      token_value = read_single_char_token();
      token_type = T_LBRACE;
    }

    // Right brace, one
    else if (c == '}') {
      token_value = read_single_char_token();
      token_type = T_RBRACE;
    }

    // Operators
    else if (char_is_operator(c)) {
      token_value = read_single_char_token();
      token_type = T_OPERATOR;
    }

    // Punctuation
    else if (char_is_punctuation(c)) {
      token_value = read_single_char_token();
      token_type = T_PUNCTUATION;
    }

    // Symbols
    else if (char_is_symbol(c)) {
      token_value = read_single_char_token();
      token_type = T_SYMBOL;
    }

    // Strings (inside quotes)
    else if (c == '"') {
      token_value = read_string_token();
      token_type = T_STR;
    }

    if (token_type == T_UNDEFINED) {
      token_value = read_single_char_token();
    }

    TOKEN token = token_new(token_type,
      (char*) malloc(sizeof(char) * strlen(token_value)));
    strcpy(token.value, token_value);
    token_list[token_list_index++] = token;
    free(token_value);

  }

  if (fclose(stream)) {
    printf("Could not close the file successfully!\n");
    return 1;
  }

  if (dst_file != NULL) {

    if ((stream = fopen(dst_file, "w")) == NULL) {
      printf("Could not open %s file!\n", dst_file);
      return 1;
    }

    printf("Wrote %d tokens to %s\n",
      fwrite(token_list, sizeof(TOKEN), token_list_index, stream),
      dst_file
    );

    if (fclose(stream)) {
      printf("Could not close %s successfully!\n", dst_file);
      return 1;
    }

  }

  // Free up the space taken up by the dynamically memory allocated strings
  for (int i = 0; i < token_list_index; i++) {
    token_print(token_list[i]);
    free(token_list[i].value);
  }

  return 0;
}


/**
 * Generic function for reading tokens.
 * Stops reading once the char_validator function returns false or EOF.
**/
char* read_token_until_invalid(int char_validator(char)) {

  unsigned int i = 0, size = 10;
  char c, *token = (char*) malloc(sizeof(char) * size);
  memset(token, '\0', size);

  while ((c = fpeekc(stream)) != EOF && char_validator(c)) {

    token[i++] = fgetc(stream);

    // Increase memory for the token string if needed
    if (i == size) {
      size *= 2;
      token = (char*) realloc(token, sizeof(char) * size);
      for (int j = i; j < size; j++) token[j] = '\0';
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


/**
 * Reads a token with type T_STR.
**/
char* read_string_token() {

  unsigned int i = 0, size = 10, backslash = 0;
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
      for (int j = i; j < size; j++) token[j] = '\0';
    }

  }

  return token;
}


/**
 * Allocates memory for a one-character string.
 * Appends a null terminator.
**/
char* read_single_char_token() {
  char *token = (char*) malloc(sizeof(char) * 2);
  token[0] = fgetc(stream);
  token[1] = '\0';
  return token;
}
