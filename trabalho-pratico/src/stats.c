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
  GList *top_drivers_by_average_score;
  GList *top_users_by_total_distance;
  GHashTable *rides_by_date;
  GArray *male_rides_by_age;
  GArray *female_rides_by_age;
};

struct city_driver_stats {
  char *id;
  double total_rating;
  int total_rides;
  double total_spent;
};

struct ride_gender_stats {
  char *id;
  struct date driver_account_creation;
  struct date user_account_creation;
};

STATS create_stats(void) {
  STATS new_stats = malloc(sizeof(struct stats));

  new_stats->top_drivers_by_average_score = NULL;
  new_stats->top_users_by_total_distance = NULL;
  new_stats->city_drivers =
      g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
  new_stats->rides_by_date =
      g_hash_table_new_full(g_int_hash, g_int_equal, free, NULL);
  new_stats->male_rides_by_age = g_array_new(1, 1, sizeof(RIDE_GENDER_STATS));
  new_stats->female_rides_by_age = g_array_new(1, 1, sizeof(RIDE_GENDER_STATS));

  return new_stats;
}

CITY_DRIVER_STATS create_city_driver_stats(char *id, double total_rating,
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

void update_city_driver_stats(CITY_DRIVER_STATS city_driver_stats,
                              double rating, double ride_price) {
  city_driver_stats->total_rating += rating;
  city_driver_stats->total_rides++;
  city_driver_stats->total_spent += ride_price;
}

GList *get_top_drivers_by_average_score(STATS stats) {
  return stats->top_drivers_by_average_score;
}

GList *get_top_users_by_total_distance(STATS stats) {
  return stats->top_users_by_total_distance;
}

GTree *get_city_driver_stats(STATS stats, char *city) {
  return g_hash_table_lookup(stats->city_drivers, city);
}

double get_city_driver_stats_total_rating(CITY_DRIVER_STATS city_driver_stats) {
  return city_driver_stats->total_rating;
}

int get_city_driver_stats_total_rides(CITY_DRIVER_STATS city_driver_stats) {
  return city_driver_stats->total_rides;
}

char *get_city_driver_stats_id(CITY_DRIVER_STATS city_driver_stats) {
  char *id = strdup(city_driver_stats->id);
  return id;
}

double get_city_driver_stats_total_spent(CITY_DRIVER_STATS city_driver_stats) {
  return city_driver_stats->total_spent;
}

GHashTable *get_rides_by_date(STATS stats) { return stats->rides_by_date; }

GArray *get_male_rides_by_age(STATS stats) { return stats->male_rides_by_age; }

GArray *get_female_rides_by_age(STATS stats) {
  return stats->female_rides_by_age;
}

void update_user_stats(CATALOG catalog, char *username, int distance,
                       double rating, double price, double tip,
                       struct date date) {
  GHashTable *users = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users, username);

  set_user_number_of_rides(user, get_user_number_of_rides(user) + 1);
  set_user_total_rating(user, get_user_total_rating(user) + rating);
  set_user_total_spent(user, get_user_total_spent(user) + price + tip);
  set_user_total_distance(user, get_user_total_distance(user) + distance);

  if (compare_dates(date, get_user_latest_ride(user)) > 0) {
    char *date_string = date_to_string(date);
    set_user_latest_ride(user, date_string);
    free(date_string);
  }
}

void update_driver_stats(CATALOG catalog, char *driver_id, double rating,
                         double price, double tip, struct date date) {
  GHashTable *drivers = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers, driver_id);

  set_driver_number_of_rides(driver, get_driver_number_of_rides(driver) + 1);
  set_driver_total_rating(driver, get_driver_total_rating(driver) + rating);
  set_driver_total_earned(driver,
                          get_driver_total_earned(driver) + price + tip);

  if (compare_dates(date, get_driver_latest_ride(driver)) > 0) {
    char *date_string = date_to_string(date);
    set_driver_latest_ride(driver, date_string);
    free(date_string);
  }
}

