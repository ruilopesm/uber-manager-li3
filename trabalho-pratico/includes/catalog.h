#ifndef CATALOG_H
#define CATALOG_H

#include <glib.h>

#include "common.h"

typedef struct catalog *CATALOG;

CATALOG create_catalog(void);

GHashTable *get_catalog_users(CATALOG catalog);

GHashTable *get_catalog_drivers(CATALOG catalog);

GHashTable *get_catalog_rides(CATALOG catalog);

void free_catalog(CATALOG catalog);

#endif
