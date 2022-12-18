#ifndef RIDES_H
#define RIDES_H

#include <glib.h>

#include "catalog.h"
#include "common.h"
#include "stats.h"

#define MAX_RIDE_TOKENS 10

typedef struct ride *RIDE;

RIDE create_ride();

void insert_ride(char **ride_params, CATALOG catalog, STATS stats);

void set_ride_id(RIDE ride, char *id_string);

void set_ride_date(RIDE ride, char *date_string);

void set_ride_driver(RIDE ride, char *driver_string);

void set_ride_user(RIDE ride, char *user_string);

void set_ride_city(RIDE ride, char *city_string);

void set_ride_distance(RIDE ride, char *distance_string);

void set_ride_score_user(RIDE ride, char *score_user_string);

void set_ride_score_driver(RIDE ride, char *score_driver_string);

void set_ride_tip(RIDE ride, char *tip_string);

void set_ride_comment(RIDE ride, char *comment_string);

void set_ride_price(RIDE ride, double price);

char *get_ride_id(RIDE ride);

struct date get_ride_date(RIDE ride);

char *get_ride_driver(RIDE ride);

char *get_ride_user(RIDE ride);

char *get_ride_city(RIDE ride);

int get_ride_distance(RIDE ride);

int get_ride_score_user(RIDE ride);

int get_ride_score_driver(RIDE ride);

double get_ride_tip(RIDE ride);

char *get_ride_comment(RIDE ride);

double get_ride_price(RIDE ride);

double calculate_ride_price(int distance, enum car_class car_class);

void free_ride(RIDE ride);

#endif
