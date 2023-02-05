#ifndef JOINT_CATALOG_H
#define JOINT_CATALOG_H

#include "drivers_catalog.h"
#include "rides_catalog.h"
#include "users_catalog.h"

/**
 * @brief Struct that contains, encapsulated, the catalogs of users, drivers and
 * rides
 */
typedef struct joint_catalog *JOINT_CATALOG;

typedef struct users_catalog *USERS_CATALOG;  // Forward declaration

typedef struct drivers_catalog *DRIVERS_CATALOG;  // Forward declaration

typedef struct rides_catalog *RIDES_CATALOG;  // Forward declaration

/**
 * @brief Function that creates a new join catalog
 *
 * @param users_catalog - The users catalog of type `USERS_CATALOG`
 * @param drivers_catalog - The drivers catalog of type `DRIVERS_CATALOG`
 * @param rides_catalog - The rides catalog of type `RIDES_CATALOG`
 *
 * @return new_joint_catalog - The new join catalog of type `JOINT_CATALOG`
 */
JOINT_CATALOG create_joint_catalog(USERS_CATALOG users_catalog,
                                   DRIVERS_CATALOG drivers_catalog,
                                   RIDES_CATALOG rides_catalog);

/**
 * @brief Function that gets the users catalog from the join catalog struct
 *
 * @param users - The users catalog of type `USERS_CATALOG`
 */
USERS_CATALOG get_users_catalog(JOINT_CATALOG catalog);

/**
 * @brief Function that gets the drivers catalog from the join catalog struct
 *
 * @param drivers - The drivers catalog of type `DRIVERS_CATALOG`
 */
DRIVERS_CATALOG get_drivers_catalog(JOINT_CATALOG catalog);

/**
 * @brief Function that gets the rides catalog from the join catalog struct
 *
 * @param rides - The rides catalog of type `RIDES_CATALOG`
 */
RIDES_CATALOG get_rides_catalog(JOINT_CATALOG catalog);

/**
 * @brief Function that frees the memory allocated for the join catalog
 *
 * @param catalog - The join catalog of type `JOINT_CATALOG`
 */
void free_joint_catalog(JOINT_CATALOG catalog);

#endif
