#ifndef RIDES_CATALOG_H
#define RIDES_CATALOG_H

#include "entities/rides.h"

typedef struct rides_catalog *RIDES_CATALOG;

typedef struct ride *RIDE;  // Forward declaration

RIDES_CATALOG create_rides_catalog(void);

/**
 * @brief Function that inserts the ride into the designated data structure
 *
 * @param catalog - The rides catalog of type `RIDES_CATALOG`
 * @param ride - The ride of type `RIDE`
 * @param key - The key of type `gpointer`
 */
void insert_ride(RIDES_CATALOG catalog, RIDE ride, gpointer key);

/**
 * @brief Function that sets the city in the catalog ride struct
 *
 * @param catalog - The rides catalog of type `RIDES_CATALOG`
 * @param ride - The ride of type `RIDE`
 * @param city - The city of type `char *`
 */
void set_catalog_ride_city(RIDES_CATALOG catalog, RIDE ride, char *city);

/**
 * @brief Function that gets the city from the rides catalog struct with given
 * city code
 *
 * @param catalog - The rides catalog of type `RIDES_CATALOG`
 * @param city_code - The city code to be fetch of type `gpointer`
 *
 * @return city - The city of type `char *`
 */
char *get_city_from_code(RIDES_CATALOG catalog, gpointer city_code);

/**
 * @brief Function that gets the city code from the rides catalog struct
 *
 * @param catalog - The rides catalog of type `RIDES_CATALOG`
 * @param city - The city to be fetch of type `char *`
 *
 * @return city_code - The city code of type `gpointer`
 */
char *get_city_code(RIDES_CATALOG catalog, char *city);

/**
 * @brief Function that free the rides from the rides catalog struct
 *
 * @param catalog - The rides catalog of type `RIDES_CATALOG`
 */
void free_rides_catalog(RIDES_CATALOG catalog);

#endif
