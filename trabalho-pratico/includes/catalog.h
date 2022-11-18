#ifndef CATALOG_H
#define CATALOG_H

#include <glib.h>

#include "common.h"

typedef struct catalog *CATALOG;

CATALOG create_catalog(void);

GHashTable *get_catalog_users(CATALOG catalog);

GHashTable *get_catalog_drivers(CATALOG catalog);

GHashTable *get_catalog_rides(CATALOG catalog);

GList *get_catalog_drivers_scores(CATALOG catalog);

void set_users(CATALOG catalog, GHashTable *users);

void set_drivers(CATALOG catalog, GHashTable *drivers);

void set_rides(CATALOG catalog, GHashTable *rides);

void update_number_of_rides(CATALOG catalog, char *user_id, char *driver_id);

void update_total_rating(CATALOG catalog, char *user_id, char *driver_id,
                         double user_score, double driver_score);

void update_ride_prices(CATALOG catalog, char *user_id, char *driver_id,
                        int distance, double tip);

void update_total_distance(CATALOG catalog, char *user_id, int distance);

void update_user_most_recent_ride(CATALOG catalog, char *user_id,
                                  struct date date);

GList *calculate_top_users_by_total_distance(CATALOG catalog);

gint compare_users_by_total_distance(gconstpointer a, gconstpointer b);

void update_latest_ride(CATALOG catalog, char *driver_id,
                        struct date ride_date);

void catalog_create_driver_score(CATALOG catalog);

void catalog_sort_drivers_by_score(CATALOG catalog);

gint compare_drivers_score(gconstpointer a, gconstpointer b);

void catalog_insert_driver_score(CATALOG catalog, char *driver_id);

void free_catalog(CATALOG catalog);

#endif
