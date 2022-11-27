#include "stats.h"

#include <glib.h>
#include <stdio.h>

#include "catalog.h"
#include "common.h"
#include "drivers.h"
#include "rides.h"
#include "users.h"

struct stats {
  GHashTable *users_stats;
  GHashTable *drivers_stats;
  GHashTable *rides_stats;
  GList *top_drivers_by_average_score;
  GList *top_users_by_total_distance;
};

struct user_stats {
  char *username;
  int number_of_rides;
  double total_rating;
  double total_spent;
  int total_distance;
  struct date latest_ride;
};

struct driver_stats {
  char *driver_id;
  int number_of_rides;
  double total_rating;
  double total_earned;
  struct date latest_ride;
};

struct ride_stats {
  char *ride_id;
  double price;
  char *city;
};

STATS create_stats(void) {
  STATS new_stats = malloc(sizeof(struct stats));

  new_stats->users_stats = g_hash_table_new_full(
      g_str_hash, g_str_equal, NULL, (GDestroyNotify)free_user_stats);
  new_stats->drivers_stats = g_hash_table_new_full(
      g_str_hash, g_str_equal, NULL, (GDestroyNotify)free_driver_stats);
  new_stats->rides_stats = g_hash_table_new_full(
      g_str_hash, g_str_equal, NULL, (GDestroyNotify)free_ride_stats);
  new_stats->top_drivers_by_average_score = NULL;
  new_stats->top_users_by_total_distance = NULL;

  return new_stats;
}

GHashTable *get_users_stats(STATS stats) { return stats->users_stats; }

GHashTable *get_drivers_stats(STATS stats) { return stats->drivers_stats; }

GHashTable *get_rides_stats(STATS stats) { return stats->rides_stats; }

GList *get_top_drivers_by_average_score(STATS stats) {
  return stats->top_drivers_by_average_score;
}

GList *get_top_users_by_total_distance(STATS stats) {
  return stats->top_users_by_total_distance;
}

USER_STATS create_user_stats(char *username, int number_of_rides,
                             double total_rating, double total_spent,
                             int total_distance, struct date latest_ride) {
  USER_STATS user_stats = malloc(sizeof(struct user_stats));

  user_stats->username = strdup(username);
  user_stats->number_of_rides = number_of_rides;
  user_stats->total_rating = total_rating;
  user_stats->total_spent = total_spent;
  user_stats->total_distance = total_distance;
  user_stats->latest_ride = latest_ride;

  return user_stats;
}

DRIVER_STATS create_driver_stats(char *driver_id, int number_of_rides,
                                 double total_rating, double total_earned,
                                 struct date latest_ride) {
  DRIVER_STATS driver_stats = malloc(sizeof(struct driver_stats));

  driver_stats->driver_id = strdup(driver_id);
  driver_stats->number_of_rides = number_of_rides;
  driver_stats->total_rating = total_rating;
  driver_stats->total_earned = total_earned;
  driver_stats->latest_ride = latest_ride;

  return driver_stats;
}

char *get_user_stats_username(USER_STATS user_stats) {
  return user_stats->username;
}

int get_user_stats_total_distance(USER_STATS user_stats) {
  return user_stats->total_distance;
}

int get_user_stats_number_of_rides(USER_STATS user_stats) {
  return user_stats->number_of_rides;
}

double get_user_stats_total_rating(USER_STATS user_stats) {
  return user_stats->total_rating;
}

double get_user_stats_total_spent(USER_STATS user_stats) {
  return user_stats->total_spent;
}

int get_driver_status_number_of_rides(DRIVER_STATS driver_stats) {
  return driver_stats->number_of_rides;
}

double get_driver_status_total_rating(DRIVER_STATS driver_stats) {
  return driver_stats->total_rating;
}

double get_driver_status_total_earned(DRIVER_STATS driver_stats) {
  return driver_stats->total_earned;
}

char *get_driver_stats_driver_id(DRIVER_STATS driver) {
  return strdup(driver->driver_id);
}

double get_driver_stats_average_score(DRIVER_STATS driver_stats) {
  double total_rating = driver_stats->total_rating;
  double total_rides = driver_stats->number_of_rides;

  return total_rating / total_rides;
}

void upsert_user_stats(STATS stats, char *username, char *ride_id,
                       double rating, int distance, double tip,
                       struct date date) {
  USER_STATS user_stats = g_hash_table_lookup(stats->users_stats, username);
  RIDE_STATS ride_stats = g_hash_table_lookup(stats->rides_stats, ride_id);
  double price = ride_stats->price;

  if (user_stats == NULL) {
    USER_STATS new_user_stats =
        create_user_stats(username, 1, rating, price + tip, distance, date);
    g_hash_table_insert(stats->users_stats, username, new_user_stats);
  } else {
    user_stats->number_of_rides++;
    user_stats->total_rating += rating;
    user_stats->total_spent += (price + tip);
    user_stats->total_distance += distance;

    if (compare_dates(date, user_stats->latest_ride) > 0) {
      user_stats->latest_ride = date;
    }
  }
}

