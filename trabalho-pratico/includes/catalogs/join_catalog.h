#ifndef JOIN_CATALOG_H
#define JOIN_CATALOG_H

#include "drivers_catalog.h"
#include "rides_catalog.h"
#include "users_catalog.h"

typedef struct join_catalog *JOIN_CATALOG;

typedef struct users_catalog *USERS_CATALOG;  // Forward declaration

typedef struct drivers_catalog *DRIVERS_CATALOG;  // Forward declaration

typedef struct rides_catalog *RIDES_CATALOG;  // Forward declaration

JOIN_CATALOG create_join_catalog(USERS_CATALOG users_catalog,
                                 DRIVERS_CATALOG drivers_catalog,
                                 RIDES_CATALOG rides_catalog);

USERS_CATALOG get_users_catalog(JOIN_CATALOG catalog);

DRIVERS_CATALOG get_drivers_catalog(JOIN_CATALOG catalog);

RIDES_CATALOG get_rides_catalog(JOIN_CATALOG catalog);

void free_join_catalog(JOIN_CATALOG catalog);

#endif
