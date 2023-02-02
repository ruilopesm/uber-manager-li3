#include "io/output.h"

#include <glib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "base/querier.h"
#include "utils/components.h"
#include "views/execute_query.h"

// Used in batch mode
void write_query_result(FILE *output_file, void *result, char query_type) {
  if (result == NULL) {
    return;
  }

  static file_output_function_pointer table[] = {
      write_query1_result, write_query2_result, write_query3_result,
      write_query4_result, write_query5_result, write_query6_result,
      write_query7_result, write_query8_result, write_query9_result};

  table[query_type - '1'](output_file, result);
}

// Used in interactive mode
void draw_query_result(MANAGER manager, WINDOW *win, char *title, void *result,
                       char query_type) {
  static window_output_function_pointer table[] = {
      draw_query1_result, draw_query2_result, draw_query3_result,
      draw_query4_result, draw_query5_result, draw_query6_result,
      draw_query7_result, draw_query8_result, draw_query9_result};

  table[query_type - '1'](manager, win, result, title);
}

void write_query1_result(FILE *output_file, void *result) {
  QUERY1_RESULT query_result = (QUERY1_RESULT)result;
  bool is_user = get_query1_bool(query_result);

  if (is_user) {
    USER user = get_query1_result_user(query_result);

    char *name = get_user_name(user);
    enum gender gender = get_user_gender(user);
    int number_of_rides = get_user_number_of_rides(user);
    double total_rating = get_user_total_rating(user);
    double average_rating = (double)(total_rating / number_of_rides);
    double total_spent = get_user_total_spent(user);

    fprintf(output_file, "%s;%s;%d;%.3f;%d;%.3f\n", name,
            gender_to_string(gender), calculate_age(get_user_birth_date(user)),
            average_rating, number_of_rides, total_spent);

    free(name);
  } else {
    DRIVER driver = get_query1_result_driver(query_result);

    char *name = get_driver_name(driver);
    enum gender gender = get_driver_gender(driver);
    int number_of_rides = get_driver_number_of_rides(driver);
    double total_rating = get_driver_total_rating(driver);
    double average_rating = (double)(total_rating / number_of_rides);
    double total_earned = get_driver_total_earned(driver);

    fprintf(output_file, "%s;%s;%d;%.3f;%d;%.3f\n", name,
            gender_to_string(gender),
            calculate_age(get_driver_birth_date(driver)), average_rating,
            number_of_rides, total_earned);

    free(name);
  }
}

void draw_query1_result(MANAGER manager, WINDOW *win, char *title,
                        void *result) {
  QUERY1_RESULT query_result = (QUERY1_RESULT)result;
  bool is_user = get_query1_bool(query_result);

  if (is_user) {
    USER user = get_query1_result_user(query_result);

    char *name = get_user_name(user);
    enum gender gender = get_user_gender(user);
    int number_of_rides = get_user_number_of_rides(user);
    double total_rating = get_user_total_rating(user);
    double average_rating = (double)(total_rating / number_of_rides);
    double total_spent = get_user_total_spent(user);

    char *to_print = malloc(sizeof(char) * 512);
    sprintf(to_print,
            "Result of the query: %s;%s;%d;%.3f;%d;%.3f (Press any key to "
            "input a query again)",
            name, gender_to_string(gender),
            calculate_age(get_user_birth_date(user)), average_rating,
            number_of_rides, total_spent);
    draw_warning_subwin(win, to_print);

    free(name);
    free(to_print);
  } else {
    DRIVER driver = get_query1_result_driver(query_result);

    char *name = get_driver_name(driver);
    enum gender gender = get_driver_gender(driver);
    int number_of_rides = get_driver_number_of_rides(driver);
    double total_rating = get_driver_total_rating(driver);
    double average_rating = (double)(total_rating / number_of_rides);
    double total_earned = get_driver_total_earned(driver);

    char *to_print = malloc(sizeof(char) * 512);
    sprintf(to_print,
            "Result of the query: %s;%s;%d;%.3f;%d;%.3f (Press any key to "
            "input a query again)",
            name, gender_to_string(gender),
            calculate_age(get_driver_birth_date(driver)), average_rating,
            number_of_rides, total_earned);
    draw_warning_subwin(win, to_print);

    free(name);
  }

  (void)manager;
  (void)title;
}

