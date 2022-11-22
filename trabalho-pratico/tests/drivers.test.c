#include "drivers.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/greatest.h"
#include "common.h"

TEST driver_id_test(void) {
  DRIVER driver = create_driver();
  char *id = strdup("000000000003");

  set_driver_id(driver, id);

  ASSERT_STR_EQ(id, get_driver_id(driver));

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

  ASSERT_EQ(1, get_driver_birth_date(driver).day);
  ASSERT_EQ(1, get_driver_birth_date(driver).month);
  ASSERT_EQ(2002, get_driver_birth_date(driver).year);

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

TEST driver_license_plate_test(void) {
  DRIVER driver = create_driver();
  char *license_plate = strdup("AA-00-AA");

  set_driver_license_plate(driver, license_plate);

  ASSERT_STR_EQ(license_plate, get_driver_license_plate(driver));

  free(license_plate);

  PASS();
}

TEST driver_city_test(void) {
  DRIVER driver = create_driver();
  char *city = strdup("Lisboa");

  set_driver_city(driver, city);

  ASSERT_STR_EQ(city, get_driver_city(driver));

  free(city);

  PASS();
}

TEST driver_account_creation_test(void) {
  DRIVER driver = create_driver();
  char *account_creation = strdup("01/01/2002");

  set_driver_account_creation(driver, account_creation);

  ASSERT_EQ(1, get_driver_account_creation(driver).day);
  ASSERT_EQ(1, get_driver_account_creation(driver).month);
  ASSERT_EQ(2002, get_driver_account_creation(driver).year);

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
