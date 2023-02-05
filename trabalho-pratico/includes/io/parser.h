#ifndef PARSER_H
#define PARSER_H

#include <glib.h>
#include <stdio.h>

#include "base/stats.h"

#define SEPARATOR ";"

#define MAX_LINE_LENGTH 1024

#define MAX_USER_TOKENS 7
#define MAX_DRIVER_TOKENS 9
#define MAX_RIDE_TOKENS 10

typedef void (*build_function_pointer)(char **, void *, STATS);

/**
 * @brief Function that parses any type of file
 *
 * @param file - The file of type `FILE *`
 * @param max_tokens - The maximum number of tokens of type `int`
 * @param insert - The function that inserts the data into the data structures
 * of type `insert_function_pointer`
 * @param catalog - The catalog of type `void *` (CATALOG or USER_CATALOG)
 * @param stats - The stats of type `STATS`
 */
void parse_file(FILE *file, int max_tokens, build_function_pointer build,
                void *catalog, STATS stats);

/**
 * @brief Function that parses a line
 *
 * @param line - The line of type `char *`
 * @param token_count - The number of tokens of type `int`
 *
 * @return tokens - The tokens of type `char **`
 */
char **parse_line(char *line, int token_count);

#endif
