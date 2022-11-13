#include "../lib/greatest.h"
#include "drivers.test.c"
#include "parser.test.c"
#include "rides.test.c"
#include "users.test.c"

GREATEST_MAIN_DEFS();

SUITE(users) {
  RUN_TEST(user_username_test);
  RUN_TEST(user_name_test);
  RUN_TEST(user_gender_test);
  RUN_TEST(user_birth_date_test);
  RUN_TEST(user_account_creation_test);
  RUN_TEST(user_pay_method_test);
  RUN_TEST(user_account_status_test);
  RUN_TEST(user_number_of_rides_test);
  RUN_TEST(user_total_rating_test);
  RUN_TEST(user_total_spent_test);
}

SUITE(drivers) {
  RUN_TEST(driver_id_test);
  RUN_TEST(driver_name_test);
  RUN_TEST(driver_birth_date_test);
  RUN_TEST(driver_gender_test);
  RUN_TEST(driver_car_class_test);
  RUN_TEST(driver_license_plate_test);
  RUN_TEST(driver_city_test);
  RUN_TEST(driver_account_creation_test);
  RUN_TEST(driver_account_status_test);
  RUN_TEST(driver_number_of_rides_test);
  RUN_TEST(driver_total_rating_test);
  RUN_TEST(driver_total_earned_test);
}

SUITE(rides) {
  RUN_TEST(ride_id_test);
  RUN_TEST(ride_date_test);
  RUN_TEST(ride_driver_test);
  RUN_TEST(ride_user_test);
  RUN_TEST(ride_city_test);
  RUN_TEST(ride_distance_test);
  RUN_TEST(ride_score_user_test);
  RUN_TEST(ride_score_driver_test);
  RUN_TEST(ride_tip_test);
  RUN_TEST(ride_comment_test);
}

SUITE(parser) { RUN_TEST(parse_line_test); }

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();

  RUN_SUITE(users);
  RUN_SUITE(drivers);
  RUN_SUITE(rides);
  RUN_SUITE(parser);

  GREATEST_MAIN_END();
}