void write_query2_result(FILE *output_file, void *result) {
  GArray *query_result = (GArray *)result;

  for (int i = 0; i < (int)query_result->len; i++) {
    DRIVER driver = g_array_index(query_result, DRIVER, i);

    int driver_id = get_driver_id(driver);
    char *name = get_driver_name(driver);
    int number_of_rides = get_driver_number_of_rides(driver);
    double total_rating = get_driver_total_rating(driver);
    double average_rating = (double)(total_rating / number_of_rides);

    fprintf(output_file, "%012d;%s;%.3f\n", driver_id, name, average_rating);

    free(name);
  }
}

void draw_query2_result(MANAGER manager, WINDOW *win, char *title,
                        void *result) {
  int y, x;
  getmaxyx(win, y, x);

  GArray *drivers = (GArray *)result;

  int current_page = 0;
  int drivers_per_page = y - 4;
  int max_pages = (int)(drivers->len / drivers_per_page) + 1;

  if (drivers->len % drivers_per_page == 0) {
    max_pages--;
  }

  while (true) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, title);

    mvwprintw(win, y - 1, 2, "Page %d of %d", current_page + 1, max_pages);

    // Draw schema & instructions
    mvwprintw(win, 0, x / 2 - 15, "driver_id;name;average_score");
    mvwprintw(win, y - 1, x / 2 - 15, "n: next page, p: previous page");
    mvwprintw(win, y - 1, x - 15 - 2, "Press q to quit");

    // Draw drivers
    int counter = 0;
    int start = current_page * drivers_per_page;
    int end = start + drivers_per_page - 1;

    for (int i = 0; i < (int)drivers->len; i++) {
      if (counter >= start && counter <= end) {
        DRIVER driver = g_array_index(drivers, DRIVER, i);

        int driver_id = get_driver_id(driver);
        char *name = get_driver_name(driver);
        int number_of_rides = get_driver_number_of_rides(driver);
        double total_rating = get_driver_total_rating(driver);
        double average_rating = (double)(total_rating / number_of_rides);

        mvwprintw(win, counter - start + 2, x / 2 - 15, "%012d;%s;%.3f",
                  driver_id, name, average_rating);

        free(name);
      }

      counter++;
    }

    int key;
    key = wgetch(win);

    switch (key) {
      case 'q':
        g_array_free(drivers, true);
        change_page_and_cleanup_window(manager, EXECUTE_QUERY, win);
        echo();
        execute_query(manager);
        break;

      case 'n':
        if (current_page < max_pages - 1) {
          current_page++;
        }

        break;

      case 'p':
        if (current_page > 0) {
          current_page--;
        }

        break;
    }
  }
}

void write_query3_result(FILE *output_file, void *result) {
  QUERY3_RESULT query_result = (QUERY3_RESULT)result;
  GArray *users = get_query3_result_users(query_result);
  GPtrArray *users_reverse_lookup =
      get_query3_result_users_reverse_lookup(query_result);

  for (int i = 0; i < (int)users->len; i++) {
    USER user = g_array_index(users, USER, i);

    int username = get_user_username(user);
    char *username_str = g_ptr_array_index(users_reverse_lookup, username);
    char *name = get_user_name(user);
    int total_distance = get_user_total_distance(user);

    fprintf(output_file, "%s;%s;%d\n", username_str, name, total_distance);

    free(name);
  }
}

