#include "entities/users.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base/catalog.h"
#include "base/stats.h"
#include "io/input.h"

struct user {
  gpointer username;
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

void build_user(char **user_params, CATALOG catalog, STATS stats) {
  // If the input verification failed, we don't insert the user
  if (!verify_user_input(user_params)) return;

  USER user = create_user();

  set_catalog_user_username(catalog, user, user_params[0]);
  set_user_name(user, user_params[1]);
  set_user_gender(user, user_params[2]);
  set_user_birth_date(user, user_params[3]);
  set_user_account_creation(user, user_params[4]);
  set_user_account_status(user, user_params[6]);
  set_user_number_of_rides(user, 0);
  set_user_total_rating(user, 0.0);
  set_user_total_spent(user, 0.0);
  set_user_total_distance(user, 0);
  set_user_latest_ride(user, 0);

  insert_user(catalog, user, user->username);
  insert_user_into_stats(stats, user);
}

void set_user_username(USER user, gpointer username_code) {
  user->username = username_code;
}

void set_user_name(USER user, char *name_string) {
  user->name = strdup(name_string);
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

void set_user_latest_ride(USER user, int latest_ride_date) {
  user->latest_ride = latest_ride_date;
}

int get_user_username(USER user) { return GPOINTER_TO_INT(user->username); }

char *get_user_name(USER user) { return strdup(user->name); }

enum gender get_user_gender(USER user) { return user->gender; }

int get_user_birth_date(USER user) { return user->birth_date; }

int get_user_account_creation(USER user) { return user->account_creation; }

enum account_status get_user_account_status(USER user) {
  return user->account_status;
}

int get_user_number_of_rides(USER user) { return user->number_of_rides; }

double get_user_total_rating(USER user) { return user->total_rating; }

double get_user_total_spent(USER user) { return user->total_spent; }

int get_user_total_distance(USER user) { return user->total_distance; }

int get_user_latest_ride(USER user) { return user->latest_ride; }

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
