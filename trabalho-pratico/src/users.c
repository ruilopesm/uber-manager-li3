#include "users.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "catalog.h"
#include "input.h"
#include "stats.h"

struct user {
  int *username;
  char *name;
  double total_rating;
  double total_spent;
  int birth_date;
  int account_creation;
  int latest_ride;
  int number_of_rides;
  int total_distance;
  enum gender gender : 1;
  enum account_status account_status : 1;
};

USER create_user(void) {
  USER new_user = malloc(sizeof(struct user));
  new_user->username = NULL;
  new_user->name = NULL;

  return new_user;
}

void insert_user(char **user_params, CATALOG catalog, STATS stats) {
  // If the input verification failed, we don't insert the user
  if (!verify_user_input(user_params)) return;

  GHashTable *users_hash_table = get_catalog_users(catalog);
  USER user = create_user();

  GHashTable *users_code = get_catalog_users_code(catalog);
  GPtrArray *users_reverse = get_catalog_users_reverse_lookup(catalog);
  set_user_username(user, user_params[0], users_code, users_reverse);
  set_user_name(user, user_params[1]);
  set_user_gender(user, user_params[2]);
  set_user_birth_date(user, user_params[3]);
  set_user_account_creation(user, user_params[4]);
  set_user_account_status(user, user_params[6]);
  set_user_number_of_rides(user, 0);
  set_user_total_rating(user, 0.0);
  set_user_total_spent(user, 0.0);
  set_user_total_distance(user, 0);
  set_user_latest_ride(user, "00/00/0000");

  // udpate users array
  GArray *users_array = get_top_users_by_total_distance(stats);
  g_array_append_val(users_array, user);

  g_hash_table_insert(users_hash_table, user->username, user);

  (void)stats;  // To avoid the "unused variable" warning
}

void set_user_username(USER user, char *username_string, GHashTable *users_code,
                       GPtrArray *users_reverse) {
  static int users_parsed = 0;

  // Creates the user_code and inserts it into the hash table
  char *username = strdup(username_string);
  int *user_code = malloc(sizeof(int));
  *user_code = users_parsed;
  g_hash_table_insert(users_code, username, user_code);

  // Inserts the username into the reverse search array
  char *username_copy = strdup(username_string);
  g_ptr_array_add(users_reverse, username_copy);

  // Puts the user code into the user struct
  int *username_code = malloc(sizeof(int));
  *username_code = users_parsed;
  user->username = username_code;
  users_parsed++;
}

void set_user_name(USER user, char *name_string) {
  char *name = strdup(name_string);
  user->name = name;
}

void set_user_gender(USER user, char *gender_string) {
  enum gender gender;

  if (!strcmp(gender_string, "M")) {
    gender = M;
  } else {
    gender = F;
  }

  user->gender = gender;
}

void set_user_birth_date(USER user, char *birth_date_string) {
  int date = 0;

  date = (birth_date_string[0] - '0') * 10;
  date += (birth_date_string[1] - '0');

  date += (birth_date_string[3] - '0') * 1000;
  date += (birth_date_string[4] - '0') * 100;

  date += (birth_date_string[6] - '0') * 10000000;
  date += (birth_date_string[7] - '0') * 1000000;
  date += (birth_date_string[8] - '0') * 100000;
  date += (birth_date_string[9] - '0') * 10000;

  user->birth_date = date;
}

void set_user_account_creation(USER user, char *account_creation_date_string) {
  int date = 0;

  date = (account_creation_date_string[0] - '0') * 10;
  date += (account_creation_date_string[1] - '0');

  date += (account_creation_date_string[3] - '0') * 1000;
  date += (account_creation_date_string[4] - '0') * 100;

  date += (account_creation_date_string[6] - '0') * 10000000;
  date += (account_creation_date_string[7] - '0') * 1000000;
  date += (account_creation_date_string[8] - '0') * 100000;
  date += (account_creation_date_string[9] - '0') * 10000;

  user->account_creation = date;
}

void set_user_account_status(USER user, char *account_status_string) {
  enum account_status account_status;

  if (!strcmp(account_status_string, "active")) {
    account_status = ACTIVE;
  } else {
    account_status = INACTIVE;
  }

  user->account_status = account_status;
}

void set_user_number_of_rides(USER user, int number_of_rides) {
  user->number_of_rides = number_of_rides;
}

void set_user_total_rating(USER user, double total_rating) {
  user->total_rating = total_rating;
}

void set_user_total_spent(USER user, double total_spent) {
  user->total_spent = total_spent;
}

void set_user_total_distance(USER user, int total_distance) {
  user->total_distance = total_distance;
}

void set_user_latest_ride(USER user, char *latest_ride_date_string) {
  int date = 0;

  date = (latest_ride_date_string[0] - '0') * 10;
  date += (latest_ride_date_string[1] - '0');

  date += (latest_ride_date_string[3] - '0') * 1000;
  date += (latest_ride_date_string[4] - '0') * 100;

  date += (latest_ride_date_string[6] - '0') * 10000000;
  date += (latest_ride_date_string[7] - '0') * 1000000;
  date += (latest_ride_date_string[8] - '0') * 100000;
  date += (latest_ride_date_string[9] - '0') * 10000;

  user->latest_ride = date;
}

int get_user_username(USER user) {
  int username_copy = *user->username;

  return username_copy;
}

char *get_user_name(USER user) {
  char *name_copy = strdup(user->name);

  return name_copy;
}

enum gender get_user_gender(USER user) {
  enum gender gender_copy = user->gender;

  return gender_copy;
}

int get_user_birth_date(USER user) {
  int birth_date_copy = user->birth_date;

  return birth_date_copy;
}

int get_user_account_creation(USER user) {
  int account_creation_copy = user->account_creation;

  return account_creation_copy;
}

enum account_status get_user_account_status(USER user) {
  enum account_status account_status_copy = user->account_status;

  return account_status_copy;
}

int get_user_number_of_rides(USER user) {
  int number_of_rides_copy = user->number_of_rides;

  return number_of_rides_copy;
}

double get_user_total_rating(USER user) {
  double total_rating_copy = user->total_rating;

  return total_rating_copy;
}

double get_user_total_spent(USER user) {
  double total_spent_copy = user->total_spent;

  return total_spent_copy;
}

int get_user_total_distance(USER user) {
  int total_distance_copy = user->total_distance;

  return total_distance_copy;
}

int get_user_latest_ride(USER user) {
  int latest_ride_copy = user->latest_ride;

  return latest_ride_copy;
}

void free_user(USER user) {
  free(user->name);
  free(user);
}

int verify_user_input(char **parameters) {
  // Verifies if the username isn't empty
  if (!(parameters[0])) return 0;

  // Verifies if the user's name isn't empty
  if (!(parameters[1])) return 0;

  // Verifies if the user's gender isn't empty
  if (!(parameters[2])) return 0;

  // Verifies if the payment method isn't empty
  if (!(parameters[5])) return 0;

  // Verifies if the birth date follows the format
  if (!verify_date_format(parameters[3])) return 0;

  // Verifies if the account date follows the format
  if (!verify_date_format(parameters[4])) return 0;

  // Verifies if account status follows the format
  if (!verify_account_status_format(parameters[6])) return 0;

  // If all fields are valid then the user is valid
  return 1;
}
