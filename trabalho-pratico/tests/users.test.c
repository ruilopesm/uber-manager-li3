#include "users.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/greatest.h"
#include "common.h"

TEST user_username_test(void) {
  USER user = create_user();
  char *username = strdup("JorBranco31");

  set_user_username(user, username);

  ASSERT_STR_EQ(username, get_user_username(user));

  free(username);

  PASS();
}

TEST user_name_test(void) {
  USER user = create_user();
  char *name = strdup("Jorge Branco");

  set_user_name(user, name);

  ASSERT_STR_EQ(name, get_user_name(user));

  free(name);

  PASS();
}

TEST user_gender_test(void) {
  USER user = create_user();
  char *gender = strdup("M");

  set_user_gender(user, gender);

  ASSERT_ENUM_EQ(M, get_user_gender(user), gender_to_string);

  free(gender);

  PASS();
}

TEST user_birth_date_test(void) {
  USER user = create_user();
  char *birth_date = strdup("01/01/2002");

  set_user_birth_date(user, birth_date);

  ASSERT(get_user_birth_date(user).day == 1);
  ASSERT(get_user_birth_date(user).month == 1);
  ASSERT(get_user_birth_date(user).year == 2002);

  free(birth_date);

  PASS();
}

TEST user_account_creation_test(void) {
  USER user = create_user();
  char *account_creation = strdup("01/01/2020");

  set_user_account_creation(user, account_creation);

  ASSERT(get_user_account_creation(user).day == 1);
  ASSERT(get_user_account_creation(user).month == 1);
  ASSERT(get_user_account_creation(user).year == 2020);

  free(account_creation);

  PASS();
}

TEST user_pay_method_test(void) {
  USER user = create_user();
  char *pay_method = strdup("cash");

  set_user_pay_method(user, pay_method);

  ASSERT_ENUM_EQ(CASH, get_user_pay_method(user), pay_method_to_string);

  free(pay_method);

  PASS();
}

TEST user_account_status_test(void) {
  USER user = create_user();
  char *account_status = strdup("active");

  set_user_account_status(user, account_status);

  ASSERT_ENUM_EQ(ACTIVE, get_user_account_status(user),
                 account_status_to_string);

  free(account_status);

  PASS();
}

TEST user_number_of_rides_test(void) {
  USER user = create_user();
  int number_of_rides = 10;

  set_user_number_of_rides(user, number_of_rides);

  ASSERT_EQ(number_of_rides, get_user_number_of_rides(user));

  PASS();
}

TEST user_total_rating_test(void) {
  USER user = create_user();
  int total_rating = 10;

  set_user_total_rating(user, total_rating);

  ASSERT_EQ(total_rating, get_user_total_rating(user));

  PASS();
}

TEST user_total_spent_test(void) {
  USER user = create_user();
  double total_spent = 10.0;

  set_user_total_spent(user, total_spent);

  ASSERT_EQ(total_spent, get_user_total_spent(user));

  PASS();
}