void draw_query3_result(MANAGER manager, WINDOW *win, char *title,
                        void *result) {
  int y, x;
  getmaxyx(win, y, x);

  QUERY3_RESULT query_result = (QUERY3_RESULT)result;
  GArray *users = get_query3_result_users(query_result);
  GPtrArray *users_reverse_lookup =
      get_query3_result_users_reverse_lookup(query_result);

  int current_page = 0;
  int users_per_page = y - 4;
  int max_pages = (int)(users->len / users_per_page) + 1;

  if (users->len % users_per_page == 0) {
    max_pages--;
  }

  while (true) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, title);

    mvwprintw(win, y - 1, 2, "Page %d of %d", current_page + 1, max_pages);

    // Draw schema & instructions
    mvwprintw(win, 0, x / 2 - 15, "username;name;total_distance");
    mvwprintw(win, y - 1, x / 2 - 15, "n: next page, p: previous page");
    mvwprintw(win, y - 1, x - 15 - 2, "Press q to quit");

    // Draw users
    int counter = 0;
    int start = current_page * users_per_page;
    int end = start + users_per_page - 1;

    for (int i = 0; i < (int)users->len; i++) {
      if (counter >= start && counter <= end) {
        USER user = g_array_index(users, USER, i);

        int username = get_user_username(user);
        char *username_str = g_ptr_array_index(users_reverse_lookup, username);
        char *name = get_user_name(user);
        int total_distance = get_user_total_distance(user);

        mvwprintw(win, counter - start + 2, x / 2 - 15, "%s;%s;%d",
                  username_str, name, total_distance);

        free(name);
      }

      counter++;
    }

    int key;
    key = wgetch(win);

    switch (key) {
      case 'q':
        g_array_free(users, true);
        free(query_result);
        change_page_and_cleanup_window(manager, EXECUTE_QUERY, win);
        echo();
        execute_query(manager);
        break;

      case 'n':
        if (current_page < max_pages - 1) {
          current_page++;
        }

        break;

      case 'p':
        if (current_page > 0) {
          current_page--;
        }

        break;
    }
  }
}

void write_query4_result(FILE *output_file, void *result) {
  char *query_result = (char *)result;
  fprintf(output_file, "%s\n", query_result);
}

void draw_query4_result(MANAGER manager, WINDOW *win, char *title,
                        void *result) {
  char *query_result = (char *)result;

  char *to_print = malloc(sizeof(char) * 128);
  sprintf(to_print,
          "Result of the query: %s (Press any key to input a query again)",
          query_result);
  draw_warning_subwin(win, to_print);

  (void)manager;
  (void)title;

  free(to_print);
}

void write_query5_result(FILE *output_file, void *result) {
  char *query_result = (char *)result;
  fprintf(output_file, "%s\n", query_result);
}

void draw_query5_result(MANAGER manager, WINDOW *win, char *title,
                        void *result) {
  char *query_result = (char *)result;

  char *to_print = malloc(sizeof(char) * 128);
  sprintf(to_print,
          "Result of the query: %s (Press any key to input a query again)",
          query_result);
  draw_warning_subwin(win, to_print);

  (void)manager;
  (void)title;

  free(to_print);
}

void write_query6_result(FILE *output_file, void *result) {
  char *query_result = (char *)result;
  fprintf(output_file, "%s\n", query_result);
}

void draw_query6_result(MANAGER manager, WINDOW *win, char *title,
                        void *result) {
  char *query_result = (char *)result;

  char *to_print = malloc(sizeof(char) * 128);
  sprintf(to_print,
          "Result of the query: %s (Press any key to input a query again)",
          query_result);
  draw_warning_subwin(win, to_print);

  (void)manager;
  (void)title;

  free(to_print);
}

void write_query7_result(FILE *output_file, void *result) {
  GPtrArray *drivers = (GPtrArray *)result;

  for (int i = 0; i < (int)drivers->len; i++) {
    QUERY7_AUXILIAR auxiliar = g_ptr_array_index(drivers, i);

    DRIVER driver = get_query7_auxiliar_driver(auxiliar);
    int driver_id = get_driver_id(driver);
    char *name = get_driver_name(driver);
    double average_score = get_query7_auxiliar_average_score(auxiliar);

    fprintf(output_file, "%012d;%s;%.3f\n", driver_id, name, average_score);

    free(name);
  }
}

