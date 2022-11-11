#include "querier.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_profile_info(char** parameter) {
  printf("O codigo esta a funcionar :)");
  // adicionar codigo
  free(parameter);

  return NULL;
}

char* list_best_rating(char** parameter) {
  free(parameter);
  return NULL;
}

char* list_most_travelled(char** parameter) {
  // adicionar codigo
  free(parameter);

  return NULL;
}

char* list_avg_trip_price_city(char** parameter) {
  // adicionar codigo
  free(parameter);

  return NULL;
}

char* list_avg_trip_price_time(char** parameter) {
  // adicionar codigo
  free(parameter);

  return NULL;
}

char* avg_dist_travelled_city(char** parameter) {
  // adicionar codigo
  free(parameter);

  return NULL;
}

char* top_drivers_city(char** parameter) {
  // adicionar codigo
  free(parameter);

  return NULL;
}

char* driver_passenger_similar(char** parameter) {
  // adicionar codigo
  free(parameter);

  return NULL;
}

char* passenger_tipped_time(char** parameter) {
  // adicionar codigo
  free(parameter);

  return NULL;
}

char* querier(char* line) {
  char** query_parameter = malloc(sizeof(char*) * 4);
  char* token = strtok(line, " ");

  int query_number = atoi(token);
  token = strtok(NULL, " ");

  int i = 0;
  while (token) {
    query_parameter[i] = token;

    printf("token: %s\n", token);
    token = strtok(NULL, " ");
    i++;
  }

  static function_pointer table[] = {
      get_profile_info,         list_best_rating,
      list_most_travelled,      list_avg_trip_price_city,
      list_avg_trip_price_time, avg_dist_travelled_city,
      top_drivers_city,         driver_passenger_similar,
      passenger_tipped_time,
  };

  return table[query_number - 1](query_parameter);
}
