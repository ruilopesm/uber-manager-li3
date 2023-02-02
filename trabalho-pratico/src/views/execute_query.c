#include "views/execute_query.h"

#include <ncurses.h>

#include "base/querier.h"
#include "io/input.h"
#include "io/output.h"
#include "utils/components.h"
#include "views/main_menu.h"
#include "views/results_pager.h"

void execute_query(MANAGER manager) {
  initscr();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  char *title = get_page_as_string(get_current_page(manager));
  WINDOW *win = draw_window(yMax, xMax, 0.85, title);

  char *menu_entries[EXECUTE_QUERY_ENTRIES] = {"Confirm and execute", "Cancel"};

  char *input = draw_input_box(win, "Input the query: <type> <params...>");

  int menu_item = 0;
  draw_menu(win, menu_entries, EXECUTE_QUERY_ENTRIES, 3, &menu_item);
  option_switcher(win, draw_menu, menu_entries, EXECUTE_QUERY_ENTRIES, 3,
                  &menu_item);

  switch (menu_item) {
    // Confirm and execute
    case 0:
      confirm_and_execute(manager, win, input);
      free(input);
      change_page_and_cleanup_window(manager, MAIN_MENU, win);
      main_menu(manager);
      break;

    // Back
    case 1:
      change_page_and_cleanup_window(manager, MAIN_MENU, win);
      main_menu(manager);
      break;

    default:
      break;
  }

  delwin(win);
  endwin();
}

void confirm_and_execute(MANAGER manager, WINDOW *win, char *input) {
  if (strlen(input) == 0) {
    draw_warning_subwin(win,
                        "The query is empty! (Press any key to try again)");
    change_page_and_cleanup_window(manager, EXECUTE_QUERY, win);
    execute_query(manager);
  } else {
    char *to_check = strdup(input);

    if (validate_query(to_check)) {
      free(to_check);

      CATALOG catalog = get_catalog(manager);
      STATS stats = get_stats(manager);

      void *result = querier(catalog, stats, input);

      if (result == NULL) {
        draw_warning_subwin(win,
                            "No results found for the query (Press any key to "
                            "input a query again)");
        change_page_and_cleanup_window(manager, EXECUTE_QUERY, win);
        execute_query(manager);
      } else {
        if (input[0] == '1' || input[0] == '4' || input[0] == '5' ||
            input[0] == '6') {
          draw_query_result(manager, win, result, NULL, input[0]);
          change_page_and_cleanup_window(manager, EXECUTE_QUERY, win);
          execute_query(manager);
        } else {
          change_page_and_cleanup_window(manager, RESULTS_PAGER, win);
          results_pager(manager, result, input);
        }
      }
    } else {
      free(to_check);

      draw_warning_subwin(win,
                          "Invalid query format or <type> (1-9) (Press any key "
                          "to input a query again)");
      change_page_and_cleanup_window(manager, EXECUTE_QUERY, win);
      execute_query(manager);
    }
  }
}
