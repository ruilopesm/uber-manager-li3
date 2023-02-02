#include "base/interactive.h"

#include <curses.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "base/catalog.h"
#include "base/stats.h"
#include "views/main_menu.h"

struct manager {
  enum page current_page;
  char *dataset_path;
  bool is_dataset_loaded;
  CATALOG catalog;
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
  manager->catalog = create_catalog();
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

CATALOG get_catalog(MANAGER manager) { return manager->catalog; }

STATS get_stats(MANAGER manager) { return manager->stats; }

void change_page_and_cleanup_window(MANAGER manager, enum page page,
                                    WINDOW *win) {
  delwin(win);
  set_current_page(manager, page);
}

void free_manager(MANAGER manager) {
  free(manager->dataset_path);
  free_catalog(manager->catalog);
  free_stats(manager->stats);
  free(manager);
}
