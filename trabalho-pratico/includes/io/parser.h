#ifndef PARSER_H
#define PARSER_H

#include <glib.h>
#include <stdio.h>

#include "base/catalog.h"
#include "base/stats.h"

#define SEPARATOR ";"

#define MAX_LINE_LENGTH 1024

#define MAX_USER_TOKENS 7
#define MAX_DRIVER_TOKENS 9
#define MAX_RIDE_TOKENS 10

typedef void (*build_function_pointer)(char **, CATALOG, STATS);

void parse_file(FILE *file, int max_tokens, build_function_pointer build,
                CATALOG catalog, STATS stats);

char **parse_line(char *line, int token_count);

#endif
