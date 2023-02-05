#ifndef DRIVERS_CATALOG_H
#define DRIVERS_CATALOG_H

#include "entities/drivers.h"

typedef struct drivers_catalog *DRIVERS_CATALOG;

typedef struct driver *DRIVER;  // Forward declaration

DRIVERS_CATALOG create_drivers_catalog(void);

void insert_driver(DRIVERS_CATALOG catalog, DRIVER driver, gpointer key);

void update_driver(DRIVERS_CATALOG catalog, gpointer driver_code, double rating,
                   double price, double tip, int date);

DRIVER get_driver_by_id(DRIVERS_CATALOG catalog, int id);

DRIVER get_driver_by_code(DRIVERS_CATALOG catalog, gpointer driver_code);

void free_drivers_catalog(DRIVERS_CATALOG catalog);

#endif
