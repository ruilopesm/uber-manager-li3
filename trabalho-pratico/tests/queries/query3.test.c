#include <glib.h>

#include "base/querier.h"
#include "io/output.h"
#include "utils/utils.h"

#define MAX_TIME 0.01

struct query3_test_data {
  JOIN_CATALOG catalog;
  STATS stats;
};

static void query3_0_elements(gconstpointer data) {
  struct query3_test_data *query_data = (struct query3_test_data *)data;

  char *line = strdup("0");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query3(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 3 - 0 elements - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf(
        "\033[0;32mQuery 3 - 0 elements - valid elapsed time: %f "
        "seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(9);
  write_query_result(output_file, result, '3');
  free_query_result(result, '3');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command9_output.txt";

  char *file_output =
      "./Resultados/"
      "command9_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query3_10_elements(gconstpointer data) {
  struct query3_test_data *query_data = (struct query3_test_data *)data;

  char *line = strdup("10");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query3(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 3 - 10 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 3 - 10 elements - valid elapsed time: %f "
        "seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(10);
  write_query_result(output_file, result, '3');
  free_query_result(result, '3');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command10_output.txt";

  char *file_output =
      "./Resultados/"
      "command10_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query3_100_elements(gconstpointer data) {
  struct query3_test_data *query_data = (struct query3_test_data *)data;

  char *line = strdup("100");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query3(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 3 - 100 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 3 - 100 elements - valid elapsed time: %f "
        "seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(11);
  write_query_result(output_file, result, '3');
  free_query_result(result, '3');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command11_output.txt";

  char *file_output =
      "./Resultados/"
      "command11_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query3_500_elements(gconstpointer data) {
  struct query3_test_data *query_data = (struct query3_test_data *)data;

  char *line = strdup("500");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query3(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 3 - 500 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 3 - 500 elements - valid elapsed time: %f "
        "seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(12);
  write_query_result(output_file, result, '3');
  free_query_result(result, '3');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command12_output.txt";

  char *file_output =
      "./Resultados/"
      "command12_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}