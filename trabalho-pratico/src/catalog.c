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
  GList *drivers_score;
};

CATALOG create_catalog(void) {
  CATALOG new_catalog = malloc(sizeof(struct catalog));
  new_catalog->users = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                             (GDestroyNotify)free_user);
  new_catalog->drivers = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                               (GDestroyNotify)free_driver);
  new_catalog->rides = g_hash_table_new_full(g_str_hash, g_str_equal, free,
                                             (GDestroyNotify)free_ride);
  new_catalog->drivers_score = NULL;

  return new_catalog;
}

GHashTable *get_catalog_users(CATALOG catalog) { return catalog->users; }

GHashTable *get_catalog_drivers(CATALOG catalog) { return catalog->drivers; }

GHashTable *get_catalog_rides(CATALOG catalog) { return catalog->rides; }

GList *get_catalog_drivers_scores(CATALOG catalog) {
  return catalog->drivers_score;
}

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

void update_total_distance(CATALOG catalog, char *user_id, int distance) {
  GHashTable *users_hash_table = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users_hash_table, user_id);
  increment_user_total_distance(user, distance);
}

void update_user_most_recent_ride(CATALOG catalog, char *user_id,
                                  struct date date) {
  GHashTable *users_hash_table = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users_hash_table, user_id);
  struct date most_recent_ride = get_user_most_recent_ride(user);

  if (compare_dates(date, most_recent_ride) == 1) {
    set_user_most_recent_ride(user, date_to_string(date));
  }
}

GList *calculate_top_users_by_total_distance(CATALOG catalog) {
  GHashTable *users_hash_table = get_catalog_users(catalog);
  GList *users = g_hash_table_get_values(users_hash_table);

  users = g_list_sort(users, (GCompareFunc)compare_users_by_total_distance);

  return users;
}

gint compare_users_by_total_distance(gconstpointer a, gconstpointer b) {
  USER user_a = (USER)a;
  USER user_b = (USER)b;

  gint total_distance_a = (gint)get_user_total_distance(user_a);
  gint total_distance_b = (gint)get_user_total_distance(user_b);

  if (total_distance_a == total_distance_b) {
    struct date most_recent_ride_a = get_user_most_recent_ride(user_a);
    struct date most_recent_ride_b = get_user_most_recent_ride(user_b);

    int result_dates = compare_dates(most_recent_ride_a, most_recent_ride_b);

    if (result_dates == 0) {
      char *username_a = get_user_username(user_a);
      char *username_b = get_user_username(user_b);

      int result_usernames = strcmp(username_a, username_b);

      return (gint)result_usernames;

      free(username_a);
      free(username_b);
    }

    return (gint)result_dates * (-1);
  }

  return total_distance_b - total_distance_a;
}

void update_latest_ride(CATALOG catalog, char *driver_id,
                        struct date ride_date) {
  GHashTable *drivers_hash_table = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers_hash_table, driver_id);
  update_driver_latest_ride(driver, ride_date);
}

void catalog_sort_drivers_by_score(CATALOG catalog) {
  GList *drivers_score = get_catalog_drivers_scores(catalog);

  catalog->drivers_score =
      g_list_sort(drivers_score, (GCompareFunc)compare_drivers_score);
}

gint compare_drivers_score(gconstpointer a, gconstpointer b) {
  DRIVER driver_a = (DRIVER)a;
  DRIVER driver_b = (DRIVER)b;

  double a_score = get_driver_average_score(driver_a);
  double b_score = get_driver_average_score(driver_b);

  if (a_score > b_score) {
    return -1;
  } else if ((a_score == b_score) &&
             is_date_newer(get_driver_latest_ride(driver_a),
                           get_driver_latest_ride(driver_b))) {
    return -1;
  } else if ((a_score == b_score) &&
             is_date_equal(get_driver_latest_ride(driver_a),
                           get_driver_latest_ride(driver_b)) &&
             is_id_smaller(get_driver_id(driver_a), get_driver_id(driver_a))) {
    return -1;
  } else {
    return 1;
  }
}

void catalog_insert_driver_score(CATALOG catalog, char *driver_id) {
  GHashTable *drivers_hash_table = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers_hash_table, driver_id);
  GList *drivers_score = get_catalog_drivers_scores(catalog);

  catalog->drivers_score = g_list_prepend(drivers_score, driver);
  ;
}

void free_catalog(CATALOG catalog) {
  g_hash_table_destroy(catalog->users);
  g_hash_table_destroy(catalog->drivers);
  g_hash_table_destroy(catalog->rides);
  g_list_free(catalog->drivers_score);

  free(catalog);
}
