#include "catalog.h"

#include <glib.h>
#include <stdio.h>

#include "common.h"
#include "drivers.h"
#include "rides.h"
#include "users.h"

struct catalog {
  GHashTable *users;
  GHashTable *drivers;
  GHashTable *rides;
};

CATALOG create_catalog(void) {
  CATALOG new_catalog = malloc(sizeof(struct catalog));
  new_catalog->users = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                             (GDestroyNotify)free_user);
  new_catalog->drivers = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                               (GDestroyNotify)free_driver);
  new_catalog->rides = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                             (GDestroyNotify)free_ride);
  return new_catalog;
}

GHashTable *get_catalog_users(CATALOG catalog) { return catalog->users; }

GHashTable *get_catalog_drivers(CATALOG catalog) { return catalog->drivers; }

GHashTable *get_catalog_rides(CATALOG catalog) { return catalog->rides; }

void free_catalog(CATALOG catalog) {
  g_hash_table_destroy(catalog->users);
  g_hash_table_destroy(catalog->drivers);
  g_hash_table_destroy(catalog->rides);

  free(catalog);
}
