#include "catalogs/rides_catalog.h"

#include "entities/rides.h"

struct rides_catalog {
  GHashTable *rides;

  // city: char * -> city_code: int
  GHashTable *cities_code;

  // city_code: int -> city: char *
  GPtrArray *cities_reverse_lookup;
};

RIDES_CATALOG create_rides_catalog(void) {
  RIDES_CATALOG new_catalog = malloc(sizeof(struct rides_catalog));

  new_catalog->rides = g_hash_table_new_full(NULL, g_direct_equal, NULL, free);
  new_catalog->cities_code =
      g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
  new_catalog->cities_reverse_lookup = g_ptr_array_new_with_free_func(free);

  return new_catalog;
}

void insert_ride(RIDES_CATALOG catalog, RIDE ride, gpointer key) {
  g_hash_table_insert(catalog->rides, key, ride);
}

void set_catalog_ride_city(RIDES_CATALOG catalog, RIDE ride, char *city) {
  static char cities_parsed = 0;

  char *city_number;
  city_number = g_hash_table_lookup(catalog->cities_code, city);

  if (city_number) {
    set_ride_city(ride, *city_number);
  } else {
    char *first_copy = strdup(city);
    g_ptr_array_add(catalog->cities_reverse_lookup, first_copy);

    city_number = malloc(sizeof(char));
    *city_number = cities_parsed++;

    char *second_copy = strdup(city);
    g_hash_table_insert(catalog->cities_code, second_copy, city_number);

    set_ride_city(ride, *city_number);
  }
}

char *get_city_from_code(RIDES_CATALOG catalog, gpointer city_code) {
  return g_ptr_array_index(catalog->cities_reverse_lookup,
                           GPOINTER_TO_INT(city_code));
}

char *get_city_code(RIDES_CATALOG catalog, char *city) {
  return g_hash_table_lookup(catalog->cities_code, city);
}

void free_rides_catalog(RIDES_CATALOG catalog) {
  g_hash_table_destroy(catalog->rides);
  g_hash_table_destroy(catalog->cities_code);
  g_ptr_array_free(catalog->cities_reverse_lookup, TRUE);
  free(catalog);
}
