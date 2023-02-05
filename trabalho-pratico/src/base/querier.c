#include "base/querier.h"

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "base/stats.h"
#include "catalogs/join_catalog.h"
#include "entities/rides.h"
#include "utils/utils.h"

void *querier(JOIN_CATALOG catalog, STATS stats, char *line) {
  char **query_parameters = malloc(sizeof(char *) * MAX_INPUT_TOKENS);

  // Format of the line: <type> <params...>
  char *token = strtok(line, " ");
  char query_type = line[0];

  int i = 0;
  while (token != NULL) {
    token = strtok(NULL, " ");
    query_parameters[i] = token;
    i++;
  }

  static query_function_pointer table[] = {
      query1, query2, query3, query4, query5, query6, query7, query8, query9};

  void *result = table[query_type - '1'](catalog, stats, query_parameters);

  free(query_parameters);

  return result;
}

struct query1_result {
  union {
    USER user;
    DRIVER driver;
  } data;
  bool is_user;  // true if user, false if driver
};

void *query1(JOIN_CATALOG catalog, STATS stats, char **parameters) {
  char *id = parameters[0];
  bool flag = is_number(id);

  if (flag == false) {
    USERS_CATALOG users_catalog = get_users_catalog(catalog);
    USER user = get_user_by_username(users_catalog, id);

    if (user == NULL) {
      return NULL;
    }

    enum account_status account_status = get_user_account_status(user);

    if (account_status == ACTIVE) {
      QUERY1_RESULT result = malloc(sizeof(struct query1_result));
      result->data.user = user;
      result->is_user = true;

      return (void *)result;
    }
  } else {
    int driver_id = atoi(id);

    DRIVERS_CATALOG drivers_catalog = get_drivers_catalog(catalog);
    DRIVER driver = get_driver_by_id(drivers_catalog, driver_id);

    if (driver == NULL) {
      return NULL;
    }

    enum account_status account_status = get_driver_account_status(driver);

    if (account_status == ACTIVE) {
      QUERY1_RESULT result = malloc(sizeof(struct query1_result));
      result->data.driver = driver;
      result->is_user = false;

      return (void *)result;
    }
  }

  // Stats is not used in this query
  (void)stats;

  return NULL;
}

bool get_query1_is_user(QUERY1_RESULT result) { return result->is_user; }

USER get_query1_result_user(QUERY1_RESULT result) { return result->data.user; }

DRIVER get_query1_result_driver(QUERY1_RESULT result) {
  return result->data.driver;
}

// Does not have a struct result, the result is simply a GArray of DRIVERS
void *query2(JOIN_CATALOG catalog, STATS stats, char **parameters) {
  int n = atoi(parameters[0]);

  GArray *result = g_array_new(TRUE, TRUE, sizeof(DRIVER));

  static int is_drivers_sorted = 0;
  GArray *top_drivers = get_top_drivers_by_average_score(stats);

  if (!is_drivers_sorted) {
    qsort(top_drivers->data, top_drivers->len, sizeof(DRIVER),
          (GCompareFunc)compare_drivers_by_average_score);
    is_drivers_sorted = 1;
  }

  int i = 0;
  while (n > 0 && i < (int)top_drivers->len) {
    DRIVER driver = g_array_index(top_drivers, DRIVER, i);
    enum account_status account_status = get_driver_account_status(driver);

    if (account_status == ACTIVE) {
      g_array_append_val(result, driver);
      n--;
    }

    i++;
  }

  // Catalog is not used in this query
  (void)catalog;

  return (void *)result;
}

struct query3_result {
  GArray *users;
  JOIN_CATALOG catalog;
};

