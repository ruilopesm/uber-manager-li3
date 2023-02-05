#ifndef QUERIER_H
#define QUERIER_H

#include <stdbool.h>
#include <stdio.h>

#include "base/stats.h"
#include "catalogs/joint_catalog.h"
#include "entities/drivers.h"
#include "entities/rides.h"
#include "entities/users.h"

#define MAX_INPUT_TOKENS 4

/**
 * @brief Wrapper function that calls the correct query function
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param line - The line of type `char *` that represents the query to be
 * executed
 */
void *querier(JOINT_CATALOG catalog, STATS stats, char *line);

typedef void *(*query_function_pointer)(JOINT_CATALOG catalog, STATS stats,
                                        char **query_parameters);

/**
 * @struct query1_result - Struct that represents the result of query 1 to be
 * used in other places of the program
 */
typedef struct query1_result *QUERY1_RESULT;

/**
 * @brief Function that executes the query one and inserts the result in the
 * query1_result struct
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param parameters - The parameters of type `char **` that are passed to the
 * query
 *
 * @return `struct query1_result` in the form of `void *`
 */
void *query1(JOINT_CATALOG catalog, STATS stats, char **parameters);

/**
 * @brief Function that returns if the user of the query1_result struct is a
 * user
 *
 * @param result - The result of type `QUERY1_RESULT`
 *
 * @return is_user of type `bool`, true if the entity is a user, false otherwise
 */
bool get_query1_is_user(QUERY1_RESULT result);

/**
 * @brief Function that returns the user of the query1_result struct
 *
 * @param result - The result of type `QUERY1_RESULT`
 *
 * @return user of type `USER`
 */
USER get_query1_result_user(QUERY1_RESULT result);

/**
 * @brief Function that returns the driver of the query1_result struct
 *
 * @param result - The result of type `QUERY1_RESULT`
 *
 * @return driver of type `DRIVER`
 */
DRIVER get_query1_result_driver(QUERY1_RESULT result);

/**
 * @brief Function that executes the query two, it does not have a struct
 * result, the result is simply a GArray of `DRIVER`
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param parameters - The parameters of type `char **` that are passed to the
 * query
 *
 * @return GArray of `DRIVER` in the form of `void *`
 */
void *query2(JOINT_CATALOG catalog, STATS stats, char **parameters);

/**
 * @struct query3_result - Struct that represents the result of query 3 to be
 * used in other places of the program
 */
typedef struct query3_result *QUERY3_RESULT;

/**
 * @brief Function that executes the query three and inserts the result in the
 * query3_result struct
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param parameters - The parameters of type `char **` that are passed to the
 * query
 *
 * @return `struct query3_result` in the form of `void *`
 */
void *query3(JOINT_CATALOG catalog, STATS stats, char **parameters);

/**
 * @brief Function that returns the drivers of the query3_result struct
 *
 * @param result - The result of type `QUERY3_RESULT`
 *
 * @return `GArray` of `DRIVER`
 */
GArray *get_query3_result_users(QUERY3_RESULT result);

/**
 * @brief Function that returns the catalog of the query3_result struct
 *
 * @param result - The result of type `QUERY3_RESULT`
 *
 * @return `JOINT_CATALOG`
 */
JOINT_CATALOG get_query3_result_catalog(QUERY3_RESULT result);

/**
 * @brief Function that executes the query four and returns the result, it does
 * not have a struct result, the result is simply a string
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param parameters - The parameters of type `char **` that are passed to the
 * query
 *
 * @return `char*` in the form of `void *`
 */
void *query4(JOINT_CATALOG catalog, STATS stats, char **parameters);

/**
 * @brief Function that executes the query five and returns the result, it does
 * not have a struct result, the result is simply a string
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param parameters - The parameters of type `char **` that are passed to the
 * query
 *
 * @return `char*` in the form of `void *`
 */
void *query5(JOINT_CATALOG catalog, STATS stats, char **parameters);

/**
 * @brief Function that executes the query six and returns the result, it does
 * not have a struct result, the result is simply a string
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param parameters - The parameters of type `char **` that are passed to the
 * query
 *
 * @return `char*` in the form of `void *`
 */
void *query6(JOINT_CATALOG catalog, STATS stats, char **parameters);

/**
 * @struct query7_auxiliar - Struct that contains the driver and the average
 * score to auxiliate query 7 function
 */
typedef struct query7_auxiliar *QUERY7_AUXILIAR;

/**
 * @brief Function that executes the query seven
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param parameters - The parameters of type `char **` that are passed to the
 * query
 *
 * @return `GPtrArray` in the form of `void *`
 */
void *query7(JOINT_CATALOG catalog, STATS stats, char **parameters);

