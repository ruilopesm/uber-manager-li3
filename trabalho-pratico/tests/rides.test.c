#include "rides.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/greatest.h"
#include "common.h"

TEST ride_insertion(void) {
  GHashTable *hash_table =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

  char **ride_params = malloc(sizeof(char *) * MAX_RIDE_TOKENS);
  for (int i = 0; i < MAX_RIDE_TOKENS; i++) {
    ride_params[i] = malloc(sizeof(char) * 1024);
  }

  ride_params[0] = strdup("000000000231");
  ride_params[1] = strdup("21/11/2018");
  ride_params[2] = strdup("000000009366");
  ride_params[3] = strdup("EmmCarneiro48");
  ride_params[4] = strdup("Lisboa");
  ride_params[5] = strdup("12");
  ride_params[6] = strdup("5");
  ride_params[7] = strdup("3");
  ride_params[8] = strdup("2.2");
  ride_params[9] = strdup("Very good car");

  insert_ride(ride_params, hash_table);

  RIDE ride = g_hash_table_lookup(hash_table, "000000000231");
  ASSERT(ride != NULL);

  ASSERT_STR_EQ("000000000231", get_ride_id(ride));

  struct date ride_date = get_ride_date(ride);
  ASSERT_EQ(21, ride_date.day);
  ASSERT_EQ(11, ride_date.month);
  ASSERT_EQ(2018, ride_date.year);

  ASSERT_STR_EQ("000000009366", get_ride_driver(ride));
  ASSERT_STR_EQ("EmmCarneiro48", get_ride_user(ride));
  ASSERT_STR_EQ("Lisboa", get_ride_city(ride));
  ASSERT_EQ(12, get_ride_distance(ride));
  ASSERT_EQ(5, get_ride_score_user(ride));
  ASSERT_EQ(3, get_ride_score_driver(ride));
  ASSERT_EQ(2.2, get_ride_tip(ride));
  ASSERT_STR_EQ("Very good car", get_ride_comment(ride));

  g_hash_table_destroy(hash_table);

  PASS();
}
