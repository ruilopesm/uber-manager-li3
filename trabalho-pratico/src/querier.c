#include "querier.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "catalog.h"
#include "common.h"
#include "drivers.h"
#include "users.h"

void querier(CATALOG catalog, char *line, int counter) {
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

  function_pointer table[] = {query1, query2};

  table[query_number - 1](catalog, query_parameter, counter);
}

void query1(CATALOG catalog, char **parameter, int counter) {
  // Remove \n from the end of the string
  char *id = parameter[0];
  id[strlen(id) - 1] = '\0';

  // Check whether the id is a number or not
  int flag = is_number(id);

  switch (flag) {
    case 0:
      get_user_profile(catalog, id, counter);
      break;
    case 1:
      get_driver_profile(catalog, id, counter);
  }

  free(parameter);
}

void query2(CATALOG catalog, char **parameter, int counter) {
  int n = atoi(parameter[0]);

  GList *drivers_scores = get_catalog_drivers_scores(catalog);

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "w");

  while (n > 0 && drivers_scores) {
    DRIVER driver = (DRIVER)drivers_scores->data;

    char *id = get_driver_id(driver);
    char *name = get_driver_name(driver);
    double total_rating = get_driver_total_rating(driver);
    int total_rides = get_driver_number_of_rides(driver);
    double average_rating = total_rating / total_rides;
    enum account_status account_status = get_driver_account_status(driver);

    if (account_status == ACTIVE) {
      fprintf(output_file, "%s;%s;%.3f\n", id, name, average_rating);
      n--;
    }

    drivers_scores = drivers_scores->next;

    free(id);
    free(name);
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);
}

void get_user_profile(CATALOG catalog, char *id, int counter) {
  GHashTable *users_hash_table = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users_hash_table, id);

  char *name = get_user_name(user);
  enum gender gender = get_user_gender(user);
  int number_of_rides = get_user_number_of_rides(user);
  double average_rating = get_user_total_rating(user) / number_of_rides;
  double total_spent = get_user_total_spent(user);

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "w");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

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
  GHashTable *drivers_hash_table = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers_hash_table, id);

  char *name = get_driver_name(driver);
  enum gender gender = get_driver_gender(driver);
  int number_of_rides = get_driver_number_of_rides(driver);
  double average_rating = get_driver_total_rating(driver) / number_of_rides;
  double total_earned = get_driver_total_earned(driver);

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "w");

  if (output_file == NULL) {
    printf("Error opening/creating the output file\n");
    return;
  }

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
