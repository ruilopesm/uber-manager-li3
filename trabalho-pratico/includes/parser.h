#ifndef PARSER_H
#define PARSER_H

#define MAX_LINE_LENGTH 1024

#define MAX_USER_TOKENS 7
#define MAX_DRIVER_TOKENS 9
#define MAX_RIDE_TOKENS 10

char **parse_line(char *line, int token_count);

#endif
