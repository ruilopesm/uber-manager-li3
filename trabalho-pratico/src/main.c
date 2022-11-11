#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "drivers.h"
#include "parser.h"
#include "rides.h"
#include "users.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <folder>\n", argv[0]);
    return 1;
  }

  char *folder = argv[1];
  char *users_filename = create_filename(folder, "/users.csv");
  char *drivers_filename = create_filename(folder, "/drivers.csv");
  char *rides_filename = create_filename(folder, "/rides.csv");

  FILE *users_file = fopen(users_filename, "r");
  FILE *drivers_file = fopen(drivers_filename, "r");
  FILE *rides_file = fopen(rides_filename, "r");

  if (users_file == NULL || drivers_file == NULL || rides_file == NULL) {
    printf("Error opening files\n");
    return 1;
  }

  GHashTable *users_hash_table = g_hash_table_new_full(
      g_str_hash, g_str_equal, free, (GDestroyNotify)free_user);
  GHashTable *drivers_hash_table = g_hash_table_new_full(
      g_str_hash, g_str_equal, free, (GDestroyNotify)free_driver);
  GHashTable *rides_hash_table = g_hash_table_new_full(
      g_str_hash, g_str_equal, free, (GDestroyNotify)free_ride);

  parse_file(users_file, MAX_USER_TOKENS, insert_user, users_hash_table);
  parse_file(drivers_file, MAX_DRIVER_TOKENS, insert_driver,
             drivers_hash_table);
  parse_file(rides_file, MAX_RIDE_TOKENS, insert_ride, rides_hash_table);

  // Testing purposes
  USER user = g_hash_table_lookup(users_hash_table, "JorgMiranda");

  if (user != NULL) {
    printf("User: %s\n", get_user_name(user));
  } else {
    printf("User not found\n");
  }

  DRIVER driver = g_hash_table_lookup(drivers_hash_table, "000000000002");

  if (driver != NULL) {
    printf("Driver: %s\n", get_driver_name(driver));
  } else {
    printf("Driver not found\n");
  }

  RIDE ride = g_hash_table_lookup(rides_hash_table, "000000000001");

  if (ride != NULL) {
    printf("Ride: %s\n", get_ride_driver(ride));
  } else {
    printf("Ride not found\n");
  }

  fclose(users_file);
  fclose(drivers_file);
  fclose(rides_file);

  free(users_filename);
  free(drivers_filename);
  free(rides_filename);

  g_hash_table_destroy(users_hash_table);
  g_hash_table_destroy(drivers_hash_table);
  g_hash_table_destroy(rides_hash_table);

  return 0;
}
