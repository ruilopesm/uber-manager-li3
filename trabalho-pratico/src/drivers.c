#include "drivers.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "catalog.h"
#include "stats.h"

struct driver {
  int *id;
  char *name;
  double total_earned;
  double total_rating;
  int birth_date;
  int account_creation;
  int latest_ride;
  int number_of_rides;
  enum car_class car_class : 2;
  enum gender gender : 1;
  enum account_status account_status : 1;
};

DRIVER create_driver(void) {
  DRIVER new_driver = malloc(sizeof(struct driver));
  new_driver->id = NULL;
  new_driver->name = NULL;

  return new_driver;
}

void insert_driver(char **driver_params, CATALOG catalog, STATS stats) {
  DRIVER driver = create_driver();
  GHashTable *drivers_hash_table = get_catalog_drivers(catalog);

  set_driver_id(driver, driver_params[0]);
  set_driver_name(driver, driver_params[1]);
  set_driver_birth_date(driver, driver_params[2]);
  set_driver_gender(driver, driver_params[3]);
  set_driver_car_class(driver, driver_params[4]);
  set_driver_account_creation(driver, driver_params[7]);

  // Since account_status is the last token, remove the \n from the end of the
  // line
  char *account_status_string = driver_params[8];
  account_status_string[strlen(account_status_string) - 1] = '\0';
  set_driver_account_status(driver, account_status_string);

  set_driver_number_of_rides(driver, 0);
  set_driver_total_rating(driver, 0.0);
  set_driver_total_earned(driver, 0.0);
  set_driver_latest_ride(driver, "00/00/0000");

  g_hash_table_insert(drivers_hash_table, driver->id, driver);

  (void)stats;  // To avoid the "unused variable" warning
}

void set_driver_id(DRIVER driver, char *id_string) {
  driver->id = malloc(sizeof(int));
  int id_int = atoi(id_string);
  *driver->id = id_int;
}

void set_driver_name(DRIVER driver, char *name_string) {
  driver->name = strdup(name_string);
}

void set_driver_birth_date(DRIVER driver, char *birth_date_string) {
  int birth_date = 0;
  int day, month, year;

  sscanf(birth_date_string, "%d/%d/%d", &day, &month, &year);

  birth_date = day;
  birth_date += month * 100;
  birth_date += year * 10000;

  driver->birth_date = birth_date;
}

void set_driver_gender(DRIVER driver, char *gender_string) {
  enum gender gender;

  if (!strcmp(gender_string, "M")) {
    gender = M;
  } else {
    gender = F;
  }

  driver->gender = gender;
}

void set_driver_car_class(DRIVER driver, char *car_class_string) {
  enum car_class car_class;

  if (!strcmp(car_class_string, "basic")) {
    car_class = BASIC;
  } else if (!strcmp(car_class_string, "green")) {
    car_class = GREEN;
  } else {
    car_class = PREMIUM;
  }

  driver->car_class = car_class;
}

void set_driver_account_creation(DRIVER driver, char *account_creation_string) {
  int account_creation = 0;
  int day, month, year;

  sscanf(account_creation_string, "%d/%d/%d", &day, &month, &year);

  account_creation = day;
  account_creation += month * 100;
  account_creation += year * 10000;

  driver->account_creation = account_creation;
}

void set_driver_account_status(DRIVER driver, char *account_status_string) {
  enum account_status account_status;

  if (!strcmp(account_status_string, "active")) {
    account_status = ACTIVE;
  } else {
    account_status = INACTIVE;
  }

  driver->account_status = account_status;
}

void set_driver_number_of_rides(DRIVER driver, int number_of_rides) {
  driver->number_of_rides = number_of_rides;
}

void set_driver_total_rating(DRIVER driver, double total_rating) {
  driver->total_rating = total_rating;
}

void set_driver_total_earned(DRIVER driver, double total_earned) {
  driver->total_earned = total_earned;
}

void set_driver_latest_ride(DRIVER driver, char *latest_ride_string) {
  int latest_ride = 0;
  int day, month, year;

  sscanf(latest_ride_string, "%d/%d/%d", &day, &month, &year);

  latest_ride = day;
  latest_ride += month * 100;
  latest_ride += year * 10000;

  driver->latest_ride = latest_ride;
}

int get_driver_id(DRIVER driver) {
  int id = *driver->id;
  return id;
}

char *get_driver_name(DRIVER driver) {
  char *driver_name = strdup(driver->name);
  return driver_name;
}

int get_driver_birth_date(DRIVER driver) {
  int date = driver->birth_date;
  return date;
}

enum gender get_driver_gender(DRIVER driver) {
  enum gender gender_copy = driver->gender;

  return gender_copy;
}

enum car_class get_driver_car_class(DRIVER driver) {
  enum car_class car_class = driver->car_class;
  return car_class;
}

int get_driver_account_creation(DRIVER driver) {
  int account_creation = driver->account_creation;
  return account_creation;
}

enum account_status get_driver_account_status(DRIVER driver) {
  enum account_status status = driver->account_status;
  return status;
}

int get_driver_number_of_rides(DRIVER driver) {
  int number_of_rides = driver->number_of_rides;
  return number_of_rides;
}

double get_driver_total_rating(DRIVER driver) {
  double total_rating = driver->total_rating;
  return total_rating;
}

double get_driver_total_earned(DRIVER driver) {
  double total_earned = driver->total_earned;
  return total_earned;
}

int get_driver_latest_ride(DRIVER driver) {
  int latest_ride = driver->latest_ride;
  return latest_ride;
}

void free_driver(DRIVER driver) {
  free(driver->name);
  free(driver);
}
