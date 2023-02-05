#include <glib.h>

#include "base/querier.h"
#include "io/output.h"
#include "utils/utils.h"

struct query7_test_data {
  JOIN_CATALOG join_catalog;
  STATS stats;
};

#define MAX_TIME 0.01

static void query7_0_elements(gconstpointer data) {
  struct query7_test_data *test_data = (struct query7_test_data *)data;

  char *line = strdup("0 Lisboa");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query7(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 7 - 0 elements - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf("\033[0;32mQuery 7 - 0 elements - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(22);
  write_query_result(output_file, result, '7');
  free_query_result(result, '7');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command22_output.txt";

  char *file_output =
      "./Resultados/"
      "command22_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query7_10_elements(gconstpointer data) {
  struct query7_test_data *test_data = (struct query7_test_data *)data;

  char *line = strdup("7 10 Lisboa");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query7(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 7 - 10 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 7 - 10 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(23);
  write_query_result(output_file, result, '7');
  free_query_result(result, '7');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command23_output.txt";

  char *file_output =
      "./Resultados/"
      "command23_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query7_100_elements(gconstpointer data) {
  struct query7_test_data *test_data = (struct query7_test_data *)data;

  char *line = strdup("7 100 Lisboa");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query7(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 7 - 100 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 7 - 100 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(24);
  write_query_result(output_file, result, '7');
  free_query_result(result, '7');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command24_output.txt";

  char *file_output =
      "./Resultados/"
      "command24_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query7_500_elements(gconstpointer data) {
  struct query7_test_data *test_data = (struct query7_test_data *)data;

  char *line = strdup("7 500 Lisboa");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query7(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 7 - 500 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 7 - 500 elements - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(25);
  write_query_result(output_file, result, '7');
  free_query_result(result, '7');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command25_output.txt";

  char *file_output =
      "./Resultados/"
      "command25_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query7_invalid_city(gconstpointer data) {
  struct query7_test_data *test_data = (struct query7_test_data *)data;

  char *line = strdup("7 10 Leiria");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query7(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 7 - invalid city - elapsed time: %f seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 7 - invalid city - elapsed time: %f seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(26);
  write_query_result(output_file, result, '7');
  free_query_result(result, '7');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command26_output.txt";

  char *file_output =
      "./Resultados/"
      "command26_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}