void draw_query7_result(MANAGER manager, WINDOW *win, char *title,
                        void *result) {
  int y, x;
  getmaxyx(win, y, x);

  GPtrArray *drivers = (GPtrArray *)result;

  int current_page = 0;
  int drivers_per_page = y - 4;
  int max_pages = (int)(drivers->len / drivers_per_page) + 1;

  if (drivers->len % drivers_per_page == 0) {
    max_pages--;
  }

  while (true) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, title);

    mvwprintw(win, y - 1, 2, "Page %d of %d", current_page + 1, max_pages);

    // Draw schema & instructions
    mvwprintw(win, 0, x / 2 - 15, "driver_id;name;average_score");
    mvwprintw(win, y - 1, x / 2 - 15, "n: next page, p: previous page");
    mvwprintw(win, y - 1, x - 15 - 2, "Press q to quit");

    // Draw drivers
    int counter = 0;
    int start = current_page * drivers_per_page;
    int end = start + drivers_per_page - 1;

    for (int i = 0; i < (int)drivers->len; i++) {
      if (counter >= start && counter <= end) {
        QUERY7_AUXILIAR auxiliar = g_ptr_array_index(drivers, i);

        DRIVER driver = get_query7_auxiliar_driver(auxiliar);
        int driver_id = get_driver_id(driver);
        char *name = get_driver_name(driver);
        double average_score = get_query7_auxiliar_average_score(auxiliar);

        mvwprintw(win, counter - start + 2, x / 2 - 15, "%012d;%s;%.3f",
                  driver_id, name, average_score);

        free(name);
      }

      counter++;
    }

    int key;
    key = wgetch(win);

    switch (key) {
      case 'q':
        g_ptr_array_free(drivers, true);
        change_page_and_cleanup_window(manager, EXECUTE_QUERY, win);
        echo();
        execute_query(manager);
        break;

      case 'n':
        if (current_page < max_pages - 1) {
          current_page++;
        }

        break;

      case 'p':
        if (current_page > 0) {
          current_page--;
        }

        break;
    }
  }
}

void write_query8_result(FILE *output_file, void *result) {
  QUERY8_RESULT query_result = (QUERY8_RESULT)result;
  GArray *rides = get_query8_result_top_rides(query_result);
  GPtrArray *users_reverse =
      get_query8_result_users_reverse_lookup(query_result);

  CATALOG catalog = get_query8_result_catalog(query_result);

  for (int i = 0; i < (int)rides->len; i++) {
    RIDE_GENDER_STATS ride = g_array_index(rides, RIDE_GENDER_STATS, i);

    int username = get_ride_gender_stats_username(ride);
    char *username_str = g_ptr_array_index(users_reverse, username);
    USER user = get_user_by_username(catalog, username_str);
    char *user_name = get_user_name(user);

    int driver_id = get_ride_gender_stats_driver_id(ride);
    DRIVER driver = get_driver_by_id(catalog, driver_id);
    char *driver_name = get_driver_name(driver);

    fprintf(output_file, "%012d;%s;%s;%s\n", driver_id, driver_name,
            username_str, user_name);

    free(user_name);
    free(driver_name);
  }
}

void draw_query8_result(MANAGER manager, WINDOW *win, char *title,
                        void *result) {
  int y, x;
  getmaxyx(win, y, x);

  QUERY8_RESULT query_result = (QUERY8_RESULT)result;
  GArray *rides = get_query8_result_top_rides(query_result);
  GPtrArray *users_reverse =
      get_query8_result_users_reverse_lookup(query_result);

  CATALOG catalog = get_query8_result_catalog(query_result);

  int current_page = 0;
  int rides_per_page = y - 4;
  int max_pages = (int)(rides->len / rides_per_page) + 1;

  if (rides->len % rides_per_page == 0) {
    max_pages--;
  }

  while (true) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, title);

    mvwprintw(win, y - 1, 2, "Page %d of %d", current_page + 1, max_pages);

    // Draw schema & instructions
    mvwprintw(win, 0, x / 2 - 25, "driver_id;driver_name;username;user_name");
    mvwprintw(win, y - 1, x / 2 - 15, "n: next page, p: previous page");
    mvwprintw(win, y - 1, x - 15 - 2, "Press q to quit");

    // Draw rides
    int counter = 0;
    int start = current_page * rides_per_page;
    int end = start + rides_per_page - 1;

    for (int i = 0; i < (int)rides->len; i++) {
      if (counter >= start && counter <= end) {
        RIDE_GENDER_STATS ride = g_array_index(rides, RIDE_GENDER_STATS, i);

        int username = get_ride_gender_stats_username(ride);
        char *username_str = g_ptr_array_index(users_reverse, username);
        USER user = get_user_by_username(catalog, username_str);
        char *user_name = get_user_name(user);

        int driver_id = get_ride_gender_stats_driver_id(ride);
        DRIVER driver = get_driver_by_id(catalog, driver_id);
        char *driver_name = get_driver_name(driver);

        mvwprintw(win, counter - start + 2, x / 2 - 25, "%012d;%s;%s;%s",
                  driver_id, driver_name, username_str, user_name);

        free(user_name);
        free(driver_name);
      }

      counter++;
    }

    int key;
    key = wgetch(win);

    switch (key) {
      case 'q':
        g_array_free(rides, true);
        free(query_result);
        change_page_and_cleanup_window(manager, EXECUTE_QUERY, win);
        echo();
        execute_query(manager);
        break;

      case 'n':
        if (current_page < max_pages - 1) {
          current_page++;
        }

        break;

      case 'p':
        if (current_page > 0) {
          current_page--;
        }

        break;
    }
  }
}

