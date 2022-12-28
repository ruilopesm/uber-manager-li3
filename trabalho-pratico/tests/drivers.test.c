#include "drivers.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/greatest.h"
#include "utils.h"

TEST driver_id_test(void) {
  DRIVER driver = create_driver();
  char *id = strdup("000000000003");

  set_driver_id(driver, id);

  ASSERT_EQ(3, get_driver_id(driver));

  free(id);

  PASS();
}

TEST driver_name_test(void) {
  DRIVER driver = create_driver();
  char *name = strdup("Joel Campos");

  set_driver_name(driver, name);

  ASSERT_STR_EQ(name, get_driver_name(driver));

  free(name);

  PASS();
}

TEST driver_birth_date_test(void) {
  DRIVER driver = create_driver();
  char *birth_date = strdup("01/01/2002");

  set_driver_birth_date(driver, birth_date);

  ASSERT_EQ(20020101, get_driver_birth_date(driver));

  free(birth_date);

  PASS();
}

TEST driver_gender_test(void) {
  DRIVER driver = create_driver();
  char *gender = strdup("M");

  set_driver_gender(driver, gender);

  ASSERT_ENUM_EQ(M, get_driver_gender(driver), gender_to_string);

  free(gender);

  PASS();
}

TEST driver_car_class_test(void) {
  DRIVER driver = create_driver();
  char *car_class = strdup("basic");

  set_driver_car_class(driver, car_class);

  ASSERT_ENUM_EQ(BASIC, get_driver_car_class(driver), car_class_to_string);

  free(car_class);

  PASS();
}

TEST driver_account_creation_test(void) {
  DRIVER driver = create_driver();
  char *account_creation = strdup("01/01/2002");

  set_driver_account_creation(driver, account_creation);

  ASSERT_EQ(20020101, get_driver_account_creation(driver));

  free(account_creation);

  PASS();
}

TEST driver_account_status_test(void) {
  DRIVER driver = create_driver();
  char *account_status = strdup("active");

  set_driver_account_status(driver, account_status);

  ASSERT_ENUM_EQ(ACTIVE, get_driver_account_status(driver),
                 account_status_to_string);

  free(account_status);

  PASS();
}
