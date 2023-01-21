#include "input.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Verifies if the date follows the DD/MM/YYYY format
int verify_date_format(char* date_string) {
  if (!date_string) return 0;
  int day, month, year;
  int read = sscanf(date_string, "%d/%d/%d", &day, &month, &year);
  if (read == 3) {
    if (day > 31) return 0;
    if (month > 12) return 0;
    return 1;
  }
  return 0;
}

// Verifies if the character is a digit
int is_digit(char character) { return (character >= '0' && character <= '9'); }

// Verifies if the car class follows the format
int verify_car_class_format(char* class_string) {
  if (!class_string) return 0;

  to_lower(class_string);

  if (!strcmp("basic", class_string)) return 1;
  if (!strcmp("green", class_string)) return 1;
  if (!strcmp("premium", class_string)) return 1;

  return 0;
}

// Verifies if the account status follows the format
int verify_account_status_format(char* status_string) {
  if (!status_string) return 0;

  to_lower(status_string);

  if (!strcmp("active", status_string)) return 1;
  if (!strcmp("inactive", status_string)) return 1;

  return 0;
}

void to_lower(char* string) {
  for (int i = 0; string[i] != '\0'; i++) {
    string[i] = tolower(string[i]);
  }
}

// Verifies if the string represents a positive integer
int is_integer(char* int_string) {
  if (!int_string) return 0;
  if (int_string[0] == '\0') return 0;
  int not_zeros = 0, i;
  for (i = 0; int_string[i + 1] != '\0'; i++) {
    if (!is_digit(int_string[i])) return 0;
    if (int_string[i] != '0') not_zeros++;
  }
  if (!not_zeros && int_string[i] == '0') return 0;
  if (int_string[i] < '0' || int_string[i] > '9') return 0;
  return 1;
}

// Verifies if the string represents a positive float
int is_float(char* float_string) {
  if (!float_string) return 0;
  int dot_counter = 0;

  for (int i = 0; float_string[i] != '\0'; i++) {
    if (!is_digit(float_string[i])) {
      if (dot_counter || float_string[i] != '.') return 0;

      dot_counter++;
    }
  }

  return 1;
}