void *query3(JOIN_CATALOG catalog, STATS stats, char **parameters) {
  int n = atoi(parameters[0]);

  GArray *result = g_array_new(TRUE, TRUE, sizeof(DRIVER));

  static int is_users_sorted = 0;
  GArray *top_users = get_top_users_by_total_distance(stats);

  if (!is_users_sorted) {
    g_array_sort_with_data(
        top_users, (GCompareDataFunc)compare_users_by_total_distance, catalog);
    is_users_sorted = 1;
  }

  int i = 0;
  while (n > 0 && i < (int)top_users->len) {
    USER user = g_array_index(top_users, USER, i);
    enum account_status account_status = get_user_account_status(user);

    if (account_status == ACTIVE) {
      g_array_append_val(result, user);
      n--;
    }

    i++;
  }

  QUERY3_RESULT query3_result = malloc(sizeof(struct query3_result));
  query3_result->users = result;
  query3_result->catalog = catalog;

  return (void *)query3_result;
}

GArray *get_query3_result_users(QUERY3_RESULT result) { return result->users; }

JOIN_CATALOG get_query3_result_catalog(QUERY3_RESULT result) {
  return result->catalog;
}

// Does not have a struct result, the result is simply a string
void *query4(JOIN_CATALOG catalog, STATS stats, char **parameters) {
  char *city_string = parameters[0];

  char *result = malloc(sizeof(char) * 16);

  RIDES_CATALOG rides_catalog = get_rides_catalog(catalog);
  char *city_code = get_city_code(rides_catalog, city_string);

  if (city_code) {
    int city = *city_code;
    CITY_STATS city_stats = get_city_stats(stats, city);

    if (city_stats != NULL) {
      double total_spent = get_city_stats_total_spent(city_stats);
      int total_rides = get_city_stats_total_rides(city_stats);
      double average_score = (double)(total_spent / total_rides);

      sprintf(result, "%.3f", average_score);
    }
  } else {
    free_query4_result(result);
    return NULL;
  }

  return (void *)result;
}

// Does not have a struct result, the result is simply a string
void *query5(JOIN_CATALOG catalog, STATS stats, char **parameters) {
  int lower_limit = date_string_to_int(parameters[0]);
  int upper_limit = date_string_to_int(parameters[1]);

  char *result = malloc(sizeof(char) * 10);

  GHashTable *rides_by_date = get_rides_by_date(stats);
  double average =
      calculate_average_price(rides_by_date, lower_limit, upper_limit);

  if (average) {
    sprintf(result, "%.3f", average);
  } else {
    free_query5_result(result);
    return NULL;
  }

  // Catalog is not used in this query
  (void)catalog;

  return (void *)result;
}

// Does not have a struct result, the result is simply a string
void *query6(JOIN_CATALOG catalog, STATS stats, char **parameters) {
  char *city = parameters[0];
  int lower_limit = date_string_to_int(parameters[1]);
  int upper_limit = date_string_to_int(parameters[2]);

  char *result = malloc(sizeof(char) * 10);

  GHashTable *rides_by_date = get_rides_by_date(stats);
  RIDES_CATALOG rides_catalog = get_rides_catalog(catalog);
  char *city_code = get_city_code(rides_catalog, city);

  double average = 0.f;
  if (city_code) {
    average = calculate_average_distance(rides_by_date, lower_limit,
                                         upper_limit, *city_code);
  } else {
    free_query6_result(result);
    return NULL;
  }

  if (average) {
    sprintf(result, "%.3f", average);
  } else {
    free_query6_result(result);
    return NULL;
  }

  return (void *)result;
}

struct query7_auxiliar {
  DRIVER driver;
  double average_score;
};