void upsert_city_driver_stats(STATS stats, char *city, char *driver_id,
                              double driver_score, double ride_price) {
  GTree *city_drivers = g_hash_table_lookup(stats->city_drivers, city);

  if (city_drivers == NULL) {
    city_drivers =
        g_tree_new_full((GCompareDataFunc)compare_strings, NULL, free,
                        (GDestroyNotify)free_city_driver_stats);
    g_tree_insert(
        city_drivers, driver_id,
        create_city_driver_stats(driver_id, driver_score, 1, ride_price));
    g_hash_table_insert(stats->city_drivers, strdup(city), city_drivers);
  } else {
    CITY_DRIVER_STATS city_driver_stats =
        g_tree_lookup(city_drivers, driver_id);

    if (city_driver_stats == NULL) {
      g_tree_insert(
          city_drivers, driver_id,
          create_city_driver_stats(driver_id, driver_score, 1, ride_price));
    } else {
      update_city_driver_stats(city_driver_stats, driver_score, ride_price);
    }
  }
}

RIDE_GENDER_STATS create_ride_gender_stats(char *ride_id,
                                           struct date driver_account_creation,
                                           struct date user_account_creation) {
  RIDE_GENDER_STATS new = malloc(sizeof(struct ride_gender_stats));

  new->id = ride_id;
  new->driver_account_creation = driver_account_creation;
  new->user_account_creation = user_account_creation;

  return new;
}

char *get_ride_gender_stats_id(RIDE_GENDER_STATS ride) {
  return strdup(ride->id);
}

struct date get_ride_gender_stats_driver_account_creation(
    RIDE_GENDER_STATS ride) {
  return ride->driver_account_creation;
}

struct date get_ride_gender_stats_user_account_creation(
    RIDE_GENDER_STATS ride) {
  return ride->user_account_creation;
}

