#include "catalogs/users_catalog.h"

#include "entities/users.h"

struct users_catalog {
  GHashTable *users;

  // username: char * -> user_code: int
  GHashTable *users_code;

  // user_code: int -> username: char *
  GPtrArray *users_reverse_lookup;
};

USERS_CATALOG create_users_catalog(void) {
  USERS_CATALOG new_catalog = malloc(sizeof(struct users_catalog));

  new_catalog->users = g_hash_table_new_full(NULL, g_direct_equal, NULL,
                                             (GDestroyNotify)free_user);
  new_catalog->users_code =
      g_hash_table_new_full(g_str_hash, g_str_equal, free, NULL);
  new_catalog->users_reverse_lookup = g_ptr_array_new_with_free_func(free);

  return new_catalog;
}

void insert_user(USERS_CATALOG catalog, USER user, gpointer key) {
  g_hash_table_insert(catalog->users, key, user);
}

void update_user(USERS_CATALOG catalog, gpointer user_code, int distance,
                 double rating, double price, double tip, int date) {
  USER user = get_user_by_code(catalog, user_code);

  // Increment user's fields
  set_user_number_of_rides(user, get_user_number_of_rides(user) + 1);
  set_user_total_rating(user, get_user_total_rating(user) + rating);
  set_user_total_spent(user, get_user_total_spent(user) + price + tip);
  set_user_total_distance(user, get_user_total_distance(user) + distance);

  // Update user's latest ride
  if (date > get_user_latest_ride(user)) set_user_latest_ride(user, date);
}

void set_catalog_user_username(USERS_CATALOG catalog, USER user,
                               char *username) {
  static int users_parsed = 0;

  // Creates the user_code and inserts it into the users_code hash table
  char *first_copy = strdup(username);
  gpointer user_code = GINT_TO_POINTER(users_parsed);
  g_hash_table_insert(catalog->users_code, first_copy, user_code);

  // Inserts the username into the reverse lookup array
  char *second_copy = strdup(username);
  g_ptr_array_insert(catalog->users_reverse_lookup, users_parsed, second_copy);

  // Sets the user's username
  set_user_username(user, user_code);

  users_parsed++;
}

USER get_user_by_username(USERS_CATALOG catalog, char *username) {
  gpointer user_code = g_hash_table_lookup(catalog->users_code, username);

  if (user_code == NULL) return NULL;

  return g_hash_table_lookup(catalog->users, user_code);
}

USER get_user_by_code(USERS_CATALOG catalog, gpointer user_code) {
  return g_hash_table_lookup(catalog->users, user_code);
}

gpointer get_user_code_from_username(USERS_CATALOG catalog, char *username) {
  return g_hash_table_lookup(catalog->users_code, username);
}

char *get_username_from_code(USERS_CATALOG catalog, gpointer user_code) {
  return g_ptr_array_index(catalog->users_reverse_lookup,
                           GPOINTER_TO_INT(user_code));
}

void free_users_catalog(USERS_CATALOG catalog) {
  g_hash_table_destroy(catalog->users);
  g_hash_table_destroy(catalog->users_code);
  g_ptr_array_free(catalog->users_reverse_lookup, TRUE);
  free(catalog);
}
