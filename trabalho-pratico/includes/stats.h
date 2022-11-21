#ifndef STATS_H
#define STATS_H

#include <glib.h>

#include "common.h"

typedef struct stats *STATS;

typedef struct user_stats *USER_STATS;

typedef struct driver_stats *DRIVER_STATS;

STATS create_stats(void);

void free_stats(STATS stats);

void free_user_stats(struct user_stats *user);

void free_driver_stats(struct driver_stats *driver);

#endif
