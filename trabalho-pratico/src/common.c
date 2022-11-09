#include "common.h"

const char *gender_to_string(int x) {
  switch ((enum gender)x) {
    case M:
      return "M";
    case F:
      return "F";
  }

  return "NULL";
}

const char* pay_method_to_string(int x) {
  switch ((enum pay_method)x) {
    case CASH:
      return "cash";
    case CREDIT_CARD:
      return "credit card";
    case DEBIT_CARD:
      return "debit card";
  }

  return "NULL";
}

const char* account_status_to_string(int x) {
  switch ((enum account_status)x) {
    case ACTIVE:
      return "active";
    case INACTIVE:
      return "inactive";
  }

  return "NULL";
}

const char *car_class_to_string(int x) {
  switch ((enum car_class)x) {
    case BASIC:
      return "basic";
    case GREEN:
      return "green";
    case PREMIUM:
      return "premium";
  }

  return "NULL";
}
