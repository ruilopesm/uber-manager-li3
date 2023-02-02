#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

int verify_date_format(char* date_string);

int is_digit(char character);

int verify_car_class_format(char* class_string);

int verify_account_status_format(char* status_string);

void to_lower(char* string);

int is_integer(char* int_string);

int is_float(char* float_string);

int is_integer_or_zero(char* int_string);

bool validate_query(char* query);

#endif