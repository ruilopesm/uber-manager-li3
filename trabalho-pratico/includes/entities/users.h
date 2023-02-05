#ifndef USERS_H
#define USERS_H

#include <glib.h>

#include "base/stats.h"
#include "utils/utils.h"

#define MAX_USER_TOKENS 7

typedef struct user *USER;

/**
 * @brief Creates a new user
 *
 * @return new_user - The new user of type `USER`
 */
USER create_user(void);

/**
 * @brief Function that builds the user with given parameters
 *
 * @param user_params - The array of strings that contains the user's of type
 * `char **`
 * @param catalog - The catalog of type `void *` (CATALOG)
 * @param stats - The stats of type `STATS`
 */
void build_user(char **user_params, void *catalog, STATS stats);

/**
 * @brief Function that sets the user's username
 *
 * @param user - The user of type `USER`
 * @param username_string - The username of type `char *`
 * @param users_code - The hash table that contains the users code of type
 * `GHashTable *`
 * @param users_reverse - The array that contains the users reverse lookup of
 * type `GPtrArray *`
 */
void set_user_username(USER user, gpointer username);

/**
 * @brief Function that sets the user's name
 *
 * @param user - The user of type `USER`
 * @param name_string - The name of type `char *`
 */
void set_user_name(USER user, char *name_string);

/**
 * @brief Function that sets the user gender (M/F)
 *
 * @param user - The user of type `USER`
 * @param gender_string - The user's gender of type `char *`
 */
void set_user_gender(USER user, char *gender_string);

/**
 * @brief Function that sets the user's birth date
 *
 * @param user - The user of type `USER`
 * @param birth_date_string - The user's birth date of type `char *`
 */
void set_user_birth_date(USER user, char *birth_date_string);

/**
 * @brief Function that sets the user's account creation date
 *
 * @param user - The user of type `USER`
 * @param account_creation_date_string - The user's account creation date of
 * type `char *`
 */
void set_user_account_creation(USER user, char *account_creation_date);

/**
 * @brief Function that sets the user's account status
 *
 * @param user - The user of type `USER`
 * @param account_status_string - The user's account status of type `char *`
 */
void set_user_account_status(USER user, char *account_status_string);

/**
 * @brief Function that sets the user's number of rides
 *
 * @param user - The user of type `USER`
 * @param number_of_rides - The user's number of rides of type `int`
 */
void set_user_number_of_rides(USER user, int number_of_rides);

/**
 * @brief Function that sets the user's total rating
 *
 * @param user - The user of type `USER`
 * @param total_rating - The user's total rating of type `double`
 */
void set_user_total_rating(USER user, double total_rating);

/**
 * @brief Function that sets the user's total spent
 *
 * @param user - The user of type `USER`
 * @param total_spent - The user's total spent of type `double`
 */
void set_user_total_spent(USER user, double total_spent);

/**
 * @brief Function that sets the user's total distance
 *
 * @param user - The user of type `USER`
 * @param total_distance - The user's total distance of type `int`
 */
void set_user_total_distance(USER user, int total_distance);

/**
 * @brief Function that sets the user's latest ride date
 *
 * @param user - The user of type `USER`
 * @param latest_ride_date - The user's latest ride date of type `int`
 */
void set_user_latest_ride(USER user, int latest_ride_date);

/**
 * @brief Function that gets the user's username
 *
 * @param user - The user of type `USER`
 *
 * @returns The user's username of type `int`
 */
int get_user_username(USER user);

/**
 * @brief Function that gets the user's name
 *
 * @param user - The user of type `USER`
 *
 * @returns The user's name of type `char *`
 */
char *get_user_name(USER user);

/**
 * @brief Function that gets the user's gender
 *
 * @param user - The user of type `USER`
 *
 * @returns gender_copy of type `enum gender`
 */
enum gender get_user_gender(USER user);

/**
 * @brief Function that gets the user's birth date
 *
 * @param user - The user of type `USER`
 *
 * @returns The user's birth date of type `int`
 */
int get_user_birth_date(USER user);

/**
 * @brief Function that gets the user's account creation date
 *
 * @param user - The user of type `USER`
 *
 * @returns The user's account creation date of type `int`
 */
int get_user_account_creation(USER user);

/**
 * @brief Function that gets the user's account status
 *
 * @param user - The user of type `USER`
 *
 * @returns The user's account status of type `enum account_status`
 */
enum account_status get_user_account_status(USER user);

/**
 * @brief Function that gets the user's number of rides
 *
 * @param user - The user of type `USER`
 *
 * @returns The user's number of rides of type `int`
 */
int get_user_number_of_rides(USER user);

/**
 * @brief Function that gets the user's total rating
 *
 * @param user - The user of type `USER`
 *
 * @returns The user's total rating of type `double`
 */
double get_user_total_rating(USER user);

/**
 * @brief Function that gets the user's total spent
 *
 * @param user - The user of type `USER`
 *
 * @returns The user's total spent of type `double`
 */
double get_user_total_spent(USER user);

/**
 * @brief Function that gets the user's total distance
 *
 * @param user - The user of type `USER`
 *
 * @returns The user's total distance of type `int`
 */
int get_user_total_distance(USER user);

/**
 * @brief Function that gets the user's latest ride date
 *
 * @param user - The user of type `USER`
 *
 * @returns The user's latest ride date of type `int`
 */
int get_user_latest_ride(USER user);

/**
 * @brief Function that frees the memory allocated for a user
 *
 * @param user - The user of type `USER`
 */
void free_user(USER user);

/**
 * @brief Function that verifies if the user's parameters are valid
 *
 * @param parameters - The user's parameters of type `char **`
 *
 * @returns 1 if the parameters are valid, 0 otherwise
 */
int verify_user_input(char **parameters);

#endif
