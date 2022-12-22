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

char *date_to_string(struct date date) {
  char *string = malloc(sizeof(char) * 11);
  sprintf(string, "%02d/%02d/%04d", date.day, date.month, date.year);

  return string;
}

// function that return a duplicate version of the string without spaces and
// '\n' characters
char *strip(char *string) {
  char *stripped = malloc(sizeof(char) * (strlen(string) + 1));
  int j = 0;

  for (unsigned i = 0; i < strlen(string); i++) {
    if (string[i] != ' ' && string[i] != '\n') {
      stripped[j] = string[i];
      j++;
    }
  }

  stripped[j] = '\0';

  return stripped;
}

// If the first date is later, returns a positive number, if it's sooner,
// returns a negative one, if the dates are the same returns 0
int compare_dates(struct date date1, struct date date2) {
  int temp =
      date1.year - date2.year;  // If temp is positive, date1 is later than
                                // date2, if it's negative the reverse is true
                                // and if it's 0 the years are the same
  // Compare if the year is the same, if so compare months in the same way
  if (temp)
    return temp;  // If temp is 0 the years are the same and therefore moves on
                  // to the next criteria, else returns temp
  temp = date1.month - date2.month;
  if (temp) return temp;
  return date1.day - date2.day;  // If the dates are the same year and month the
                                 // result is decided by the day differential
}

// Moves the date to the next day
struct date increment_date(struct date date) {
  if (maximum_day(date)) {
    date.day = 1;
    if (date.month == 12) {
      date.year++;
      date.month = 1;
    } else
      date.month++;
  } else
    date.day++;
  return date;
}

// Returns 1 if the maximum day of that month has been reached, 0 if not
int maximum_day(struct date date) {
  return date.day ==
         31 - (!((date.month % 7) % 2)) + (date.month == 7) -
             (date.month == 2) -
             (date.month == 2) *
                 ((date.year % 4) || (!(date.year % 100) && (date.year % 400)));
}

struct date date_string_to_struct(char *date_string) {
  char day[3];
  day[0] = date_string[0];
  day[1] = date_string[1];
  day[2] = '\0';

  char month[3];
  month[0] = date_string[3];
  month[1] = date_string[4];
  month[2] = '\0';

  char year[5];
  year[0] = date_string[6];
  year[1] = date_string[7];
  year[2] = date_string[8];
  year[3] = date_string[9];
  year[4] = '\0';

  struct date date;
  date.day = atoi(day);
  date.month = atoi(month);
  date.year = atoi(year);

  return date;
}

gint compare_strings(gconstpointer a, gconstpointer b, gpointer data) {
  gint result = strcmp(a, b);
  return result;

  (void)data;
}
