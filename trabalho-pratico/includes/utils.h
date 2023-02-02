#ifndef UTILS_H
#define UTILS_H

#include <glib.h>
#include <stdio.h>

#include "catalog.h"
#include "stats.h"

#define MASTER_DATE "09/10/2022"

enum gender { M, F };

enum pay_method { CASH, CREDIT_CARD, DEBIT_CARD };

enum account_status { ACTIVE, INACTIVE };

enum car_class { BASIC, GREEN, PREMIUM };

typedef enum errors {
  ERR_OPENING_USERS_FILE = 1,
  ERR_OPENING_DRIVERS_FILE = 2,
  ERR_OPENING_RIDES_FILE = 3,
  ERR_OPENING_QUERIES_FILE = 4,
  ERR_CREATING_DIRECTORY = 5,
  ERR_OPENING_OUTPUT_FILE = 6,
} ERRORS;

int setup_catalog_and_stats(CATALOG catalog, STATS stats, char *folder);

char *get_error_as_string(ERRORS error);

char *create_filename(char *folder, const char *string);

FILE *create_output_file(int queries_counter);

int create_directory(char *folder);

const char *gender_to_string(int x);

const char *account_status_to_string(int x);

const char *car_class_to_string(int x);

const char *pay_method_to_string(int x);

int calculate_age(int birth_date);

int is_id_smaller(char *id1, char *id2);

int is_number(char *string);

char *date_to_string(int date);

char *strip(char *string);

void edit_strip(char *string);

gint compare_ints(gconstpointer a, gconstpointer b, gpointer data);

int increment_date(int date);

int maximum_day(int date_day, int date_month, int date_year);

int date_string_to_int(char *date_string);

enum gender string_to_gender(char *gender);

int string_to_int(char *string);

double string_to_float(char *string);

char *zfill_id(int *id);

#endif
