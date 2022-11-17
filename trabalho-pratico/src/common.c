#include "common.h"

#include <stdlib.h>
#include <string.h>

char *create_filename(char *folder, const char *string) {
  char *filename = malloc(sizeof(char) * (strlen(folder) + strlen(string) + 1));
  strcpy(filename, folder);
  strcat(filename, string);

  return filename;
}

const char *gender_to_string(int x) {
  switch ((enum gender)x) {
    case M:
      return "M";
    case F:
      return "F";
  }

  return "NULL";
}

const char *pay_method_to_string(int x) {
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

const char *account_status_to_string(int x) {
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

int calculate_age(struct date birth_date) {
  int age = 0;

  const char *master_date = MASTER_DATE;
  int day, month, year;
  sscanf(master_date, "%d/%d/%d", &day, &month, &year);

  age = year - birth_date.year;

  if (month < birth_date.month) {
    age--;
  } else if (month == birth_date.month) {
    if (day < birth_date.day) {
      age--;
    }
  }

  return age;
}

int is_date_newer(struct date date1, struct date date2) {
  if (date1.year > date2.year) {
    return 1;
  } else if (date1.year == date2.year) {
    if (date1.month > date2.month) {
      return 1;
    } else if (date1.month == date2.month) {
      if (date1.day > date2.day) {
        return 1;
      }
    }
  }

  return 0;
}

int is_date_equal(struct date date1, struct date date2) {
  if (date1.year == date2.year && date1.month == date2.month &&
      date1.day == date2.day) {
    return 1;
  }

  return 0;
}

int is_id_smaller(char *id1, char *id2) {
  int id1_int = atoi(id1);
  int id2_int = atoi(id2);

  if (id1_int < id2_int) {
    return 1;
  }

  return 0;
}

int is_number(char *string) {
  for (unsigned i = 0; i < strlen(string); i++) {
    if (string[i] < '0' || string[i] > '9') {
      return 0;
    }
  }

  return 1;
}
