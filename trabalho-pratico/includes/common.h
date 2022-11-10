#ifndef COMMON_H
#define COMMON_H

struct date {
  int day;
  int month;
  int year;
};

enum gender { M, F };

enum pay_method { CASH, CREDIT_CARD, DEBIT_CARD };

enum account_status { ACTIVE, INACTIVE };

enum car_class { BASIC, GREEN, PREMIUM };

const char *gender_to_string(int x);

const char *account_status_to_string(int x);

const char *car_class_to_string(int x);

const char *pay_method_to_string(int x);

#endif
