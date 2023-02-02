#include "views/help.h"

#include <ncurses.h>

#include "components.h"
#include "views/main_menu.h"

void help(MANAGER manager) {
  initscr();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  char *title = get_page_as_string(get_current_page(manager));
  WINDOW *win = draw_window(yMax, xMax, 0.85, title);

  char *menu_entries[HELP_ENTRIES] = {
      "Up/Down: Move up and down",
      "Enter: Select option",
  };

  int menu_item = 0;
  draw_menu(win, menu_entries, HELP_ENTRIES, 0, &menu_item);
  option_switcher(win, draw_menu, menu_entries, HELP_ENTRIES, 0, &menu_item);

  change_page_and_cleanup_window(manager, MAIN_MENU, win);
  main_menu(manager);
}
