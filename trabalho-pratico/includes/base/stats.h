#ifndef STATS_H
#define STATS_H

#include <glib.h>

#include "catalogs/joint_catalog.h"

/**
 * @struct stats
 *
 * @brief Struct that contains all the main data structures of the program
 */
typedef struct stats *STATS;

typedef struct joint_catalog *JOINT_CATALOG;  // Forward declaration

typedef struct user *USER;  // Forward declaration

typedef struct driver *DRIVER;  // Forward declaration

typedef struct ride *RIDE;  // Forward declaration

/**
 * @struct city_driver_stats - Struct that contains the stats of a driver in a
 * city
 */
typedef struct city_driver_stats *CITY_DRIVER_STATS;

/**
 * @struct city_stats - Struct that contains the stats of a city
 */
typedef struct city_stats *CITY_STATS;

/**
 * @struct rides_by_date - Struct that contains the stats of a day
 */
typedef struct ride_gender_stats *RIDE_GENDER_STATS;

/**
 * @struct rides_by_date - Struct that contains the stats of a day
 */
typedef struct rides_of_the_day *RIDES_OF_THE_DAY;

/**
 * @brief Function that creates a new struct stats
 *
 * @return new_stats - The new stats of type `STATS`
 */
STATS create_stats(void);

/**
 * @brief Function creates a new struct city_driver_stats
 *
 * @param id - City driver id of type `gpointer`
 * @param total_rating - City driver total rating of type `double`
 * @param total_rides - City driver total rides of type `int`
 * @param total_spent - City driver total spent of type `double`
 *
 * @return new_city_driver_stats - The new city driver stats of type
 * `CITY_DRIVER_STATS`
 */
CITY_DRIVER_STATS create_city_driver_stats(gpointer id, double total_rating,
                                           int total_rides, double ride_price);

/**
 * @brief Function that creates a new struct city_stats
 *
 * @return new_city_stats - The new city stats of type `CITY_STATS`
 */
CITY_STATS create_city_stats();

/**
 * @brief Function that gets the total spent of a city_stats struct
 *
 * @param city_stats - The city stats of type `CITY_STATS`
 *
 * @return city_stats->total_spent - The total spent of type `double`
 */
double get_city_stats_total_spent(CITY_STATS city_stats);

/**
 * @brief Function that gets the total rides of a city_stats struct
 *
 * @param city_stats - The city stats of type `CITY_STATS`
 *
 * @return city_stats->total_rides - The total rides of type `int`
 */
int get_city_stats_total_rides(CITY_STATS city_stats);

/**
 * @brief Function that updates the city drivers stats
 *
 * @param city_driver_stats - The city driver stats of type `CITY_DRIVER_STATS`
 * @param rating - The rating of type `double`
 * @param ride_price - The ride price of type `double`
 */
void update_city_driver_stats(CITY_DRIVER_STATS city_driver_stats,
                              double rating, double spent);

/**
 * @brief Function that gets the top drivers by average score from the stats
 * struct
 *
 * @param stats - The stats of type `STATS`
 *
 * @return stats->top_drivers_by_average_score - The top drivers by average
 * score of type `GArray`
 */
GArray *get_top_drivers_by_average_score(STATS stats);

/**
 * @brief Function that gets the top users by total distance from the stats
 * struct
 *
 * @param stats - The stats of type `STATS`
 *
 * @return stats->top_users_by_total_distance - The top users by total distance
 * of type `GArray`
 */
GArray *get_top_users_by_total_distance(STATS stats);

/**
 * @brief Function that gets the city stats from the stats struct
 *
 * @param stats - The stats of type `STATS`
 * @param city - The city code of type `int`
 *
 * @return city_stats - The city stats of type `CITY_STATS`
 */
CITY_STATS get_city_stats(STATS stats, int city);

/**
 * @brief Function that gets the city drivers hash from the city stats struct
 *
 * @param stats - The stats of type `STATS`
 * @param city - The city code of type `int`
 *
 * @return city_stats->drivers_hash - The city drivers hash of type `GHashTable`
 */
GHashTable *get_city_stats_hash(STATS stats, int city);

