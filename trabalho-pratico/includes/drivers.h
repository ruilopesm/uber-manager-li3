#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>

#include "common.h"

#define MAX_DRIVER_TOKENS 9

typedef struct driver *DRIVER;

DRIVER create_driver(void);

void insert_driver(char **driver_params, GHashTable *hash_table);

void set_driver_id(DRIVER driver, char *id_string);

void set_driver_name(DRIVER driver, char *name_string);

void set_driver_birth_date(DRIVER driver, char *birth_date_string);

void set_driver_gender(DRIVER driver, char *gender_string);

void set_driver_car_class(DRIVER driver, char *car_class_string);

void set_driver_license_plate(DRIVER driver, char *license_plate_string);

void set_driver_city(DRIVER driver, char *city_string);

void set_driver_account_creation(DRIVER driver, char *account_creation_string);

void set_driver_account_status(DRIVER driver, char *account_status_string);

char *get_driver_id(DRIVER driver);

char *get_driver_name(DRIVER driver);

struct date get_driver_birth_date(DRIVER driver);

enum gender get_driver_gender(DRIVER driver);

enum car_class get_driver_car_class(DRIVER driver);

char *get_driver_license_plate(DRIVER driver);

char *get_driver_city(DRIVER driver);

struct date get_driver_account_creation(DRIVER driver);

enum account_status get_driver_account_status(DRIVER driver);

void free_driver(DRIVER driver);

#endif
