#include "parser.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_file(FILE *file, int max_tokens, insert_function_pointer insert,
                GHashTable *hash_table) {
  char *line = malloc(sizeof(char) * MAX_LINE_LENGTH);

  while (fgets(line, MAX_LINE_LENGTH, file)) {
    char **tokens = parse_line(line, max_tokens);
    insert(tokens, hash_table);

    free(tokens);
  }

  free(line);
}

char **parse_line(char *line, int max_tokens) {
  char **tokens = malloc(sizeof(char *) * max_tokens);
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
