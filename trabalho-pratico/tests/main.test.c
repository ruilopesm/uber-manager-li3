#include "../lib/greatest.h"

#include "drivers.test.c"
#include "rides.test.c"
#include "users.test.c"
#include "parser.test.c"

GREATEST_MAIN_DEFS();

SUITE(users) { RUN_TEST(user_insertion); }

SUITE(rides) { RUN_TEST(ride_insertion); }

SUITE(drivers) { RUN_TEST(driver_insertion); }

SUITE(parser) { RUN_TEST(line_parsing); }

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();

  RUN_SUITE(users);
  RUN_SUITE(rides);
  RUN_SUITE(drivers);
  RUN_SUITE(parser);

  GREATEST_MAIN_END();
}
