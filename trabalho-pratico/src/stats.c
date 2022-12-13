#include "stats.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "catalog.h"
#include "common.h"
#include "drivers.h"
#include "rides.h"
#include "users.h"

struct stats {
  GList *top_drivers_by_average_score;
  GList *top_users_by_total_distance;
};

STATS create_stats(void) {
  STATS new_stats = malloc(sizeof(struct stats));

  new_stats->top_drivers_by_average_score = NULL;
  new_stats->top_users_by_total_distance = NULL;

  return new_stats;
}

GList *get_top_drivers_by_average_score(STATS stats) {
  return stats->top_drivers_by_average_score;
}

GList *get_top_users_by_total_distance(STATS stats) {
  return stats->top_users_by_total_distance;
}

void update_user_stats(CATALOG catalog, char *username, int distance,
                       double rating, double price, double tip,
                       struct date date) {
  GHashTable *users = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users, username);

  set_user_number_of_rides(user, get_user_number_of_rides(user) + 1);
  set_user_total_rating(user, get_user_total_rating(user) + rating);
  set_user_total_spent(user, get_user_total_spent(user) + price + tip);
  set_user_total_distance(user, get_user_total_distance(user) + distance);

  if (compare_dates(date, get_user_latest_ride(user)) > 0) {
    char *date_string = date_to_string(date);
    set_user_latest_ride(user, date_string);
    free(date_string);
  }
}

void update_driver_stats(CATALOG catalog, char *driver_id, double rating,
                         double price, double tip, struct date date) {
  GHashTable *drivers = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers, driver_id);

  set_driver_number_of_rides(driver, get_driver_number_of_rides(driver) + 1);
  set_driver_total_rating(driver, get_driver_total_rating(driver) + rating);
  set_driver_total_earned(driver,
                          get_driver_total_earned(driver) + price + tip);

  if (compare_dates(date, get_driver_latest_ride(driver)) > 0) {
    char *date_string = date_to_string(date);
    set_driver_latest_ride(driver, date_string);
    free(date_string);
  }
}

void calculate_top_users_by_total_distance(STATS stats, CATALOG catalog) {
  GList *top_users_by_total_distance =
      g_hash_table_get_values(get_catalog_users(catalog));

  stats->top_users_by_total_distance =
      g_list_sort(top_users_by_total_distance, compare_users_by_total_distance);
}

gint compare_users_by_total_distance(gconstpointer a, gconstpointer b) {
  USER user_a = (USER)a;
  USER user_b = (USER)b;

  int total_distance_a = get_user_total_distance(user_a);
  int total_distance_b = get_user_total_distance(user_b);

  if (total_distance_a == total_distance_b) {
    struct date most_recent_ride_a = get_user_latest_ride(user_a);
    struct date most_recent_ride_b = get_user_latest_ride(user_b);

    int result_dates = compare_dates(most_recent_ride_a, most_recent_ride_b);

    if (result_dates == 0) {
      char *username_a = get_user_username(user_a);
      char *username_b = get_user_username(user_b);

      int to_return = strcmp(username_a, username_b);

      free(username_a);
      free(username_b);

      return to_return;
    }

    return result_dates * (-1);
  }

  return total_distance_b - total_distance_a;
}

void calculate_top_drivers_by_average_score(STATS stats, CATALOG catalog) {
  GList *top_drivers_by_average_score =
      g_hash_table_get_values(get_catalog_drivers(catalog));

  stats->top_drivers_by_average_score =
      g_list_sort(top_drivers_by_average_score,
                  (GCompareFunc)compare_drivers_by_average_score);
}

gint compare_drivers_by_average_score(gconstpointer a, gconstpointer b) {
  DRIVER driver_a = (DRIVER)a;
  DRIVER driver_b = (DRIVER)b;

  double a_total_rating = get_driver_total_rating(driver_a);
  int a_number_of_rides = get_driver_number_of_rides(driver_a);
  double a_score = (double)(a_total_rating / a_number_of_rides);

  double b_total_rating = get_driver_total_rating(driver_b);
  int b_number_of_rides = get_driver_number_of_rides(driver_b);
  double b_score = (double)(b_total_rating / b_number_of_rides);

  if (a_score == b_score) {
    struct date most_recent_ride_a = get_driver_latest_ride(driver_a);
    struct date most_recent_ride_b = get_driver_latest_ride(driver_b);

    int result_dates = compare_dates(most_recent_ride_a, most_recent_ride_b);

    if (result_dates == 0) {
      char *driver_id_a = get_driver_id(driver_a);
      char *driver_id_b = get_driver_id(driver_b);

      int to_return = strcmp(driver_id_a, driver_id_b);

      free(driver_id_a);
      free(driver_id_b);

      return to_return;
    }

    return result_dates * (-1);
  }

  return a_score > b_score ? -1 : 1;
}

void free_stats(STATS stats) {
  g_list_free(stats->top_users_by_total_distance);
  g_list_free(stats->top_drivers_by_average_score);

  free(stats);
}
