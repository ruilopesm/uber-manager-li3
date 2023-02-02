#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>

#include "base/catalog.h"
#include "base/stats.h"
#include "utils/utils.h"

#define MAX_DRIVER_TOKENS 9

typedef struct driver *DRIVER;

DRIVER create_driver(void);

void insert_driver(char **driver_params, CATALOG catalog, STATS stats);

void set_driver_id(DRIVER driver, char *id_string);

void set_driver_name(DRIVER driver, char *name_string);

void set_driver_birth_date(DRIVER driver, char *birth_date_string);

void set_driver_gender(DRIVER driver, char *gender_string);

void set_driver_car_class(DRIVER driver, char *car_class_string);

void set_driver_account_creation(DRIVER driver, char *account_creation_string);

void set_driver_account_status(DRIVER driver, char *account_status_string);

void set_driver_number_of_rides(DRIVER driver, int number_of_rides);

void set_driver_total_rating(DRIVER driver, double total_rating);

void set_driver_total_earned(DRIVER driver, double total_earned);

void set_driver_latest_ride(DRIVER driver, int latest_ride_string);

int get_driver_id(DRIVER driver);

char *get_driver_name(DRIVER driver);

int get_driver_birth_date(DRIVER driver);

enum gender get_driver_gender(DRIVER driver);

enum car_class get_driver_car_class(DRIVER driver);

int get_driver_account_creation(DRIVER driver);

enum account_status get_driver_account_status(DRIVER driver);

int get_driver_number_of_rides(DRIVER driver);

double get_driver_total_rating(DRIVER driver);

double get_driver_total_earned(DRIVER driver);

int get_driver_latest_ride(DRIVER driver);

void free_driver(DRIVER driver);

int verify_driver_input(char **parameters);

#endif