void *query7(JOIN_CATALOG catalog, STATS stats, char **parameter) {
  int n = atoi(parameter[0]);
  char *city = parameter[1];

  GPtrArray *result = g_ptr_array_new();
  g_ptr_array_set_free_func(result, free);

  RIDES_CATALOG rides_catalog = get_rides_catalog(catalog);
  char *city_code = get_city_code(rides_catalog, city);

  DRIVERS_CATALOG drivers_catalog = get_drivers_catalog(catalog);

  if (city_code) {
    int city = *city_code;

    GHashTable *city_drivers_hash = get_city_stats_hash(stats, city);

    if (city_drivers_hash == NULL) {
      free_query7_result(result);
      return NULL;
    }

    GPtrArray *city_drivers_array = get_city_stats_array(stats, city);
    g_ptr_array_sort(city_drivers_array, compare_driver_stats_by_average_score);

    int i = 0;
    while (n > 0 && i < (int)city_drivers_array->len) {
      CITY_DRIVER_STATS city_driver_stats =
          g_ptr_array_index(city_drivers_array, i);

      int driver_id = get_city_driver_stats_id(city_driver_stats);
      DRIVER driver = get_driver_by_id(drivers_catalog, driver_id);
      enum account_status status = get_driver_account_status(driver);

      if (status == ACTIVE) {
        int number_of_rides =
            get_city_driver_stats_total_rides(city_driver_stats);
        double total_rating =
            get_city_driver_stats_total_rating(city_driver_stats);
        double average_score = (double)(total_rating / number_of_rides);

        QUERY7_AUXILIAR auxiliar = malloc(sizeof(struct query7_auxiliar));
        auxiliar->driver = driver;
        auxiliar->average_score = average_score;

        g_ptr_array_add(result, auxiliar);

        n--;
      }

      i++;
    }
  } else {
    free_query7_result(result);
    return NULL;
  }

  return (void *)result;
}

DRIVER get_query7_auxiliar_driver(QUERY7_AUXILIAR query7_auxiliar) {
  return query7_auxiliar->driver;
}

double get_query7_auxiliar_average_score(QUERY7_AUXILIAR query7_auxiliar) {
  return query7_auxiliar->average_score;
}

struct query8_result {
  GArray *top_rides;
  JOIN_CATALOG catalog;
};

void *query8(JOIN_CATALOG catalog, STATS stats, char **parameters) {
  char *gender = parameters[0];
  enum gender given_gender = string_to_gender(gender);
  int age = atoi(parameters[1]);

  GArray *result = g_array_new(TRUE, TRUE, sizeof(RIDE_GENDER_STATS));

  static int is_males_sorted = 0;
  static int is_females_sorted = 0;

  GArray *top_rides = NULL;

  if (given_gender == M) {
    top_rides = get_male_rides_by_age(stats);

    if (!is_males_sorted) {
      qsort(top_rides->data, top_rides->len, sizeof(RIDE_GENDER_STATS),
            (GCompareFunc)compare_rides_by_age);
      top_rides = get_male_rides_by_age(stats);

      is_males_sorted = 1;
    }
  } else {
    top_rides = get_female_rides_by_age(stats);

    if (!is_females_sorted) {
      qsort(top_rides->data, top_rides->len, sizeof(RIDE_GENDER_STATS),
            (GCompareFunc)compare_rides_by_age);
      top_rides = get_female_rides_by_age(stats);

      is_females_sorted = 1;
    }
  }

  for (int i = top_rides->len - 1; i >= 0; i--) {
    RIDE_GENDER_STATS current_ride =
        g_array_index(top_rides, RIDE_GENDER_STATS, i);

    int driver_age = calculate_age(
        get_ride_gender_stats_driver_account_creation(current_ride));

    if (driver_age < age) {
      break;
    }

    int user_age = calculate_age(
        get_ride_gender_stats_user_account_creation(current_ride));

    if (user_age < age) {
      continue;
    }

    g_array_append_val(result, current_ride);
  }

  if (result->len == 0) {
    g_array_free(result, TRUE);
    return NULL;
  }

  QUERY8_RESULT query8_result = malloc(sizeof(struct query8_result));
  query8_result->top_rides = result;
  query8_result->catalog = catalog;

  return (void *)query8_result;
}

GArray *get_query8_result_top_rides(QUERY8_RESULT query8_result) {
  return query8_result->top_rides;
}

