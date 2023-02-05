#include "views/load_dataset.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base/interactive.h"
#include "utils/components.h"
#include "utils/utils.h"
#include "views/main_menu.h"

void load_dataset(MANAGER manager) {
  initscr();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  char *title = get_page_as_string(get_current_page(manager));
  WINDOW *win = draw_window(yMax, xMax, 0.85, title);

  char *menu_entries[LOAD_DATASET_ENTRIES] = {"Confirm and load", "Cancel"};

  char *input = draw_input_box(win, "Dataset folder path: ");

  int menu_item = 0;
  draw_menu(win, menu_entries, LOAD_DATASET_ENTRIES, 3, &menu_item);
  option_switcher(win, draw_menu, menu_entries, LOAD_DATASET_ENTRIES, 3,
                  &menu_item);

  switch (menu_item) {
    // Confirm and load
    case 0:
      confirm_and_load(manager, win, input);
      free(input);
      change_page_and_cleanup_window(manager, MAIN_MENU, win);
      main_menu(manager);
      break;

    // Back
    case 1:
      free(input);
      change_page_and_cleanup_window(manager, MAIN_MENU, win);
      main_menu(manager);
      break;

    default:
      break;
  }

  delwin(win);
  endwin();
}

void confirm_and_load(MANAGER manager, WINDOW *win, char *input) {
  if (strlen(input) == 0) {
    draw_warning_subwin(win, "The path is empty! (Press any key to try again)");
    change_page_and_cleanup_window(manager, LOAD_DATASET, win);
    load_dataset(manager);
  } else {
    JOINT_CATALOG catalog = get_catalog(manager);
    STATS stats = get_stats(manager);
    int ret = setup_catalog_and_stats(catalog, stats, input);

    if (ret != 0) {
      char *error = get_error_as_string(ret);
      char *message = malloc(strlen(error) + 50);
      sprintf(message, "%s (Press any key to try again)", error);
      draw_warning_subwin(win, message);
      free(message);
      change_page_and_cleanup_window(manager, LOAD_DATASET, win);
      load_dataset(manager);
    } else {
      set_is_dataset_loaded(manager, true);
      set_dataset_path(manager, input);
      draw_warning_subwin(
          win, "The dataset has been loaded! (Press any key to continue)");
    }
  }
}
