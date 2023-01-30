#ifndef CATALOG_H
#define CATALOG_H

#include <glib.h>

#include "utils.h"

typedef struct catalog *CATALOG;

struct query4_utils {
  CATALOG catalog;
  double total_spent;
  int total_rides;
};

CATALOG create_catalog(void);

GHashTable *get_catalog_users(CATALOG catalog);

GHashTable *get_catalog_drivers(CATALOG catalog);

GHashTable *get_catalog_rides(CATALOG catalog);

GHashTable *get_catalog_city_code(CATALOG catalog);

GPtrArray *get_catalog_city_reverse_lookup(CATALOG catalog);

GHashTable *get_catalog_users_code(CATALOG catalog);

GPtrArray *get_catalog_users_reverse_lookup(CATALOG catalog);

char *get_catalog_driver_name(CATALOG catalog, int *driver_id);

void free_catalog(CATALOG catalog);

#endif