void upsert_driver_stats(STATS stats, char *driver_id, char *ride_id,
                         double rating, double tip, struct date date) {
  DRIVER_STATS driver_stats =
      g_hash_table_lookup(stats->drivers_stats, driver_id);
  RIDE_STATS ride_stats = g_hash_table_lookup(stats->rides_stats, ride_id);
  double price = ride_stats->price;

  if (driver_stats == NULL) {
    DRIVER_STATS new_driver_stats =
        create_driver_stats(driver_id, 1, rating, price + tip, date);
    g_hash_table_insert(stats->drivers_stats, driver_id, new_driver_stats);
  } else {
    driver_stats->number_of_rides++;
    driver_stats->total_rating += rating;
    driver_stats->total_earned += (price + tip);

    if (compare_dates(date, driver_stats->latest_ride) > 0) {
      driver_stats->latest_ride = date;
    }
  }
}

RIDE_STATS create_ride_stats(STATS stats, char *ride_id, double price,
                             char *city) {
  RIDE_STATS ride_stats = malloc(sizeof(struct ride_stats));

  ride_stats->ride_id = strdup(ride_id);
  ride_stats->price = price;
  ride_stats->city = strdup(city);

  return ride_stats;
}

char *get_ride_stats_city(RIDE_STATS ride_stats) {
  return strdup(ride_stats->city);
}

double get_ride_stats_price(RIDE_STATS ride_stats) { return ride_stats->price; }

void insert_ride_stats(STATS stats, char *ride_id, int distance,
                       enum car_class car_class, char *city) {
  double price = calculate_ride_price(distance, car_class);

  RIDE_STATS ride_stats = create_ride_stats(stats, ride_id, price, city);

  g_hash_table_insert(stats->rides_stats, ride_id, ride_stats);
}

void calculate_top_users_by_total_distance(STATS stats) {
  GList *top_users_by_total_distance =
      g_hash_table_get_values(stats->users_stats);
  stats->top_users_by_total_distance = g_list_sort(
      top_users_by_total_distance, compare_users_stats_by_total_distance);
}

gint compare_users_stats_by_total_distance(gconstpointer a, gconstpointer b) {
  USER_STATS user_stats_a = (USER_STATS)a;
  USER_STATS user_stats_b = (USER_STATS)b;

  int total_distance_a = user_stats_a->total_distance;
  int total_distance_b = user_stats_b->total_distance;

  if (total_distance_a == total_distance_b) {
    struct date most_recent_ride_a = user_stats_a->latest_ride;
    struct date most_recent_ride_b = user_stats_b->latest_ride;

    int result_dates = compare_dates(most_recent_ride_a, most_recent_ride_b);

    if (result_dates == 0) {
      return strcmp(user_stats_a->username, user_stats_b->username);
    }

    return result_dates * (-1);
  }

  return user_stats_b->total_distance - user_stats_a->total_distance;
}

void calculate_top_drivers_by_average_score(STATS stats) {
  GList *top_drivers_by_average_score =
      g_hash_table_get_values(stats->drivers_stats);

  stats->top_drivers_by_average_score =
      g_list_sort(top_drivers_by_average_score,
                  (GCompareFunc)compare_drivers_by_average_score);
}

gint compare_drivers_by_average_score(gconstpointer a, gconstpointer b) {
  DRIVER_STATS driver_a = (DRIVER_STATS)a;
  DRIVER_STATS driver_b = (DRIVER_STATS)b;

  double a_total_rating = driver_a->total_rating;
  int a_total_rides = driver_a->number_of_rides;
  double a_score = a_total_rating / a_total_rides;

  double b_total_rating = driver_b->total_rating;
  int b_total_rides = driver_b->number_of_rides;
  double b_score = b_total_rating / b_total_rides;

  if (a_score > b_score) {
    return -1;
  } else if ((a_score == b_score) &&
             is_date_newer(driver_a->latest_ride, driver_b->latest_ride)) {
    return -1;
  } else if ((a_score == b_score) &&
             is_date_equal(driver_a->latest_ride, driver_b->latest_ride) &&
             is_id_smaller(driver_a->driver_id, driver_b->driver_id)) {
    return -1;
  } else {
    return 1;
  }
}

void free_stats(STATS stats) {
  g_hash_table_destroy(stats->users_stats);
  g_hash_table_destroy(stats->drivers_stats);

  free(stats);
}

void free_user_stats(USER_STATS user) { free(user); }

void free_driver_stats(DRIVER_STATS driver) { free(driver); }

void free_ride_stats(RIDE_STATS ride_stats) { free(ride_stats); }
