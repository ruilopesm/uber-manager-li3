#ifndef QUERIER_H
#define QUERIER_H

#include <stdbool.h>
#include <stdio.h>

#include "base/stats.h"
#include "catalogs/join_catalog.h"
#include "entities/drivers.h"
#include "entities/rides.h"
#include "entities/users.h"

#define MAX_INPUT_TOKENS 4

void *querier(JOIN_CATALOG catalog, STATS stats, char *line);

typedef void *(*query_function_pointer)(JOIN_CATALOG catalog, STATS stats,
                                        char **query_parameters);

typedef struct query1_result *QUERY1_RESULT;

void *query1(JOIN_CATALOG catalog, STATS stats, char **parameters);

bool get_query1_is_user(QUERY1_RESULT result);

USER get_query1_result_user(QUERY1_RESULT result);

DRIVER get_query1_result_driver(QUERY1_RESULT result);

void *query2(JOIN_CATALOG catalog, STATS stats, char **parameters);

typedef struct query3_result *QUERY3_RESULT;

void *query3(JOIN_CATALOG catalog, STATS stats, char **parameters);

GArray *get_query3_result_users(QUERY3_RESULT result);

JOIN_CATALOG get_query3_result_catalog(QUERY3_RESULT result);

void *query4(JOIN_CATALOG catalog, STATS stats, char **parameters);

void *query5(JOIN_CATALOG catalog, STATS stats, char **parameters);

void *query6(JOIN_CATALOG catalog, STATS stats, char **parameters);

typedef struct query7_auxiliar *QUERY7_AUXILIAR;

void *query7(JOIN_CATALOG catalog, STATS stats, char **parameters);

DRIVER get_query7_auxiliar_driver(QUERY7_AUXILIAR auxiliar);

double get_query7_auxiliar_average_score(QUERY7_AUXILIAR auxiliar);

typedef struct query8_result *QUERY8_RESULT;

void *query8(JOIN_CATALOG catalog, STATS stats, char **parameters);

GArray *get_query8_result_top_rides(QUERY8_RESULT result);

JOIN_CATALOG get_query8_result_catalog(QUERY8_RESULT result);

typedef struct query9_result *QUERY9_RESULT;

void *query9(JOIN_CATALOG catalog, STATS stats, char **parameters);

GArray *get_query9_result_rides_in_range(QUERY9_RESULT result);

JOIN_CATALOG get_query9_result_catalog(QUERY9_RESULT result);

double calculate_average_price(GHashTable *rides_by_date, int lower_limit,
                               int upper_limit);

double calculate_average_distance(GHashTable *rides_by_date, int lower_limit,
                                  int upper_limit, char city_code);

gint compare_rides_by_distance(gconstpointer a, gconstpointer b);

void free_query_result(void *result, char query_type);

typedef void (*free_query_result_function_pointer)(void *result);

void free_query1_result(void *result);

void free_query2_result(void *result);

void free_query3_result(void *result);

void free_query4_result(void *result);

void free_query5_result(void *result);

void free_query6_result(void *result);

void free_query7_result(void *result);

void free_query8_result(void *result);

void free_query9_result(void *result);

#endif
