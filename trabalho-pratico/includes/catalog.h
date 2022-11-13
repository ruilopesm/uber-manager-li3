#ifndef CATALOG_H
#define CATALOG_H

#include <glib.h>

typedef struct catalog *CATALOG;

CATALOG create_catalog(void);

GHashTable *get_catalog_users(CATALOG catalog);

GHashTable *get_catalog_drivers(CATALOG catalog);

GHashTable *get_catalog_rides(CATALOG catalog);

void set_users(CATALOG catalog, GHashTable *users);

void set_drivers(CATALOG catalog, GHashTable *drivers);

void set_rides(CATALOG catalog, GHashTable *rides);

void update_number_of_rides(CATALOG catalog, char *user_id, char *driver_id);

void update_total_rating(CATALOG catalog, char *user_id, char *driver_id,
                         double user_score, double driver_score);

void update_ride_prices(CATALOG catalog, char *user_id, char *driver_id,
                        int distance, double tip);

void free_catalog(CATALOG catalog);

#endif