#include "querier.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "catalog.h"
#include "common.h"
#include "drivers.h"
#include "rides.h"
#include "stats.h"
#include "users.h"

void querier(CATALOG catalog, STATS stats, char *line, int counter) {
  char **query_parameter = malloc(sizeof(char *) * MAX_INPUT_TOKENS);
  char *token = strtok(line, " ");

  int query_number = atoi(token);
  token = strtok(NULL, " ");

  int i = 0;
  while (token) {
    query_parameter[i] = token;

    token = strtok(NULL, " ");
    i++;
  }

  function_pointer table[] = {query1, query2, query3, query4, query5,
                              query6, query7, query8, query9};

  table[query_number - 1](catalog, stats, query_parameter, counter);
}

void query1(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *id = parameter[0];
  id[strlen(id) - 1] = '\0';

  int flag = is_number(id);

  switch (flag) {
    case 0:
      get_user_profile(catalog, id, counter);
      break;
    case 1:
      get_driver_profile(catalog, id, counter);
  }

  free(parameter);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%d: Query 1 elapsed time: %f seconds\n", counter, time_spent);

  // Since stats is not used in this query, we can ignore the warning
  (void)stats;
}

void query2(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  int n;
  sscanf(parameter[0], "%d", &n);

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  GList *top_drivers = get_top_drivers_by_average_score(stats);

  if (top_drivers == NULL) {
    calculate_top_drivers_by_average_score(stats, catalog);
    top_drivers = get_top_drivers_by_average_score(stats);
  }

  GList *iterator = top_drivers;

  while (iterator != NULL && n > 0) {
    DRIVER driver = iterator->data;
    char *driver_id = get_driver_id(driver);
    char *name = get_driver_name(driver);

    double total_rating = get_driver_total_rating(driver);
    int number_of_rides = get_driver_number_of_rides(driver);
    double average_score = (double)(total_rating / number_of_rides);

    enum account_status account_status = get_driver_account_status(driver);

    if (account_status == ACTIVE) {
      fprintf(output_file, "%s;%s;%.3f\n", driver_id, name, average_score);
      n--;
    }

    iterator = iterator->next;

    free(driver_id);
    free(name);
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("%d: Query 2 elapsed time: %f seconds\n", counter, time_spent);
}

void query3(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  int n;
  sscanf(parameter[0], "%d", &n);

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  GList *top_users = get_top_users_by_total_distance(stats);

  if (top_users == NULL) {
    calculate_top_users_by_total_distance(stats, catalog);
    top_users = get_top_users_by_total_distance(stats);
  }

  GList *iterator = top_users;

  while (iterator != NULL && n > 0) {
    USER user = iterator->data;
    char *username = get_user_username(user);
    char *name = get_user_name(user);

    int total_distance = get_user_total_distance(user);
    enum account_status account_status = get_user_account_status(user);

    if (account_status == ACTIVE) {
      fprintf(output_file, "%s;%s;%d\n", username, name, total_distance);
      n--;
    }

    iterator = iterator->next;

    free(username);
    free(name);
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("%d: Query 3 elapsed time: %f seconds\n", counter, time_spent);
}

void query4(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *city = parameter[0];
  city[strlen(city) - 1] = '\0';

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  // in order to fit every parameter in the g_tree_foreach function, we need to
  // utilize a struct that contains those parameters
  struct query4_utils *utils = malloc(sizeof(struct query4_utils));
  utils->catalog = catalog;
  utils->total_spent = 0;
  utils->total_rides = 0;

  GTree *city_drivers_tree = get_city_driver_stats(stats, city);

  if (city_drivers_tree != NULL) {
    g_tree_foreach(city_drivers_tree, (GTraverseFunc)count_city_total_spent,
                   utils);

    double result = utils->total_spent / utils->total_rides;

    fprintf(output_file, "%.3f\n", result);
  }

  free(utils);
  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("%d: Query 4 elapsed time: %f seconds\n", counter, time_spent);

  // Since stats is not used in this query, we can safely ignore the warning
  (void)stats;
}

gboolean count_city_total_spent(gpointer key, gpointer value,
                                gpointer user_data) {
  struct query4_utils *utils = (struct query4_utils *)user_data;

  CITY_DRIVER_STATS city_driver_stats = (CITY_DRIVER_STATS)value;

  utils->total_spent += get_city_driver_stats_total_spent(city_driver_stats);
  utils->total_rides += get_city_driver_stats_total_rides(city_driver_stats);

  return FALSE;

  (void)key;
}
gboolean tree_to_array(gpointer key, gpointer value, gpointer user_data) {
  GPtrArray *array = (GPtrArray *)user_data;
  g_ptr_array_add(array, value);
  return FALSE;

  (void)key;
}

void query5(CATALOG catalog, STATS stats, char **parameter, int counter) {
  query5_6(catalog, stats, parameter, counter, 0);
}

void query6(CATALOG catalog, STATS stats, char **parameter, int counter) {
  query5_6(catalog, stats, parameter, counter, 1);
}

void query5_6(CATALOG catalog, STATS stats, char **parameters, int counter,
              int query6_determiner) {  // If query_determiner is 0, query5 is
                                        // made, if it's 1, query 6 is made
  clock_t begin = clock();
  double average = 0.f;
  GArray *rides_by_date = get_rides_by_date(stats);
  GHashTable *drivers_hash = get_catalog_drivers(catalog);
  char *city = NULL;
  if (query6_determiner)
    city = parameters[0];  // if we are calculating query6, the city has value
  struct date lower_limit = date_string_to_struct(
      parameters[0 + query6_determiner]);  // Earliest date at which rides are
                                           // considered, if query6_determiner
                                           // is true we add its value (1) due
                                           // to the additional first parameter
                                           // in query6, which is the city
  struct date upper_limit = date_string_to_struct(
      parameters[1 + query6_determiner]);  // Latest date at which rides are
                                           // considered
  int starting_position = -1;  // Position of the earliest ride still in range,
                               // where counting the average will start

  // We will search for the position of the array where the first ride dated on
  // or after the lower limit is located and start searching from there
  get_starting_date_position(rides_by_date, &starting_position, lower_limit,
                             upper_limit);

  // If strating_position is -1, that means there are no rides made after the
  // lower limit and before the upper one so we don't need to calculate its
  // average
  if (starting_position >= 0) {
    if (query6_determiner)
      average = calculate_avg_distance(rides_by_date, starting_position,
                                       upper_limit, city);
    else
      average = calculate_avg_price(rides_by_date, drivers_hash,
                                    starting_position, upper_limit);
  }

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "w");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  if (average)
    fprintf(output_file, "%.3f\n", average);
  else
    fprintf(output_file, "\n");
  free(parameters);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  if (!query6_determiner)
    printf("%d: Query 5 elapsed time: %f seconds\n", counter, time_spent);
  else
    printf("%d: Query 6 elapsed time: %f seconds\n", counter, time_spent);
}

void query7(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  int n;
  sscanf(parameter[0], "%d", &n);
  char *city = strip(parameter[1]);

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  GTree *city_drivers_tree = get_city_driver_stats(stats, city);
  if (city_drivers_tree == NULL) {
    return;
  }

  GPtrArray *city_drivers_array = g_ptr_array_new();
  g_tree_foreach(city_drivers_tree, (GTraverseFunc)tree_to_array,
                 city_drivers_array);
  g_ptr_array_sort(city_drivers_array, compare_driver_stats_by_rating);

  int i = 0;
  while (n > 0 && i < (int)city_drivers_array->len) {
    CITY_DRIVER_STATS city_driver_stats =
        g_ptr_array_index(city_drivers_array, i);
    char *driver_id = get_city_driver_stats_id(city_driver_stats);

    GHashTable *drivers = get_catalog_drivers(catalog);
    DRIVER driver = g_hash_table_lookup(drivers, driver_id);
    enum account_status status = get_driver_account_status(driver);

    if (status == ACTIVE) {
      char *driver_name = get_catalog_driver_name(catalog, driver_id);

      double driver_rating =
          get_city_driver_stats_total_rating(city_driver_stats);

      int driver_number_of_rides =
          get_city_driver_stats_total_rides(city_driver_stats);

      double driver_average_score = driver_rating / driver_number_of_rides;

      fprintf(output_file, "%s;%s;%.3f\n", driver_id, driver_name,
              driver_average_score);

      free(driver_name);
      free(driver_id);
      n--;
    }
    i++;
  }

  g_ptr_array_free(city_drivers_array, TRUE);
  free(parameter);
  free(city);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("%d: Query 7 elapsed time: %f seconds\n", counter, time_spent);
}

// Finds the position of the array whose date is closest to the lower limit of
// search while being in range, returns -1 if it doesn't exist
void get_starting_date_position(GArray *rides_by_date, int *starting_position,
                                struct date lower_limit,
                                struct date upper_limit) {
  char search_result =
      0;  // Used as boolean to know if the binary search found a relevant date
  /*We will search for the position of the array where the first ride dated on
  or after the lower limit is located. While we are looking for dates in range
  and before the master date, we add a day to temp_date until we find one in
  which a ride was made (an array with a ride exists) This strategy is
  worthwhile compared to going through the entire array and only conting dates
  in range due to the benefits of binary search, though only if the date range
  given was short and closest to the master date*/
  for (struct date temp_date = lower_limit;
       compare_dates(temp_date, MASTER_DATE_DATE) <= 0 &&
       compare_dates(temp_date, upper_limit) <= 0;
       temp_date = increment_date(temp_date)) {
    search_result = g_array_binary_search(rides_by_date, &temp_date,
                                          compare_dates_wrapper_array_date,
                                          (guint *)starting_position);
    if (search_result)
      break;  // If a ride is found in range, the loop stops as we found the
              // starting position for the search
  }
}

// Calculates the average price or distance
double calculate_avg_price(GArray *rides_by_date, GHashTable *drivers_hash,
                           int starting_position, struct date upper_limit) {
  double total = 0.f;     // Price accumulator
  int rides_counter = 0;  // Rides Accumulator
  struct date temp_date;
  RIDE temp_ride = NULL;
  enum car_class
      temp_car_class;  // Temporary variables used to fetch the car class of the
                       // driver and calculate the price charged

  int number_of_dates =
      rides_by_date->len;  // Number of separate dates registered
  GArray *rides_of_the_day =
      g_array_index(rides_by_date, GArray *, starting_position);
  temp_date = get_ride_date(
      g_array_index(rides_of_the_day, RIDE,
                    0));  // The date of the rides in the array is fetched

  for (int i = starting_position;
       i < number_of_dates && compare_dates(upper_limit, temp_date) >= 0;
       i++) {  // If the date searched for already surpasses the upper limit the
               // cycle is stopped
    int number_of_rides = rides_of_the_day->len;
    for (int j = 0; j < number_of_rides; j++) {
      temp_ride =
          g_array_index(rides_of_the_day, RIDE,
                        j);  // Ride which we are calculating the total cost
      if (temp_ride == NULL)
        break;  // Make sure there is something in that array position
      char *ride_driver = get_ride_driver(temp_ride);
      temp_car_class = get_driver_car_class(g_hash_table_lookup(
          drivers_hash,
          ride_driver));  //  We need to get the driver's car class to calculate
                          //  the ride price, so we search for the driver using
                          //  the ride ID and get their car class
      total += calculate_ride_price(
          get_ride_distance(temp_ride),
          temp_car_class);  // the price of that specific ride is then
                            // calculated and added to the accumulator
      rides_counter++;
      free(ride_driver);
    }
    if (i < number_of_dates -
                1) {  // We check this to prevent acessing array positions that
                      // were never filled up (i+1 when i==number_of_dates-1
                      // would search for a NULL address)
      rides_of_the_day = g_array_index(rides_by_date, GArray *, i + 1);
      temp_date = get_ride_date(g_array_index(
          rides_of_the_day, RIDE,
          0));  // After all the rides of the day are accounted for, we update
                // the date to be the next one where rides happened, so the day
                // can be bound checked in the next iteration
    }
  }
  return (total /
          ((double)rides_counter));  // The average is then calculated and
                                     // returned using the accumulators
}

double calculate_avg_distance(GArray *rides_by_date, int starting_position,
                              struct date upper_limit, char *city) {
  double total = 0.f;     // Distance accumulator
  int rides_counter = 0;  // Rides Accumulator
  struct date temp_date;
  RIDE temp_ride = NULL;

  int number_of_dates =
      rides_by_date->len;  // Number of separate dates registered
  GArray *rides_of_the_day =
      g_array_index(rides_by_date, GArray *, starting_position);
  temp_date = get_ride_date(
      g_array_index(rides_of_the_day, RIDE,
                    0));  // The date of the rides in the array is fetched

  for (int i = starting_position;
       i < number_of_dates && compare_dates(upper_limit, temp_date) >= 0;
       i++) {  // If the date searched for already surpasses the upper limit the
               // cycle is stopped
    int number_of_rides = rides_of_the_day->len;
    for (int j = 0; j < number_of_rides; j++) {
      temp_ride =
          g_array_index(rides_of_the_day, RIDE,
                        j);  // Ride which we are calculating the total cost
      if (temp_ride == NULL)
        break;  // Make sure there is something in that array position

      char *ride_city = get_ride_city(temp_ride);
      if (strcmp(city, ride_city)) {
        free(ride_city);  // If the cities are different, we skip this ride and
                          // head to the next
      } else {
        free(ride_city);
        total +=
            get_ride_distance(temp_ride);  // the length of the ride is fetched
                                           // and added to the accumulator
        rides_counter++;
      }
    }
    if (i < number_of_dates -
                1) {  // We check this to prevent acessing array positions that
                      // were never filled up (i+1 when i==number_of_dates-1
                      // would search for a NULL address)
      rides_of_the_day = g_array_index(rides_by_date, GArray *, i + 1);
      temp_date = get_ride_date(g_array_index(
          rides_of_the_day, RIDE,
          0));  // After all the rides of the day are accounted for, we update
                // the date to be the next one where rides happened, so the day
                // can be bound checked in the next iteration
    }
  }
  return (total /
          ((double)rides_counter));  // The average is then calculated and
                                     // returned using the accumulators
}

void query8(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("%d: Query 8 elapsed time: %f seconds\n", counter, time_spent);

  (void)catalog;
  (void)stats;
  (void)parameter;
  (void)counter;
}

void query9(CATALOG catalog, STATS stats, char **parameter, int counter) {
  clock_t begin = clock();

  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "a");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  free(parameter);
  free(output_filename);
  fclose(output_file);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("%d: Query 9 elapsed time: %f seconds\n", counter, time_spent);

  (void)catalog;
  (void)stats;
  (void)parameter;
  (void)counter;
}

