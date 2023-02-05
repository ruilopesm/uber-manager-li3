#ifndef USERS_CATALOG_H
#define USERS_CATALOG_H

#include "entities/users.h"

typedef struct users_catalog *USERS_CATALOG;

typedef struct user *USER;  // Forward declaration

USERS_CATALOG create_users_catalog(void);

/**
 * @brief Function that inserts a user into the users catalog struct
 *
 * @param catalog - The users catalog of type `USERS_CATALOG`
 * @param user - The user of type `USER`
 * @param key - The key of type `gpointer`
 */
void insert_user(USERS_CATALOG catalog, USER user, gpointer key);

/**
 * @brief Function that updates the user in the users catalog struct
 *
 * @param catalog - The users catalog of type `USERS_CATALOG`
 * @param user_code - The user code of type `gpointer`
 * @param distance - The distance of type `int`
 * @param rating - The rating of type `double`
 * @param price - The price of type `double`
 * @param tip - The tip of type `double`
 * @param date - The date of type `int`
 */
void update_user(USERS_CATALOG catalog, gpointer user_code, int distance,
                 double rating, double price, double tip, int date);

/**
 * @brief Function that sets the username of a user in the users catalog struct
 *
 * @param catalog - The users catalog of type `USERS_CATALOG`
 * @param user - The user of type `USER`
 * @param username - The username of type `char *`
 */
void set_catalog_user_username(USERS_CATALOG catalog, USER user,
                               char *username);

/**
 * @brief Function that gets a user from the users catalog struct with given
 * username
 *
 * @param catalog - The users catalog of type `USERS_CATALOG`
 * @param username - The username to be fetch of type `char*`
 *
 * @return user - The user of type `USER`
 */
USER get_user_by_username(USERS_CATALOG catalog, char *username);

/**
 * @brief Function that gets a user from the users catalog struct with given
 * user code
 *
 * @param catalog - The users catalog of type `USERS_CATALOG`
 * @param user_code - The user code to be fetch of type `gpointer`
 *
 * @return user - The user of type `USER`
 */
USER get_user_by_code(USERS_CATALOG catalog, gpointer user_code);

/**
 * @brief Function that gets the user code from the users catalog struct with
 * given username
 *
 * @param catalog - The users catalog of type `USERS_CATALOG`
 * @param username - The username to be fetch of type `char*`
 *
 * @return user_code - The user code of type `gpointer`
 */
gpointer get_user_code_from_username(USERS_CATALOG catalog, char *username);

/**
 * @brief Function that gets the username from the users catalog struct with
 * given user code
 *
 * @param catalog - The users catalog of type `USERS_CATALOG`
 * @param user_code - The user code to be fetch of type `gpointer`
 *
 * @return username - The username of type `char *`
 */
char *get_username_from_code(USERS_CATALOG catalog, gpointer user_code);

/**
 * @brief Function that frees the users catalog struct
 *
 * @param catalog - The users catalog of type `USERS_CATALOG`
 */
void free_users_catalog(USERS_CATALOG catalog);

#endif
