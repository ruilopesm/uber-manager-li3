#ifndef RIDES_CATALOG_H
#define RIDES_CATALOG_H

#include "entities/rides.h"

typedef struct rides_catalog *RIDES_CATALOG;

typedef struct ride *RIDE;  // Forward declaration

RIDES_CATALOG create_rides_catalog(void);

void insert_ride(RIDES_CATALOG catalog, RIDE ride, gpointer key);

void set_catalog_ride_city(RIDES_CATALOG catalog, RIDE ride, char *city);

char *get_city_from_code(RIDES_CATALOG catalog, gpointer city_code);

char *get_city_code(RIDES_CATALOG catalog, char *city);

void free_rides_catalog(RIDES_CATALOG catalog);

#endif
