#include "../lib/greatest.h"

#include "rides.test.c"
#include "users.test.c"
#include "drivers.test.c"

GREATEST_MAIN_DEFS();

SUITE(users) { RUN_TEST(user_insertion); }

SUITE(rides) { RUN_TEST(ride_insertion); }

SUITE(drivers) { RUN_TEST(driver_insertion); }

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();

  RUN_SUITE(users);
  RUN_SUITE(rides);
  RUN_SUITE(drivers);

  GREATEST_MAIN_END();
}
