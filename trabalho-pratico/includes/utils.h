#ifndef UTILS_H
#define UTILS_H

#include <glib.h>
#include <stdio.h>

#define MASTER_DATE "09/10/2022"

enum gender { M, F };

enum pay_method { CASH, CREDIT_CARD, DEBIT_CARD };

enum account_status { ACTIVE, INACTIVE };

enum car_class { BASIC, GREEN, PREMIUM };

char *create_filename(char *folder, const char *string);

const char *gender_to_string(int x);

const char *account_status_to_string(int x);

const char *car_class_to_string(int x);

const char *pay_method_to_string(int x);

int calculate_age(int birth_date);

int is_date_newer(int date1, int date2);

int is_date_equal(int date1, int date2);

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

#endif
