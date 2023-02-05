#include <glib.h>

#include "base/querier.h"
#include "io/output.h"
#include "utils/utils.h"

struct query5_test_data {
  JOINT_CATALOG catalog;
  STATS stats;
};

#define MAX_TIME 0.01

static void query5_valid_dates(gconstpointer data) {
  struct query5_test_data *test_data = (struct query5_test_data *)data;

  char *line = strdup("01/01/2020 01/01/2021");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query5(test_data->catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 5 - valid dates - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 5 - valid dates - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(15);
  write_query_result(output_file, result, '5');
  free_query_result(result, '5');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command15_output.txt";

  char *file_output =
      "./Resultados/"
      "command15_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query5_invalid_dates(gconstpointer data) {
  struct query5_test_data *test_data = (struct query5_test_data *)data;

  char *line = strdup("41/01/2020 01/01/2027");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query5(test_data->catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 5 - invalid dates - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 5 - invalid dates - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(16);
  write_query_result(output_file, result, '5');
  free_query_result(result, '5');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command16_output.txt";

  char *file_output =
      "./Resultados/"
      "command16_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query5_large_range(gconstpointer data) {
  struct query5_test_data *test_data = (struct query5_test_data *)data;

  char *line = strdup("01/01/1999 01/01/2040");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query5(test_data->catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 5 - large range - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 5 - large range - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(17);
  write_query_result(output_file, result, '5');
  free_query_result(result, '5');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command17_output.txt";

  char *file_output =
      "./Resultados/"
      "command17_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}
