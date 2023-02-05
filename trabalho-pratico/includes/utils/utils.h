#ifndef UTILS_H
#define UTILS_H

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief enum that holds the gender possible values - M or F
 *
 */
enum gender { M, F };

/**
 * @brief enum that holds the car class possible values - BASIC, GREEN or
 * PREMIUM
 *
 */
enum car_class { BASIC, GREEN, PREMIUM };

/**
 * @brief enum that holds the account status possible values - ACTIVE or
 * INACTIVE
 *
 */
enum account_status { ACTIVE, INACTIVE };

#include "base/stats.h"
#include "catalogs/joint_catalog.h"

typedef struct joint_catalog *JOINT_CATALOG;  // Forward declaration

typedef struct stats *STATS;  // Forward declaration

#define MASTER_DATE "09/10/2022"

/**
 * @brief enum that holds the possible errors - ERR_OPENING_USERS_FILE,
 * ERR_OPENING_DRIVERS_FILE, ERR_OPENING_RIDES_FILE, ERR_OPENING_QUERIES_FILE,
 * ERR_CREATING_DIRECTORY, ERR_OPENING_OUTPUT_FILE
 *
 */
typedef enum errors {
  ERR_OPENING_USERS_FILE = 1,
  ERR_OPENING_DRIVERS_FILE = 2,
  ERR_OPENING_RIDES_FILE = 3,
  ERR_OPENING_QUERIES_FILE = 4,
  ERR_CREATING_DIRECTORY = 5,
  ERR_OPENING_OUTPUT_FILE = 6,
} ERRORS;

/**
 * @brief Function that setups catalog and stats
 *
 * @param catalog The join catalog of type `JOINT_CATALOG`
 * @param stats The stats of type `STATS`
 * @param folder The folder of type `char *`
 * @return int 1 if the setup was successful, 0 otherwise
 */
int setup_catalog_and_stats(JOINT_CATALOG catalog, STATS stats, char *folder);

/**
 * @brief Function that gets the error as a string
 *
 * @param error The error of type `ERRORS`
 * @return char * The error as a string
 */
char *get_error_as_string(ERRORS error);

/**
 * @brief Function that gets the error as a string
 *
 * @param error The error of type `ERRORS`
 * @return char * The error as a string
 */
char *create_filename(char *folder, const char *string);

/**
 * @brief Function that creates the output file
 *
 * @param queries_counter The queries counter of type `int`
 * @return FILE * The output file
 */
FILE *create_output_file(int queries_counter);

/**
 * @brief Function that creates the directory
 *
 * @param folder The folder of type `char *`
 * @return int 1 if the directory was created, 0 otherwise
 */
int create_directory(char *folder);

/**
 * @brief Function that translates an enum gender to a string
 *
 * @param x An integer representing the enum
 * @return const char * The string
 */
const char *gender_to_string(int x);

/**
 * @brief Function that translates an enum account status to a string
 *
 * @param x An integer representing the enum
 * @return const char * The string
 */
const char *account_status_to_string(int x);

/**
 * @brief Function that translates an enum car class to a string
 *
 * @param x An integer representing the enum
 * @return const char * The string
 */
const char *car_class_to_string(int x);

/**
 * @brief Function that calculates the age of a user
 *
 * @param birth_date The birth date of type `int`
 * @return int The age
 */
int calculate_age(int birth_date);

/**
 * @brief Function that checks if a string is a number
 *
 * @param string The string of type `char *` to check
 * @return bool 1 if the string is a number, 0 otherwise
 */
bool is_number(char *string);

/**
 * @brief Function that converts a date represented by an integer to a date
 * represented by a string
 *
 * @param date The date of type `int`
 * @return char * The converted date
 */
char *date_to_string(int date);

/**
 * @brief Function that increments a date represented by an integer
 *
 * @param date The date of type `int`
 * @return int The incremented date
 */
int increment_date(int date);

/**
 * @brief Function that checks if the maximum day of a date has been reached
 *
 * @param date_day The day of the date of type `int`
 * @param date_month The month of the date of type `int`
 * @param date_year The year of the date of type `int`
 * @return int 1 if the maximum day has been reached, 0 otherwise
 */
int maximum_day(int date_day, int date_month, int date_year);

/**
 * @brief Function that converts a date represented by a string to a date
 * represented by an integer
 *
 * @param date_string The date of type `char *`
 * @return int The converted date
 */
int date_string_to_int(char *date_string);

/**
 * @brief Function that converts a gender represented by a string to a gender
 * represented by an enum
 *
 * @param gender The gender of type `char *`
 * @return enum gender The converted gender
 */
enum gender string_to_gender(char *gender);

/**
 * @brief Function that converts a string to an array of strings
 *
 * @param line The string of type `char *`
 * @return char** The array of strings
 */
char **string_to_array(char *line);

/**
 * @brief Function that compares two files
 *
 * @param file1 The first file path of type `char *`
 * @param file2 The second file path of type `char *`
 * @return int 1 if the files are equal, 0 otherwise
 */
int compare_files(char *file1, char *file2);

/**
 * @brief Function that converts a string to a valid integer
 *
 * @param string The string of type `char *`
 * @return int The converted integer
 */
int string_to_int(char *string);

/**
 * @brief Function that converts a string to a valid double
 *
 * @param string The string of type `char *`
 * @return double The converted double
 */
double string_to_float(char *string);

/**
 * @brief Function that zero fills an id
 *
 * @param id The id of type `int`
 * @return char* The zero filled id
 */
char *zfill_id(int *id);

#endif
