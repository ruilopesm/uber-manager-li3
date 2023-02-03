#include "base/catalog.h"

#include <glib.h>
#include <stdio.h>

#include "entities/drivers.h"
#include "entities/rides.h"
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

// Users
void insert_user(CATALOG catalog, USER user, gpointer key) {
  g_hash_table_insert(catalog->users, key, user);
}

void set_catalog_user_username(CATALOG catalog, USER user, char *username) {
  static int users_parsed = 0;

  // Creates the user_code and inserts it into the users_code table
  char *username_copy = strdup(username);
  gpointer user_code = GINT_TO_POINTER(users_parsed);
  g_hash_table_insert(catalog->users_code, username_copy, user_code);

  // Inserts the username into the reverse search array
  char *username_copy_to_reverse = strdup(username);
  g_ptr_array_add(catalog->users_reverse_lookup, username_copy_to_reverse);

  // Puts the user code into the user struct
  gpointer username_code = GINT_TO_POINTER(users_parsed);
  set_user_username(user, username_code);

  users_parsed++;
}

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

void update_user_catalog(CATALOG catalog, gpointer username, int distance,
                         double rating, double price, double tip, int date) {
  USER user = get_user_by_code(catalog, username);

  set_user_number_of_rides(user, get_user_number_of_rides(user) + 1);
  set_user_total_rating(user, get_user_total_rating(user) + rating);
  set_user_total_spent(user, get_user_total_spent(user) + price + tip);
  set_user_total_distance(user, get_user_total_distance(user) + distance);

  if ((date - get_user_latest_ride(user)) > 0) {
    set_user_latest_ride(user, date);
  }
}

// Drivers
void insert_driver(CATALOG catalog, DRIVER driver, gpointer key) {
  g_hash_table_insert(catalog->drivers, key, driver);
}

DRIVER get_driver_by_id(CATALOG catalog, int driver_id) {
  gpointer driver_id_ptr = GINT_TO_POINTER(driver_id);

  return g_hash_table_lookup(catalog->drivers, driver_id_ptr);
}

DRIVER get_driver_by_code(CATALOG catalog, gpointer driver_code) {
  return g_hash_table_lookup(catalog->drivers, driver_code);
}

char *get_username_from_code(CATALOG catalog, int user_code) {
  return g_ptr_array_index(catalog->users_reverse_lookup, user_code);
}

void update_driver_catalog(CATALOG catalog, gpointer driver_id, double rating,
                           double price, double tip, int date) {
  DRIVER driver = get_driver_by_code(catalog, driver_id);

  set_driver_number_of_rides(driver, get_driver_number_of_rides(driver) + 1);
  set_driver_total_rating(driver, get_driver_total_rating(driver) + rating);
  set_driver_total_earned(driver,
                          get_driver_total_earned(driver) + price + tip);

  if ((date - get_driver_latest_ride(driver)) > 0) {
    set_driver_latest_ride(driver, date);
  }
}

// Rides
void insert_ride_and_update_catalog(CATALOG catalog, RIDE ride, gpointer key,
                                    gpointer user, gpointer driver,
                                    int distance, double score_user,
                                    double price, double tip, int date,
                                    double score_driver) {
  g_hash_table_insert(catalog->rides, key, ride);
  update_user_catalog(catalog, user, distance, score_user, price, tip, date);
  update_driver_catalog(catalog, driver, score_driver, price, tip, date);
}

void set_catalog_ride_user(CATALOG catalog, RIDE ride, char *username) {
  gpointer user_code = g_hash_table_lookup(catalog->users_code, username);
  set_ride_user(ride, user_code);
}

void set_catalog_ride_city(CATALOG catalog, RIDE ride, char *city) {
  static char cities_parsed = 0;

  char *city_number;
  city_number = g_hash_table_lookup(catalog->cities_code, city);

  if (city_number) {
    set_ride_city(ride, *city_number);
  } else {
    char *city_copy = strdup(city);
    g_ptr_array_add(catalog->cities_reverse_lookup, city_copy);
    city_number = malloc(sizeof(char));
    *city_number = cities_parsed;
    cities_parsed++;
    char *city_key = strdup(city);
    g_hash_table_insert(catalog->cities_code, city_key, city_number);
    set_ride_city(ride, *city_number);
  }
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