JOIN_CATALOG get_query8_result_catalog(QUERY8_RESULT query8_result) {
  return query8_result->catalog;
}

struct query9_result {
  GArray *rides_in_range;
  JOIN_CATALOG catalog;
};

void *query9(JOIN_CATALOG catalog, STATS stats, char **parameters) {
  int lower_limit = date_string_to_int(parameters[0]);
  int upper_limit = date_string_to_int(parameters[1]);

  GArray *rides_in_range = g_array_new(1, 1, sizeof(RIDE));

  GHashTable *rides_by_date = get_rides_by_date(stats);

  for (int temp_date = lower_limit; upper_limit >= temp_date;
       temp_date = increment_date(temp_date)) {
    // Tries to find if there are rides in that specific day
    RIDES_OF_THE_DAY rides_of_the_day_struct =
        g_hash_table_lookup(rides_by_date, &temp_date);

    if (rides_of_the_day_struct) {
      GArray *rides_of_the_day =
          get_ride_of_the_day_array(rides_of_the_day_struct);

      if (rides_of_the_day) {
        int number_of_cities = rides_of_the_day->len;

        for (int i = 0; i < number_of_cities; i++) {
          GArray *city_rides = g_array_index(rides_of_the_day, GArray *, i);

          if (city_rides) {
            int number_of_rides = city_rides->len;

            for (int j = 0; j < number_of_rides; j++) {
              RIDE temp_ride = g_array_index(city_rides, RIDE, j);
              // Make sure there is something in that array position
              if (temp_ride == NULL) break;
              // The ride is inserted into the temporary structure if the user
              // tipped
              if (get_ride_tip(temp_ride))
                g_array_append_val(rides_in_range, temp_ride);
            }
          }
        }
      }
    }
  }

  qsort(rides_in_range->data, rides_in_range->len, sizeof(RIDE),
        (GCompareFunc)compare_rides_by_distance);

  if (rides_in_range->len == 0) {
    g_array_free(rides_in_range, TRUE);
    return NULL;
  }

  QUERY9_RESULT query9_result = malloc(sizeof(struct query9_result));
  query9_result->rides_in_range = rides_in_range;
  query9_result->catalog = catalog;

  return (void *)query9_result;
}

GArray *get_query9_result_rides_in_range(QUERY9_RESULT query9_result) {
  return query9_result->rides_in_range;
}

JOIN_CATALOG get_query9_result_catalog(QUERY9_RESULT query9_result) {
  return query9_result->catalog;
}

double calculate_average_price(GHashTable *rides_by_date, int lower_limit,
                               int upper_limit) {
  double total = 0.f;
  int rides_counter = 0;
  int temp_date;

  for (temp_date = lower_limit; upper_limit >= temp_date;
       temp_date = increment_date(temp_date)) {
    RIDES_OF_THE_DAY rides_of_the_day =
        g_hash_table_lookup(rides_by_date, &temp_date);

    if (rides_of_the_day) {
      GArray *day_rides = get_ride_of_the_day_array(rides_of_the_day);

      // If this day's total price wasn't calculated yet, we calculate it

      if (get_ride_of_the_day_avg_price(rides_of_the_day) == -1) {
        int number_of_cities = day_rides->len, day_rides_counter = 0;
        double daily_total = 0.f;
        // We add the price of every ride in every city in that day

        for (int i = 0; i < number_of_cities; i++) {
          GArray *city_rides = g_array_index(day_rides, GArray *, i);
          // We check if any rides were made on that city on that day
          if (city_rides) {
            int number_of_rides = city_rides->len;

            for (int j = 0; j < number_of_rides; j++) {
              RIDE temp_ride = g_array_index(city_rides, RIDE, j);
              // Make sure there is something in that array position
              if (temp_ride == NULL) {
                break;
              }

              daily_total += get_ride_price(temp_ride);
              day_rides_counter++;
            }
          }
        }

        // If any rides were made in that day, we add them to the total
        if (day_rides_counter) {
          set_ride_of_the_day_avg_price(rides_of_the_day, daily_total);
          set_ride_of_the_day_number_of_rides(rides_of_the_day,
                                              day_rides_counter);
        } else {
          set_ride_of_the_day_avg_price(rides_of_the_day, 0);
          set_ride_of_the_day_number_of_rides(rides_of_the_day, 0);
        }
      }

      total += get_ride_of_the_day_avg_price(rides_of_the_day);
      rides_counter += get_ride_of_the_day_number_of_rides(rides_of_the_day);
    }
  }

  if (rides_counter) {
    return (double)(total / rides_counter);
  }
  return 0;
}

