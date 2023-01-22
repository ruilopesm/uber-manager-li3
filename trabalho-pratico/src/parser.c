#include "parser.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_file(FILE *file, int max_tokens, insert_function_pointer insert,
                CATALOG catalog, STATS stats) {
  char *line = malloc(sizeof(char) * MAX_LINE_LENGTH);

  // Skip first line
  fgets(line, MAX_LINE_LENGTH, file);

  while (fgets(line, MAX_LINE_LENGTH, file)) {
    // Remove the \n from the end of the line
    line[strlen(line) - 1] = '\0';

    char **tokens = parse_line(line, max_tokens);
    insert(tokens, catalog, stats);

    free(tokens);
  }

  free(line);
}

char **parse_line(char *line, int max_tokens) {
  char **tokens = malloc(sizeof(char *) * max_tokens);
  char comma[2] = ";";
  char *temp = strstr(line, comma);
  char *token = NULL;

  int i = 0;
  while (temp != NULL) {
    if (temp != line) {
      token = line;
    } else {
      token = NULL;
    }
    tokens[i] = token;
    line = temp + 1;
    *temp = '\0';
    temp = strstr(line, comma);
    i++;
  }
  token = line;
  tokens[i] = token;

  return tokens;
}