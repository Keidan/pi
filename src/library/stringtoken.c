#include <pi/stringtoken.h>
#include <pi/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

typedef struct {
  char*    str;
  char*    sep;
  uint32_t len;
  uint32_t offset;
} stringtoken_handle_t;


stringtoken_t stringtoken_init(const char* str, const char* sep) {
  stringtoken_handle_t *tok = malloc(sizeof(stringtoken_handle_t));
  tok->str = (char*)str;
  tok->sep = (char*)sep;
  tok->len = strlen(str);
  tok->offset = 0;
  return tok;
}

uint32_t stringtoken_count(stringtoken_t tok) {
  stringtoken_handle_t *t = (stringtoken_handle_t *)tok;
  if(!t) return 0;
  uint32_t offset = t->offset, count = 0;
  t->offset = 0;
  while(stringtoken_has_more_tokens(t)) {
    stringtoken_next_token(t);
    count++;
  }
  t->offset = offset;
  return count;
}

void stringtoken_release(stringtoken_t tok) {
  free(tok);
}

int stringtoken_has_more_tokens(stringtoken_t tok) {
  stringtoken_handle_t *t = (stringtoken_handle_t *)tok;
  if(!t) return 0;
  return t->offset < t->len;
}

char* stringtoken_next_token(stringtoken_t tok) {
  stringtoken_handle_t *t = (stringtoken_handle_t *)tok;
  if(!t) return NULL;
  // search the next split
  char c;
  int i = 0;
  int end = 0;
  // check immediate end of look
  if (!stringtoken_has_more_tokens(tok))
    return NULL;
  while (!end) {
    // check end of look
    if (t->offset + i >= t->len)
      break;
    // look next char
    c = t->str[t->offset + i];
    if (stringtoken_split_condition(c, t->sep)) {
      // split here
      end = 1;
    }
    else i++;
  }
  char* s = string_substring(t->str, t->offset, i);
  t->offset += i + 1; // go just after the sep
  return s;
}

void stringtoken_set_separator(stringtoken_t tok, char* sep) {
  stringtoken_handle_t *t = (stringtoken_handle_t *)tok;
  t->sep = sep;
}

int stringtoken_split_condition(char c, char* sep) {
  uint32_t i;
  for (i = 0; i< strlen(sep); i++)
    if (c== sep[i]) return 1;
  return 0; // no matches
}

