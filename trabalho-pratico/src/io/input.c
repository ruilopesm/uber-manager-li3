#include "io/input.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Verifies if the date follows the DD/MM/YYYY format
int verify_date_format(char *date_string) {
  if (!date_string) return 0;
  int temp;
  if (is_digit(date_string[0]))
    temp = (date_string[0] - '0') * 10;
  else
    return 0;
  if (is_digit(date_string[1]))
    temp += (date_string[1] - '0');
  else
    return 0;
  if (temp > 31) return 0;
  if (is_digit(date_string[3]))
    temp = (date_string[3] - '0') * 10;
  else
    return 0;
  if (is_digit(date_string[4]))
    temp += (date_string[4] - '0');
  else
    return 0;
  if (temp > 12) return 0;
  if (!is_digit(date_string[6])) return 0;
  if (!is_digit(date_string[7])) return 0;
  if (!is_digit(date_string[8])) return 0;
  if (!is_digit(date_string[9])) return 0;

  return 1;
}

// Verifies if the character is a digit
int is_digit(char character) { return (character >= '0' && character <= '9'); }

// Verifies if the car class follows the format
int verify_car_class_format(char *class_string) {
  if (!class_string) return 0;

  to_lower(class_string);

  if (!strcmp("basic", class_string)) return 1;
  if (!strcmp("green", class_string)) return 1;
  if (!strcmp("premium", class_string)) return 1;

  return 0;
}

// Verifies if the account status follows the format
int verify_account_status_format(char *status_string) {
  if (!status_string) return 0;

  to_lower(status_string);

  if (!strcmp("active", status_string)) return 1;
  if (!strcmp("inactive", status_string)) return 1;

  return 0;
}

void to_lower(char *string) {
  for (int i = 0; string[i] != '\0'; i++) {
    string[i] = tolower(string[i]);
  }
}

// Verifies if the string represents a positive integer
int is_integer(char *int_string) {
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

// Verifies is the string represents a positive integer or zero
int is_integer_or_zero(char *int_string) {
  if (!int_string) return 0;
  if (int_string[0] == '\0') return 0;
  int i;
  for (i = 0; int_string[i + 1] != '\0'; i++) {
    if (!is_digit(int_string[i])) return 0;
  }
  if (int_string[i] < '0' || int_string[i] > '9') return 0;
  return 1;
}

// Verifies if the string represents a positive float
int is_float(char *float_string) {
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

// Format of the query: <type> <params...>
bool validate_query(char *input) {
  // type should be between 1 and 9
  if (input[0] < '1' || input[0] > '9') return false;

  // type 1: <type> <username or driver_id: string>
  if (input[0] == '1') {
    char *token = strtok(input, " ");
    token = strtok(NULL, " ");

    if (!token) return false;
  }

  // type 2: <type> <number: integer >= 0>
  if (input[0] == '2') {
    char *token = strtok(input, " ");
    token = strtok(NULL, " ");

    if (!token) return false;
    if (!is_integer_or_zero(token)) return false;
  }

  // type 3: <type> <integer >= 0>
  if (input[0] == '3') {
    char *token = strtok(input, " ");
    token = strtok(NULL, " ");

    if (!token) return false;
    if (!is_integer_or_zero(token)) return false;
  }

  // type 4: <type> <city: string>
  if (input[0] == '4') {
    char *token = strtok(input, " ");
    token = strtok(NULL, " ");

    if (!token) return false;
  }

  // type 5: <type> <date: DD/MM/YYYY> <date: DD/MM/YYYY>
  if (input[0] == '5') {
    char *token = strtok(input, " ");
    token = strtok(NULL, " ");

    if (!token) return false;
    if (!verify_date_format(token)) return false;

    token = strtok(NULL, " ");

    if (!token) return false;
    if (!verify_date_format(token)) return false;
  }

  // type 6: <type> <city: string> <date: DD/MM/YYYY> <date: DD/MM/YYYY>
  if (input[0] == '6') {
    char *token = strtok(input, " ");
    token = strtok(NULL, " ");

    if (!token) return false;

    token = strtok(NULL, " ");

    if (!token) return false;
    if (!verify_date_format(token)) return false;

    token = strtok(NULL, " ");

    if (!token) return false;
    if (!verify_date_format(token)) return false;
  }

  // type 7: <type> <number: integer >= 0> <city: string>
  if (input[0] == '7') {
    char *token = strtok(input, " ");
    token = strtok(NULL, " ");

    if (!token) return false;
    if (!is_integer_or_zero(token)) return false;

    token = strtok(NULL, " ");

    if (!token) return false;
  }

  // type 8: <type> <gender: M | F> <number: integer >= 0>
  if (input[0] == '8') {
    char *token = strtok(input, " ");
    token = strtok(NULL, " ");

    if (!token) return false;
    if (token[0] != 'M' && token[0] != 'F') return false;

    token = strtok(NULL, " ");

    if (!token) return false;
    if (!is_integer_or_zero(token)) return false;
  }

  // type 9: <type> <date: DD/MM/YYYY> <date: DD/MM/YYYY>
  if (input[0] == '9') {
    char *token = strtok(input, " ");
    token = strtok(NULL, " ");

    if (!token) return false;
    if (!verify_date_format(token)) return false;

    token = strtok(NULL, " ");

    if (!token) return false;
    if (!verify_date_format(token)) return false;
  }

  return true;
}
