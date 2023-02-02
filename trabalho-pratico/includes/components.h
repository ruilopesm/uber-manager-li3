#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <ncurses.h>
#include <string.h>

#define MENU_Y_COORDINATE(x, i) (x / 6) * (i + 1)
#define MENU_X_COORDINATE(x, str) (x / 2) - (strlen(str) / 2)

#define INPUT_BOX_Y_COORDINATE(y) (y / 2) - 1
#define INPUT_BOX_X_COORDINATE(x, title) (x / 2) - (strlen(title) / 2)

typedef void (*draw_menu_function_pointer)(WINDOW *, char **, int, int, int *);

WINDOW *draw_window(int yMax, int xMax, float multiplier, char *title);

void draw_menu(WINDOW *win, char **menu_entries, int menu_size, int multiplier,
               int *selected_item);

void option_switcher(WINDOW *win, draw_menu_function_pointer draw_menu_function,
                     char **menu_entries, int menu_size, int multiplier,
                     int *selected_item);

char *draw_input_box(WINDOW *win, char *title);

void draw_label(WINDOW *win, char *label, int y, int x);

void draw_warning_subwin(WINDOW *win, char *warning);

#endif
