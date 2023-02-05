#include <glib.h>

#include "base/querier.h"
#include "io/output.h"
#include "utils/utils.h"

#define MAX_TIME 0.01

struct query1_test_data {
  JOIN_CATALOG catalog;
  STATS stats;
};

static void query1_valid_user(gconstpointer data) {
  struct query1_test_data *query_data = (struct query1_test_data *)data;

  char *line = strdup("SaCruz110");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query1(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 1 - valid user - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf("\033[0;32mQuery 1 - valid user - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(1);
  write_query_result(output_file, result, '1');
  free_query_result(result, '1');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command1_output.txt";

  char *file_output =
      "./Resultados/"
      "command1_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query1_valid_driver(gconstpointer data) {
  struct query1_test_data *query_data = (struct query1_test_data *)data;

  char *line = strdup("000000004780");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query1(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 1 - valid driver - elapsed time: %f "
        "seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 1 - valid driver - elapsed time: %f "
        "seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(2);
  write_query_result(output_file, result, '1');
  free_query_result(result, '1');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command2_output.txt";

  char *file_output =
      "./Resultados/"
      "command2_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query1_invalid_user(gconstpointer data) {
  struct query1_test_data *query_data = (struct query1_test_data *)data;

  char *line = strdup("SaCruz1100");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query1(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 1 - invalid user - elapsed time: %f "
        "seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 1 - invalid user - elapsed time: %f "
        "seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(3);
  write_query_result(output_file, result, '1');
  free_query_result(result, '1');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command3_output.txt";

  char *file_output =
      "./Resultados/"
      "command3_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query1_invalid_driver(gconstpointer data) {
  struct query1_test_data *query_data = (struct query1_test_data *)data;

  char *line = strdup("0000000047800");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result = query1(query_data->catalog, query_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf(
        "\033[0;31mQuery 1 - invalid driver - elapsed time: %f "
        "seconds\033[0m\n",
        time_spent);
  } else {
    printf(
        "\033[0;32mQuery 1 - invalid driver - elapsed time: %f "
        "seconds\033[0m\n",
        time_spent);
  }

  FILE *output_file = create_output_file(4);
  write_query_result(output_file, result, '1');
  free_query_result(result, '1');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command4_output.txt";

  char *file_output =
      "./Resultados/"
      "command4_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}
