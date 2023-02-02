#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include <ncurses.h>
#include <stdbool.h>

#include "base/catalog.h"
#include "base/stats.h"

// Use wide characters
#define _XOPEN_SOURCE_EXTENDED

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

CATALOG get_catalog(MANAGER manager);

STATS get_stats(MANAGER manager);

void change_page_and_cleanup_window(MANAGER manager, enum page page,
                                    WINDOW *window);

void free_manager(MANAGER manager);

#endif
