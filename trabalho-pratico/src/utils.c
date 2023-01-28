#include "utils.h"

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

int calculate_age(int birth_date) {
  int age = 0;
  int birth_date_year = birth_date / 10000;
  int birth_date_month = (birth_date % 10000) / 100;
  int birth_date_day = birth_date % 100;

  const char *master_date = MASTER_DATE;
  int day = 0, month = 0, year = 0;

  day = (master_date[0] - '0') * 10;
  day += (master_date[1] - '0');

  month = (master_date[3] - '0') * 10;
  month += (master_date[4] - '0');

  year = (master_date[6] - '0') * 1000;
  year += (master_date[7] - '0') * 100;
  year += (master_date[8] - '0') * 10;
  year += (master_date[9] - '0');

  age = year - birth_date_year;

  if (month < birth_date_month) {
    age--;
  } else if (month == birth_date_month) {
    if (day < birth_date_day) {
      age--;
    }
  }

  return age;
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

char *date_to_string(int date) {
  char *string = malloc(sizeof(char) * 11);
  int date_year = date / 10000;
  int date_month = (date % 10000) / 100;
  int date_day = date % 100;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-overflow"
  sprintf(string, "%02d/%02d/%04d", date_day, date_month, date_year);
#pragma GCC diagnostic pop

  return string;
}

// function that return a duplicate version of the string without spaces and
// '\n' characters
char *strip(char *string) {
  char *stripped = malloc(sizeof(char) * (strlen(string) + 1));
  int j = 0;

  for (unsigned i = 0; i < strlen(string); i++) {
    if (string[i] != ' ' && string[i] != '\n' && string[i] != '\r') {
      stripped[j] = string[i];
      j++;
    }
  }

  stripped[j] = '\0';

  return stripped;
}

// function that edits the string to remove spaces and '\n' characters
void edit_strip(char *string) {
  int j = 0;
  unsigned i;

  for (i = 0; string[i] != '\0'; i++) {
    if (string[i] != '\n' && string[i] != '\r' && string[i] != '\t' &&
        string[i] != '\v' && string[i] != '\f') {
      string[i - j] = string[i];
    } else
      j++;
  }
  string[i - j + 1] = '\0';
}

// Moves the date to the next day
int increment_date(int date) {
  int date_year = date / 10000;
  int date_month = (date % 10000) / 100;
  int date_day = date % 100;
  if (maximum_day(date_day, date_month, date_year)) {
    date_day = 1;
    if (date_month == 12) {
      date_year++;
      date_month = 1;
    } else
      date_month++;
  } else
    date_day++;
  date = date_year * 10000 + date_month * 100 + date_day;
  return date;
}

// Returns 1 if the maximum day of that month has been reached, 0 if not
int maximum_day(int date_day, int date_month, int date_year) {
  return date_day ==
         31 - (!((date_month % 7) % 2)) + (date_month == 7) -
             (date_month == 2) -
             (date_month == 2) *
                 ((date_year % 4) || (!(date_year % 100) && (date_year % 400)));
}

int date_string_to_int(char *date_string) {
  char date[9];
  date[0] = date_string[6];
  date[1] = date_string[7];
  date[2] = date_string[8];
  date[3] = date_string[9];
  date[4] = date_string[3];
  date[5] = date_string[4];
  date[6] = date_string[0];
  date[7] = date_string[1];
  date[8] = '\0';

  int date_int;
  date_int = atoi(date);

  return date_int;
}

gint compare_ints(gconstpointer a, gconstpointer b, gpointer data) {
  gint result = *(int *)a - *(int *)b;
  return result;

  (void)data;
}

enum gender string_to_gender(char *gender) {
  if (!strcmp(gender, "M")) {
    return M;
  } else {
    return F;
  }
}

int string_to_int(char *string) {
  int value = 0;
  for (int i = 0; string[i] != '\0'; i++) {
    value *= 10;
    value += string[i] - '0';
  }
  return value;
}

double string_to_float(char *string) {
  double value = 0;
  int i;
  for (i = 0; string[i] != '.'; i++) {
    value *= 10;
    value += string[i] - '0';
  }
  double temp = 1;
  i++;
  while (string[i] != '\0') {
    double digit = (string[i] - '0');
    value += digit / (10 * temp);
    temp++;
    i++;
  }
  return value;
}
