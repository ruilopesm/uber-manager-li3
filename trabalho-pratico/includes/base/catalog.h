#ifndef CATALOG_H
#define CATALOG_H

#include <glib.h>

typedef struct catalog *CATALOG;

typedef struct user *USER;  // Forward declaration

typedef struct driver *DRIVER;  // Forward declaration

CATALOG create_catalog(void);

GHashTable *get_catalog_users(CATALOG catalog);

GHashTable *get_catalog_drivers(CATALOG catalog);

GHashTable *get_catalog_rides(CATALOG catalog);

USER get_user_by_username(CATALOG catalog, char *username);

char *get_username_from_code(CATALOG catalog, int user_code);

DRIVER get_driver_by_id(CATALOG catalog, int driver_id);

USER get_user_by_code(CATALOG catalog, gpointer user_code);

DRIVER get_driver_by_code(CATALOG catalog, gpointer driver_code);

GHashTable *get_catalog_cities_code(CATALOG catalog);

char *get_city_from_code(CATALOG catalog, int city_code);

char *get_city_code(CATALOG catalog, char *city);

GPtrArray *get_catalog_cities_reverse_lookup(CATALOG catalog);

GHashTable *get_catalog_users_code(CATALOG catalog);

GPtrArray *get_catalog_users_reverse_lookup(CATALOG catalog);

void free_catalog(CATALOG catalog);

#endif