void update_genders_rides_by_age(CATALOG catalog, STATS stats, char *ride_id,
                                 char *driver_id, char *username) {
  GArray *male_rides_by_age = get_male_rides_by_age(stats);
  GArray *female_rides_by_age = get_female_rides_by_age(stats);

  USER user = g_hash_table_lookup(get_catalog_users(catalog), username);
  enum gender user_gender = get_user_gender(user);
  struct date user_account_creation = get_user_account_creation(user);

  DRIVER driver = g_hash_table_lookup(get_catalog_drivers(catalog), driver_id);
  enum gender driver_gender = get_driver_gender(driver);
  struct date driver_account_creation = get_driver_account_creation(driver);

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

void calculate_rides_by_age(GArray *rides_by_age) {
  g_array_sort(rides_by_age, (GCompareFunc)compare_rides_by_age);
}

gint compare_rides_by_age(gconstpointer a, gconstpointer b) {
  RIDE_GENDER_STATS ride_a = *(RIDE_GENDER_STATS *)a;
  RIDE_GENDER_STATS ride_b = *(RIDE_GENDER_STATS *)b;

  struct date driver_account_creation_a = ride_a->driver_account_creation;
  struct date driver_account_creation_b = ride_b->driver_account_creation;

  int result_dates =
      compare_dates(driver_account_creation_a, driver_account_creation_b);

  if (result_dates == 0) {
    struct date user_account_creation_a = ride_a->user_account_creation;
    struct date user_account_creation_b = ride_b->user_account_creation;

    int result_dates =
        compare_dates(user_account_creation_a, user_account_creation_b);

    if (result_dates == 0) {
      char *ride_id_a = ride_a->id;
      char *ride_id_b = ride_b->id;

      return strcmp(ride_id_a, ride_id_b) * (-1);
    }

    return result_dates * (-1);
  }

  return result_dates * (-1);
}

void calculate_top_users_by_total_distance(STATS stats, CATALOG catalog) {
  GList *top_users_by_total_distance =
      g_hash_table_get_values(get_catalog_users(catalog));

  stats->top_users_by_total_distance =
      g_list_sort(top_users_by_total_distance, compare_users_by_total_distance);
}

gint compare_users_by_total_distance(gconstpointer a, gconstpointer b) {
  USER user_a = (USER)a;
  USER user_b = (USER)b;

  int total_distance_a = get_user_total_distance(user_a);
  int total_distance_b = get_user_total_distance(user_b);

  if (total_distance_a == total_distance_b) {
    struct date most_recent_ride_a = get_user_latest_ride(user_a);
    struct date most_recent_ride_b = get_user_latest_ride(user_b);

    int result_dates = compare_dates(most_recent_ride_a, most_recent_ride_b);

    if (result_dates == 0) {
      char *username_a = get_user_username(user_a);
      char *username_b = get_user_username(user_b);

      int to_return = strcmp(username_a, username_b);

      free(username_a);
      free(username_b);

      return to_return;
    }

    return result_dates * (-1);
  }

  return total_distance_b - total_distance_a;
}

gint compare_driver_stats_by_rating(gconstpointer a, gconstpointer b) {
  CITY_DRIVER_STATS *driver_stats_a = (CITY_DRIVER_STATS *)a;
  CITY_DRIVER_STATS *driver_stats_b = (CITY_DRIVER_STATS *)b;

  int total_distance_a = get_city_driver_stats_total_rides(*driver_stats_a);
  int total_distance_b = get_city_driver_stats_total_rides(*driver_stats_b);

  double total_score_a = get_city_driver_stats_total_rating(*driver_stats_a);
  double total_score_b = get_city_driver_stats_total_rating(*driver_stats_b);

  double average_score_a = total_score_a / total_distance_a;
  double average_score_b = total_score_b / total_distance_b;

  if (average_score_a < average_score_b) {
    return 1;
  } else if (average_score_a > average_score_b) {
    return -1;
  } else {
    char *driver_a_id = get_city_driver_stats_id(*driver_stats_a);
    char *driver_b_id = get_city_driver_stats_id(*driver_stats_b);

    if (is_id_smaller(driver_a_id, driver_b_id)) {
      return 1;
    } else {
      return -1;
    }
  }
}

void calculate_top_drivers_by_average_score(STATS stats, CATALOG catalog) {
  GList *top_drivers_by_average_score =
      g_hash_table_get_values(get_catalog_drivers(catalog));

  stats->top_drivers_by_average_score =
      g_list_sort(top_drivers_by_average_score,
                  (GCompareFunc)compare_drivers_by_average_score);
}

gint compare_drivers_by_average_score(gconstpointer a, gconstpointer b) {
  DRIVER driver_a = (DRIVER)a;
  DRIVER driver_b = (DRIVER)b;

  double a_total_rating = get_driver_total_rating(driver_a);
  int a_number_of_rides = get_driver_number_of_rides(driver_a);
  double a_score = (double)(a_total_rating / a_number_of_rides);

  double b_total_rating = get_driver_total_rating(driver_b);
  int b_number_of_rides = get_driver_number_of_rides(driver_b);
  double b_score = (double)(b_total_rating / b_number_of_rides);

  if (a_score == b_score) {
    struct date most_recent_ride_a = get_driver_latest_ride(driver_a);
    struct date most_recent_ride_b = get_driver_latest_ride(driver_b);

    int result_dates = compare_dates(most_recent_ride_a, most_recent_ride_b);

    if (result_dates == 0) {
      char *driver_id_a = get_driver_id(driver_a);
      char *driver_id_b = get_driver_id(driver_b);

      int to_return = strcmp(driver_id_a, driver_id_b);

      free(driver_id_a);
      free(driver_id_b);

      return to_return;
    }

    return result_dates * (-1);
  }

  return a_score > b_score ? -1 : 1;
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
  struct date ride_date = get_ride_date(ride);
  int ride_date_int = date_struct_to_int(ride_date);
  GArray *rides_of_the_day = NULL;
  rides_of_the_day = g_hash_table_lookup(
      rides_by_date, &ride_date_int);  // Tries to find if there are any rides
                                       // already inserted with the same day
  if (rides_of_the_day) {
    g_array_append_val(rides_of_the_day,
                       ride);  // The ride is then added to the array that has
                               // all the rides made in the same day
  } else {
    int *date = g_malloc(sizeof(struct date));
    *date = date_struct_to_int(ride_date);
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

void free_stats(STATS stats) {
  g_list_free(stats->top_users_by_total_distance);
  g_list_free(stats->top_drivers_by_average_score);
  g_hash_table_destroy(stats->city_drivers);
  g_hash_table_destroy(stats->rides_by_date);
  g_array_free(stats->male_rides_by_age, 1);
  g_array_free(stats->female_rides_by_age, 1);

  free(stats);
}
