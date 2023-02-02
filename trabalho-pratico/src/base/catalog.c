#include "base/catalog.h"

#include <glib.h>
#include <stdio.h>

#include "entities/drivers.h"
#include "entities/users.h"
#include "utils/utils.h"

struct catalog {
  // username -> user_code: int
  GHashTable *users_code;
  GPtrArray *users_reverse_lookup;

  GHashTable *users;
  GHashTable *drivers;
  GHashTable *rides;

  // city -> city_code: int
  GHashTable *cities_code;
  GPtrArray *cities_reverse_lookup;
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
  new_catalog->cities_code =
      g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
  new_catalog->cities_reverse_lookup = g_ptr_array_new();
  g_ptr_array_set_free_func(new_catalog->cities_reverse_lookup, free);

  return new_catalog;
}

GHashTable *get_catalog_users(CATALOG catalog) { return catalog->users; }

GHashTable *get_catalog_drivers(CATALOG catalog) { return catalog->drivers; }

GHashTable *get_catalog_rides(CATALOG catalog) { return catalog->rides; }

USER get_user_by_username(CATALOG catalog, char *username) {
  GHashTable *users_code = catalog->users_code;
  gpointer user_code = g_hash_table_lookup(users_code, username);

  if (user_code == NULL) {
    return NULL;
  }

  return g_hash_table_lookup(catalog->users, user_code);
}

USER get_user_by_code(CATALOG catalog, gpointer user_code) {
  return g_hash_table_lookup(catalog->users, user_code);
}

char *get_username_from_code(CATALOG catalog, int user_code) {
  return g_ptr_array_index(catalog->users_reverse_lookup, user_code);
}

DRIVER get_driver_by_id(CATALOG catalog, int driver_id) {
  gpointer driver_id_ptr = GINT_TO_POINTER(driver_id);

  return g_hash_table_lookup(catalog->drivers, driver_id_ptr);
}

DRIVER get_driver_by_code(CATALOG catalog, gpointer driver_code) {
  return g_hash_table_lookup(catalog->drivers, driver_code);
}

GHashTable *get_catalog_cities_code(CATALOG catalog) {
  return catalog->cities_code;
}

char *get_city_from_code(CATALOG catalog, int city_code) {
  return g_ptr_array_index(catalog->cities_reverse_lookup, city_code);
}

char *get_city_code(CATALOG catalog, char *city) {
  return g_hash_table_lookup(catalog->cities_code, city);
}

GPtrArray *get_catalog_cities_reverse_lookup(CATALOG catalog) {
  return catalog->cities_reverse_lookup;
}

GHashTable *get_catalog_users_code(CATALOG catalog) {
  return catalog->users_code;
}

GPtrArray *get_catalog_users_reverse_lookup(CATALOG catalog) {
  return catalog->users_reverse_lookup;
}

void free_catalog(CATALOG catalog) {
  g_hash_table_destroy(catalog->users_code);
  g_ptr_array_free(catalog->users_reverse_lookup, 1);
  g_hash_table_destroy(catalog->users);
  g_hash_table_destroy(catalog->drivers);
  g_hash_table_destroy(catalog->rides);
  g_hash_table_destroy(catalog->cities_code);
  g_ptr_array_free(catalog->cities_reverse_lookup, 1);

  free(catalog);
}
