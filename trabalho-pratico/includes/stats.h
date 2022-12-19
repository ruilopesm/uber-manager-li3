#ifndef STATS_H
#define STATS_H

#include <glib.h>

#include "catalog.h"
#include "common.h"

typedef struct stats *STATS;

typedef struct user_stats *USER_STATS;

typedef struct driver_stats *DRIVER_STATS;

typedef struct ride_stats *RIDE_STATS;

typedef struct city_driver_stats *CITY_DRIVER_STATS;

typedef struct ride *RIDE;  // To not cause conflicts

STATS create_stats(void);

CITY_DRIVER_STATS create_city_driver_stats(char *id, double total_rating,
                                           int total_rides);

void update_city_driver_stats(CITY_DRIVER_STATS city_driver_stats,
                              double rating);

GList *get_top_drivers_by_average_score(STATS stats);

GList *get_top_users_by_total_distance(STATS stats);

GTree *get_city_driver_stats(STATS stats, char *city);

double get_city_driver_stats_total_rating(CITY_DRIVER_STATS city_driver_stats);

int get_city_driver_stats_total_rides(CITY_DRIVER_STATS city_driver_stats);

char *get_city_driver_stats_id(CITY_DRIVER_STATS city_driver_stats);

GArray *get_rides_by_date(STATS stats);

void update_user_stats(CATALOG catalog, char *username, int distance,
                       double rating, double price, double tip,
                       struct date date);

void update_driver_stats(CATALOG catalog, char *driver_id, double rating,
                         double price, double tip, struct date date);

void upsert_city_driver_stats(STATS stats, char *city, char *driver_id,
                              double driver_score);

void calculate_top_users_by_total_distance(STATS stats, CATALOG catalog);

gint compare_users_by_total_distance(gconstpointer a, gconstpointer b);

void calculate_top_drivers_by_average_score(STATS stats, CATALOG catalog);

gint compare_drivers_by_average_score(gconstpointer a, gconstpointer b);

gint compare_city_driver_stats_by_id(gconstpointer a, gconstpointer b);

gint compare_driver_stats_by_rating(gconstpointer a, gconstpointer b);

void free_city_driver_stats(CITY_DRIVER_STATS city_driver_stats);

void insert_ride_by_date(RIDE ride, STATS stats);

struct date get_day_of_array(GArray *rides_by_date, int index);

int compare_dates_wrapper_array_date(gconstpointer array_constpointer,
                                     gconstpointer date_constpointer);

void free_stats(STATS stats);

#endif
