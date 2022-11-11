#include "parser.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **parse_line(char *line, int token_count) {
  char **tokens = malloc(sizeof(char *) * token_count);
  char *token = strtok(line, ";");

  int i = 0;
  while (token != NULL) {
    tokens[i] = token;
    token = strtok(NULL, ";");

    i++;
  }

  free(token);

  return tokens;
}
