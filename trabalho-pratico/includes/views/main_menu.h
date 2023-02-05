#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <ncurses.h>

#include "base/interactive.h"

#define MAIN_MENU_ENTRIES 5

/**
 * @brief Function that draws the main menu component to a window
 *
 * @param manager - The manager of type `MANAGER`
 */
void main_menu(MANAGER manager);

#endif
