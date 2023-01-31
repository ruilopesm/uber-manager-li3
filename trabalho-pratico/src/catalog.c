#include "catalog.h"

#include <glib.h>
#include <stdio.h>

#include "drivers.h"
#include "rides.h"
#include "users.h"
#include "utils.h"

struct catalog {
  GHashTable *users_code;
  // Used in situations where you have a user code and need to find the username
  GPtrArray *users_reverse_lookup;
  GHashTable *users;
  GHashTable *drivers;
  GHashTable *rides;
  GHashTable *city_code;
  // Used in situations where you have a city code and need to find the city
  // name
  GPtrArray *city_reverse_lookup;
};

CATALOG create_catalog(void) {
  CATALOG new_catalog = malloc(sizeof(struct catalog));
  new_catalog->users_code =
      g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
  new_catalog->users_reverse_lookup = g_ptr_array_new();
  g_ptr_array_set_free_func(new_catalog->users_reverse_lookup, free);
  new_catalog->users = g_hash_table_new_full(NULL, g_direct_equal, NULL,
                                             (GDestroyNotify)free_user);
  new_catalog->drivers = g_hash_table_new_full(NULL, g_direct_equal, NULL,
                                               (GDestroyNotify)free_driver);
  new_catalog->rides = g_hash_table_new_full(NULL, g_direct_equal, NULL, free);
  new_catalog->city_code =
      g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
  new_catalog->city_reverse_lookup = g_ptr_array_new();
  g_ptr_array_set_free_func(new_catalog->city_reverse_lookup, free);
  return new_catalog;
}

GHashTable *get_catalog_users(CATALOG catalog) { return catalog->users; }

GHashTable *get_catalog_drivers(CATALOG catalog) { return catalog->drivers; }

GHashTable *get_catalog_rides(CATALOG catalog) { return catalog->rides; }

GHashTable *get_catalog_city_code(CATALOG catalog) {
  return catalog->city_code;
}

GPtrArray *get_catalog_city_reverse_lookup(CATALOG catalog) {
  return catalog->city_reverse_lookup;
}

GHashTable *get_catalog_users_code(CATALOG catalog) {
  return catalog->users_code;
}

GPtrArray *get_catalog_users_reverse_lookup(CATALOG catalog) {
  return catalog->users_reverse_lookup;
}

char *get_catalog_driver_name(CATALOG catalog, int *driver_id) {
  DRIVER driver =
      g_hash_table_lookup(catalog->drivers, GINT_TO_POINTER(*driver_id));
  return get_driver_name(driver);
}

void free_catalog(CATALOG catalog) {
  g_hash_table_destroy(catalog->users_code);
  g_ptr_array_free(catalog->users_reverse_lookup, 1);
  g_hash_table_destroy(catalog->users);
  g_hash_table_destroy(catalog->drivers);
  g_hash_table_destroy(catalog->rides);
  g_hash_table_destroy(catalog->city_code);
  g_ptr_array_free(catalog->city_reverse_lookup, 1);

  free(catalog);
}
