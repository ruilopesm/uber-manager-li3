#ifndef CATALOG_H
#define CATALOG_H

#include <glib.h>

typedef struct catalog *CATALOG;

CATALOG create_catalog(void);

GHashTable *get_catalog_users(CATALOG catalog);

GHashTable *get_catalog_drivers(CATALOG catalog);

GHashTable *get_catalog_rides(CATALOG catalog);

GHashTable *get_catalog_cities_code(CATALOG catalog);

GPtrArray *get_catalog_cities_reverse_lookup(CATALOG catalog);

GHashTable *get_catalog_users_code(CATALOG catalog);

GPtrArray *get_catalog_users_reverse_lookup(CATALOG catalog);

char *get_catalog_driver_name(CATALOG catalog, int *driver_id);

void free_catalog(CATALOG catalog);

#endif
