#include "views/rides_pager.h"

#include <glib.h>
#include <ncurses.h>
#include <stdbool.h>

#include "base/catalog.h"
#include "base/interactive.h"
#include "base/stats.h"
#include "entities/rides.h"
#include "utils/components.h"
#include "utils/utils.h"
#include "views/inspect_dataset.h"

void rides_pager(MANAGER manager) {
  initscr();
  noecho();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  char *title = get_page_as_string(get_current_page(manager));
  WINDOW *win = draw_window(yMax, xMax, 0.85, title);

  int y, x;
  getmaxyx(win, y, x);

  CATALOG catalog = get_catalog(manager);
  GHashTable *rides = get_catalog_rides(catalog);
  GPtrArray *cities_reverse_lookup = get_catalog_cities_reverse_lookup(catalog);
  GPtrArray *users_reverse_lookup = get_catalog_users_reverse_lookup(catalog);

  int current_page = 0;
  int rides_per_page = y - 5;
  int max_pages = g_hash_table_size(rides) / rides_per_page;

  GHashTableIter iter;
  gpointer key, value;

  while (true) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, title);

    mvwprintw(win, y - 1, 2, "Page %d of %d", current_page + 1, max_pages);

    // Draw schema & instructions
    mvwprintw(win, 0, x / 2 - 35,
              "id;date;driver;user;city;distance;score_user;score_driver;tip");
    mvwprintw(win, y - 1, x / 2 - 15, "n: next page, p: previous page");
    mvwprintw(win, y - 1, x - 15 - 2, "Press q to quit");

    // Draw rides
    g_hash_table_iter_init(&iter, rides);
    int counter = 0;
    int start = current_page * rides_per_page;
    int end = start + rides_per_page;

    while (g_hash_table_iter_next(&iter, &key, &value)) {
      if (counter >= start && counter <= end) {
        RIDE ride = (RIDE)value;

        gpointer ride_id = (gpointer)key;
        int id = GPOINTER_TO_INT(ride_id);
        char *zfilled_id = zfill_id(&id);

        int date = get_ride_date(ride);
        char *date_str = date_to_string(date);

        gpointer driver = get_ride_driver(ride);
        int driver_int = GPOINTER_TO_INT(driver);
        char *zfilled_driver = zfill_id(&driver_int);

        gpointer user = get_ride_user(ride);
        int user_int = GPOINTER_TO_INT(user);
        char *user_str = g_ptr_array_index(users_reverse_lookup, user_int);

        int city = get_ride_city(ride);
        char *city_str = g_ptr_array_index(cities_reverse_lookup, city);

        int distance = get_ride_distance(ride);
        int score_user = get_ride_score_user(ride);
        int score_driver = get_ride_score_driver(ride);
        double tip = get_ride_tip(ride);

        mvwprintw(win, counter - start + 2, x / 2 - 35,
                  "%s;%s;%s;%s;%s;%d;%d;%d;%.1f", zfilled_id, date_str,
                  zfilled_driver, user_str, city_str, distance, score_user,
                  score_driver, tip);

        free(zfilled_id);
        free(date_str);
        free(zfilled_driver);
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
