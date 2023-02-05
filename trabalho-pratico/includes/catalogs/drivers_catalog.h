#ifndef DRIVERS_CATALOG_H
#define DRIVERS_CATALOG_H

#include "entities/drivers.h"

typedef struct drivers_catalog *DRIVERS_CATALOG;

typedef struct driver *DRIVER;  // Forward declaration

DRIVERS_CATALOG create_drivers_catalog(void);

/**
 * @brief Function that inserts a driver into the driver catalog struct
 *
 * @param catalog - The catalog of type `DRIVERS_CATALOG`
 * @param driver - The driver of type `DRIVER`
 * @param key - The key of type `gpointer`
 */
void insert_driver(DRIVERS_CATALOG catalog, DRIVER driver, gpointer key);

/**
 * @brief Function that updates a driver from the driver catalog struct
 *
 * @param catalog - The catalog of type `DRIVERS_CATALOG`
 * @param driver_code - The driver code of type `gpointer`
 * @param rating - The rating of type `double`
 * @param price - The price of type `double`
 * @param tip - The tip of type `double`
 * @param date - The date of type `int`
 */
void update_driver(DRIVERS_CATALOG catalog, gpointer driver_code, double rating,
                   double price, double tip, int date);

/**
 * @brief Function that gets a driver from the driver catalog struct with given
 * id
 *
 * @param catalog - The catalog of type `DRIVERS_CATALOG`
 * @param id - The id to be fetch of type `int`
 *
 * @return driver - The driver of type `DRIVER`
 */
DRIVER get_driver_by_id(DRIVERS_CATALOG catalog, int id);

/**
 * @brief Function that gets a driver from the driver catalog struct with given
 * driver code
 *
 * @param catalog - The catalog of type `DRIVERS_CATALOG`
 * @param driver_code - The driver code to be fetch of type `gpointer`
 *
 * @return driver - The driver of type `DRIVER`
 */
DRIVER get_driver_by_code(DRIVERS_CATALOG catalog, gpointer driver_code);

/**
 * @brief Function frees the memory allocated for the driver catalog struct
 *
 * @param catalog - The catalog of type `DRIVERS_CATALOG`
 */
void free_drivers_catalog(DRIVERS_CATALOG catalog);

#endif
