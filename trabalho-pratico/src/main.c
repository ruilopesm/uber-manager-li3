#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char *users_filename =
      malloc(sizeof(char) * (strlen(folder) + strlen("/users.csv") + 1));
  char *drivers_filename =
      malloc(sizeof(char) * (strlen(folder) + strlen("/drivers.csv") + 1));
  char *rides_filename =
      malloc(sizeof(char) * (strlen(folder) + strlen("/rides.csv") + 1));

  strcpy(users_filename, folder);
  strcpy(drivers_filename, folder);
  strcpy(rides_filename, folder);

  strcat(users_filename, "/users.csv");
  strcat(drivers_filename, "/drivers.csv");
  strcat(rides_filename, "/rides.csv");

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

  char *line = malloc(sizeof(char) * MAX_LINE_LENGTH);

  while (fgets(line, MAX_LINE_LENGTH, users_file)) {
    char **tokens = parse_line(line, MAX_USER_TOKENS);
    insert_user(tokens, users_hash_table);

    free(tokens);
  }

  while (fgets(line, MAX_LINE_LENGTH, drivers_file)) {
    char **tokens = parse_line(line, MAX_DRIVER_TOKENS);
    insert_driver(tokens, drivers_hash_table);

    free(tokens);
  }

  while (fgets(line, MAX_LINE_LENGTH, rides_file)) {
    char **tokens = parse_line(line, MAX_RIDE_TOKENS);
    insert_ride(tokens, rides_hash_table);

    free(tokens);
  }

  free(line);

  USER user = g_hash_table_lookup(users_hash_table, "JorgMiranda");

  if (user != NULL) {
    printf("User: %s\n", get_user_name(user));
  }

  DRIVER driver = g_hash_table_lookup(drivers_hash_table, "000000000002");

  if (driver != NULL) {
    printf("Driver: %s\n", get_driver_name(driver));
  }

  RIDE ride = g_hash_table_lookup(rides_hash_table, "000000000001");

  if (ride != NULL) {
    printf("Ride: %s\n", get_ride_driver(ride));
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
