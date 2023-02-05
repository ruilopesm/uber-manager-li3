#include "base/interactive.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "base/stats.h"
#include "catalogs/drivers_catalog.h"
#include "catalogs/join_catalog.h"
#include "catalogs/rides_catalog.h"
#include "catalogs/users_catalog.h"
#include "views/main_menu.h"

struct manager {
  enum page current_page;
  char *dataset_path;
  bool is_dataset_loaded;
  JOIN_CATALOG catalog;
  STATS stats;
};

void interactive() {
  setlocale(LC_ALL, "");

  MANAGER manager = create_manager();

  main_menu(manager);

  free_manager(manager);
}

MANAGER create_manager() {
  MANAGER manager = malloc(sizeof(struct manager));

  manager->current_page = MAIN_MENU;
  manager->dataset_path = NULL;
  manager->is_dataset_loaded = false;

  USERS_CATALOG users_catalog = create_users_catalog();
  DRIVERS_CATALOG drivers_catalog = create_drivers_catalog();
  RIDES_CATALOG rides_catalog = create_rides_catalog();
  manager->catalog =
      create_join_catalog(users_catalog, drivers_catalog, rides_catalog);

  manager->stats = create_stats();

  return manager;
}

void set_current_page(MANAGER manager, enum page page) {
  manager->current_page = page;
}

void set_dataset_path(MANAGER manager, char *path) {
  manager->dataset_path = strdup(path);
}

void set_is_dataset_loaded(MANAGER manager, bool is_loaded) {
  manager->is_dataset_loaded = is_loaded;
}

enum page get_current_page(MANAGER manager) { return manager->current_page; }

char *get_page_as_string(enum page page) {
  switch (page) {
    case MAIN_MENU:
      return "Main menu";
    case EXECUTE_QUERY:
      return "Execute query";
    case INSPECT_DATASET:
      return "Inspect dataset";
    case LOAD_DATASET:
      return "Load dataset";
    case HELP:
      return "Help";
    case USERS_PAGER:
      return "Users pager";
    case DRIVERS_PAGER:
      return "Drivers pager";
    case RIDES_PAGER:
      return "Rides pager";
    default:
      return "Unkonwn page";
  }
}

char *get_dataset_path(MANAGER manager) { return manager->dataset_path; }

bool get_is_dataset_loaded(MANAGER manager) {
  return manager->is_dataset_loaded;
}

JOIN_CATALOG get_catalog(MANAGER manager) { return manager->catalog; }

STATS get_stats(MANAGER manager) { return manager->stats; }

void change_page_and_cleanup_window(MANAGER manager, enum page page,
                                    WINDOW *win) {
  delwin(win);
  set_current_page(manager, page);
}

void free_manager(MANAGER manager) {
  free(manager->dataset_path);
  free_join_catalog(manager->catalog);
  free_users_catalog(get_users_catalog(manager->catalog));
  free_drivers_catalog(get_drivers_catalog(manager->catalog));
  free_rides_catalog(get_rides_catalog(manager->catalog));
  free_stats(manager->stats);
  free(manager);
}
