#ifndef QUERIER_H
#define QUERIER_H

#include <stdio.h>

#define MAX_INPUT_TOKENS 2

char* querier(char* query);

typedef char* (*function_pointer)(char** query_parameters);

char* get_profile_info(char** parameters);

char* list_best_rating(char** parameters);

char* list_most_travelled(char** parameters);

char* list_avg_trip_price_city(char** parameters);

char* list_avg_trip_price_time(char** parameters);

char* avg_dist_travelled_city(char** parameters);

char* top_drivers_city(char** parameters);

char* driver_passenger_similar(char** parameters);

char* passenger_tipped_time(char** parameters);

#endif
