#ifndef STATS_H
#define STATS_H

#include <glib.h>

#include "catalog.h"
#include "utils.h"

typedef struct stats *STATS;

typedef struct user_stats *USER_STATS;

typedef struct driver_stats *DRIVER_STATS;

typedef struct ride_stats *RIDE_STATS;

typedef struct city_driver_stats *CITY_DRIVER_STATS;

typedef struct city *CITY_STATS;

typedef struct ride_gender_stats *RIDE_GENDER_STATS;

typedef struct ride *RIDE;  // To not cause conflicts

STATS create_stats(void);

CITY_DRIVER_STATS create_city_driver_stats(char *id, double total_rating,
                                           int total_rides, double ride_price);

CITY_STATS create_city_stats(char *city);

void update_city_driver_stats(CITY_DRIVER_STATS city_driver_stats,
                              double rating, double spent);

GList *get_top_drivers_by_average_score(STATS stats);

GList *get_top_users_by_total_distance(STATS stats);

CITY_STATS get_city_stats(STATS stats, char *city);

GTree *get_city_stats_tree(STATS stats, char *city);

GPtrArray *get_city_stats_array(STATS stats, char *city);

double get_city_driver_stats_total_rating(CITY_DRIVER_STATS city_driver_stats);

int get_city_driver_stats_total_rides(CITY_DRIVER_STATS city_driver_stats);

char *get_city_driver_stats_id(CITY_DRIVER_STATS city_driver_stats);

double get_city_driver_stats_total_spent(CITY_DRIVER_STATS city_driver_stats);

GHashTable *get_rides_by_date(STATS stats);

void set_city_drivers_array(STATS stats, char *city, GPtrArray *drivers_array);

GArray *get_male_rides_by_age(STATS stats);

GArray *get_female_rides_by_age(STATS stats);

void update_user_stats(CATALOG catalog, char *username, int distance,
                       double rating, double price, double tip, int date);

void update_driver_stats(CATALOG catalog, char *driver_id, double rating,
                         double price, double tip, int date);

void upsert_city_driver_stats(STATS stats, char *city, char *driver_id,
                              double driver_score, double ride_price);

void update_genders_rides_by_age(CATALOG catalog, STATS stats, char *ride_id,
                                 char *driver_id, char *username);

char *get_ride_gender_stats_id(RIDE_GENDER_STATS ride);

int get_ride_gender_stats_driver_account_creation(RIDE_GENDER_STATS ride);

int get_ride_gender_stats_user_account_creation(RIDE_GENDER_STATS ride);

void calculate_rides_by_age(GArray *rides_by_age);

gint compare_rides_by_age(gconstpointer a, gconstpointer b);

void calculate_top_users_by_total_distance(STATS stats, CATALOG catalog);

gint compare_users_by_total_distance(gconstpointer a, gconstpointer b);

void calculate_top_drivers_by_average_score(STATS stats, CATALOG catalog);

gint compare_drivers_by_average_score(gconstpointer a, gconstpointer b);

gint compare_city_driver_stats_by_id(gconstpointer a, gconstpointer b);

gint compare_driver_stats_by_rating(gconstpointer a, gconstpointer b);

void free_city_driver_stats(CITY_DRIVER_STATS city_driver_stats);

void insert_ride_by_date(RIDE ride, STATS stats);

void free_stats(STATS stats);

#endif
