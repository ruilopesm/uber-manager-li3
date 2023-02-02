#include "views/results_pager.h"

#include <ncurses.h>

#include "io/output.h"
#include "utils/components.h"

void results_pager(MANAGER manager, void *result, char *input) {
  initscr();
  noecho();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  char *title = malloc(sizeof(char) * 128);
  sprintf(title, "Results for %s", input);
  WINDOW *win = draw_window(yMax, xMax, 0.85, title);

  draw_query_result(manager, win, result, title, input[0]);

  delwin(win);
  endwin();
}
