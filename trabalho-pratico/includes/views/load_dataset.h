#ifndef LOAD_DATASET_H
#define LOAD_DATASET_H

#include <ncurses.h>

#include "catalog.h"
#include "interactive.h"
#include "stats.h"

#define LOAD_DATASET_ENTRIES 2

void load_dataset(MANAGER manager);

void confirm_and_load(MANAGER manager, WINDOW *win, char *input);

#endif
