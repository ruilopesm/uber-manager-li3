#ifndef LOAD_DATASET_H
#define LOAD_DATASET_H

#include <ncurses.h>

#include "base/interactive.h"
#include "base/stats.h"
#include "catalogs/join_catalog.h"

#define LOAD_DATASET_ENTRIES 2

void load_dataset(MANAGER manager);

void confirm_and_load(MANAGER manager, WINDOW *win, char *input);

#endif
