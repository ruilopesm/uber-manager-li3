#include <glib.h>

#include "base/querier.h"
#include "io/output.h"
#include "utils/utils.h"

struct query8_test_data {
  JOINT_CATALOG join_catalog;
  STATS stats;
};

#define MAX_TIME 0.01

static void query8_male(gconstpointer data) {
  struct query8_test_data *test_data = (struct query8_test_data *)data;

  char *line = strdup("M 12");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query8(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 8 - valid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf("\033[0;32mQuery 8 - valid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(27);
  write_query_result(output_file, result, '8');
  free_query_result(result, '8');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command27_output.txt";

  char *file_output =
      "./Resultados/"
      "command27_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query8_female(gconstpointer data) {
  struct query8_test_data *test_data = (struct query8_test_data *)data;

  char *line = strdup("F 12");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query8(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 8 - valid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf("\033[0;32mQuery 8 - valid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(28);
  write_query_result(output_file, result, '8');
  free_query_result(result, '8');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command28_output.txt";

  char *file_output =
      "./Resultados/"
      "command28_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}

static void query8_big_age(gconstpointer data) {
  struct query8_test_data *test_data = (struct query8_test_data *)data;

  char *line = strdup("M 100");
  char **query_params = string_to_array(line);

  clock_t begin = clock();
  void *result =
      query8(test_data->join_catalog, test_data->stats, query_params);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (time_spent > MAX_TIME) {
    printf("\033[0;31mQuery 8 - invalid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  } else {
    printf("\033[0;32mQuery 8 - invalid - elapsed time: %f seconds\033[0m\n",
           time_spent);
  }

  FILE *output_file = create_output_file(29);
  write_query_result(output_file, result, '8');
  free_query_result(result, '8');

  free(line);
  fclose(output_file);

  char *file_expected =
      "./tests/results/"
      "command29_output.txt";

  char *file_output =
      "./Resultados/"
      "command29_output.txt";

  g_assert_true(compare_files(file_expected, file_output));
}
