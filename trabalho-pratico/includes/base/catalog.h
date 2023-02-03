#ifndef CATALOG_H
#define CATALOG_H

#include <glib.h>

typedef struct catalog *CATALOG;

typedef struct user *USER;  // Forward declaration

typedef struct driver *DRIVER;  // Forward declaration

typedef struct ride *RIDE;  // Forward declaration

CATALOG create_catalog(void);

GHashTable *get_catalog_users(CATALOG catalog);

GHashTable *get_catalog_drivers(CATALOG catalog);

GHashTable *get_catalog_rides(CATALOG catalog);

// Users
void insert_user(CATALOG catalog, USER user, gpointer key);

void set_catalog_user_username(CATALOG catalog, USER user, char *username);

USER get_user_by_username(CATALOG catalog, char *username);

USER get_user_by_code(CATALOG catalog, gpointer user_code);

void update_user_catalog(CATALOG catalog, gpointer username, int distace,
                         double rating, double price, double tip, int date);

// Drivers
void insert_driver(CATALOG catalog, DRIVER driver, gpointer key);

DRIVER get_driver_by_id(CATALOG catalog, int driver_id);

DRIVER get_driver_by_code(CATALOG catalog, gpointer driver_code);

char *get_username_from_code(CATALOG catalog, int user_code);

void update_driver_catalog(CATALOG catalog, gpointer driver_id, double rating,
                           double price, double tip, int date);

// Rides
void insert_ride_and_update_catalog(CATALOG catalog, RIDE ride, gpointer key,
                                    gpointer user, gpointer driver,
                                    int distance, double score_user,
                                    double price, double tip, int date,
                                    double score_driver);

void set_catalog_ride_user(CATALOG catalog, RIDE ride, char *username);

void set_catalog_ride_city(CATALOG catalog, RIDE ride, char *city);

GHashTable *get_catalog_cities_code(CATALOG catalog);

char *get_city_from_code(CATALOG catalog, int city_code);

char *get_city_code(CATALOG catalog, char *city);

GPtrArray *get_catalog_cities_reverse_lookup(CATALOG catalog);

GHashTable *get_catalog_users_code(CATALOG catalog);

GPtrArray *get_catalog_users_reverse_lookup(CATALOG catalog);

void free_catalog(CATALOG catalog);

#endif
