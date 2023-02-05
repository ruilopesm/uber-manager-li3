#ifndef RESULTS_PAGER_H
#define RESULTS_PAGER_H

#include <ncurses.h>

#include "base/interactive.h"

/**
 * @brief Function that draws the results pager component to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param result - The result of type `void *`
 * @param input - The input of type `char *`
 */
void results_pager(MANAGER manager, void *result, char *input);

#endif
