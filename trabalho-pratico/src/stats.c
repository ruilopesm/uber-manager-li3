#include "stats.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "catalog.h"
#include "drivers.h"
#include "rides.h"
#include "stats.h"
#include "users.h"
#include "utils.h"

struct stats {
  GHashTable *city_drivers;
  GArray *top_drivers_by_average_score;
  GArray *top_users_by_total_distance;
  GHashTable *rides_by_date;
  GArray *male_rides_by_age;
  GArray *female_rides_by_age;
};

struct city_driver_stats {
  int *id;
  double total_rating;
  int total_rides;
  double total_spent;
};

struct city {
  GTree *drivers_tree;
  double total_spent;
  int total_rides;
  GPtrArray *drivers_array;
};

struct ride_gender_stats {
  int id;
  int driver_account_creation;
  int user_account_creation;
};

STATS create_stats(void) {
  STATS new_stats = malloc(sizeof(struct stats));

  new_stats->top_drivers_by_average_score =
      g_array_new(FALSE, FALSE, sizeof(DRIVER));
  new_stats->top_users_by_total_distance =
      g_array_new(FALSE, FALSE, sizeof(USER));
  new_stats->city_drivers =
      g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
  new_stats->rides_by_date =
      g_hash_table_new_full(g_int_hash, g_int_equal, free, NULL);
  new_stats->male_rides_by_age = g_array_new(1, 1, sizeof(RIDE_GENDER_STATS));
  new_stats->female_rides_by_age = g_array_new(1, 1, sizeof(RIDE_GENDER_STATS));

  return new_stats;
}

CITY_DRIVER_STATS create_city_driver_stats(int *id, double total_rating,
                                           int total_rides,
                                           double total_spent) {
  CITY_DRIVER_STATS new_city_driver_stats =
      malloc(sizeof(struct city_driver_stats));

  new_city_driver_stats->id = id;
  new_city_driver_stats->total_rating = total_rating;
  new_city_driver_stats->total_rides = total_rides;
  new_city_driver_stats->total_spent = total_spent;

  return new_city_driver_stats;
}

CITY_STATS create_city_stats() {
  CITY_STATS new_city_stats = malloc(sizeof(struct city));

  new_city_stats->drivers_tree =
      g_tree_new_full((GCompareDataFunc)compare_ints, NULL, free,
                      (GDestroyNotify)free_city_driver_stats);
  new_city_stats->drivers_array = NULL;
  new_city_stats->total_spent = 0.f;
  new_city_stats->total_rides = 0;

  return new_city_stats;
}

double get_city_stats_total_spent(CITY_STATS city_stats) {
  return city_stats->total_spent;
}

int get_city_stats_total_rides(CITY_STATS city_stats) {
  return city_stats->total_rides;
}

void update_city_driver_stats(CITY_DRIVER_STATS city_driver_stats,
                              double rating, double ride_price) {
  city_driver_stats->total_rating += rating;
  city_driver_stats->total_rides++;
  city_driver_stats->total_spent += ride_price;
}

GArray *get_top_drivers_by_average_score(STATS stats) {
  return stats->top_drivers_by_average_score;
}

GArray *get_top_users_by_total_distance(STATS stats) {
  return stats->top_users_by_total_distance;
}

CITY_STATS get_city_stats(STATS stats, char *city) {
  return g_hash_table_lookup(stats->city_drivers, city);
}

GTree *get_city_stats_tree(STATS stats, char *city) {
  CITY_STATS city_stats = get_city_stats(stats, city);

  if (city_stats == NULL) return NULL;

  return city_stats->drivers_tree;
}

GPtrArray *get_city_stats_array(STATS stats, char *city) {
  CITY_STATS city_stats = get_city_stats(stats, city);

  if (city_stats == NULL) return NULL;

  return city_stats->drivers_array;
}

