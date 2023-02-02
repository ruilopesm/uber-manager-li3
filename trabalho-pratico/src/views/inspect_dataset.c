#include "views/inspect_dataset.h"

#include <ncurses.h>

#include "utils/components.h"
#include "views/drivers_pager.h"
#include "views/main_menu.h"
#include "views/rides_pager.h"
#include "views/users_pager.h"

void inspect_dataset(MANAGER manager) {
  initscr();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  char *title = get_page_as_string(get_current_page(manager));
  WINDOW *win = draw_window(yMax, xMax, 0.85, title);

  char *menu_entries[INSPECT_DATASET_ENTRIES] = {
      "Users",
      "Drivers",
      "Rides",
      "Back",
  };

  int menu_item = 0;
  draw_menu(win, menu_entries, INSPECT_DATASET_ENTRIES, 0, &menu_item);
  option_switcher(win, draw_menu, menu_entries, INSPECT_DATASET_ENTRIES, 0,
                  &menu_item);

  switch (menu_item) {
    // See users
    case 0:
      change_page_and_cleanup_window(manager, USERS_PAGER, win);
      users_pager(manager);
      break;

    // See drivers
    case 1:
      change_page_and_cleanup_window(manager, DRIVERS_PAGER, win);
      drivers_pager(manager);
      break;

    // See rides
    case 2:
      change_page_and_cleanup_window(manager, RIDES_PAGER, win);
      rides_pager(manager);
      break;

    // Back
    case 3:
      change_page_and_cleanup_window(manager, MAIN_MENU, win);
      main_menu(manager);
      break;
  }

  delwin(win);
  endwin();
}
