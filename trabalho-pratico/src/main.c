#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "catalog.h"
#include "common.h"
#include "drivers.h"
#include "parser.h"
#include "querier.h"
#include "rides.h"
#include "stats.h"
#include "users.h"

int main(int argc, char **argv) {
  double time_spent = 0.0;
  clock_t begin = clock();

  if (argc != 3) {
    printf("Usage: %s <folder> <file>\n", argv[0]);
    return 1;
  }

  char *folder = argv[1];
  char *users_filename = create_filename(folder, "/users.csv");
  char *drivers_filename = create_filename(folder, "/drivers.csv");
  char *rides_filename = create_filename(folder, "/rides.csv");

  FILE *users_file = fopen(users_filename, "r");
  FILE *drivers_file = fopen(drivers_filename, "r");
  FILE *rides_file = fopen(rides_filename, "r");
  FILE *queries_file = fopen(argv[2], "r");

  if (users_file == NULL || drivers_file == NULL || rides_file == NULL ||
      queries_file == NULL) {
    printf("Error opening input files\n");
    return 1;
  }

  CATALOG catalog = create_catalog();
  STATS stats = create_stats();

  parse_file(users_file, MAX_USER_TOKENS, insert_user, catalog, stats);
  parse_file(drivers_file, MAX_DRIVER_TOKENS, insert_driver, catalog, stats);
  parse_file(rides_file, MAX_RIDE_TOKENS, insert_ride, catalog, stats);

  // Create output directory
  int ret = g_mkdir_with_parents("Resultados", 0777);

  if (ret == -1) {
    printf("Error creating output directory\n");
    return 1;
  }

  char *line = malloc(sizeof(char) * MAX_LINE_LENGTH);
  int counter = 1;

  while (fgets(line, MAX_LINE_LENGTH, queries_file)) {
    querier(catalog, stats, line, counter);
    counter++;
  }

  free(line);

  fclose(users_file);
  fclose(drivers_file);
  fclose(rides_file);

  free(users_filename);
  free(drivers_filename);
  free(rides_filename);

  free_catalog(catalog);

  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Elapsed time: %f seconds\n", time_spent);
  return 0;
}