/**
 * @brief Function that gets the stats array from the city stats struct
 *
 * @param stats - The stats of type `STATS`
 * @param city - The city code of type `int`
 *
 * @return city_stats->drivers_array - The city drivers array of type
 * `GPtrArray`
 */
GPtrArray *get_city_stats_array(STATS stats, int city);

/**
 * @brief Function that gets the total rating of a city driver from the city
 * stats struct
 *
 * @param stats - The stats of type `STATS`
 *
 * @return city_driver_stats->total_rating
 */
double get_city_driver_stats_total_rating(CITY_DRIVER_STATS city_driver_stats);

/**
 * @brief Returns the total number of rides of a driver in a city
 *
 * @param city_driver_stats - The city driver stats of type CITY_DRIVER_STATS
 *
 * @return city_driver_stats->total_rides - The total number of rides of a
 * driver in a city of type `int`
 */
int get_city_driver_stats_total_rides(CITY_DRIVER_STATS city_driver_stats);

/**
 * @brief Returns the id of a city driver stats
 *
 * @param city_driver_stats The city driver stats
 *
 * @return city_driver_stats->id - The id of the city driver stats of type `int`
 */
int get_city_driver_stats_id(CITY_DRIVER_STATS city_driver_stats);

/**
 * @brief Returns the total spent of a driver in a city
 *
 * @param city_driver_stats - The city driver stats of type CITY_DRIVER_STATS
 *
 * @return city_driver_stats->total_spent - The total spent of a driver in a
 * city of type `double`
 */
double get_city_driver_stats_total_spent(CITY_DRIVER_STATS city_driver_stats);

/**
 * @brief Returns all the rides in a given date
 *
 * @param stats - The stats of type `STATS`
 *
 * @return stats->rides_by_date - All the rides by date of type `GHashTable`
 */
GHashTable *get_rides_by_date(STATS stats);

/**
 * @brief Sets the city drivers array in the stats struct
 *
 * @param stats - The stats of type `STATS`
 * @param city - The city code of type `int`
 * @param drivers_array - The city drivers array of type `GPtrArray`
 */
void set_city_drivers_array(STATS stats, int city, GPtrArray *drivers_array);

/**
 * @brief Gets all the males rides by age
 *
 * @param stats - The stats of type `STATS`
 *
 * @return stats->male_rides_by_age - Array of type `GArray`
 */
GArray *get_male_rides_by_age(STATS stats);

/**
 * @brief Gets all the females rides by age
 *
 * @param stats - The stats of type `STATS`
 *
 * @return stats->female_rides_by_age - Array of type `GArray`
 */
GArray *get_female_rides_by_age(STATS stats);

/**
 * @brief Inserts a user into the stats struct
 *
 * @param stats - The stats of type `STATS`
 * @param user - The user of type `USER`
 */
void insert_user_into_stats(STATS stats, USER user);

/**
 * @brief Inserts a driver into the stats struct
 *
 * @param stats - The stats of type `STATS`
 * @param driver - The driver of type `DRIVER`
 */
void insert_driver_into_stats(STATS stats, DRIVER driver);

/**
 * @brief Inserts a ride into the stats struct
 *
 * @param stats - The stats of type `STATS`
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param ride - The ride of type `RIDE`
 * @param id - The id of type `gpointer`
 * @param driver - The driver of type `gpointer`
 * @param user - The user of type `gpointer`
 * @param city - The city code of type `int`
 * @param score_driver - The score driver of type `double`
 * @param price - The price of type `double`
 */
void insert_ride_into_stats(STATS stats, JOINT_CATALOG catalog, RIDE ride,
                            gpointer id, gpointer driver, gpointer user,
                            int city, double score_driver, double price);

/**
 * @brief Function that updates/inserts the __city_drivers_stats__ struct
 *
 * @param stats - The stats of type `STATS`
 * @param city - The city code of type `int`
 * @param driver_id - The driver id of type `gpointer`
 * @param driver_score - The driver score of type `double`
 * @param ride_price - The ride price of type `double`
 */
void upsert_city_driver_stats(STATS stats, int city, gpointer driver_id,
                              double driver_score, double ride_price);

/**
 * @brief Function that update the genders in the __rides_by_age__ struct
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param ride_id - The ride id of type `gpointer`
 * @param driver_id - The driver id of type `gpointer`
 * @param username - The username of type `gpointer`
 */
