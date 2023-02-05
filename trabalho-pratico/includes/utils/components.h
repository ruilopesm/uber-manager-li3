#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <ncurses.h>
#include <string.h>

#define MENU_Y_COORDINATE(x, i) (x / 6) * (i + 1)
#define MENU_X_COORDINATE(x, str) (x / 2) - (strlen(str) / 2)

#define INPUT_BOX_Y_COORDINATE(y) (y / 2) - 1
#define INPUT_BOX_X_COORDINATE(x, title) (x / 2) - (strlen(title) / 2)

typedef void (*draw_menu_function_pointer)(WINDOW *, char **, int, int, int *);

/**
 * @brief Function that draws a window component
 *
 * @param yMax - The maximum y coordinate of type `int` that the window will
 * have
 * @param xMax - The maximum x coordinate of type `int` that the window will
 * have
 * @param multiplier - The multiplier of type `float` that will be used to
 * calculate the
 * @param title - The title of type `char *` that will be drawn to the window
 *
 * @return The window of type `WINDOW *`
 */
WINDOW *draw_window(int yMax, int xMax, float multiplier, char *title);

/**
 * @brief Function that draws a menu to a window
 *
 * @param win - The window of type `WINDOW *` where the menu will be drawn
 * @param menu_entries - The menu entries of type `char **` that will be drawn
 * to the
 * @param menu_size - The size of the menu of type `int` that will be drawn to
 * the
 * @param multiplier - The multiplier of type `int` that will be used to
 * calculate the
 * @param selected_item - The selected item of type `int` that will be drawn to
 * the
 */
void draw_menu(WINDOW *win, char **menu_entries, int menu_size, int multiplier,
               int *selected_item);

/**
 * @brief Function that changes the state of the selected item in a menu
 *
 * @param win - The window of type `WINDOW *` where the menu will be drawn
 * @param draw_menu_function - The function pointer of type
 * `draw_menu_function_pointer` that will be used to draw the menu
 * @param menu_entries - The menu entries of type `char **` that will be drawn
 * to the
 * @param menu_size - The size of the menu of type `int` that will be drawn to
 * the
 * @param multiplier - The multiplier of type `int` that will be used to
 * calculate the
 * @param selected_item - The selected item of type `int` that will be drawn to
 * the
 */
void option_switcher(WINDOW *win, draw_menu_function_pointer draw_menu_function,
                     char **menu_entries, int menu_size, int multiplier,
                     int *selected_item);

/**
 * @brief Function that draws the input box in a specified window
 *
 * @param win - The window of type `WINDOW *` where the input box will be drawn
 * @param title - The title of type `char *` that will be drawn to the input box
 *
 * @return The input of type `char *`
 */
char *draw_input_box(WINDOW *win, char *title);

/**
 * @brief Function that draws a label in a specified window
 *
 * @param win - The window of type `WINDOW *` where the label will be drawn
 * @param label - The label of type `char *` that will be drawn to the window
 * @param y - The y coordinate of type `int` where the label will be drawn
 * @param x - The x coordinate of type `int` where the label will be drawn
 */
void draw_label(WINDOW *win, char *label, int y, int x);

/**
 * @brief Function that draws a warning in a specified window
 *
 * @param win - The window of type `WINDOW *` where the warning will be drawn
 * @param warning - The warning of type `char *` that will be drawn to the
 * window
 */
void draw_warning_subwin(WINDOW *win, char *warning);

#endif
