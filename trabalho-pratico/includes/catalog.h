#ifndef CATALOG_H
#define CATALOG_H

#include <glib.h>

#include "common.h"

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

char *get_catalog_driver_name(CATALOG catalog, char *driver_id);

void free_catalog(CATALOG catalog);

#endif
