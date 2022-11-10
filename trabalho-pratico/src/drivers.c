#include "drivers.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct driver {
  char *id;
  char *name;
  struct date birth_date;
  enum gender gender;
  enum car_class car_class;
  char *license_plate;
  char *city;
  struct date account_creation;
  enum account_status account_status;
};

DRIVER
create_driver(void) {
  DRIVER new_driver = malloc(sizeof(struct driver));
  new_driver->id = NULL;
  new_driver->name = NULL;
  new_driver->license_plate = NULL;
  new_driver->city = NULL;

  return new_driver;
}

void insert_driver(char **driver_params, GHashTable *hash_table) {
  DRIVER driver = create_driver();

  set_driver_id(driver, driver_params[0]);
  set_driver_name(driver, driver_params[1]);
  set_driver_birth_date(driver, driver_params[2]);
  set_driver_gender(driver, driver_params[3]);
  set_driver_car_class(driver, driver_params[4]);
  set_driver_license_plate(driver, driver_params[5]);
  set_driver_city(driver, driver_params[6]);
  set_driver_account_creation(driver, driver_params[7]);
  set_driver_account_status(driver, driver_params[8]);

  g_hash_table_insert(hash_table, driver->id, driver);
}

void set_driver_id(DRIVER driver, char *id_string) {
  driver->id = strdup(id_string);
}

void set_driver_name(DRIVER driver, char *name_string) {
  driver->name = strdup(name_string);
}

void set_driver_birth_date(DRIVER driver, char *birth_date_string) {
  struct date birth_date;
  int day, month, year;

  sscanf(birth_date_string, "%d/%d/%d", &day, &month, &year);

  birth_date.day = day;
  birth_date.month = month;
  birth_date.year = year;

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
void set_driver_license_plate(DRIVER driver, char *license_plate_string) {
  driver->license_plate = strdup(license_plate_string);
}

void set_driver_city(DRIVER driver, char *city_string) {
  driver->city = strdup(city_string);
}

void set_driver_account_creation(DRIVER driver, char *account_creation_string) {
  struct date account_creation_date;
  int day, month, year;

  sscanf(account_creation_string, "%d/%d/%d", &day, &month, &year);

  account_creation_date.day = day;
  account_creation_date.month = month;
  account_creation_date.year = year;

  driver->account_creation = account_creation_date;
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

char *get_driver_id(DRIVER driver) {
  char *id = strdup(driver->id);
  return id;
}

char *get_driver_name(DRIVER driver) {
  char *driver_name = strdup(driver->name);
  return driver_name;
}

struct date get_driver_birth_date(DRIVER driver) {
  struct date date = driver->birth_date;
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

char *get_driver_license_plate(DRIVER driver) {
  char *license_plate = strdup(driver->license_plate);
  return license_plate;
}

char *get_driver_city(DRIVER driver) {
  char *city = strdup(driver->city);
  return city;
}

struct date get_driver_account_creation(DRIVER driver) {
  struct date account_creation = driver->account_creation;
  return account_creation;
}

enum account_status get_driver_account_status(DRIVER driver) {
  enum account_status status = driver->account_status;
  return status;
}