void write_query9_result(FILE *output_file, void *result) {
  QUERY9_RESULT query_result = (QUERY9_RESULT)result;
  GArray *rides = get_query9_result_rides_in_range(query_result);
  GPtrArray *cities_reverse =
      get_query9_result_cities_reverse_lookup(query_result);

  for (int i = rides->len - 1; i >= 0; i--) {
    RIDE ride = g_array_index(rides, RIDE, i);

    int id = get_ride_id(ride);
    char *date = date_to_string(get_ride_date(ride));
    int distance = get_ride_distance(ride);
    char *city = g_ptr_array_index(cities_reverse, get_ride_city(ride));
    double tip = get_ride_tip(ride);

    fprintf(output_file, "%012d;%s;%d;%s;%.3f\n", id, date, distance, city,
            tip);

    free(date);
  }
}

void draw_query9_result(MANAGER manager, WINDOW *win, char *title,
                        void *result) {
  int y, x;
  getmaxyx(win, y, x);

  QUERY9_RESULT query_result = (QUERY9_RESULT)result;
  GArray *rides = get_query9_result_rides_in_range(query_result);
  GPtrArray *cities_reverse =
      get_query9_result_cities_reverse_lookup(query_result);

  int current_page = 0;
  int rides_per_page = y - 4;
  int max_pages = (int)(rides->len / rides_per_page) + 1;

  if (rides->len % rides_per_page == 0) {
    max_pages--;
  }

  while (true) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, title);

    mvwprintw(win, y - 1, 2, "Page %d of %d", current_page + 1, max_pages);

    // Draw schema & instructions
    mvwprintw(win, 0, x / 2 - 15, "ride_id;date;distance;city;tip");
    mvwprintw(win, y - 1, x / 2 - 15, "n: next page, p: previous page");
    mvwprintw(win, y - 1, x - 15 - 2, "Press q to quit");

    // Draw rides
    int counter = 0;
    int start = current_page * rides_per_page;
    int end = start + rides_per_page - 1;

    for (int i = rides->len - 1; i >= 0; i--) {
      if (counter >= start && counter <= end) {
        RIDE ride = g_array_index(rides, RIDE, i);

        int id = get_ride_id(ride);
        char *date = date_to_string(get_ride_date(ride));
        int distance = get_ride_distance(ride);
        char *city = g_ptr_array_index(cities_reverse, get_ride_city(ride));
        double tip = get_ride_tip(ride);

        mvwprintw(win, counter - start + 2, x / 2 - 15, "%012d;%s;%d;%s;%.3f",
                  id, date, distance, city, tip);

        free(date);
      }

      counter++;
    }

    int key;
    key = wgetch(win);

    switch (key) {
      case 'q':
        g_array_free(rides, true);
        free(query_result);
        change_page_and_cleanup_window(manager, EXECUTE_QUERY, win);
        echo();
        execute_query(manager);
        break;

      case 'n':
        if (current_page < max_pages - 1) {
          current_page++;
        }

        break;

      case 'p':
        if (current_page > 0) {
          current_page--;
        }

        break;
    }
  }
}
