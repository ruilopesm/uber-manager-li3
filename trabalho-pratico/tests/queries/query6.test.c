#include <glib.h>

#include "base/querier.h"
#include "io/output.h"
#include "utils/utils.h"

struct query6_test_data {
  JOIN_CATALOG join_catalog;
  STATS stats;
};

#define MAX_TIME 0.01

static void query6_valid_city_and_dates(gconstpointer data) {
  struct query6_test_data *test_data = (struct query6_test_data *)data;

  char *line = strdup("Porto 01/01/2021 01/02/2021");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query6(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 6 - valid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf("\033[0;32mQuery 6 - valid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(18);
  write_query_result(output_file, result, '6');
  free_query_result(result, '6');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command18_output.txt";

  char *file_output =
      "./Resultados/"
      "command18_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query6_invalid_city(gconstpointer data) {
  struct query6_test_data *test_data = (struct query6_test_data *)data;

  char *line = strdup("Leiria 01/01/2021 01/02/2022");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query6(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 6 - invalid city - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf("\033[0;32mQuery 6 - valid city - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(19);
  write_query_result(output_file, result, '6');
  free_query_result(result, '6');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command19_output.txt";

  char *file_output =
      "./Resultados/"
      "command19_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query6_invalid_dates(gconstpointer data) {
  struct query6_test_data *test_data = (struct query6_test_data *)data;

  char *line = strdup("Porto 41/01/2020 01/02/2025");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query6(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 6 - invalid dates - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 6 - valid dates - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(20);
  write_query_result(output_file, result, '6');
  free_query_result(result, '6');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command20_output.txt";

  char *file_output =
      "./Resultados/"
      "command20_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query6_large_range(gconstpointer data) {
  struct query6_test_data *test_data = (struct query6_test_data *)data;

  char *line = strdup("Porto 01/01/1999 01/01/2040");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query6(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 6 - large range - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 6 - large range - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(21);
  write_query_result(output_file, result, '6');
  free_query_result(result, '6');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command21_output.txt";

  char *file_output =
      "./Resultados/"
      "command21_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}