void update_genders_rides_by_age(JOINT_CATALOG catalog, STATS stats,
                                 gpointer ride_id, gpointer driver_id,
                                 gpointer username);

/**
 * @brief Function that creates the __ride_gender_stats__ struct
 *
 * @param ride_id - The ride id of type `gpointer`
 * @param driver_id - The driver id of type `gpointer`
 * @param username - The username of type `gpointer`
 *
 * @return new_ride_gender_stats - struct of type `RIDE_GENDER_STATS`
 */
RIDE_GENDER_STATS create_ride_gender_stats(gpointer ride_id, gpointer driver_id,
                                           gpointer username,
                                           int driver_account_creation,
                                           int user_account_creation);

/**
 * @brief Function that gets the __ride_gender_stats__ struct id
 *
 * @param ride - The ride_gender stats of type `RIDE_GENDER_STATS`
 *
 * @return ride->id - The id of type `int`
 */
int get_ride_gender_stats_id(RIDE_GENDER_STATS ride);

/**
 * @brief Function that gets the driver id from a __ride_gender_stats__ struct
 *
 * @param ride - The ride_gender stats of type `RIDE_GENDER_STATS`
 *
 * @return ride->driver_id - The driver id of type `int`
 */
int get_ride_gender_stats_driver_id(RIDE_GENDER_STATS ride);

/**
 * @brief Function that gets the username from a __ride_gender_stats__ struct
 *
 * @param ride - The ride_gender stats of type `RIDE_GENDER_STATS`
 *
 * @return ride->username - The username of type `int`
 */
int get_ride_gender_stats_username(RIDE_GENDER_STATS ride);

/**
 * @brief Function that gets the driver account creation date in the
 * __ride_gender_stats__ struct
 *
 * @param ride - The ride_gender stats of type `RIDE_GENDER_STATS`
 *
 * @return ride->driver_account_creation - The driver account creation date of
 * type `int`
 */
int get_ride_gender_stats_driver_account_creation(RIDE_GENDER_STATS ride);

/**
 * @brief Function that gets the user account creation date in the
 * __ride_gender_stats__ struct
 *
 * @param ride - The ride_gender stats of type `RIDE_GENDER_STATS`
 *
 * @return ride->user_account_creation - The driver account creation date of
 * type `int`
 */
int get_ride_gender_stats_user_account_creation(RIDE_GENDER_STATS ride);

/**
 * @brief Function that compares rides by age
 *
 * @param a - The first ride of type `gconstpointer`
 * @param b - The second ride of type `gconstpointer`
 *
 * @return 1 if a > b, -1 if a < b, 0 if a == b
 */
gint compare_rides_by_age(gconstpointer a, gconstpointer b);

/**
 * @brief Functin that compares user by total distance
 *
 * @param a - The first user of type `gconstpointer`
 * @param b - The second user of type `gconstpointer`
 * @param users_reverse_gpointer - The users_reverse of type `gpointer`
 *
 * @return 1 if a > b, -1 if a < b, 0 if a == b
 */
gint compare_users_by_total_distance(gconstpointer a, gconstpointer b,
                                     gpointer users_reverse_gpointer);

/**
 * @brief Function that adds a driver to the array
 *
 * @param key - The key of type `gpointer`
 * @param value - The value of type `gpointer`
 * @param data - The data of type `gpointer`
 */
void add_driver_to_array(gpointer key, gpointer value, gpointer data);

/**
 * @brief Function that comapres drivers by average score
 *
 * @param a - The first driver of type `gconstpointer`
 * @param b - The second driver of type `gconstpointer`
 *
 * @return 1 if a > b, -1 if a < b, 0 if a == b
 */
gint compare_drivers_by_average_score(gconstpointer a, gconstpointer b);

/**
 * @brief Function that compares city drivers stats by id
 *
 * @param a - The first city driver stats of type `gconstpointer`
 * @param b - The second city driver stats of type `gconstpointer`
 *
 * @return 1 if a > b, -1 if a < b, 0 if a == b
 */
gint compare_city_driver_stats_by_id(gconstpointer a, gconstpointer b);

