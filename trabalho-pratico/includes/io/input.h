#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

/**
 * @brief Function that verifies if the date format is valid
 *
 * @param date_string - The date string to be verified of type `char*`
 *
 * @return 1 if the date format is valid, 0 otherwise
 */
int verify_date_format(char* date_string);

/**
 * @brief Function that verifies if the the given argument is a digit
 *
 * @param character - The character to be verified of type `char`
 *
 * @return 1 if the character is a digit, 0 otherwise
 */
int is_digit(char character);

/**
 * @brief Function that verifies if the car class follows the format
 *
 * @param class_string - The car class string to be verified of type `char*`
 *
 * @return 1 if the character is a letter, 0 otherwise
 */
int verify_car_class_format(char* class_string);

/**
 * @brief Function that verifies if the account_status follows the format
 *
 * @param status_string - The account_status string to be verified of type
 *
 * @return 1 if it follows the format, 0 otherwise
 */
int verify_account_status_format(char* status_string);

/**
 * @brief Function that lowercases the given string
 *
 * @param string - The string to be lowercased of type `char*`
 */
void to_lower(char* string);

/**
 * @brief Function that verifies if the given string is a valid integer
 *
 * @param int_string - The string to be verified of type `char*`
 *
 * @return 1 if the string is a valid integer, 0 otherwise
 */
int is_integer(char* int_string);

/**
 * @brief Function that verifies if the given string is a valid float
 *
 * @param float_string - The string to be verified of type `char*`
 *
 * @return 1 if the string is a valid float, 0 otherwise
 */
int is_float(char* float_string);

/**
 * @brief Function that verifies if the given string is a valid integer or zero
 *
 * @param int_string - The string to be verified of type `char*`
 *
 * @return 1 if the string is a valid integer or zero, 0 otherwise
 */
int is_integer_or_zero(char* int_string);

/**
 * @brief Function that verifies if the given string is a valid query
 *
 * @param query - The string to be verified of type `char*`
 *
 * @return 1 if the string is a valid query, 0 otherwise
 */
bool validate_query(char* query);

#endif
