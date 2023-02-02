#include "batch.h"

#include "catalog.h"
#include "drivers.h"
#include "output.h"
#include "parser.h"
#include "querier.h"
#include "rides.h"
#include "stats.h"
#include "users.h"
#include "utils.h"

int batch(char **argv) {
  CATALOG catalog = create_catalog();
  STATS stats = create_stats();

  if (setup_catalog_and_stats(catalog, stats, argv[1]) == -1) {
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

  char *line = malloc(sizeof(char) * MAX_LINE_LENGTH);
  int queries_counter = 1;

  while (fgets(line, MAX_LINE_LENGTH, queries_file)) {
    // Remove \n from the end of line
    line[strlen(line) - 1] = '\0';

    void *result = querier(catalog, stats, line);

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

  free_catalog(catalog);
  free_stats(stats);

  return 0;
}
