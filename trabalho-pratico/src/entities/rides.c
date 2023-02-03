#include "entities/rides.h"

#include <glib.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#include "base/catalog.h"
#include "base/stats.h"
#include "entities/drivers.h"
#include "entities/users.h"
#include "io/input.h"

struct ride {
  gpointer id;
  gpointer driver;
  gpointer user;
  double tip;
  double price;
  int city;
  int date;
  int distance;
  int score_user;
  int score_driver;
};

RIDE create_ride() {
  RIDE ride = malloc(sizeof(struct ride));
  ride->id = NULL;
  ride->driver = NULL;

  return ride;
}

void build_ride(char **ride_params, CATALOG catalog, STATS stats) {
  // If the input verification failed, we don't insert the ride
  if (!verify_ride_input(ride_params)) return;

  RIDE ride = create_ride();

  set_ride_id(ride, ride_params[0]);
  set_ride_date(ride, ride_params[1]);
  set_ride_driver(ride, ride_params[2]);
  set_catalog_ride_user(catalog, ride, ride_params[3]);
  set_catalog_ride_city(catalog, ride, ride_params[4]);
  set_ride_distance(ride, ride_params[5]);
  set_ride_score_user(ride, ride_params[6]);
  set_ride_score_driver(ride, ride_params[7]);
  set_ride_tip(ride, ride_params[8]);

  DRIVER driver = get_driver_by_code(catalog, ride->driver);
  enum car_class car_class = get_driver_car_class(driver);
  double price = calculate_ride_price(ride->distance, car_class);
  set_ride_price(ride, price);

  insert_ride_and_update_catalog(
      catalog, ride, ride->id, ride->user, ride->driver, ride->distance,
      ride->score_user, ride->price, ride->tip, ride->date, ride->score_driver);
  insert_ride_into_stats(stats, catalog, ride, ride->id, ride->driver,
                         ride->user, ride->city, ride->score_driver,
                         ride->price);
}

void set_ride_id(RIDE ride, char *id_string) {
  gint id_int = string_to_int(id_string);
  gpointer id_pointer = GINT_TO_POINTER(id_int);
  ride->id = id_pointer;
}

void set_ride_date(RIDE ride, char *date_string) {
  int date = 0;

  date = (date_string[0] - '0') * 10;
  date += (date_string[1] - '0');

  date += (date_string[3] - '0') * 1000;
  date += (date_string[4] - '0') * 100;

  date += (date_string[6] - '0') * 10000000;
  date += (date_string[7] - '0') * 1000000;
  date += (date_string[8] - '0') * 100000;
  date += (date_string[9] - '0') * 10000;

  ride->date = date;
}

void set_ride_driver(RIDE ride, char *driver_string) {
  int driver_id = string_to_int(driver_string);
  ride->driver = GINT_TO_POINTER(driver_id);
}

void set_ride_user(RIDE ride, gpointer user_code) { ride->user = user_code; }

void set_ride_city(RIDE ride, char city) { ride->city = city; }

void set_ride_distance(RIDE ride, char *distance_string) {
  ride->distance = string_to_int(distance_string);
}

void set_ride_score_user(RIDE ride, char *score_user_string) {
  ride->score_user = string_to_int(score_user_string);
}

void set_ride_score_driver(RIDE ride, char *score_driver_string) {
  ride->score_driver = string_to_int(score_driver_string);
}

void set_ride_tip(RIDE ride, char *tip_string) {
  ride->tip = string_to_float(tip_string);
}

void set_ride_price(RIDE ride, double price) { ride->price = price; }

int get_ride_id(RIDE ride) { return GPOINTER_TO_INT(ride->id); }

int get_ride_date(RIDE ride) {
  int date_copy = ride->date;
  return date_copy;
}

gpointer get_ride_driver(RIDE ride) {
  gpointer driver_copy = ride->driver;
  return driver_copy;
}
gpointer get_ride_user(RIDE ride) {
  gpointer user_copy = ride->user;
  return user_copy;
}

int get_ride_city(RIDE ride) { return ride->city; }

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

double get_ride_price(RIDE ride) {
  double price_copy = ride->price;
  return price_copy;
}

double calculate_ride_price(int distance, enum car_class car_class) {
  double price = 0.0;

  switch (car_class) {
    case BASIC:
      price = 3.25 + 0.62 * distance;
      break;
    case GREEN:
      price = 4.00 + 0.79 * distance;
      break;
    case PREMIUM:
      price = 5.20 + 0.94 * distance;
      break;
  }

  return price;
}

int verify_ride_input(char **parameters) {
  // Verifies if the ID string isn't empty
  if (!(parameters[0])) return 0;

  // Verifies if the driver ID isn't empty
  if (!(parameters[2])) return 0;

  // Verifies if the username string isn't empty
  if (!(parameters[3])) return 0;

  // Verifies if the city string isn't empty
  if (!(parameters[4])) return 0;

  // Verifies if the date follows the format
  if (!verify_date_format(parameters[1])) return 0;

  // Verifies if distance is an integer higher than zero
  if (!is_integer(parameters[5])) return 0;

  // Verifies if score_user is an integer higher than zero
  if (!is_integer(parameters[6])) return 0;

  // Verifies if score_driver is an integer higher than zero
  if (!is_integer(parameters[7])) return 0;

  // Verifies if tip is a double higher than 0
  if (!is_float(parameters[8])) return 0;

  // If all fields are valid then the ride is verified
  return 1;
}
