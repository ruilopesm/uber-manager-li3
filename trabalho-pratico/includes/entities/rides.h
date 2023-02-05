#ifndef RIDES_H
#define RIDES_H

#include <glib.h>

#include "base/stats.h"
#include "utils/utils.h"

#define MAX_RIDE_TOKENS 10

typedef struct ride *RIDE;

/**
 * @brief Creates a new ride
 *
 * @return new_ride - The new ride of type `RIDE`
 */
RIDE create_ride();

/**
 * @brief Builds the ride with given parameters
 *
 * @param ride_params - The parameters of the ride of type `char **`
 * @param catalog - The program's catalog of type `void *` (CATALOG)
 * @param stats - The program's stats of type `STATS`
 */
void build_ride(char **ride_params, void *catalog, STATS stats);

/**
 * @brief Sets the ride's id
 *
 * @param ride - The ride of type `RIDE`
 * @param id_string - The id of the ride of type `char *`
 */
void set_ride_id(RIDE ride, char *id_string);

/**
 * @brief Sets the ride's date
 *
 * @param ride - The ride of type `RIDE`
 * @param date_string - The date of the ride of type `char *`
 */
void set_ride_date(RIDE ride, char *date_string);

/**
 * @brief Sets the ride's driver
 *
 * @param ride - The ride of type `RIDE`
 * @param driver_string - The driver of the ride of type `char *`
 */
void set_ride_driver(RIDE ride, char *driver_string);

/**
 * @brief Sets the ride's user
 *
 * @param ride - The ride of type `RIDE`
 * @param user - The user of the ride of type `gpointer`
 */
void set_ride_user(RIDE ride, gpointer user);

/**
 * @brief Sets the ride's city
 *
 * @param ride - The ride of type `RIDE`
 * @param city_string - The city of the ride of type `char *`
 */
void set_ride_city(RIDE ride, char city);

/**
 * @brief Sets the ride's distance
 *
 * @param ride - The ride of type `RIDE`
 * @param distance_string - The distance of the ride of type `char *`
 */
void set_ride_distance(RIDE ride, char *distance_string);

/**
 * @brief Sets the ride's score user
 *
 * @param ride - The ride of type `RIDE`
 * @param score_user_string - The score user of the ride of type `char *`
 */
void set_ride_score_user(RIDE ride, char *score_user_string);

/**
 * @brief Sets the ride's score driver
 *
 * @param ride - The ride of type `RIDE`
 * @param score_driver_string - The score driver of the ride of type `char *`
 */
void set_ride_score_driver(RIDE ride, char *score_driver_string);

/**
 * @brief Sets the ride's tip
 *
 * @param ride - The ride of type `RIDE`
 * @param tip_string - The tip of the ride of type `char *`
 */
void set_ride_tip(RIDE ride, char *tip_string);

/**
 * @brief Sets the ride's price
 *
 * @param ride - The ride of type `RIDE`
 * @param price_string - The price of the ride of type `char *`
 */
void set_ride_price(RIDE ride, double price);

/**
 * @brief Gets the ride id
 *
 * @param ride - The ride of type `RIDE`
 *
 * @return The ride id of type `int`
 */
int get_ride_id(RIDE ride);

/**
 * @brief Gets the ride date
 *
 * @param ride - The ride of type `RIDE`
 *
 * @return The ride date of type `int`
 */
int get_ride_date(RIDE ride);

/**
 * @brief Gets the ride driver
 *
 * @param ride - The ride of type `RIDE`
 *
 * @return The ride driver of type `gpointer`
 */
gpointer get_ride_driver(RIDE ride);

/**
 * @brief Gets the ride user
 *
 * @param ride - The ride of type `RIDE`
 *
 * @return The ride user of type `gpointer`
 */
gpointer get_ride_user(RIDE ride);

/**
 * @brief Gets the ride city
 *
 * @param ride - The ride of type `RIDE`
 *
 * @return The ride city number of type `int`
 */
int get_ride_city(RIDE ride);

/**
 * @brief Gets the ride distance
 *
 * @param ride - The ride of type `RIDE`
 *
 * @return The ride distance of type `int`
 */
int get_ride_distance(RIDE ride);

/**
 * @brief Gets the ride score user
 *
 * @param ride - The ride of type `RIDE`
 *
 * @return The ride score user of type `int`
 */
int get_ride_score_user(RIDE ride);

/**
 * @brief Gets the ride score driver
 *
 * @param ride - The ride of type `RIDE`
 *
 * @return The ride score driver of type `int`
 */
int get_ride_score_driver(RIDE ride);

/**
 * @brief Gets the ride tip
 *
 * @param ride - The ride of type `RIDE`
 *
 * @return The ride tip of type `double`
 */
double get_ride_tip(RIDE ride);

/**
 * @brief Gets the ride price
 *
 * @param ride - The ride of type `RIDE`
 *
 * @return The ride price of type `double`
 */
double get_ride_price(RIDE ride);

/**
 * @brief Function that calculates the price of a ride
 *
 * @param distance - The distance of the ride of type `int`
 * @param car_class - The car class of the ride of type `enum car_class`
 *
 * @return The price of the ride of type `double`
 */
double calculate_ride_price(int distance, enum car_class car_class);

/**
 * @brief Function that verufies if the date parameter are correct
 *
 * @param parameters - The parameters of the ride of type `char **`
 *
 * @return 1 if the input is correct, 0 otherwise
 */
int verify_ride_input(char **parameters);

#endif