double get_city_driver_stats_total_rating(CITY_DRIVER_STATS city_driver_stats) {
  return city_driver_stats->total_rating;
}

int get_city_driver_stats_total_rides(CITY_DRIVER_STATS city_driver_stats) {
  return city_driver_stats->total_rides;
}

int get_city_driver_stats_id(CITY_DRIVER_STATS city_driver_stats) {
  int *id = city_driver_stats->id;
  return *id;
}

double get_city_driver_stats_total_spent(CITY_DRIVER_STATS city_driver_stats) {
  return city_driver_stats->total_spent;
}

GHashTable *get_rides_by_date(STATS stats) { return stats->rides_by_date; }

void set_city_drivers_array(STATS stats, char *city, GPtrArray *drivers_array) {
  CITY_STATS city_stats = g_hash_table_lookup(stats->city_drivers, city);

  if (city_stats == NULL) return;

  city_stats->drivers_array = drivers_array;
}

GArray *get_male_rides_by_age(STATS stats) { return stats->male_rides_by_age; }

GArray *get_female_rides_by_age(STATS stats) {
  return stats->female_rides_by_age;
}

void update_user_stats(CATALOG catalog, char *username, int distance,
                       double rating, double price, double tip, int date) {
  GHashTable *users = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users, username);

  set_user_number_of_rides(user, get_user_number_of_rides(user) + 1);
  set_user_total_rating(user, get_user_total_rating(user) + rating);
  set_user_total_spent(user, get_user_total_spent(user) + price + tip);
  set_user_total_distance(user, get_user_total_distance(user) + distance);

  if ((date - get_user_latest_ride(user)) > 0) {
    char *date_string = date_to_string(date);
    set_user_latest_ride(user, date_string);
    free(date_string);
  }
}

void update_driver_stats(CATALOG catalog, int *driver_id, double rating,
                         double price, double tip, int date) {
  GHashTable *drivers = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers, driver_id);

  set_driver_number_of_rides(driver, get_driver_number_of_rides(driver) + 1);
  set_driver_total_rating(driver, get_driver_total_rating(driver) + rating);
  set_driver_total_earned(driver,
                          get_driver_total_earned(driver) + price + tip);

  if ((date - get_driver_latest_ride(driver)) > 0) {
    char *date_string = date_to_string(date);
    set_driver_latest_ride(driver, date_string);
    free(date_string);
  }
}

void upsert_city_driver_stats(STATS stats, char *city, int *driver_id,
                              double driver_score, double ride_price) {
  CITY_STATS city_stats = g_hash_table_lookup(stats->city_drivers, city);

  if (city_stats == NULL) {
    city_stats = create_city_stats(city);

    g_tree_insert(
        city_stats->drivers_tree, driver_id,
        create_city_driver_stats(driver_id, driver_score, 1, ride_price));

    g_hash_table_insert(stats->city_drivers, city, city_stats);
  } else {
    CITY_DRIVER_STATS city_driver_stats =
        g_tree_lookup(city_stats->drivers_tree, driver_id);

    if (city_driver_stats == NULL) {
      g_tree_insert(
          city_stats->drivers_tree, driver_id,
          create_city_driver_stats(driver_id, driver_score, 1, ride_price));
    } else {
      update_city_driver_stats(city_driver_stats, driver_score, ride_price);
    }

    city_stats->total_spent += ride_price;
    city_stats->total_rides++;
  }
}

RIDE_GENDER_STATS create_ride_gender_stats(int *ride_id,
                                           int driver_account_creation,
                                           int user_account_creation) {
  RIDE_GENDER_STATS new = malloc(sizeof(struct ride_gender_stats));

  new->id = *ride_id;
  new->driver_account_creation = driver_account_creation;
  new->user_account_creation = user_account_creation;

  return new;
}

int get_ride_gender_stats_id(RIDE_GENDER_STATS ride) { return ride->id; }

