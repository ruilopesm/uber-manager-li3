#ifndef PARSER_H
#define PARSER_H

#include <glib.h>
#include <stdio.h>

#include "catalog.h"
#include "stats.h"

#define MAX_LINE_LENGTH 1024

#define MAX_USER_TOKENS 7
#define MAX_DRIVER_TOKENS 9
#define MAX_RIDE_TOKENS 10

FILE *open_file(char *filename);

typedef void (*insert_function_pointer)(char **, CATALOG);

void parse_file(FILE *file, int max_tokens, insert_function_pointer insert,
                CATALOG catalog);

char **parse_line(char *line, int token_count);

#endif
