#ifndef STATS_H
#define STATS_H

#include <glib.h>

#include "catalog.h"
#include "common.h"

typedef struct stats *STATS;

typedef struct user_stats *USER_STATS;

typedef struct driver_stats *DRIVER_STATS;

typedef struct ride_stats *RIDE_STATS;

STATS create_stats(void);

GList *get_top_drivers_by_average_score(STATS stats);

GList *get_top_users_by_total_distance(STATS stats);

void update_user_stats(CATALOG catalog, char *username, int distance,
                       double rating, double price, double tip,
                       struct date date);

void update_driver_stats(CATALOG catalog, char *driver_id, double rating,
                         double price, double tip, struct date date);

void calculate_top_users_by_total_distance(STATS stats, CATALOG catalog);

gint compare_users_by_total_distance(gconstpointer a, gconstpointer b);

void calculate_top_drivers_by_average_score(STATS stats, CATALOG catalog);

gint compare_drivers_by_average_score(gconstpointer a, gconstpointer b);

void free_stats(STATS stats);

#endif
