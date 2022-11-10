#include "drivers.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/greatest.h"
#include "common.h"

TEST driver_insertion(void) {
  GHashTable *hash_table =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

  char **driver_params = malloc(sizeof(char *) * MAX_DRIVER_TOKENS);
  for (int i = 0; i < MAX_DRIVER_TOKENS; i++) {
    driver_params[i] = malloc(sizeof(char) * 1024);
  }

  driver_params[0] = strdup("000000000416");
  driver_params[1] = strdup("Duarte Ribeiro");
  driver_params[2] = strdup("06/12/1943");
  driver_params[3] = strdup("M");
  driver_params[4] = strdup("premium");
  driver_params[5] = strdup("91-CD-15");
  driver_params[6] = strdup("Gonça City");
  driver_params[7] = strdup("13/3/2020");
  driver_params[8] = strdup("active");

  insert_driver(driver_params, hash_table);

  DRIVER driver = g_hash_table_lookup(hash_table, "000000000416");
  ASSERT(driver != NULL);

  ASSERT_STR_EQ("000000000416", get_driver_id(driver));

  ASSERT_STR_EQ("Duarte Ribeiro", get_driver_name(driver));
  struct date driver_birth_date = get_driver_birth_date(driver);
  ASSERT_EQ(6, driver_birth_date.day);
  ASSERT_EQ(12, driver_birth_date.month);
  ASSERT_EQ(1943, driver_birth_date.year);
  ASSERT_ENUM_EQ(M, get_driver_gender(driver), gender_to_string);
  ASSERT_ENUM_EQ(PREMIUM, get_driver_car_class(driver), car_class_to_string);
  ASSERT_STR_EQ("91-CD-15", get_driver_license_plate(driver));
  ASSERT_STR_EQ("Gonça City", get_driver_city(driver));
  struct date driver_creation = get_driver_account_creation(driver);
  ASSERT_EQ(13, driver_creation.day);
  ASSERT_EQ(3, driver_creation.month);
  ASSERT_EQ(2020, driver_creation.year);
  ASSERT_ENUM_EQ(ACTIVE, get_driver_account_status(driver),
                 account_status_to_string);

  g_hash_table_destroy(hash_table);

  PASS();
}
