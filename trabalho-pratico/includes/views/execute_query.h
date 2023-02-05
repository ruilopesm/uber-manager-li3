#ifndef EXECUTE_QUERY_H
#define EXECUTE_QUERY_H

#include "base/interactive.h"

#define EXECUTE_QUERY_ENTRIES 2

/**
 * @brief Function that deals with the execution of a query in the interactive
 * mode
 *
 * @param manager - The manager of type `MANAGER`
 */
void execute_query(MANAGER manager);

/**
 * @brief Function that deals with the confirmation and execution of a query in
 * the interactive mode
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param input - The input of type `char *` that will be used to execute the
 * query
 */
void confirm_and_execute(MANAGER manager, WINDOW *win, char *input);

#endif
