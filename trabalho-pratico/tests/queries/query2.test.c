#include <glib.h>

#include "base/querier.h"
#include "io/output.h"
#include "utils/utils.h"

#define MAX_TIME 0.01

struct query2_test_data {
  JOINT_CATALOG catalog;
  STATS stats;
};

static void query2_0_elements(gconstpointer data) {
  struct query2_test_data *query_data = (struct query2_test_data *)data;

  char *line = strdup("0");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query2(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 2 - 0 elements - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf("\033[0;32mQuery 2 - 0 elements - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(5);
  write_query_result(output_file, result, '2');
  free_query_result(result, '2');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command5_output.txt";

  char *file_output =
      "./Resultados/"
      "command5_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query2_10_elements(gconstpointer data) {
  struct query2_test_data *query_data = (struct query2_test_data *)data;

  char *line = strdup("10");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query2(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 2 - 10 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 2 - 10 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(6);
  write_query_result(output_file, result, '2');
  free_query_result(result, '2');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command6_output.txt";
  char *file_output =
      "./Resultados/"
      "command6_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query2_100_elements(gconstpointer data) {
  struct query2_test_data *query_data = (struct query2_test_data *)data;

  char *line = strdup("100");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query2(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 2 - 100 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 2 - 100 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(7);
  write_query_result(output_file, result, '2');
  free_query_result(result, '2');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command7_output.txt";
  char *file_output =
      "./Resultados/"
      "command7_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query2_500_elements(gconstpointer data) {
  struct query2_test_data *query_data = (struct query2_test_data *)data;

  char *line = strdup("500");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query2(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 2 - 500 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 2 - 500 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(8);
  write_query_result(output_file, result, '2');
  free_query_result(result, '2');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command8_output.txt";
  char *file_output =
      "./Resultados/"
      "command8_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}
