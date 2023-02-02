#include "stats.h"

#include <glib.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "catalog.h"
#include "drivers.h"
#include "rides.h"
#include "stats.h"
#include "users.h"
#include "utils.h"

struct stats {
  GArray *city_drivers;
  GArray *top_drivers_by_average_score;
  GArray *top_users_by_total_distance;
  GHashTable *rides_by_date;
  GArray *male_rides_by_age;
  GArray *female_rides_by_age;
};

struct city_driver_stats {
  int id;
  double total_rating;
  int total_rides;
  double total_spent;
};

struct city_stats {
  GHashTable *drivers_hash;
  GPtrArray *drivers_array;
  double total_spent;
  int total_rides;
};

struct ride_gender_stats {
  int id;
  int driver_id;
  int username;
  int driver_account_creation;
  int user_account_creation;
};

struct rides_of_the_day {
  GArray *array;
  double avg_price;
  int number_of_rides;
};

STATS create_stats(void) {
  STATS new_stats = malloc(sizeof(struct stats));

  new_stats->top_drivers_by_average_score =
      g_array_new(FALSE, FALSE, sizeof(DRIVER));
  new_stats->top_users_by_total_distance =
      g_array_new(FALSE, FALSE, sizeof(USER));
  new_stats->city_drivers = g_array_new(1, 1, sizeof(CITY_STATS));
  g_array_set_clear_func(new_stats->city_drivers, free_city_stats);
  new_stats->rides_by_date = g_hash_table_new_full(
      g_int_hash, g_int_equal, free, (GDestroyNotify)free_rides_by_date);
  new_stats->male_rides_by_age = g_array_new(1, 1, sizeof(RIDE_GENDER_STATS));
  new_stats->female_rides_by_age = g_array_new(1, 1, sizeof(RIDE_GENDER_STATS));
  g_array_set_clear_func(new_stats->male_rides_by_age, free_rides_by_age);
  g_array_set_clear_func(new_stats->female_rides_by_age, free_rides_by_age);

  return new_stats;
}

CITY_DRIVER_STATS create_city_driver_stats(gpointer id, double total_rating,
                                           int total_rides,
                                           double total_spent) {
  CITY_DRIVER_STATS new_city_driver_stats =
      malloc(sizeof(struct city_driver_stats));

  new_city_driver_stats->id = GPOINTER_TO_INT(id);
  new_city_driver_stats->total_rating = total_rating;
  new_city_driver_stats->total_rides = total_rides;
  new_city_driver_stats->total_spent = total_spent;

  return new_city_driver_stats;
}

