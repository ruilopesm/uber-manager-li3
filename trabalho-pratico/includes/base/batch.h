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

int batch(char **argv);

#endif