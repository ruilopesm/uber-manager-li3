#ifndef BATCH_H
#define BATCH_H

#include "base/querier.h"
#include "base/stats.h"
#include "catalogs/drivers_catalog.h"
#include "catalogs/join_catalog.h"
#include "catalogs/rides_catalog.h"
#include "catalogs/users_catalog.h"
#include "io/output.h"
#include "io/parser.h"
#include "utils/utils.h"

/**
 * @brief Function that deals with batch mode of the program execution
 *
 * @param argv Array of strings containing the arguments passed to the program
 * argv[1] is the path to the directory containing the files to be read argv[2]
 * is the path to the file containing the queries to be executed
 *
 * @return int 0 if the function was executed successfully, -1 otherwise
 */
int batch(char **argv);

#endif
