#include "../lib/greatest.h"

#include "users.test.c"

GREATEST_MAIN_DEFS();

SUITE(users) {
  RUN_TEST(user_insertion);
}

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();

  RUN_SUITE(users);

  GREATEST_MAIN_END();
}
