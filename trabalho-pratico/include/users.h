#ifndef USERS_H
#define USERS_H

#include <glib.h>

#include "common.h"

#define MAX_USER_TOKENS 7

typedef struct user *USER;

USER create_user(void);

void insert_user(char **user_params, GHashTable *hash_table);

void set_user_username(USER user, char username_string[]);

void set_user_name(USER user, char name_string[]);

void set_user_gender(USER user, char gender_string[]);

void set_user_birth_date(USER user, char birth_date_string[]);

void set_user_account_creation(USER user, char account_creation_date[]);

void set_user_payment_method(USER user, char pay_method_string[]);

void set_user_account_status(USER user, char account_status_string[]);

char *get_user_username(USER user);

char *get_user_name(USER user);

enum gender get_user_gender(USER user);

struct date get_user_birth_date(USER user);

struct date get_user_account_creation(USER user);

enum pay_method get_user_pay_method(USER user);

enum account_status get_user_account_status(USER user);

void free_user(USER user);

#endif
