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
  GList *top_users_by_total_distance;
};

struct user_stats {
  char *username;
  int number_of_rides;
  double total_rating;
  double total_spent;
  int total_distance;
  struct date most_recent_ride;
};

struct driver_stats {
  char *driver_id;
  int number_of_rides;
  int total_rating;
  int total_earned;
  struct date most_recent_ride;
};

struct ride_stats {
  char *ride_id;
  double price;
};

STATS create_stats(void) {
  STATS new_stats = malloc(sizeof(struct stats));

  new_stats->users_stats = g_hash_table_new_full(
      g_str_hash, g_str_equal, free, (GDestroyNotify)free_user_stats);
  new_stats->drivers_stats = g_hash_table_new_full(
      g_str_hash, g_str_equal, free, (GDestroyNotify)free_driver_stats);

  new_stats->rides_stats = g_hash_table_new_full(
      g_str_hash, g_str_equal, free, (GDestroyNotify)free_ride_stats);
  new_stats->top_users_by_total_distance = NULL;

  return new_stats;
}

GList *get_top_users_by_total_distance(STATS stats) {
  return stats->top_users_by_total_distance;
}

USER_STATS create_user_stats(char *username, int number_of_rides,
                             int total_rating, int total_spent,
                             int total_distance, struct date most_recent_ride) {
  USER_STATS user_stats = malloc(sizeof(struct user_stats));

  user_stats->username = strdup(username);
  user_stats->number_of_rides = number_of_rides;
  user_stats->total_rating = total_rating;
  user_stats->total_spent = total_spent;
  user_stats->total_distance = total_distance;
  user_stats->most_recent_ride = most_recent_ride;

  return user_stats;
}

char *get_user_stats_username(USER_STATS user_stats) {
  return user_stats->username;
}

int get_user_stats_total_distance(USER_STATS user_stats) {
  return user_stats->total_distance;
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

    if (compare_dates(date, user_stats->most_recent_ride) > 0) {
      user_stats->most_recent_ride = date;
    }
  }
}

RIDE_STATS create_ride_stats(STATS stats, char *ride_id, double price) {
  RIDE_STATS ride_stats = malloc(sizeof(struct ride_stats));

  ride_stats->ride_id = strdup(ride_id);
  ride_stats->price = price;

  return ride_stats;
}

void insert_ride_stats(STATS stats, char *ride_id, int distance,
                       enum car_class car_class) {
  double price = calculate_ride_price(distance, car_class);

  RIDE_STATS ride_stats = create_ride_stats(stats, ride_id, price);

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
    struct date most_recent_ride_a = user_stats_a->most_recent_ride;
    struct date most_recent_ride_b = user_stats_b->most_recent_ride;

    int result_dates = compare_dates(most_recent_ride_a, most_recent_ride_b);

    if (result_dates == 0) {
      return strcmp(user_stats_a->username, user_stats_b->username);
    }

    return result_dates * (-1);
  }

  return user_stats_b->total_distance - user_stats_a->total_distance;
}

void free_stats(STATS stats) {
  g_hash_table_destroy(stats->users_stats);
  g_hash_table_destroy(stats->drivers_stats);

  free(stats);
}

void free_user_stats(USER_STATS user_stats) {
  free(user_stats->username);
  free(user_stats);
}

void free_driver_stats(DRIVER_STATS driver_stats) {
  free(driver_stats->driver_id);
  free(driver_stats);
}

void free_ride_stats(RIDE_STATS ride_stats) {
  free(ride_stats->ride_id);
  free(ride_stats);
}
