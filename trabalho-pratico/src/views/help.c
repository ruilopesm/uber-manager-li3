#include "views/help.h"

#include <ncurses.h>
#include <string.h>

#include "utils/components.h"
#include "views/main_menu.h"

void help(MANAGER manager) {
  initscr();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  char *title = get_page_as_string(get_current_page(manager));
  WINDOW *win = draw_window(yMax, xMax, 0.85, title);

  char *entries[HELP_ENTRIES] = {
      "1 <username: str | driver_id: int> - Shows the user/driver profile",
      "2 <N: int> - Top N drivers by average rating",
      "3 <N: int> - Top N users by total travelled distance",
      "4 <city: str> - Average trips' price in a city",
      "5 <date: DD/MM/YYYY date: DD/MM/YYYY> - Average trips' price, not "
      "considering tip, in a date range",
      "6 <city: str date: DD/MM/YYYY date: DD/MM/YYYY> - Average travelled "
      "distance in a city in a date range",
      "7 <N: int city: str> - Top N drivers by average rating in a city",
      "8 <gender: M|F X: int> - Trips where the user and the driver have the "
      "same gender and have profiles with X or more years",
      "9 <date: DD/MM/YYYY date: DD/MM/YYYY> - Trips where the user gave tip "
      "in a date range ordered by travelled distance",
  };

  int y, x;
  getmaxyx(win, y, x);
  (void)y;

  // Draw the help entries
  for (int i = 0; i < HELP_ENTRIES; i++) {
    draw_label(win, entries[i], 8 + i * 2, x / 2 - strlen(entries[i]) / 2);
  }

  draw_label(win, "Press any key to go back", y - 1, x / 2 - 15);

  wgetch(win);

  change_page_and_cleanup_window(manager, MAIN_MENU, win);
  main_menu(manager);
}
