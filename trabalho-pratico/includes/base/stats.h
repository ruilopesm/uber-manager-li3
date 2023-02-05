#ifndef STATS_H
#define STATS_H

#include <glib.h>

#include "catalogs/join_catalog.h"

typedef struct stats *STATS;

typedef struct user_stats *USER_STATS;

typedef struct driver_stats *DRIVER_STATS;

typedef struct ride_stats *RIDE_STATS;

typedef struct city_driver_stats *CITY_DRIVER_STATS;

typedef struct city_stats *CITY_STATS;

typedef struct ride_gender_stats *RIDE_GENDER_STATS;

typedef struct rides_of_the_day *RIDES_OF_THE_DAY;

typedef struct join_catalog *JOIN_CATALOG;  // Forward declaration

typedef struct user *USER;  // Forward declaration

typedef struct driver *DRIVER;  // Forward declaration

typedef struct ride *RIDE;  // Forward declaration

STATS create_stats(void);

CITY_DRIVER_STATS create_city_driver_stats(gpointer id, double total_rating,
                                           int total_rides, double ride_price);

CITY_STATS create_city_stats();

double get_city_stats_total_spent(CITY_STATS city_stats);

int get_city_stats_total_rides(CITY_STATS city_stats);

void update_city_driver_stats(CITY_DRIVER_STATS city_driver_stats,
                              double rating, double spent);

GArray *get_top_drivers_by_average_score(STATS stats);

GArray *get_top_users_by_total_distance(STATS stats);

CITY_STATS get_city_stats(STATS stats, int city);

GHashTable *get_city_stats_hash(STATS stats, int city);

GPtrArray *get_city_stats_array(STATS stats, int city);

double get_city_driver_stats_total_rating(CITY_DRIVER_STATS city_driver_stats);

int get_city_driver_stats_total_rides(CITY_DRIVER_STATS city_driver_stats);

int get_city_driver_stats_id(CITY_DRIVER_STATS city_driver_stats);

double get_city_driver_stats_total_spent(CITY_DRIVER_STATS city_driver_stats);

GHashTable *get_rides_by_date(STATS stats);

void set_city_drivers_array(STATS stats, int city, GPtrArray *drivers_array);

GArray *get_male_rides_by_age(STATS stats);

GArray *get_female_rides_by_age(STATS stats);

void insert_user_into_stats(STATS stats, USER user);

void insert_driver_into_stats(STATS stats, DRIVER driver);

void insert_ride_into_stats(STATS stats, JOIN_CATALOG catalog, RIDE ride,
                            gpointer id, gpointer driver, gpointer user,
                            int city, double score_driver, double price);

void upsert_city_driver_stats(STATS stats, int city, gpointer driver_id,
                              double driver_score, double ride_price);

void update_genders_rides_by_age(JOIN_CATALOG catalog, STATS stats,
                                 gpointer ride_id, gpointer driver_id,
                                 gpointer username);

RIDE_GENDER_STATS create_ride_gender_stats(gpointer ride_id, gpointer driver_id,
                                           gpointer username,
                                           int driver_account_creation,
                                           int user_account_creation);

int get_ride_gender_stats_id(RIDE_GENDER_STATS ride);

int get_ride_gender_stats_driver_id(RIDE_GENDER_STATS ride);

int get_ride_gender_stats_username(RIDE_GENDER_STATS ride);

int get_ride_gender_stats_driver_account_creation(RIDE_GENDER_STATS ride);

int get_ride_gender_stats_user_account_creation(RIDE_GENDER_STATS ride);

gint compare_rides_by_age(gconstpointer a, gconstpointer b);

gint compare_users_by_total_distance(gconstpointer a, gconstpointer b,
                                     gpointer users_reverse_gpointer);

void add_driver_to_array(gpointer key, gpointer value, gpointer data);

gint compare_drivers_by_average_score(gconstpointer a, gconstpointer b);

gint compare_city_driver_stats_by_id(gconstpointer a, gconstpointer b);

gint compare_driver_stats_by_average_score(gconstpointer a, gconstpointer b);

void insert_ride_by_date(RIDE ride, STATS stats);

GArray *get_ride_of_the_day_array(RIDES_OF_THE_DAY rides_of_the_day);

double get_ride_of_the_day_number_of_rides(RIDES_OF_THE_DAY rides_of_the_day);

void set_ride_of_the_day_number_of_rides(RIDES_OF_THE_DAY rides_of_the_day,
                                         int ride_number);

double get_ride_of_the_day_avg_price(RIDES_OF_THE_DAY rides_of_the_day);

void set_ride_of_the_day_avg_price(RIDES_OF_THE_DAY rides_of_the_day,
                                   double price);

void free_rides_by_age(gpointer ride_gender_stats_gpointer);

void free_city_stats(gpointer city_stats_gpointer);

void free_rides_by_date(gpointer rides_of_the_day_gpointer);

void free_stats(STATS stats);

#endif