/**
 * @brief Function that returns the driver of the query7_auxiliar struct
 *
 * @param auxiliar - The auxiliar of type `QUERY7_AUXILIAR`
 *
 * @return `DRIVER`
 */
DRIVER get_query7_auxiliar_driver(QUERY7_AUXILIAR auxiliar);

/**
 * @brief Function that returns the average score of the query7_auxiliar struct
 *
 * @param auxiliar - The auxiliar of type `QUERY7_AUXILIAR`
 *
 * @return `double`
 */
double get_query7_auxiliar_average_score(QUERY7_AUXILIAR auxiliar);

/**
 * @struct query8_result - Struct that represents the result of query 8 to be
 * used in other places of the program
 */
typedef struct query8_result *QUERY8_RESULT;

/**
 * @brief Function that executes the query eight
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param parameters - The parameters of type `char **` that are passed to the
 * query
 *
 * @return `GArray` in the form of `void *`
 */
void *query8(JOINT_CATALOG catalog, STATS stats, char **parameters);

/**
 * @brief Function that returns the rides of the query8_result struct
 *
 * @param result - The result of type `QUERY8_RESULT`
 *
 * @return `GArray` of `RIDE`
 */
GArray *get_query8_result_top_rides(QUERY8_RESULT result);

/**
 * @brief Function that returns the catalog of the query8_result struct
 *
 * @param result - The result of type `QUERY8_RESULT`
 *
 * @return `JOINT_CATALOG`
 */
JOINT_CATALOG get_query8_result_catalog(QUERY8_RESULT result);

/**
 * @struct query9_result - Struct that represents the result of query 9 to be
 * used in other places of the program
 */
typedef struct query9_result *QUERY9_RESULT;

/**
 * @brief Function that executes the query nine
 *
 * @param catalog - The catalog of type `JOINT_CATALOG`
 * @param stats - The stats of type `STATS`
 * @param parameters - The parameters of type `char **` that are passed to the
 * query
 *
 * @return `GArray` in the form of `void *`
 */
void *query9(JOINT_CATALOG catalog, STATS stats, char **parameters);

/**
 * @brief Function that returns the rides of the query9_result struct
 *
 * @param result - The result of type `QUERY9_RESULT`
 *
 * @return `GArray` of `RIDE`
 */
GArray *get_query9_result_rides_in_range(QUERY9_RESULT result);

/**
 * @brief Function that returns the catalog of the query9_result struct
 *
 * @param result - The result of type `QUERY9_RESULT`
 *
 * @return `JOINT_CATALOG`
 */
JOINT_CATALOG get_query9_result_catalog(QUERY9_RESULT result);

/**
 * @brief Function that compares two rides distances
 *
 * @param a - The first ride of type `gconstpointer`
 * @param b - The second ride of type `gconstpointer`
 *
 * @return `int` that represents the difference between the two rides distances
 */
gint compare_rides_by_distance(gconstpointer a, gconstpointer b);

/**
 * @brief Wrapper function that frees the memory allocated for the specified
 * query result
 * @param result The result to be freed of `type void *`
 * @param query_type The type of the query of type `char`
 */
void free_query_result(void *result, char query_type);

typedef void (*free_query_result_function_pointer)(void *result);

/**
 * @brief Function that frees the memory allocated for the result of query 1
 *
 * @param result - The result of type `void *`
 */
void free_query1_result(void *result);

/**
 * @brief Function that frees the memory allocated for the result of query 2
 *
 * @param result - The result of type `void *`
 */
void free_query2_result(void *result);

/**
 * @brief Function that frees the memory allocated for the result of query 3
 *
 * @param result - The result of type `void *`
 */
void free_query3_result(void *result);

/**
 * @brief Function that frees the memory allocated for the result of query 4
 *
 * @param result - The result of type `void *`
 */
void free_query4_result(void *result);

/**
 * @brief Function that frees the memory allocated for the result of query 5
 *
 * @param result - The result of type `void *`
 */
void free_query5_result(void *result);

/**
 * @brief Function that frees the memory allocated for the result of query 6
 *
 * @param result - The result of type `void *`
 */
void free_query6_result(void *result);

/**
 * @brief Function that frees the memory allocated for the result of query 7
 *
 * @param result - The result of type `void *`
 */
void free_query7_result(void *result);

/**
 * @brief Function that frees the memory allocated for the result of query 8
 *
 * @param result - The result of type `void *`
 */
void free_query8_result(void *result);

/**
 * @brief Function that frees the memory allocated for the result of query 9
 *
 * @param result - The result of type `void *`
 */
void free_query9_result(void *result);

#endif
