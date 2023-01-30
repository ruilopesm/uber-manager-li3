#include "users.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/greatest.h"
#include "utils.h"

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

  ASSERT(get_user_birth_date(user) == 20020101);

  free(birth_date);

  PASS();
}

TEST user_account_creation_test(void) {
  USER user = create_user();
  char *account_creation = strdup("01/01/2020");

  set_user_account_creation(user, account_creation);

  ASSERT(get_user_account_creation(user) == 20200101);

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