int get_ride_gender_stats_driver_account_creation(RIDE_GENDER_STATS ride) {
  return ride->driver_account_creation;
}

int get_ride_gender_stats_user_account_creation(RIDE_GENDER_STATS ride) {
  return ride->user_account_creation;
}

void update_genders_rides_by_age(CATALOG catalog, STATS stats, int *ride_id,
                                 int *driver_id, char *username) {
  GArray *male_rides_by_age = get_male_rides_by_age(stats);
  GArray *female_rides_by_age = get_female_rides_by_age(stats);

  USER user = g_hash_table_lookup(get_catalog_users(catalog), username);
  enum gender user_gender = get_user_gender(user);
  int user_account_creation = get_user_account_creation(user);

  DRIVER driver = g_hash_table_lookup(get_catalog_drivers(catalog), driver_id);
  enum gender driver_gender = get_driver_gender(driver);
  int driver_account_creation = get_driver_account_creation(driver);

  if (get_driver_account_status(driver) == INACTIVE ||
      get_user_account_status(user) == INACTIVE) {
    return;
  }

  RIDE_GENDER_STATS to_insert = create_ride_gender_stats(
      ride_id, driver_account_creation, user_account_creation);

  if (user_gender == driver_gender) {
    if (user_gender == M) {
      g_array_append_val(male_rides_by_age, to_insert);
    } else {
      g_array_append_val(female_rides_by_age, to_insert);
    }
  }
}

gint compare_rides_by_age(gconstpointer a, gconstpointer b) {
  RIDE_GENDER_STATS ride_a = *(RIDE_GENDER_STATS *)a;
  RIDE_GENDER_STATS ride_b = *(RIDE_GENDER_STATS *)b;

  int driver_account_creation_a = ride_a->driver_account_creation;
  int driver_account_creation_b = ride_b->driver_account_creation;

  int result_dates = driver_account_creation_b - driver_account_creation_a;

  if (result_dates != 0) {
    return result_dates;
  }

  int user_account_creation_a = ride_a->user_account_creation;
  int user_account_creation_b = ride_b->user_account_creation;

  result_dates = user_account_creation_b - user_account_creation_a;

  if (result_dates != 0) {
    return result_dates;
  }

  int ride_id_a = ride_a->id;
  int ride_id_b = ride_b->id;

  return ride_id_b - ride_id_a;
}

void add_user_to_array(gpointer key, gpointer value, gpointer data) {
  USER user = (USER)value;
  GArray *users = (GArray *)data;

  g_array_append_val(users, user);

  (void)key;
}

gint compare_users_by_total_distance(gconstpointer a, gconstpointer b) {
  USER user_a = *(USER *)a;
  USER user_b = *(USER *)b;

  int total_distance_a = get_user_total_distance(user_a);
  int total_distance_b = get_user_total_distance(user_b);

  if (total_distance_a != total_distance_b) {
    return total_distance_b - total_distance_a;
  }

  int latest_ride_a = get_user_latest_ride(user_a);
  int latest_ride_b = get_user_latest_ride(user_b);

  int result_dates = latest_ride_b - latest_ride_a;

  if (result_dates != 0) {
    return result_dates;
  }

  char *username_a = get_user_username(user_a);
  char *username_b = get_user_username(user_b);

  int to_return = strcmp(username_a, username_b);

  free(username_a);
  free(username_b);

  return to_return;
}

gint compare_driver_stats_by_average_score(gconstpointer a, gconstpointer b) {
  CITY_DRIVER_STATS driver_stats_a = *(CITY_DRIVER_STATS *)a;
  CITY_DRIVER_STATS driver_stats_b = *(CITY_DRIVER_STATS *)b;

  double a_total_rating = driver_stats_a->total_rating;
  int a_number_of_rides = driver_stats_a->total_rides;
  double a_score = (double)(a_total_rating / a_number_of_rides);

  double b_total_rating = driver_stats_b->total_rating;
  int b_number_of_rides = driver_stats_b->total_rides;
  double b_score = (double)(b_total_rating / b_number_of_rides);

  if (a_score == b_score) {
    int driver_id_a = *driver_stats_a->id;
    int driver_id_b = *driver_stats_b->id;

    return driver_id_b - driver_id_a;
  }

  return a_score > b_score ? -1 : 1;
}

