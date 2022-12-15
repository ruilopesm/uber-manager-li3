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
#include "rides.h"
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

  function_pointer table[] = {query1, query2, query3, query4, query5,
                              query6, query7, query8, query9};

  table[query_number - 1](catalog, stats, query_parameter, counter);
}

void query1(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *id = parameter[0];
  id[strlen(id) - 1] = '\0';

  int flag = is_number(id);

  switch (flag) {
    case 0:
      get_user_profile(catalog, id, counter);
      break;
    case 1:
      get_driver_profile(catalog, id, counter);
  }

  free(parameter);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Query 1 elapsed time: %f seconds\n", time_spent);

  // Since stats is not used in this query, we can ignore the warning
  (void)stats;
}

void query2(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  int n;
  sscanf(parameter[0], "%d", &n);

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  GList *top_drivers = get_top_drivers_by_average_score(stats);

  if (top_drivers == NULL) {
    calculate_top_drivers_by_average_score(stats, catalog);
    top_drivers = get_top_drivers_by_average_score(stats);
  }

  GList *iterator = top_drivers;

  while (iterator != NULL && n > 0) {
    DRIVER driver = iterator->data;
    char *driver_id = get_driver_id(driver);
    char *name = get_driver_name(driver);

    double total_rating = get_driver_total_rating(driver);
    int number_of_rides = get_driver_number_of_rides(driver);
    double average_score = (double)(total_rating / number_of_rides);

    enum account_status account_status = get_driver_account_status(driver);

    if (account_status == ACTIVE) {
      fprintf(output_file, "%s;%s;%.3f\n", driver_id, name, average_score);
      n--;
    }

    iterator = iterator->next;

    free(driver_id);
    free(name);
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Query 2 elapsed time: %f seconds\n", time_spent);
}

void query3(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  int n;
  sscanf(parameter[0], "%d", &n);

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  GList *top_users = get_top_users_by_total_distance(stats);

  if (top_users == NULL) {
    calculate_top_users_by_total_distance(stats, catalog);
    top_users = get_top_users_by_total_distance(stats);
  }

  GList *iterator = top_users;

  while (iterator != NULL && n > 0) {
    USER user = iterator->data;
    char *username = get_user_username(user);
    char *name = get_user_name(user);

    int total_distance = get_user_total_distance(user);
    enum account_status account_status = get_user_account_status(user);

    if (account_status == ACTIVE) {
      fprintf(output_file, "%s;%s;%d\n", username, name, total_distance);
      n--;
    }

    iterator = iterator->next;

    free(username);
    free(name);
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Query 3 elapsed time: %f seconds\n", time_spent);
}

void query4(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *chosen = parameter[0];
  chosen[strlen(chosen) - 1] = '\0';

  int total = 0;
  double total_price = 0.0;

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  GHashTable *rides_hash_table = get_catalog_rides(catalog);
  GList *rides = g_hash_table_get_values(rides_hash_table);
  GList *iterator = rides;

  while (iterator != NULL) {
    RIDE ride = iterator->data;
    char *city = get_ride_city(ride);

    if (!strcmp(city, chosen)) {
      total_price += get_ride_price(ride);
      total++;
    }

    iterator = iterator->next;

    free(city);
  }

  g_list_free(rides);

  fprintf(output_file, "%.3f\n", total_price / total);

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Query 4 elapsed time: %f seconds\n", time_spent);

  // Since catalog is not used in this query, we can safely ignore the warning
  (void)stats;
}

void query5(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Query 5 elapsed time: %f seconds\n", time_spent);

  (void)catalog;
  (void)stats;
  (void)parameter;
  (void)counter;
}

void query6(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Query 6 elapsed time: %f seconds\n", time_spent);

  (void)catalog;
  (void)stats;
  (void)parameter;
  (void)counter;
}

void query7(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Query 7 elapsed time: %f seconds\n", time_spent);

  (void)catalog;
  (void)stats;
  (void)parameter;
  (void)counter;
}

void query8(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Query 8 elapsed time: %f seconds\n", time_spent);

  (void)catalog;
  (void)stats;
  (void)parameter;
  (void)counter;
}

void query9(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Query 9 elapsed time: %f seconds\n", time_spent);

  (void)catalog;
  (void)stats;
  (void)parameter;
  (void)counter;
}

void get_user_profile(CATALOG catalog, char *id, int counter) {
  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "w");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  GHashTable *users_hash_table = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users_hash_table, id);

  if (user == NULL) {
    free(output_filename);
    fclose(output_file);
    printf("User with id %s does not exist\n", id);
    return;
  }

  char *name = get_user_name(user);
  enum gender gender = get_user_gender(user);

  int number_of_rides = get_user_number_of_rides(user);
  double average_rating =
      (double)(get_user_total_rating(user) / number_of_rides);

  double total_spent = get_user_total_spent(user);
  enum account_status account_status = get_user_account_status(user);

  if (account_status == ACTIVE) {
    fprintf(output_file, "%s;%s;%d;%.3f;%d;%.3f\n", name,
            gender_to_string(gender), calculate_age(get_user_birth_date(user)),
            average_rating, number_of_rides, total_spent);
  }

  free(name);
  free(output_filename);
  fclose(output_file);
}

void get_driver_profile(CATALOG catalog, char *id, int counter) {
  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);
  FILE *output_file = fopen(output_filename, "w");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  GHashTable *drivers_hash_table = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers_hash_table, id);

  if (driver == NULL) {
    free(output_filename);
    fclose(output_file);
    printf("Driver with id %s does not exist\n", id);
    return;
  }

  char *name = get_driver_name(driver);
  enum gender gender = get_driver_gender(driver);

  int number_of_rides = get_driver_number_of_rides(driver);
  double average_rating =
      (double)(get_driver_total_rating(driver) / number_of_rides);

  double total_earned = get_driver_total_earned(driver);
  enum account_status account_status = get_driver_account_status(driver);

  if (account_status == ACTIVE) {
    fprintf(output_file, "%s;%s;%d;%.3f;%d;%.3f\n", name,
            gender_to_string(gender),
            calculate_age(get_driver_birth_date(driver)), average_rating,
            number_of_rides, total_earned);
  }

  free(name);
  free(output_filename);
  fclose(output_file);
}
