#include "rides.h"

#include <glib.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#include "catalog.h"
#include "drivers.h"
#include "input.h"
#include "stats.h"
#include "users.h"

struct ride {
  int *id;
  int *driver;
  char *user;
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
  ride->user = NULL;

  return ride;
}

void insert_ride(char **ride_params, CATALOG catalog, STATS stats) {
  // If the input verification failed, we don't insert the ride
  if (!verify_ride_input(ride_params)) return;

  RIDE ride = create_ride();
  GHashTable *rides_hash_table = get_catalog_rides(catalog);

  set_ride_id(ride, ride_params[0]);
  set_ride_date(ride, ride_params[1]);
  set_ride_driver(ride, ride_params[2]);
  set_ride_user(ride, ride_params[3]);
  set_ride_city(ride, ride_params[4], get_catalog_city_code(catalog),
                get_catalog_city_reverse_lookup(catalog));
  set_ride_distance(ride, ride_params[5]);
  set_ride_score_user(ride, ride_params[6]);
  set_ride_score_driver(ride, ride_params[7]);
  set_ride_tip(ride, ride_params[8]);

  GHashTable *drivers_hash_table = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers_hash_table, ride->driver);
  enum car_class car_class = get_driver_car_class(driver);

  double price = calculate_ride_price(ride->distance, car_class);
  set_ride_price(ride, price);

  g_hash_table_insert(rides_hash_table, ride->id, ride);

  insert_ride_by_date(ride, stats);
  update_user_stats(catalog, ride->user, ride->distance, ride->score_user,
                    ride->price, ride->tip, ride->date);
  update_driver_stats(catalog, ride->driver, ride->score_driver, ride->price,
                      ride->tip, ride->date);
  upsert_city_driver_stats(stats, ride->city, ride->driver, ride->score_driver,
                           ride->price);

  update_genders_rides_by_age(catalog, stats, ride->id, ride->driver,
                              ride->user);
}

void set_ride_id(RIDE ride, char *id_string) {
  ride->id = malloc(sizeof(int));
  int id_int = atoi(id_string);
  *ride->id = id_int;
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
  ride->driver = malloc(sizeof(int));
  int driver_id = atoi(driver_string);
  *ride->driver = driver_id;
}

void set_ride_user(RIDE ride, char *user_string) {
  ride->user = strdup(user_string);
}

void set_ride_city(RIDE ride, char *city_string, GHashTable *city_code,
                   GPtrArray *city_reverse_lookup) {
  static char cities_parsed = 0;
  char *city_number;
  city_number = g_hash_table_lookup(city_code, city_string);
  if (city_number) {
    ride->city = *city_number;
  } else {
    char *city_copy = strdup(city_string);
    g_ptr_array_add(city_reverse_lookup, city_copy);
    city_number = malloc(sizeof(char));
    *city_number = cities_parsed;
    ride->city = cities_parsed;
    cities_parsed++;
    char *city_key = strdup(city_string);
    g_hash_table_insert(city_code, city_key, city_number);
  }
}

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

int get_ride_id(RIDE ride) { return *ride->id; }

int get_ride_date(RIDE ride) {
  int date_copy = ride->date;
  return date_copy;
}

int get_ride_driver(RIDE ride) {
  int driver_copy = *ride->driver;
  return driver_copy;
}

char *get_ride_user(RIDE ride) {
  char *user_copy = strdup(ride->user);
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

void free_ride(RIDE ride) {
  free(ride->driver);
  free(ride->user);
  free(ride);
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
