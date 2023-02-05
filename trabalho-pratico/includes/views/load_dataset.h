#ifndef LOAD_DATASET_H
#define LOAD_DATASET_H

#include <ncurses.h>

#include "base/interactive.h"
#include "base/stats.h"
#include "catalogs/joint_catalog.h"

#define LOAD_DATASET_ENTRIES 2

/**
 * @brief Function that draws and deals the load dataset component to a window
 *
 * @param manager - The manager of type `MANAGER`
 */
void load_dataset(MANAGER manager);

/**
 * @brief Function that draws and deals with the confirmation and loading of a
 * dataset in the interactive mode
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param input - The input of type `char *` that will be used to load the
 * dataset
 */
void confirm_and_load(MANAGER manager, WINDOW *win, char *input);

#endif
