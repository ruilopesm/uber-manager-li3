#include <glib.h>

#include "base/querier.h"
#include "io/output.h"
#include "utils/utils.h"

#define MAX_TIME 0.01

struct query9_test_data {
  JOINT_CATALOG join_catalog;
  STATS stats;
};

static void query9_valid_dates(gconstpointer data) {
  struct query9_test_data *test_data = (struct query9_test_data *)data;

  char *line = strdup("24/12/2021 25/12/2021");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query9(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 9 - valid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf("\033[0;32mQuery 9 - valid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(30);
  write_query_result(output_file, result, '9');
  free_query_result(result, '9');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command30_output.txt";

  char *file_output =
      "./Resultados/"
      "command30_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query9_invalid_dates(gconstpointer data) {
  struct query9_test_data *test_data = (struct query9_test_data *)data;

  char *line = strdup("24/12/2027 45/12/2029");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query9(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 9 - invalid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf("\033[0;32mQuery 9 - invalid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(31);
  write_query_result(output_file, result, '9');
  free_query_result(result, '9');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command31_output.txt";

  char *file_output =
      "./Resultados/"
      "command31_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query9_large_range(gconstpointer data) {
  struct query9_test_data *test_data = (struct query9_test_data *)data;

  char *line = strdup("24/12/2019 25/12/2021");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query9(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 9 - large range - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 9 - large range - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(32);
  write_query_result(output_file, result, '9');
  free_query_result(result, '9');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command32_output.txt";

  char *file_output =
      "./Resultados/"
      "command32_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}
