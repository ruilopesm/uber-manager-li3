#include "io/parser.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_file(FILE *file, int max_tokens, build_function_pointer build,
                void *catalog, STATS stats) {
  char *line = NULL;
  size_t line_size = 0;

  // Skip first line
  getline(&line, &line_size, file);

  while (getline(&line, &line_size, file) != -1) {
    // Remove the \n from the end of the line
    line[strlen(line) - 1] = '\0';

    char **tokens = parse_line(line, max_tokens);
    build(tokens, catalog, stats);

    free(tokens);
  }

  free(line);
}

char **parse_line(char *line, int max_tokens) {
  char **tokens = malloc(sizeof(char *) * max_tokens);
  char *temp = strstr(line, SEPARATOR);
  char *token = NULL;

  int i = 0;
  while (temp != NULL) {
    token = temp != line ? line : NULL;

    tokens[i] = token;
    line = temp + 1;
    *temp = '\0';
    temp = strstr(line, SEPARATOR);
    i++;
  }

  token = line;
  tokens[i] = token;

  return tokens;
}
