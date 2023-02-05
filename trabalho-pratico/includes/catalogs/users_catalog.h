#ifndef USERS_CATALOG_H
#define USERS_CATALOG_H

#include "entities/users.h"

typedef struct users_catalog *USERS_CATALOG;

typedef struct user *USER;  // Forward declaration

USERS_CATALOG create_users_catalog(void);

void insert_user(USERS_CATALOG catalog, USER user, gpointer key);

void update_user(USERS_CATALOG catalog, gpointer user_code, int distance,
                 double rating, double price, double tip, int date);

void set_catalog_user_username(USERS_CATALOG catalog, USER user,
                               char *username);

USER get_user_by_username(USERS_CATALOG catalog, char *username);

USER get_user_by_code(USERS_CATALOG catalog, gpointer user_code);

gpointer get_user_code_from_username(USERS_CATALOG catalog, char *username);

char *get_username_from_code(USERS_CATALOG catalog, gpointer user_code);

void free_users_catalog(USERS_CATALOG catalog);

#endif
