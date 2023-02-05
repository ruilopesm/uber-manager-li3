#include "views/main_menu.h"

#include <ncurses.h>
#include <stdlib.h>

#include "utils/components.h"
#include "views/execute_query.h"
#include "views/help.h"
#include "views/inspect_dataset.h"
#include "views/load_dataset.h"

void main_menu(MANAGER manager) {
  initscr();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  char *title = get_page_as_string(get_current_page(manager));
  WINDOW *win = draw_window(yMax, xMax, 0.85, title);

  char *menu_entries[MAIN_MENU_ENTRIES] = {"Execute query", "Load dataset",
                                           "Help", "Leave"};

  if (get_is_dataset_loaded(manager)) {
    char *dataset_path = get_dataset_path(manager);
    char *dataset_path_label = malloc(strlen(dataset_path) + 15);
    sprintf(dataset_path_label, "Dataset path: %s", dataset_path);

    int y, x;
    getmaxyx(win, y, x);
    (void)x;

    draw_label(win, dataset_path_label, y - 1, 2);

    free(dataset_path_label);
  }

  int menu_item = 0;
  draw_menu(win, menu_entries, MAIN_MENU_ENTRIES, 0, &menu_item);
  option_switcher(win, draw_menu, menu_entries, MAIN_MENU_ENTRIES, 0,
                  &menu_item);

  switch (menu_item) {
    // Execute query
    case 0: {
      if (get_is_dataset_loaded(manager)) {
        change_page_and_cleanup_window(manager, EXECUTE_QUERY, win);
        execute_query(manager);
      } else {
        change_page_and_cleanup_window(manager, LOAD_DATASET, win);
        load_dataset(manager);
      }

      break;
    }

    // Load dataset
    case 1:
      change_page_and_cleanup_window(manager, LOAD_DATASET, win);
      load_dataset(manager);
      break;

    // Help
    case 2:
      change_page_and_cleanup_window(manager, HELP, win);
      help(manager);
      break;

    // Leave
    case 3:
      curs_set(1);
      echo();
      delwin(win);
      endwin();
      fflush(stdout);
      clear();
      exit(0);
      break;

    default:
      break;
  }

  delwin(win);
  endwin();
}