/**
 * @brief Function that compares city drivers stats by average score
 *
 * @param a - The first city driver stats of type `gconstpointer`
 * @param b - The second city driver stats of type `gconstpointer`
 *
 * @return 1 if a > b, -1 if a < b, 0 if a == b
 */
gint compare_driver_stats_by_average_score(gconstpointer a, gconstpointer b);

/**
 * @brief Function that inserts a ride by date
 *
 * @param ride - The ride of type `RIDE`
 * @param stats - The stats of type `STATS`
 */
void insert_ride_by_date(RIDE ride, STATS stats);

/**
 * @brief Function gets the __ride_of_the_day__ struct array
 *
 * @param rides_of_the_day - The rides of the day of type `RIDES_OF_THE_DAY`
 *
 * @return rides_of_the_day->array - The rides of type `GArray`
 */
GArray *get_ride_of_the_day_array(RIDES_OF_THE_DAY rides_of_the_day);

/**
 * @brief Function that gets the __ride_of_the_day__ struct number of rides
 *
 * @param rides_of_the_day - The rides of the day of type `RIDES_OF_THE_DAY`
 *
 * @return rides_of_the_day->number_of_rides - The number of rides of type
 * `double`
 */
double get_ride_of_the_day_number_of_rides(RIDES_OF_THE_DAY rides_of_the_day);

/**
 * @brief Function that gets the __ride_of_the_day__ struct number of rides
 *
 * @param rides_of_the_day - The rides of the day of type `RIDES_OF_THE_DAY`
 * @param ride_number - The number of rides of type `int`
 */
void set_ride_of_the_day_number_of_rides(RIDES_OF_THE_DAY rides_of_the_day,
                                         int ride_number);

/**
 * @brief Function that gets the __ride_of_the_day__ struct average price
 *
 * @param rides_of_the_day - The rides of the day of type `RIDES_OF_THE_DAY`
 * @param price - The price of type `double`
 *
 * @return rides_of_the_day->avg_price - The average price of type `double`
 */
double get_ride_of_the_day_avg_price(RIDES_OF_THE_DAY rides_of_the_day);

/**
 * @brief Function that sets the __ride_of_the_day__ struct average price
 *
 * @param rides_of_the_day - The rides of the day of type `RIDES_OF_THE_DAY`
 * @param price - The price of type `double`
 */
void set_ride_of_the_day_avg_price(RIDES_OF_THE_DAY rides_of_the_day,
                                   double price);

/**
 * @brief Function that gets the average price of the __rides_by_date__ hash
 * table with the given uper and lowe limits
 *
 * @param rides_by_date - The rides by date of type `GHashTable`
 * @param lower_limit - The lower limit of type `int`
 * @param upper_limit - The upper limit of type `int`
 *
 * @return average_price - The average price of type `double`
 */
double calculate_average_price(GHashTable *rides_by_date, int lower_limit,
                               int upper_limit);

/**
 * @brief Function that gets the average distance of the __rides_by_date__ hash
 * table with the given uper and lowe limits
 *
 * @param rides_by_date - The rides by date of type `GHashTable`
 * @param lower_limit - The lower limit of type `int`
 * @param upper_limit - The upper limit of type `int`
 *
 * @return average_distance - The average distance of type `double`
 */
double calculate_average_distance(GHashTable *rides_by_date, int lower_limit,
                                  int upper_limit, char city_code);

/**
 * @brief Function that frees the __rides_by_age__ struct
 *
 * @param ride_gender_stats_gpointer - Object to be freed of type `gpointer`
 */
void free_rides_by_age(gpointer ride_gender_stats_gpointer);

/**
 * @brief Function that frees the __city_stats__ struct
 *
 * @param city_stats_gpointer - Object to be freed of type `gpointer`
 */
void free_city_stats(gpointer city_stats_gpointer);

/**
 * @brief Function that frees the __rides_of_the_day__ struct
 *
 * @param rides_of_the_day_gpointer - Object to be freed of type `gpointer`
 */
void free_rides_by_date(gpointer rides_of_the_day_gpointer);

/**
 * @brief Function that frees the __stats__ struct
 *
 * @param stats - The stats of type `STATS`
 */
void free_stats(STATS stats);

#endif
