#include "include/validators.h"

int char_is_alpha(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int char_is_digit(char c) {
  return c >= '0' && c <= '9';
}

int char_is_whitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}

int char_is_punctuation(char c) {
  return
    c == ',' || c == '.' || c == ';' ||
    c == ':' || c == '?' || c == '!';
}

int char_is_operator(char c) {
  return
    c == '+' || c == '-' || c == '*' || c == '/' ||
    c == '%' || c == '^' || c == '|' || c == '&';
}

int char_is_symbol(char c) {
  return c == '$' || c == '@' || c == '#';
}

int char_is_word(char c) {
  return
    char_is_alpha(c)
    || char_is_digit(c)
    || c == '_'
    || c == '-';
}

int char_is_number(char c) {
  return char_is_digit(c) || c == '_' || c == '.';
}
