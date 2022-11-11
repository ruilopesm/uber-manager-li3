#include "users.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
  char *username;
  char *name;
  enum gender gender;
  struct date birth_date;
  struct date account_creation;
  enum pay_method pay_method;
  enum account_status account_status;
};

USER create_user(void) {
  USER new_user = malloc(sizeof(struct user));
  new_user->username = NULL;
  new_user->name = NULL;

  return new_user;
}

void insert_user(char **user_params, GHashTable *hash_table) {
  USER user = create_user();

  set_user_username(user, user_params[0]);
  set_user_name(user, user_params[1]);
  set_user_gender(user, user_params[2]);
  set_user_birth_date(user, user_params[3]);
  set_user_account_creation(user, user_params[4]);
  set_user_payment_method(user, user_params[5]);
  set_user_account_status(user, user_params[6]);

  g_hash_table_insert(hash_table, user->username, user);
}

void set_user_username(USER user, char username_string[]) {
  char *username = strdup(username_string);
  user->username = username;
}

void set_user_name(USER user, char name_string[]) {
  char *name = strdup(name_string);
  user->name = name;
}

void set_user_gender(USER user, char gender_string[]) {
  enum gender gender;

  if (!strcmp(gender_string, "M")) {
    gender = M;
  } else {
    gender = F;
  }

  user->gender = gender;
}

void set_user_birth_date(USER user, char birth_date_string[]) {
  struct date birth_date;
  int day, month, year;

  sscanf(birth_date_string, "%d/%d/%d", &day, &month, &year);

  birth_date.day = day;
  birth_date.month = month;
  birth_date.year = year;

  user->birth_date = birth_date;
}

void set_user_account_creation(USER user, char account_creation_date_string[]) {
  struct date account_creation;
  int day, month, year;

  sscanf(account_creation_date_string, "%d/%d/%d", &day, &month, &year);

  account_creation.day = day;
  account_creation.month = month;
  account_creation.year = year;

  user->account_creation = account_creation;
}

void set_user_payment_method(USER user, char pay_method_string[]) {
  enum pay_method pay_method;

  if (!strcmp(pay_method_string, "cash")) {
    pay_method = CASH;
  } else if (!strcmp(pay_method_string, "credit_card")) {
    pay_method = CREDIT_CARD;
  } else {
    pay_method = DEBIT_CARD;
  }

  user->pay_method = pay_method;
}

void set_user_account_status(USER user, char account_status_string[]) {
  enum account_status account_status;

  if (!strcmp(account_status_string, "active")) {
    account_status = ACTIVE;
  } else {
    account_status = INACTIVE;
  }

  user->account_status = account_status;
}

char *get_user_username(USER user) {
  char *username_copy = strdup(user->username);

  return username_copy;
}

char *get_user_name(USER user) {
  char *name_copy = strdup(user->name);

  return name_copy;
}

enum gender get_user_gender(USER user) {
  enum gender gender_copy = user->gender;

  return gender_copy;
}

struct date get_user_birth_date(USER user) {
  struct date birth_date_copy = user->birth_date;

  return birth_date_copy;
}

struct date get_user_account_creation(USER user) {
  struct date account_creation_copy = user->account_creation;

  return account_creation_copy;
}

enum pay_method get_user_pay_method(USER user) {
  enum pay_method pay_method_copy = user->pay_method;

  return pay_method_copy;
}

enum account_status get_user_account_status(USER user) {
  enum account_status account_status_copy = user->account_status;

  return account_status_copy;
}

void free_user(USER user) {
  free(user->name);
  free(user);
}