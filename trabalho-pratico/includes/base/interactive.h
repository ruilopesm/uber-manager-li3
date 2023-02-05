#ifndef INTERACTIVE_H
#define INTERACTIVE_H

// Use wide characters
#define _XOPEN_SOURCE_EXTENDED

#include <curses.h>
#include <locale.h>
#include <ncurses.h>

#include "base/stats.h"
#include "catalogs/join_catalog.h"

typedef struct manager *MANAGER;

enum page {
  MAIN_MENU,
  EXECUTE_QUERY,
  INSPECT_DATASET,
  LOAD_DATASET,
  HELP,
  USERS_PAGER,
  DRIVERS_PAGER,
  RIDES_PAGER,
  RESULTS_PAGER,
};

void interactive();

MANAGER create_manager();

void set_current_page(MANAGER manager, enum page page);

void set_dataset_path(MANAGER manager, char *path);

void set_is_dataset_loaded(MANAGER manager, bool is_loaded);

enum page get_current_page(MANAGER manager);

char *get_page_as_string(enum page page);

char *get_dataset_path(MANAGER manager);

bool get_is_dataset_loaded(MANAGER manager);

JOIN_CATALOG get_catalog(MANAGER manager);

STATS get_stats(MANAGER manager);

void change_page_and_cleanup_window(MANAGER manager, enum page page,
                                    WINDOW *window);

void free_manager(MANAGER manager);

#endif
