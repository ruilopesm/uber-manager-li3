#include "catalog.h"

#include <glib.h>
#include <stdio.h>

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

void update_number_of_rides(CATALOG catalog, char *user_id, char *driver_id) {
  GHashTable *users_hash_table = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users_hash_table, user_id);
  increment_user_number_of_rides(user);

  GHashTable *drivers_hash_table = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers_hash_table, driver_id);
  increment_driver_number_of_rides(driver);
}

void update_total_rating(CATALOG catalog, char *user_id, char *driver_id,
                         double user_score, double driver_score) {
  GHashTable *users_hash_table = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users_hash_table, user_id);
  increment_user_total_rating(user, user_score);

  GHashTable *drivers_hash_table = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers_hash_table, driver_id);
  increment_driver_total_rating(driver, driver_score);
}

void update_ride_prices(CATALOG catalog, char *user_id, char *driver_id,
                        int distance, double tip) {
  GHashTable *drivers_hash_table = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers_hash_table, driver_id);
  enum car_class car_class = get_driver_car_class(driver);
  double ride_price = calculate_ride_price(distance, car_class);
  increment_driver_total_earned(driver, ride_price + tip);

  GHashTable *users_hash_table = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users_hash_table, user_id);
  increment_user_total_spent(user, ride_price + tip);
}

void free_catalog(CATALOG catalog) {
  g_hash_table_destroy(catalog->users);
  g_hash_table_destroy(catalog->drivers);
  g_hash_table_destroy(catalog->rides);

  free(catalog);
}
