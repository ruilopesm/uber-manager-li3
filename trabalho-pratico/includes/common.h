#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#define MASTER_DATE "09/10/2022"

struct date {
  int day;
  int month;
  int year;
};

enum gender { M, F };

enum pay_method { CASH, CREDIT_CARD, DEBIT_CARD };

enum account_status { ACTIVE, INACTIVE };

enum car_class { BASIC, GREEN, PREMIUM };

char *create_filename(char *folder, const char *string);

const char *gender_to_string(int x);

const char *account_status_to_string(int x);

const char *car_class_to_string(int x);

const char *pay_method_to_string(int x);

int calculate_age(struct date birth_date);

int is_date_newer(struct date date1, struct date date2);

int is_date_equal(struct date date1, struct date date2);

int is_id_smaller(char *id1, char *id2);

int is_number(char *string);

#endif
