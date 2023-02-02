#include "components.h"

#include <glib.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

WINDOW *draw_window(int yMax, int xMax, float multiplier, char *title) {
  int new_y = (int)(multiplier * yMax);
  int new_x = (int)(multiplier * xMax);

  WINDOW *win = newwin(new_y, new_x, (yMax - new_y) / 2, (xMax - new_x) / 2);

  // Draw the box and the title
  box(win, 0, 0);
  mvwprintw(win, 0, 2, title);

  return win;
}

void draw_menu(WINDOW *win, char **menu_entries, int menu_size, int multiplier,
               int *selected_item) {
  int yMax, xMax;
  getmaxyx(win, yMax, xMax);

  // Draw the menu
  for (int i = 0; i < menu_size; i++) {
    if (i == *selected_item) {
      wattron(win, A_REVERSE);
      mvwprintw(win, MENU_Y_COORDINATE(yMax, i + multiplier),
                MENU_X_COORDINATE(xMax, menu_entries[i]), menu_entries[i]);
      wattroff(win, A_REVERSE);
    } else {
      mvwprintw(win, MENU_Y_COORDINATE(yMax, i + multiplier),
                MENU_X_COORDINATE(xMax, menu_entries[i]), menu_entries[i]);
    }
  }
}

void option_switcher(WINDOW *win, draw_menu_function_pointer draw_menu_function,
                     char **menu_entries, int menu_size, int multiplier,
                     int *selected_item) {
  // Enable keyboard input and disable cursor
  keypad(win, TRUE);
  curs_set(0);
  int key;

  do {
    key = wgetch(win);

    switch (key) {
      case KEY_DOWN:
        (*selected_item)++;
        if (*selected_item > menu_size - 1) *selected_item = 0;
        break;

      case KEY_UP:
        (*selected_item)--;
        if (*selected_item < 0) *selected_item = menu_size - 1;
        break;

      default:
        break;
    }

    draw_menu_function(win, menu_entries, menu_size, multiplier, selected_item);

  } while (key != '\n');  // '\n' is the enter key
}

char *draw_input_box(WINDOW *win, char *title) {
  int yMax, xMax;
  getmaxyx(win, yMax, xMax);

  // Draw the title
  mvwprintw(win, INPUT_BOX_Y_COORDINATE(yMax),
            INPUT_BOX_X_COORDINATE(xMax, title), title);

  // Draw the input box
  mvwprintw(win, INPUT_BOX_Y_COORDINATE(yMax) + 1,
            INPUT_BOX_X_COORDINATE(xMax, title), "> ");

  // Enable keyboard input and enable cursor
  keypad(win, TRUE);
  curs_set(2);

  // Get the input
  char *input = malloc(sizeof(char) * 128);
  wgetstr(win, input);

  return input;
}

void draw_label(WINDOW *win, char *label, int y, int x) {
  mvwprintw(win, y, x, label);
}

void draw_warning_subwin(WINDOW *win, char *warning) {
  int yMax, xMax;
  getmaxyx(win, yMax, xMax);

  WINDOW *sub_win = subwin(win, 3, strlen(warning) + 4, (yMax - 4) / 2,
                           (xMax / 2) - (strlen(warning) / 2) + 10);
  box(sub_win, 0, 0);

  curs_set(0);

  // Draw the warning
  draw_label(sub_win, warning, 1, 2);

  wgetch(sub_win);
  curs_set(1);
  delwin(sub_win);
}