void add_driver_to_array(gpointer key, gpointer value, gpointer data) {
  DRIVER driver = (DRIVER)value;
  GArray *drivers = (GArray *)data;

  g_array_append_val(drivers, driver);

  (void)key;
}

gint compare_drivers_by_average_score(gconstpointer a, gconstpointer b) {
  DRIVER driver_a = *(DRIVER *)a;
  DRIVER driver_b = *(DRIVER *)b;

  double a_total_rating = get_driver_total_rating(driver_a);
  int a_number_of_rides = get_driver_number_of_rides(driver_a);
  double a_score = (double)(a_total_rating / a_number_of_rides);

  double b_total_rating = get_driver_total_rating(driver_b);
  int b_number_of_rides = get_driver_number_of_rides(driver_b);
  double b_score = (double)(b_total_rating / b_number_of_rides);

  if (a_score != b_score) {
    return a_score > b_score ? -1 : 1;
  }

  int latest_ride_a = get_driver_latest_ride(driver_a);
  int latest_ride_b = get_driver_latest_ride(driver_b);

  int result_dates = latest_ride_b - latest_ride_a;

  if (result_dates != 0) {
    return result_dates;
  }

  int driver_id_a = get_driver_id(driver_a);
  int driver_id_b = get_driver_id(driver_b);

  return driver_id_a - driver_id_b;
}

gint compare_city_driver_stats_by_id(gconstpointer a, gconstpointer b) {
  char *city_driver_stats_a = (char *)a;
  char *city_driver_stats_b = (char *)b;

  return strcmp(city_driver_stats_a, city_driver_stats_b);
}

void free_city_driver_stats(CITY_DRIVER_STATS city_driver_stats) {
  /* free(city_driver_stats->id); */
  free(city_driver_stats);
}

// Inserts a ride on the rides by date stats
void insert_ride_by_date(RIDE ride, STATS stats) {
  GHashTable *rides_by_date = get_rides_by_date(stats);
  int ride_date = get_ride_date(ride);
  GArray *rides_of_the_day = NULL;
  rides_of_the_day = g_hash_table_lookup(
      rides_by_date, &ride_date);  // Tries to find if there are any rides
                                   // already inserted with the same day
  if (rides_of_the_day) {
    g_array_append_val(rides_of_the_day,
                       ride);  // The ride is then added to the array that has
                               // all the rides made in the same day
  } else {
    int *date = g_malloc(sizeof(int));
    *date = ride_date;
    GArray *new_day = g_array_new(
        1, 1, sizeof(RIDE));  // If no rides made on the same day were added
                              // yet, we create a new array to store all the
                              // rides made on this day
    g_array_append_val(new_day, ride);
    g_hash_table_insert(rides_by_date, date,
                        new_day);  // The new day with the ride is inserted
                                   // ordered by date into the hash table
  }
}

void free_city_stats(CITY_STATS city_stats) {
  g_tree_destroy(city_stats->drivers_tree);
  if (city_stats->drivers_array) {
    g_ptr_array_free(city_stats->drivers_array, TRUE);
  }
  free(city_stats);
}

void free_stats(STATS stats) {
  g_array_free(stats->top_users_by_total_distance, FALSE);
  g_array_free(stats->top_drivers_by_average_score, FALSE);
  g_hash_table_destroy(stats->city_drivers);
  g_hash_table_destroy(stats->rides_by_date);
  g_array_free(stats->male_rides_by_age, 1);
  g_array_free(stats->female_rides_by_age, 1);

  free(stats);
}
