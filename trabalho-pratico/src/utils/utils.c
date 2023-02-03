#include "utils/utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "entities/drivers.h"
#include "entities/rides.h"
#include "entities/users.h"
#include "io/parser.h"

int setup_catalog_and_stats(CATALOG catalog, STATS stats, char *folder) {
  char *users_filename = create_filename(folder, "/users.csv");
  FILE *users_file = fopen(users_filename, "r");
  if (users_file == NULL) {
    return ERR_OPENING_USERS_FILE;
  }

  char *drivers_filename = create_filename(folder, "/drivers.csv");
  FILE *drivers_file = fopen(drivers_filename, "r");
  if (drivers_file == NULL) {
    return ERR_OPENING_DRIVERS_FILE;
  }

  char *rides_filename = create_filename(folder, "/rides.csv");
  FILE *rides_file = fopen(rides_filename, "r");
  if (rides_file == NULL) {
    return ERR_OPENING_RIDES_FILE;
  }

  parse_file(users_file, MAX_USER_TOKENS, build_user, catalog, stats);
  parse_file(drivers_file, MAX_DRIVER_TOKENS, build_driver, catalog, stats);
  parse_file(rides_file, MAX_RIDE_TOKENS, build_ride, catalog, stats);

  free(users_filename);
  free(drivers_filename);
  free(rides_filename);

  fclose(users_file);
  fclose(drivers_file);
  fclose(rides_file);

  return 0;
}

char *get_error_as_string(ERRORS error) {
  switch (error) {
    case ERR_OPENING_USERS_FILE:
      return "Error opening users file!";

    case ERR_OPENING_DRIVERS_FILE:
      return "Error opening drivers file!";

    case ERR_OPENING_RIDES_FILE:
      return "Error opening rides file!";

    case ERR_CREATING_DIRECTORY:
      return "Error creating directory!";

    case ERR_OPENING_QUERIES_FILE:
      return "Error opening queries file!";

    case ERR_OPENING_OUTPUT_FILE:
      return "Error opening output file!";

    default:
      return "Unknown error.";
  }
}

char *create_filename(char *folder, const char *string) {
  char *filename = malloc(sizeof(char) * (strlen(folder) + strlen(string) + 1));
  strcpy(filename, folder);
  strcat(filename, string);

  return filename;
}

int create_directory(char *folder) {
  int ret = g_mkdir_with_parents(folder, 0777);

  if (ret == -1) {
    return ERR_CREATING_DIRECTORY;
  }

  return 0;
}

FILE *create_output_file(int queries_counter) {
  char *filename = malloc(sizeof(char) * 256);
  sprintf(filename, "Resultados/command%d_output.txt", queries_counter);

  FILE *output_file = fopen(filename, "w");
  free(filename);

  return output_file;
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
      return "credit_card";
    case DEBIT_CARD:
      return "debit_card";
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

bool is_number(char *string) {
  for (unsigned i = 0; i < strlen(string); i++) {
    if (string[i] < '0' || string[i] > '9') {
      return false;
    }
  }

  return true;
}

char *date_to_string(int date) {
  char *string = malloc(sizeof(char) * 11);
  int date_year = date / 10000;
  int date_month = (date % 10000) / 100;
  int date_day = date % 100;
  string[0] = (date_day / 10) + '0';
  string[1] = (date_day % 10) + '0';
  string[2] = '/';
  string[3] = (date_month / 10) + '0';
  string[4] = (date_month % 10) + '0';
  string[5] = '/';
  string[6] = (date_year / 1000) + '0';
  string[7] = ((date_year / 100) % 10) + '0';
  string[8] = ((date_year % 100) / 10) + '0';
  string[9] = (date_year % 10) + '0';
  string[10] = '\0';

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

char *zfill_id(int *id) {
  char *id_string = malloc(sizeof(char) * 13);
  sprintf(id_string, "%d", *id);
  char *id_string_zfilled = malloc(sizeof(char) * 13);
  sprintf(id_string_zfilled, "%012d", *id);
  free(id_string);

  return id_string_zfilled;
}
