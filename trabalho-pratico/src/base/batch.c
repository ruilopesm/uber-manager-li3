#include "base/batch.h"

int batch(char **argv) {
  // Catalogs and stats part
  USERS_CATALOG users_catalog = create_users_catalog();
  DRIVERS_CATALOG drivers_catalog = create_drivers_catalog();
  RIDES_CATALOG rides_catalog = create_rides_catalog();
  JOIN_CATALOG join_catalog =
      create_join_catalog(users_catalog, drivers_catalog, rides_catalog);
  STATS stats = create_stats();

  if (setup_catalog_and_stats(join_catalog, stats, argv[1]) == -1) {
    return -1;
  }

  // Queries part
  char *queries_filename = argv[2];
  FILE *queries_file = fopen(queries_filename, "r");
  if (queries_file == NULL) {
    return ERR_OPENING_QUERIES_FILE;
  }

  // Create output directory
  if (create_directory("Resultados") != 0) {
    return ERR_CREATING_DIRECTORY;
  }

  char *line = NULL;
  size_t line_size = 0;
  int queries_counter = 1;

  while (getline(&line, &line_size, queries_file) != -1) {
    // Remove \n from the end of line
    line[strlen(line) - 1] = '\0';

    void *result = querier(join_catalog, stats, line);

    FILE *output_file = create_output_file(queries_counter);
    if (output_file == NULL) {
      return ERR_OPENING_OUTPUT_FILE;
    }

    write_query_result(output_file, result, line[0]);
    free_query_result(result, line[0]);

    fclose(output_file);
    queries_counter++;
  }

  free(line);
  fclose(queries_file);

  free_users_catalog(users_catalog);
  free_drivers_catalog(drivers_catalog);
  free_rides_catalog(rides_catalog);
  free_join_catalog(join_catalog);
  free_stats(stats);

  return 0;
}