void get_user_profile(CATALOG catalog, char *id, int counter) {
  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);

  FILE *output_file = fopen(output_filename, "w");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  GHashTable *users_hash_table = get_catalog_users(catalog);
  USER user = g_hash_table_lookup(users_hash_table, id);

  if (user == NULL) {
    free(output_filename);
    fclose(output_file);
    printf("User with id %s does not exist\n", id);
    return;
  }

  char *name = get_user_name(user);
  enum gender gender = get_user_gender(user);

  int number_of_rides = get_user_number_of_rides(user);
  double average_rating =
      (double)(get_user_total_rating(user) / number_of_rides);

  double total_spent = get_user_total_spent(user);
  enum account_status account_status = get_user_account_status(user);

  if (account_status == ACTIVE) {
    fprintf(output_file, "%s;%s;%d;%.3f;%d;%.3f\n", name,
            gender_to_string(gender), calculate_age(get_user_birth_date(user)),
            average_rating, number_of_rides, total_spent);
  }

  free(name);
  free(output_filename);
  fclose(output_file);
}

void get_driver_profile(CATALOG catalog, char *id, int counter) {
  char *output_filename = malloc(sizeof(char) * 256);
  sprintf(output_filename, "Resultados/command%d_output.txt", counter);
  FILE *output_file = fopen(output_filename, "w");

  if (output_file == NULL) {
    printf("Error creating command%d_output.txt file\n", counter);
    return;
  }

  GHashTable *drivers_hash_table = get_catalog_drivers(catalog);
  DRIVER driver = g_hash_table_lookup(drivers_hash_table, id);

  if (driver == NULL) {
    free(output_filename);
    fclose(output_file);
    printf("Driver with id %s does not exist\n", id);
    return;
  }

  char *name = get_driver_name(driver);
  enum gender gender = get_driver_gender(driver);

  int number_of_rides = get_driver_number_of_rides(driver);
  double average_rating =
      (double)(get_driver_total_rating(driver) / number_of_rides);

  double total_earned = get_driver_total_earned(driver);
  enum account_status account_status = get_driver_account_status(driver);

  if (account_status == ACTIVE) {
    fprintf(output_file, "%s;%s;%d;%.3f;%d;%.3f\n", name,
            gender_to_string(gender),
            calculate_age(get_driver_birth_date(driver)), average_rating,
            number_of_rides, total_earned);
  }

  free(name);
  free(output_filename);
  fclose(output_file);
}
