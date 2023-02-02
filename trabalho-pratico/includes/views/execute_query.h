#ifndef EXECUTE_QUERY_H
#define EXECUTE_QUERY_H

#include "interactive.h"

#define EXECUTE_QUERY_ENTRIES 2

void execute_query(MANAGER manager);

void confirm_and_execute(MANAGER manager, WINDOW *win, char *input);

#endif