CITY_STATS create_city_stats() {
  CITY_STATS new_city_stats = malloc(sizeof(struct city_stats));

  new_city_stats->drivers_array = g_ptr_array_new();
  new_city_stats->drivers_hash =
      g_hash_table_new_full(NULL, g_direct_equal, NULL, free);
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

CITY_STATS get_city_stats(STATS stats, int city) {
  return g_array_index(stats->city_drivers, CITY_STATS, city);
}

GHashTable *get_city_stats_hash(STATS stats, int city) {
  CITY_STATS city_stats = get_city_stats(stats, city);

  if (city_stats == NULL) return NULL;

  return city_stats->drivers_hash;
}

GPtrArray *get_city_stats_array(STATS stats, int city) {
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
  return city_driver_stats->id;
}

double get_city_driver_stats_total_spent(CITY_DRIVER_STATS city_driver_stats) {
  return city_driver_stats->total_spent;
}

GHashTable *get_rides_by_date(STATS stats) { return stats->rides_by_date; }

void set_city_drivers_array(STATS stats, int city, GPtrArray *drivers_array) {
  CITY_STATS city_stats = g_array_index(stats->city_drivers, CITY_STATS, city);

  if (city_stats == NULL) return;

  city_stats->drivers_array = drivers_array;
}

GArray *get_male_rides_by_age(STATS stats) { return stats->male_rides_by_age; }

GArray *get_female_rides_by_age(STATS stats) {
  return stats->female_rides_by_age;
}

void update_user_stats(CATALOG catalog, gpointer username, int distance,
                       double rating, double price, double tip, int date) {
  USER user = get_user_by_code(catalog, username);

  set_user_number_of_rides(user, get_user_number_of_rides(user) + 1);
  set_user_total_rating(user, get_user_total_rating(user) + rating);
  set_user_total_spent(user, get_user_total_spent(user) + price + tip);
  set_user_total_distance(user, get_user_total_distance(user) + distance);

  if ((date - get_user_latest_ride(user)) > 0) {
    set_user_latest_ride(user, date);
  }
}

void update_driver_stats(CATALOG catalog, gpointer driver_id, double rating,
                         double price, double tip, int date) {
  DRIVER driver = get_driver_by_code(catalog, driver_id);

  set_driver_number_of_rides(driver, get_driver_number_of_rides(driver) + 1);
  set_driver_total_rating(driver, get_driver_total_rating(driver) + rating);
  set_driver_total_earned(driver,
                          get_driver_total_earned(driver) + price + tip);

  if ((date - get_driver_latest_ride(driver)) > 0) {
    set_driver_latest_ride(driver, date);
  }
}

void upsert_city_driver_stats(STATS stats, int city, gpointer driver_id,
                              double driver_score, double ride_price) {
  CITY_STATS city_stats = g_array_index(stats->city_drivers, CITY_STATS, city);

  if (city_stats == NULL) {
    city_stats = create_city_stats(city);

    CITY_DRIVER_STATS city_driver_stats =
        create_city_driver_stats(driver_id, driver_score, 1, ride_price);

    g_ptr_array_add(city_stats->drivers_array, city_driver_stats);
    g_hash_table_insert(city_stats->drivers_hash, driver_id, city_driver_stats);

    g_array_insert_val(stats->city_drivers, city, city_stats);
  } else {
    CITY_DRIVER_STATS city_driver_stats =
        g_hash_table_lookup(city_stats->drivers_hash, driver_id);

    if (city_driver_stats == NULL) {
      CITY_DRIVER_STATS city_driver_stats =
          create_city_driver_stats(driver_id, driver_score, 1, ride_price);
      g_ptr_array_add(city_stats->drivers_array, city_driver_stats);
      g_hash_table_insert(city_stats->drivers_hash, driver_id,
                          city_driver_stats);
    } else {
      update_city_driver_stats(city_driver_stats, driver_score, ride_price);
    }

    city_stats->total_spent += ride_price;
    city_stats->total_rides++;
  }
}

RIDE_GENDER_STATS create_ride_gender_stats(gpointer ride_id, gpointer driver_id,
                                           gpointer username,
                                           int driver_account_creation,
                                           int user_account_creation) {
  RIDE_GENDER_STATS new = malloc(sizeof(struct ride_gender_stats));

  new->id = GPOINTER_TO_INT(ride_id);
  new->driver_id = GPOINTER_TO_INT(driver_id);
  new->username = GPOINTER_TO_INT(username);
  new->driver_account_creation = driver_account_creation;
  new->user_account_creation = user_account_creation;

  return new;
}

int get_ride_gender_stats_id(RIDE_GENDER_STATS ride) { return ride->id; }

int get_ride_gender_stats_driver_id(RIDE_GENDER_STATS ride) {
  return ride->driver_id;
}

int get_ride_gender_stats_username(RIDE_GENDER_STATS ride) {
  return ride->username;
}

int get_ride_gender_stats_driver_account_creation(RIDE_GENDER_STATS ride) {
  return ride->driver_account_creation;
}

int get_ride_gender_stats_user_account_creation(RIDE_GENDER_STATS ride) {
  return ride->user_account_creation;
}

void update_genders_rides_by_age(CATALOG catalog, STATS stats, gpointer ride_id,
                                 gpointer driver_id, gpointer username) {
  GArray *male_rides_by_age = get_male_rides_by_age(stats);
  GArray *female_rides_by_age = get_female_rides_by_age(stats);

  USER user = get_user_by_code(catalog, username);
  enum gender user_gender = get_user_gender(user);
  int user_account_creation = get_user_account_creation(user);

  DRIVER driver = get_driver_by_code(catalog, driver_id);
  enum gender driver_gender = get_driver_gender(driver);
  int driver_account_creation = get_driver_account_creation(driver);

  if (get_driver_account_status(driver) == INACTIVE ||
      get_user_account_status(user) == INACTIVE) {
    return;
  }
  if (user_gender == driver_gender) {
    RIDE_GENDER_STATS to_insert = create_ride_gender_stats(
        ride_id, driver_id, username, driver_account_creation,
        user_account_creation);

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

gint compare_users_by_total_distance(gconstpointer a, gconstpointer b,
                                     gpointer users_reverse_gpointer) {
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

  int username_code_a = get_user_username(user_a);
  int username_code_b = get_user_username(user_b);
  GPtrArray *user_reverse = (GPtrArray *)users_reverse_gpointer;

  char *username_a = g_ptr_array_index(user_reverse, username_code_a);
  char *username_b = g_ptr_array_index(user_reverse, username_code_b);

  int to_return = strcmp(username_a, username_b);

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
    int driver_id_a = driver_stats_a->id;
    int driver_id_b = driver_stats_b->id;

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
  if (a_number_of_rides == 0) {
    return 1;  // Division by zero check
  }

  double a_score = (double)(a_total_rating / a_number_of_rides);

  double b_total_rating = get_driver_total_rating(driver_b);

  int b_number_of_rides = get_driver_number_of_rides(driver_b);
  if (b_number_of_rides == 0) {
    return -1;  // Division by zero check
  }

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

// Inserts a ride on the rides by date stats
void insert_ride_by_date(RIDE ride, STATS stats) {
  GHashTable *rides_by_date = get_rides_by_date(stats);
  int ride_date = get_ride_date(ride);
  int ride_city = get_ride_city(ride);
  RIDES_OF_THE_DAY rides_of_the_day = NULL;
  // Tries to find if there are any rides already inserted with the same day
  rides_of_the_day = g_hash_table_lookup(rides_by_date, &ride_date);

  if (rides_of_the_day) {
    GArray *day_rides = rides_of_the_day->array;
    // prevent checking out of bounds
    if (day_rides->len > (guint)ride_city) {
      GArray *city_rides = g_array_index(day_rides, GArray *, ride_city);
      if (city_rides) {
        // The ride is then added to the array that has all the rides made in
        // the same day in the same city
        g_array_append_val(city_rides, ride);
      } else {
        GArray *new_city = g_array_new(1, 1, sizeof(RIDE));
        g_array_append_val(new_city, ride);
        g_array_index(day_rides, GArray *, ride_city) = new_city;
      }
    } else {
      GArray *new_city = g_array_new(1, 1, sizeof(RIDE));
      g_array_append_val(new_city, ride);
      g_array_insert_val(day_rides, ride_city, new_city);
    }
  } else {
    int *date = g_malloc(sizeof(int));
    *date = ride_date;
    // If no rides made on the same day were added yet, we create a new array to
    // store all the rides made on this day
    GArray *new_city_array = g_array_new(1, 1, sizeof(RIDE));
    g_array_append_val(new_city_array, ride);
    GArray *new_day_array = g_array_new(1, 1, sizeof(GArray *));
    g_array_insert_val(new_day_array, ride_city, new_city_array);

    RIDES_OF_THE_DAY new_day_struct = malloc(sizeof(struct rides_of_the_day));
    new_day_struct->avg_price = -1;
    new_day_struct->number_of_rides = -1;
    new_day_struct->array = new_day_array;

    // The new day with the ride is inserted in the hash table
    g_hash_table_insert(rides_by_date, date, new_day_struct);
  }
}

gint compare_rides_by_distance(gconstpointer a, gconstpointer b) {
  int temp = 0;
  RIDE ride1 = *(RIDE *)(a);
  RIDE ride2 = *(RIDE *)(b);

  int ride1_distance = get_ride_distance(ride1);
  int ride2_distance = get_ride_distance(ride2);
  temp = ride1_distance - ride2_distance;
  if (temp) return temp;

  int ride1_date = get_ride_date(ride1);
  int ride2_date = get_ride_date(ride2);
  temp = ride1_date - ride2_date;
  if (temp) return temp;

  int ride1_id = get_ride_id(ride1);
  int ride2_id = get_ride_id(ride2);

  return ride1_id - ride2_id;
}

GArray *get_ride_of_the_day_array(RIDES_OF_THE_DAY rides_of_the_day) {
  return rides_of_the_day->array;
}

double get_ride_of_the_day_number_of_rides(RIDES_OF_THE_DAY rides_of_the_day) {
  return rides_of_the_day->number_of_rides;
}

void set_ride_of_the_day_number_of_rides(RIDES_OF_THE_DAY rides_of_the_day,
                                         int ride_number) {
  rides_of_the_day->number_of_rides = ride_number;
}

double get_ride_of_the_day_avg_price(RIDES_OF_THE_DAY rides_of_the_day) {
  return rides_of_the_day->avg_price;
}

void set_ride_of_the_day_avg_price(RIDES_OF_THE_DAY rides_of_the_day,
                                   double price) {
  rides_of_the_day->avg_price = price;
}

void free_rides_by_age(gpointer ride_gender_stats_gpointer) {
  RIDE_GENDER_STATS stats = *(RIDE_GENDER_STATS *)ride_gender_stats_gpointer;
  free(stats);
}

void free_rides_by_date(gpointer rides_of_the_day_gpointer) {
  RIDES_OF_THE_DAY rides_of_the_day =
      (RIDES_OF_THE_DAY)(rides_of_the_day_gpointer);
  GArray *array = rides_of_the_day->array;

  for (int i = 0; i < (int)array->len; i++) {
    GArray *temp = g_array_index(rides_of_the_day->array, GArray *, i);

    if (temp != NULL) {
      g_array_free(temp, 1);
    }
  }

  g_array_free(rides_of_the_day->array, 1);
  free(rides_of_the_day);
}

void free_city_stats(gpointer city_stats_gpointer) {
  CITY_STATS city_stats = *(CITY_STATS *)city_stats_gpointer;

  g_hash_table_destroy(city_stats->drivers_hash);
  g_ptr_array_free(city_stats->drivers_array, 1);
  free(city_stats);
}

void free_stats(STATS stats) {
  g_hash_table_destroy(stats->rides_by_date);
  g_array_free(stats->top_users_by_total_distance, 1);
  g_array_free(stats->top_drivers_by_average_score, 1);
  g_array_free(stats->city_drivers, 1);
  g_array_free(stats->male_rides_by_age, 1);
  g_array_free(stats->female_rides_by_age, 1);

  free(stats);
}
