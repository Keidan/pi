#include <pi/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <errno.h>

void string_tolower(const char* source, char* dest) {
  int i;
  for(i = 0; i < strlen(source); i++)
    dest[i] = tolower(source[i]);
}

void string_toupper(const char* source, char* dest) {
  int i;
  for(i = 0; i < strlen(source); i++)
    dest[i] = toupper(source[i]);
}

char* string_substring(const char* str, size_t begin, size_t len)  { 
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return 0; 
  return strndup(str + begin, len); 
} 

int string_indexof(const char* source, const char* needed) {
  char * found = strstr(source, needed);
  if(found != NULL)  return found - source;
  return -1;
}

int string_isint(const char* source) {
  int i;
  for(i = 0; i < strlen(source); i++)
    if(!isdigit(source[i]))
      return 0;
  return 1;
}

int string_parse_int(char* str, int def) {
  int n = strtol(str, NULL, 10);
  if((errno == ERANGE) || (errno == EINVAL)) {
    return def;
  }
  return n;
}
