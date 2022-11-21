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
};

struct user_stats {
  char *user_id;
  int number_of_rides;
  int total_rating;
  int total_spent;
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

STATS create_stats(void) {
  STATS new_stats = malloc(sizeof(struct stats));

  new_stats->users_stats = g_hash_table_new_full(
      g_str_hash, g_str_equal, free, (GDestroyNotify)free_user_stats);
  new_stats->drivers_stats = g_hash_table_new_full(
      g_str_hash, g_str_equal, free, (GDestroyNotify)free_driver_stats);
  return new_stats;
}

void free_stats(STATS stats) {
  g_hash_table_destroy(stats->users_stats);
  g_hash_table_destroy(stats->drivers_stats);

  free(stats);
}

void free_user_stats(struct user_stats *user) {
  free(user->user_id);
  free(user);
}

void free_driver_stats(struct driver_stats *driver) {
  free(driver->driver_id);
  free(driver);
}
