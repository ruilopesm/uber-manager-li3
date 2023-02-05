#ifndef INTERACTIVE_H
#define INTERACTIVE_H

// Use wide characters
#define _XOPEN_SOURCE_EXTENDED

#include <curses.h>
#include <locale.h>
#include <ncurses.h>

#include "base/stats.h"
#include "catalogs/join_catalog.h"

/**
 * @struct manager
 *
 * @brief Struct that contains auxiliar data to run the interactive mode
 */
typedef struct manager *MANAGER;

/**
 * @enum page
 *
 * @brief Enum that contains the different pages of the interactive mode
 */
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

/**
 * @brief Function that initializes the interactive mode by calling the
 * __main_menu__ function
 *
 */
void interactive();

/**
 * @brief Function that creates a new manager struct
 *
 * @return manager - The new manager of type `MANAGER`
 */
MANAGER create_manager();

/**
 * @brief Function that changes the state of the current page in the manager
 * struct
 *
 * @param manager - The altered manager of type `MANAGER`
 * @param page - The new page of type `enum page`
 */
void set_current_page(MANAGER manager, enum page page);

/**
 * @brief Function that changes the state of the dataset path in the manager
 * struct
 *
 * @param manager - The altered manager of type `MANAGER`
 * @param path - The new path of type `char *`
 */
void set_dataset_path(MANAGER manager, char *path);

/**
 * @brief Function that changes the state of the dataset loaded in the manager
 * struct
 *
 * @param manager - The altered manager of type `MANAGER`
 * @param is_loaded - The new state of type `bool`
 */
void set_is_dataset_loaded(MANAGER manager, bool is_loaded);

/**
 * @brief Function that gets the state of the current page in the manager struct
 *
 * @param manager - The manager struct of type `MANAGER`
 *
 * @return page - The current page of type `enum page`
 */
enum page get_current_page(MANAGER manager);

/**
 * @brief Function that translates the current state of the page to a string
 *
 * @param page - The current page of type `enum page`
 *
 * @return page - The current page as a string of type `char *`
 */
char *get_page_as_string(enum page page);

/**
 * @brief Function that gets the dataset path in the manager struct
 *
 * @param manager - The manager struct of type `MANAGER`
 *
 * @return dataset_path - The dataset path of type `char *`
 */
char *get_dataset_path(MANAGER manager);

/**
 * @brief Function that gets the state of the dataset loaded in the manager
 * struct
 *
 * @param manager - The manager struct of type `MANAGER`
 *
 * @return is_dataset_loaded - The state of the dataset loaded of type `bool`,
 * `true` if the dataset is loaded, `false` otherwise
 */
bool get_is_dataset_loaded(MANAGER manager);

/**
 * @brief Function that gets the catalog in the manager struct
 *
 * @param manager - The manager struct of type `MANAGER`
 *
 * @return catalog - The catalog of type `JOIN_CATALOG`
 */
JOIN_CATALOG get_catalog(MANAGER manager);

/**
 * @brief Function that gets the stats in the manager struct
 *
 * @param manager - The manager struct of type `MANAGER`
 *
 * @return stats - The stats of type `STATS`
 */
STATS get_stats(MANAGER manager);

/**
 * @brief Function that changes the state of the current page in the manager
 * struct and frees the window
 *
 * @param manager - The altered manager of type `MANAGER`
 * @param page - The new page of type `enum page`
 * @param win - The window to be freed of type `WINDOW *`
 */
void change_page_and_cleanup_window(MANAGER manager, enum page page,
                                    WINDOW *window);

/**
 * @brief Function that frees the manager struct
 *
 * @param manager - The manager to be freed of type `MANAGER`
 */
void free_manager(MANAGER manager);

#endif
