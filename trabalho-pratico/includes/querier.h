#ifndef QUERIER_H
#define QUERIER_H

#include <stdio.h>

#include "catalog.h"

#define MAX_INPUT_TOKENS 4

void querier(CATALOG catalog, char *query, int counter);

typedef void (*function_pointer)(CATALOG catalog, char **query_parameters,
                                 int counter);

void query1(CATALOG catalog, char **parameters, int counter);

void query2(CATALOG catalog, char **parameter, int counter);

void get_user_profile(CATALOG catalog, char *id, int counter);

void get_driver_profile(CATALOG catalog, char *id, int counter);

#endif
