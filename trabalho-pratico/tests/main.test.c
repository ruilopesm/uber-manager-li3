#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base/querier.h"
#include "base/stats.h"
#include "catalogs/joint_catalog.h"
#include "io/output.h"
#include "queries/query1.test.c"
#include "queries/query2.test.c"
#include "queries/query3.test.c"
#include "queries/query4.test.c"
#include "queries/query5.test.c"
#include "queries/query6.test.c"
#include "queries/query7.test.c"
#include "queries/query8.test.c"
#include "queries/query9.test.c"
#include "utils/utils.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <dataset>\n", argv[0]);
    return 1;
  }

  // Disclaimer
  printf("\033[0;31m[DISCLAIMER]\033[0m\n");
  printf(
      "\033[0;31mThis program only works with the dataset provided by the "
      "professors - data-regular.\033[0m\n");
  printf(
      "\033[0;31mIf you want to use another dataset, you will have to change "
      "the tests input.\033[0m\n");

  puts("\n");

  // Information about the tests
  printf("\033[0;32m[INFO]\033[0m\n");
  printf("\033[0;32mThis program will run 32 tests for the queries.\033[0m\n");
  printf(
      "\033[0;32mEvery time a query exceeds 0.01s it will be printed in red "
      "color.\033[0m\n");
  printf(
      "\033[0;32mIf you want to change the maximum time, change the MAX_TIME "
      "variable in the tests.\033[0m\n");

  puts("\n");

  printf("Press any key to continue...");
  getchar();

  // Tests part
  g_test_init(&argc, &argv, NULL);

  USERS_CATALOG users_catalog = create_users_catalog();
  DRIVERS_CATALOG drivers_catalog = create_drivers_catalog();
  RIDES_CATALOG rides_catalog = create_rides_catalog();
  JOINT_CATALOG join_catalog =
      create_joint_catalog(users_catalog, drivers_catalog, rides_catalog);
  STATS stats = create_stats();

  // Setup dataset
  setup_catalog_and_stats(join_catalog, stats, argv[1]);

  // Create output directory
  create_directory("./Resultados");

  // Query 1
  struct query1_test_data data = {join_catalog, stats};

  g_test_add_data_func("/query1/valid_user", &data, query1_valid_user);
  g_test_add_data_func("/query1/valid_driver", &data, query1_valid_driver);
  g_test_add_data_func("/query1/invalid_user", &data, query1_invalid_user);
  g_test_add_data_func("/query1/invalid_driver", &data, query1_invalid_driver);

  // Query 2
  struct query2_test_data data2 = {join_catalog, stats};

  g_test_add_data_func("/query2/0_elements", &data2, query2_0_elements);
  g_test_add_data_func("/query2/10_elements", &data2, query2_10_elements);
  g_test_add_data_func("/query2/100_elements", &data2, query2_100_elements);
  g_test_add_data_func("/query2/500_elements", &data2, query2_500_elements);

  // Query 3
  struct query3_test_data data3 = {join_catalog, stats};

  g_test_add_data_func("/query3/0_elements", &data3, query3_0_elements);
  g_test_add_data_func("/query3/10_elements", &data3, query3_10_elements);
  g_test_add_data_func("/query3/100_elements", &data3, query3_100_elements);
  g_test_add_data_func("/query3/500_elements", &data3, query3_500_elements);

  // Query 4
  struct query4_test_data data4 = {join_catalog, stats};

  g_test_add_data_func("/query4/valid_city", &data4, query4_valid_city);
  g_test_add_data_func("/query4/invalid_city", &data4, query4_invalid_city);

  // Query 5
  struct query5_test_data data5 = {join_catalog, stats};

  g_test_add_data_func("/query5/valid_dates", &data5, query5_valid_dates);
  g_test_add_data_func("/query5/invalid_dates", &data5, query5_invalid_dates);
  g_test_add_data_func("/query5/large_range", &data5, query5_large_range);

  // Query 6
  struct query6_test_data data6 = {join_catalog, stats};

  g_test_add_data_func("/query6/valid_city_and_dates", &data6,
                       query6_valid_city_and_dates);
  g_test_add_data_func("/query6/invalid_city", &data6, query6_invalid_city);
  g_test_add_data_func("/query6/invalid_dates", &data6, query6_invalid_dates);
  g_test_add_data_func("/query6/large_range", &data6, query6_large_range);

  // Query 7
  struct query7_test_data data7 = {join_catalog, stats};

  g_test_add_data_func("/query7/0_elements", &data7, query7_0_elements);
  g_test_add_data_func("/query7/10_elements", &data7, query7_10_elements);
  g_test_add_data_func("/query7/100_elements", &data7, query7_100_elements);
  g_test_add_data_func("/query7/500_elements", &data7, query7_500_elements);
  g_test_add_data_func("/query7/invalid_city", &data7, query7_invalid_city);

  // Query 8
  struct query8_test_data data8 = {join_catalog, stats};

  g_test_add_data_func("/query8/male", &data8, query8_male);
  g_test_add_data_func("/query8/female", &data8, query8_female);
  g_test_add_data_func("/query8/big_age", &data8, query8_big_age);

  // Query 9
  struct query9_test_data data9 = {join_catalog, stats};

  g_test_add_data_func("/query9/valid_dates", &data9, query9_valid_dates);
  g_test_add_data_func("/query9/invalid_dates", &data9, query9_invalid_dates);
  g_test_add_data_func("/query9/large_range", &data9, query9_large_range);

  // Run tests
  return g_test_run();
}
