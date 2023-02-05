#include <glib.h>

#include "base/querier.h"
#include "io/output.h"
#include "utils/utils.h"

#define MAX_TIME 0.01

struct query4_test_data {
  JOIN_CATALOG catalog;
  STATS stats;
};

static void query4_valid_city(gconstpointer data) {
  struct query4_test_data *test_data = (struct query4_test_data *)data;

  char *line = strdup("Porto");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query4(test_data->catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 4 - valid city - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf("\033[0;32mQuery 4 - valid city - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(13);
  write_query_result(output_file, result, '4');
  free_query_result(result, '4');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command13_output.txt";

  char *file_output =
      "./Resultados/"
      "command13_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query4_invalid_city(gconstpointer data) {
  struct query4_test_data *test_data = (struct query4_test_data *)data;

  char *line = strdup("Leiria");
  char **params = string_to_array(line);

  clock_t begin = clock();
  void *result = query4(test_data->catalog, test_data->stats, params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 4 - invalid city - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 4 - invalid city - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(14);
  write_query_result(output_file, result, '4');
  free_query_result(result, '4');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command14_output.txt";

  char *file_output =
      "./Resultados/"
      "command14_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}
