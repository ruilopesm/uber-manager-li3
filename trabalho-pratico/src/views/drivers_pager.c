#include "views/drivers_pager.h"

#include <glib.h>
#include <ncurses.h>
#include <stdbool.h>

#include "base/interactive.h"
#include "base/stats.h"
#include "catalogs/join_catalog.h"
#include "entities/drivers.h"
#include "utils/components.h"
#include "utils/utils.h"
#include "views/inspect_dataset.h"

void drivers_pager(MANAGER manager) {
  initscr();
  noecho();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  char *title = get_page_as_string(get_current_page(manager));
  WINDOW *win = draw_window(yMax, xMax, 0.85, title);

  int y, x;
  getmaxyx(win, y, x);

  GHashTable *drivers = NULL;

  int current_page = 0;
  int drivers_per_page = y - 5;
  int max_pages = g_hash_table_size(drivers) / drivers_per_page;

  GHashTableIter iter;
  gpointer key, value;

  while (true) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, title);

    mvwprintw(win, y - 1, 2, "Page %d of %d", current_page + 1, max_pages);

    // Draw schema & instructions
    mvwprintw(
        win, 0, x / 2 - 35,
        "id;name;birth_day;gender;car_class;account_creation;account_status");
    mvwprintw(win, y - 1, x / 2 - 15, "n: next page, p: previous page");
    mvwprintw(win, y - 1, x - 15 - 2, "Press q to quit");

    // Draw drivers
    g_hash_table_iter_init(&iter, drivers);
    int counter = 0;
    int start = current_page * drivers_per_page;
    int end = start + drivers_per_page;

    while (g_hash_table_iter_next(&iter, &key, &value)) {
      if (counter >= start && counter <= end) {
        DRIVER driver = (DRIVER)value;

        gpointer driver_id = (gpointer)key;
        int id = GPOINTER_TO_INT(driver_id);
        char *zfilled_id = zfill_id(&id);

        char *name = get_driver_name(driver);

        int birth_date = get_driver_birth_date(driver);
        char *birth_date_str = date_to_string(birth_date);

        enum gender gender = get_driver_gender(driver);
        const char *gender_str = gender_to_string(gender);

        enum car_class car_class = get_driver_car_class(driver);
        const char *car_class_str = car_class_to_string(car_class);

        int account_creation = get_driver_account_creation(driver);
        char *account_creation_str = date_to_string(account_creation);

        enum account_status account_status = get_driver_account_status(driver);
        const char *account_status_str =
            account_status_to_string(account_status);

        mvwprintw(win, counter - start + 2, x / 2 - 35, "%s;%s;%s;%s;%s;%s;%s",
                  zfilled_id, name, birth_date_str, gender_str, car_class_str,
                  account_creation_str, account_status_str);

        free(zfilled_id);
        free(name);
        free(birth_date_str);
        free(account_creation_str);
      }

      counter++;
    }

    int key;
    key = wgetch(win);

    switch (key) {
      case 'q':
        change_page_and_cleanup_window(manager, INSPECT_DATASET, win);
        echo();
        inspect_dataset(manager);
        break;

      case 'n':
        if (current_page < max_pages - 1) {
          current_page++;
        }

        break;

      case 'p':
        if (current_page > 0) {
          current_page--;
        }

        break;
    }
  }

  delwin(win);
  endwin();
}
