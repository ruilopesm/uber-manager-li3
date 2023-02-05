#include "views/users_pager.h"

#include <glib.h>
#include <ncurses.h>
#include <stdbool.h>

#include "base/interactive.h"
#include "base/stats.h"
#include "catalogs/join_catalog.h"
#include "entities/users.h"
#include "utils/components.h"
#include "views/inspect_dataset.h"

void users_pager(MANAGER manager) {
  initscr();
  noecho();

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);

  char *title = get_page_as_string(get_current_page(manager));
  WINDOW *win = draw_window(yMax, xMax, 0.85, title);

  int y, x;
  getmaxyx(win, y, x);

  JOIN_CATALOG catalog = get_catalog(manager);
  USERS_CATALOG users_catalog = get_users_catalog(catalog);
  GHashTable *users = NULL;

  int current_page = 0;
  int users_per_page = y - 5;
  int max_pages = g_hash_table_size(users) / users_per_page;

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
        "username;name;gender;birth_date;account_creation;account_status");
    mvwprintw(win, y - 1, x / 2 - 15, "n: next page, p: previous page");
    mvwprintw(win, y - 1, x - 15 - 2, "Press q to quit");

    // Draw users
    g_hash_table_iter_init(&iter, users);
    int counter = 0;
    int start = current_page * users_per_page;
    int end = start + users_per_page;

    while (g_hash_table_iter_next(&iter, &key, &value)) {
      if (counter >= start && counter <= end) {
        USER user = (USER)value;

        gpointer username = (gpointer)key;
        char *username_str = get_username_from_code(users_catalog, username);

        char *name = get_user_name(user);

        enum gender gender = get_user_gender(user);
        const char *gender_str = gender_to_string(gender);

        int birth_date = get_user_birth_date(user);
        char *birth_date_str = date_to_string(birth_date);

        int account_creation = get_user_account_creation(user);
        char *account_creation_str = date_to_string(account_creation);

        enum account_status account_status = get_user_account_status(user);
        const char *account_status_str =
            account_status_to_string(account_status);

        mvwprintw(win, counter - start + 2, x / 2 - 35, "%s;%s;%s;%s;%s;%s",
                  username_str, name, gender_str, birth_date_str,
                  account_creation_str, account_status_str);

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
