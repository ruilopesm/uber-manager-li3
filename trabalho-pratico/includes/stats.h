#ifndef STATS_H
#define STATS_H

#include <glib.h>

#include "common.h"

typedef struct stats *STATS;

typedef struct user_stats *USER_STATS;

typedef struct driver_stats *DRIVER_STATS;

typedef struct ride_stats *RIDE_STATS;

STATS create_stats(void);

GList *get_top_users_by_total_distance(STATS stats);

USER_STATS create_user_stats(char *username, int number_of_rides,
                             int total_rating, int total_spent,
                             int total_distance, struct date most_recent_ride);

char *get_user_stats_username(USER_STATS user_stats);

int get_user_stats_total_distance(USER_STATS user_stats);

void upsert_user_stats(STATS stats, char *username, char *ride_id,
                       double rating, int distance, double tip,
                       struct date date);

RIDE_STATS create_ride_stats(STATS stats, char *ride_id, double price);

void insert_ride_stats(STATS stats, char *ride_id, int distance,
                       enum car_class car_class);

void calculate_top_users_by_total_distance(STATS stats);

gint compare_users_stats_by_total_distance(gconstpointer a, gconstpointer b);

void free_stats(STATS stats);

void free_user_stats(USER_STATS user);

void free_driver_stats(DRIVER_STATS driver);

void free_ride_stats(RIDE_STATS ride_stats);

#endif
