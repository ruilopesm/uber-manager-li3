#include "querier.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "catalog.h"
#include "common.h"
#include "drivers.h"
#include "stats.h"
#include "users.h"

void querier(CATALOG catalog, STATS stats, char *line, int counter) {
  char **query_parameter = malloc(sizeof(char *) * MAX_INPUT_TOKENS);
  char *token = strtok(line, " ");

  int query_number = atoi(token);
  token = strtok(NULL, " ");

  int i = 0;
  while (token) {
    query_parameter[i] = token;

    token = strtok(NULL, " ");
    i++;
  }

  function_pointer table[] = {query3};

  table[query_number - 1](catalog, stats, query_parameter, counter);
}

void query3(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  int n;
  sscanf(parameter[0], "%d", &n);

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  GList *top_users = get_top_users_by_total_distance(stats);

  if (top_users == NULL) {
    calculate_top_users_by_total_distance(stats);
    top_users = get_top_users_by_total_distance(stats);
  }

  GList *iterator = top_users;

  while (iterator != NULL && n > 0) {
    USER_STATS user_stats = iterator->data;
    char *username = get_user_stats_username(user_stats);

    GHashTable *users = get_catalog_users(catalog);
    USER user = g_hash_table_lookup(users, username);
    char *name = get_user_name(user);

    int total_distance = get_user_stats_total_distance(user_stats);
    enum account_status account_status = get_user_account_status(user);

    if (account_status == ACTIVE) {
      fprintf(output_file, "%s;%s;%d\n", username, name, total_distance);
      n--;
    }

    iterator = iterator->next;

    free(username);
    free(name);
  }

  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  n = sscanf(parameter[0], "%d", &n);
  printf("Execution time of query 3 with input %d: %lf seconds\n", n,
         time_spent);
}
