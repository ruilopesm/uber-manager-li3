#include "users.h"

#include <glib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/greatest.h"
#include "common.h"

TEST user_insertion(void) {
  GHashTable *hash_table =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

  char **user_params = malloc(sizeof(char *) * MAX_USER_TOKENS);
  for (int i = 0; i < MAX_USER_TOKENS; i++) {
    user_params[i] = malloc(sizeof(char) * 1024);
  }

  user_params[0] = strdup("LNascimento40");
  user_params[1] = strdup("Luis Nascimento");
  user_params[2] = strdup("M");
  user_params[3] = strdup("07/01/2003");
  user_params[4] = strdup("09/11/2020");
  user_params[5] = strdup("cash");
  user_params[6] = strdup("active");

  insert_user(user_params, hash_table);

  USER user = g_hash_table_lookup(hash_table, "LNascimento40");
  ASSERT(user != NULL);

  ASSERT_STR_EQ("LNascimento40", get_user_username(user));
  ASSERT_STR_EQ("Luis Nascimento", get_user_name(user));
  ASSERT_ENUM_EQ(M, get_user_gender(user), gender_to_string);

  struct date birth_date = get_user_birth_date(user);
  ASSERT_EQ(7, birth_date.day);
  ASSERT_EQ(1, birth_date.month);
  ASSERT_EQ(2003, birth_date.year);

  struct date account_creation = get_user_account_creation(user);
  ASSERT_EQ(9, account_creation.day);
  ASSERT_EQ(11, account_creation.month);
  ASSERT_EQ(2020, account_creation.year);

  ASSERT_ENUM_EQ(CASH, get_user_pay_method(user), pay_method_to_string);
  ASSERT_ENUM_EQ(ACTIVE, get_user_account_status(user),
                 account_status_to_string);

  g_hash_table_destroy(hash_table);

  PASS();
}
