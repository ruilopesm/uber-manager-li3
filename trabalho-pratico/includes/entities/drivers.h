#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>

#include "base/stats.h"
#include "utils/utils.h"

#define MAX_DRIVER_TOKENS 9

typedef struct driver *DRIVER;

typedef struct stats *STATS;  // Forward declaration

/**
 * @brief Creates a new driver
 *
 * @return new_driver - The new driver of type `DRIVER`
 */
DRIVER create_driver(void);

/**
 * @brief Builds the driver with given parameters
 *
 * @param driver_params - The driver parameters of type `char**`
 * @param catalog - The catalog of type `void*` (CATALOG)
 * @param stats - The stats of type `STATS`
 */
void build_driver(char **driver_params, void *catalog, STATS stats);

/**
 * @brief Sets the driver id
 *
 * @param driver - The driver of type `DRIVER`
 * @param id_string - The id string of type `char*`
 */
void set_driver_id(DRIVER driver, char *id_string);

/**
 * @brief Sets the driver name
 *
 * @param driver - The driver of type `DRIVER`
 * @param name_string - The name string of type `char*`
 */
void set_driver_name(DRIVER driver, char *name_string);

/**
 * @brief Sets the driver birth date
 *
 * @param driver - The driver of type `DRIVER`
 * @param birth_date_string - The birth date string of type `char*`
 */
void set_driver_birth_date(DRIVER driver, char *birth_date_string);

/**
 * @brief Sets the driver gender
 *
 * @param driver - The driver of type `DRIVER`
 * @param gender_string - The gender string of type `char*`
 */
void set_driver_gender(DRIVER driver, char *gender_string);

/**
 * @brief Sets the driver car class
 *
 * @param driver - The driver of type `DRIVER`
 * @param car_class_string - The car class string of type `char*`
 */
void set_driver_car_class(DRIVER driver, char *car_class_string);

/**
 * @brief Sets the driver account creation
 *
 * @param driver - The driver of type `DRIVER`
 * @param account_creation_string - The account creation string of type `char*`
 */
void set_driver_account_creation(DRIVER driver, char *account_creation_string);

/**
 * @brief Sets the driver account status
 *
 * @param driver - The driver of type `DRIVER`
 * @param account_status_string - The account status string of type `char*`
 */
void set_driver_account_status(DRIVER driver, char *account_status_string);

/**
 * @brief Sets the driver number of rides
 *
 * @param driver - The driver of type `DRIVER`
 * @param number_of_rides - The number of rides of type `int`
 */
void set_driver_number_of_rides(DRIVER driver, int number_of_rides);

/**
 * @brief Sets the driver total rating
 *
 * @param driver - The driver of type `DRIVER`
 * @param total_rating - The total rating of type `double`
 */
void set_driver_total_rating(DRIVER driver, double total_rating);

/**
 * @brief Sets the driver total earned
 *
 * @param driver - The driver of type `DRIVER`
 * @param total_earned - The total earned of type `double`
 */
void set_driver_total_earned(DRIVER driver, double total_earned);

/**
 * @brief Sets the driver latest ride
 *
 * @param driver - The driver of type `DRIVER`
 * @param latest_ride - The latest ride of type `int`
 */
void set_driver_latest_ride(DRIVER driver, int latest_ride_string);

/**
 * @brief Gets the driver id
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return id - The driver id of type `int`
 */
int get_driver_id(DRIVER driver);

/**
 * @brief Gets the driver name
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return driver_name - The driver name of type `char*`
 */
char *get_driver_name(DRIVER driver);

/**
 * @brief Gets the driver birth date
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return int - The driver birth date
 */
int get_driver_birth_date(DRIVER driver);

/**
 * @brief Gets the driver gender
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return gender_copy - The driver gender of type `enum gender`
 */
enum gender get_driver_gender(DRIVER driver);

/**
 * @brief Gets the driver car class
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return car_class - The driver car class of type `enum car_class`
 */
enum car_class get_driver_car_class(DRIVER driver);

/**
 * @brief Gets the driver account creation
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return account_creation - The driver account creation of type `int`
 */
int get_driver_account_creation(DRIVER driver);

/**
 * @brief Gets the driver account status
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return status - The driver account status of type `enum account_status`
 */
enum account_status get_driver_account_status(DRIVER driver);

/**
 * @brief Gets the driver number of rides
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return number_of_rides - The driver number of rides of type `int`
 */
int get_driver_number_of_rides(DRIVER driver);

/**
 * @brief Gets the driver total rating
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return total_rating - The driver total rating of type `double`
 */
double get_driver_total_rating(DRIVER driver);

/**
 * @brief Gets the driver total earned
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return total_earned - The driver total earned of type `double`
 */
double get_driver_total_earned(DRIVER driver);

/**
 * @brief Gets the driver latest ride
 *
 * @param driver - The driver of type `DRIVER`
 *
 * @return latest_ride - The driver latest ride of type `int`
 */
int get_driver_latest_ride(DRIVER driver);

/**
 * @brief Frees the the memory allocated to store a driver
 *
 * @param driver - The driver of type `DRIVER`
 */
void free_driver(DRIVER driver);

/**
 * @brief Verifies if the driver input is valid
 *
 * @param parameters - The driver parameters of type `char**`
 */
int verify_driver_input(char **parameters);

#endif
