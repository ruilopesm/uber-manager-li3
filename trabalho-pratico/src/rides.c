#include "rides.h"

#include <glib.h>
#include <stdlib.h>
#include <string.h>

struct ride {
  char *id;
  struct date date;
  char *driver;
  char *user;
  char *city;
  int distance;
  int score_user;
  int score_driver;
  double tip;
  char *comment;
};

RIDE create_ride() {
  RIDE ride = malloc(sizeof(struct ride));
  ride->id = NULL;
  ride->driver = NULL;
  ride->user = NULL;
  ride->city = NULL;
  ride->comment = NULL;

  return ride;
}

void insert_ride(char **ride_params, GHashTable *hash_table) {
  RIDE ride = create_ride();

  set_ride_id(ride, ride_params[0]);
  set_ride_date(ride, ride_params[1]);
  set_ride_driver(ride, ride_params[2]);
  set_ride_user(ride, ride_params[3]);
  set_ride_city(ride, ride_params[4]);
  set_ride_distance(ride, ride_params[5]);
  set_ride_score_user(ride, ride_params[6]);
  set_ride_score_driver(ride, ride_params[7]);
  set_ride_tip(ride, ride_params[8]);
  set_ride_comment(ride, ride_params[9]);

  g_hash_table_insert(hash_table, ride->id, ride);
}

void set_ride_id(RIDE ride, char *id_string) {
  char *id = malloc(sizeof(char) * 13);
  strcpy(id, id_string);

  ride->id = id;
}

void set_ride_date(RIDE ride, char *date_string) {
  char day[3];
  day[0] = date_string[0];
  day[1] = date_string[1];
  day[2] = '\0';

  char month[3];
  month[0] = date_string[3];
  month[1] = date_string[4];
  month[2] = '\0';

  char year[5];
  year[0] = date_string[6];
  year[1] = date_string[7];
  year[2] = date_string[8];
  year[3] = date_string[9];
  year[4] = '\0';

  struct date date;
  date.day = atoi(day);
  date.month = atoi(month);
  date.year = atoi(year);

  ride->date = date;
}

void set_ride_driver(RIDE ride, char *driver_string) {
  ride->driver = strdup(driver_string);
}

void set_ride_user(RIDE ride, char *user_string) {
  ride->user = strdup(user_string);
}

void set_ride_city(RIDE ride, char *city_string) {
  ride->city = strdup(city_string);
}

void set_ride_distance(RIDE ride, char *distance_string) {
  char *ptr;
  ride->distance = strtol(distance_string, &ptr, 10);
}

void set_ride_score_user(RIDE ride, char *score_user_string) {
  char *ptr;
  ride->score_user = strtol(score_user_string, &ptr, 10);
}

void set_ride_score_driver(RIDE ride, char *score_driver_string) {
  char *ptr;
  ride->score_driver = strtol(score_driver_string, &ptr, 10);
}

void set_ride_tip(RIDE ride, char *tip_string) {
  char *ptr;
  ride->tip = strtod(tip_string, &ptr);
}

void set_ride_comment(RIDE ride, char *comment_string) {
  ride->comment = strdup(comment_string);
}

char *get_ride_id(RIDE ride) { return strdup(ride->id); }

struct date get_ride_date(RIDE ride) {
  struct date date_copy = ride->date;
  return date_copy;
}

char *get_ride_driver(RIDE ride) {
  char *driver_copy = strdup(ride->driver);
  return driver_copy;
}

char *get_ride_user(RIDE ride) {
  char *user_copy = strdup(ride->user);
  return user_copy;
}

char *get_ride_city(RIDE ride) {
  char *city_copy = strdup(ride->city);
  return city_copy;
}

int get_ride_distance(RIDE ride) {
  int distance_copy = ride->distance;
  return distance_copy;
}

int get_ride_score_user(RIDE ride) {
  int score_user_copy = ride->score_user;
  return score_user_copy;
}

int get_ride_score_driver(RIDE ride) {
  int score_driver_copy = ride->score_driver;
  return score_driver_copy;
}

double get_ride_tip(RIDE ride) {
  double tip_copy = ride->tip;
  return tip_copy;
}

char *get_ride_comment(RIDE ride) {
  char *comment_copy = strdup(ride->comment);
  return comment_copy;
}

void free_ride(RIDE ride) {
  free(ride->driver);
  free(ride->user);
  free(ride->city);
  free(ride->comment);
  free(ride);
}