double calculate_average_distance(GHashTable *rides_by_date, int lower_limit,
                                  int upper_limit, char city_code) {
  double total = 0.f;
  int rides_counter = 0;
  int temp_date;
  RIDE temp_ride = NULL;

  for (temp_date = lower_limit; upper_limit >= temp_date;
       temp_date = increment_date(temp_date)) {
    RIDES_OF_THE_DAY rides_of_the_day =
        g_hash_table_lookup(rides_by_date, &temp_date);

    if (rides_of_the_day) {
      GArray *array = get_ride_of_the_day_array(rides_of_the_day);

      // Prevent checking NULL and out of bounds
      if (array && array->len >= (guint)city_code) {
        GArray *city_rides = g_array_index(array, GArray *, (int)city_code);
        if (city_rides) {
          int number_of_rides = city_rides->len;
          for (int i = 0; i < number_of_rides; i++) {
            temp_ride = g_array_index(city_rides, RIDE, i);
            // Make sure there is something in that array position
            if (temp_ride == NULL) {
              break;
            }
            total += get_ride_distance(temp_ride);
            rides_counter++;
          }
        }
      }
    }
  }

  if (rides_counter) {
    return (double)(total / rides_counter);
  }

  return 0;
}

void free_query_result(void *result, char query_type) {
  static free_query_result_function_pointer table[] = {
      free_query1_result, free_query2_result, free_query3_result,
      free_query4_result, free_query5_result, free_query6_result,
      free_query7_result, free_query8_result, free_query9_result,
  };

  table[query_type - '1'](result);
}

void free_query1_result(void *result) {
  QUERY1_RESULT query1_result = (QUERY1_RESULT)result;
  free(query1_result);
}

void free_query2_result(void *result) {
  GArray *drivers = (GArray *)result;
  g_array_free(drivers, TRUE);
}

void free_query3_result(void *result) {
  QUERY3_RESULT query3_result = (QUERY3_RESULT)result;
  GArray *users = get_query3_result_users(query3_result);
  g_array_free(users, TRUE);
  free(query3_result);
}

void free_query4_result(void *result) {
  char *query4_result = (char *)result;
  free(query4_result);
}

void free_query5_result(void *result) {
  char *query5_result = (char *)result;
  free(query5_result);
}

void free_query6_result(void *result) {
  char *query6_result = (char *)result;
  free(query6_result);
}

void free_query7_result(void *result) {
  GPtrArray *drivers = (GPtrArray *)result;

  if (drivers != NULL) {
    g_ptr_array_free(drivers, TRUE);
  }
}

void free_query8_result(void *result) {
  QUERY8_RESULT query8_result = (QUERY8_RESULT)result;

  if (query8_result == NULL) {
    return;
  }

  GArray *rides = get_query8_result_top_rides(query8_result);
  g_array_free(rides, TRUE);
  free(query8_result);
}

void free_query9_result(void *result) {
  QUERY9_RESULT query9_result = (QUERY9_RESULT)result;

  if (query9_result == NULL) {
    return;
  }

  GArray *rides = get_query9_result_rides_in_range(query9_result);
  g_array_free(rides, TRUE);
  free(query9_result);
}
