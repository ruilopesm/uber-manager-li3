#include "catalogs/drivers_catalog.h"

#include "entities/drivers.h"

struct drivers_catalog {
  GHashTable *drivers;
};

DRIVERS_CATALOG create_drivers_catalog(void) {
  DRIVERS_CATALOG new_catalog = malloc(sizeof(struct drivers_catalog));

  new_catalog->drivers = g_hash_table_new_full(NULL, g_direct_equal, NULL,
                                               (GDestroyNotify)free_driver);

  return new_catalog;
}

void insert_driver(DRIVERS_CATALOG catalog, DRIVER driver, gpointer key) {
  g_hash_table_insert(catalog->drivers, key, driver);
}

void update_driver(DRIVERS_CATALOG catalog, gpointer driver_code, double rating,
                   double price, double tip, int date) {
  DRIVER driver = get_driver_by_code(catalog, driver_code);

  // Increment driver's fields
  set_driver_number_of_rides(driver, get_driver_number_of_rides(driver) + 1);
  set_driver_total_rating(driver, get_driver_total_rating(driver) + rating);
  set_driver_total_earned(driver,
                          get_driver_total_earned(driver) + price + tip);

  // Update driver's latest ride
  if (date > get_driver_latest_ride(driver))
    set_driver_latest_ride(driver, date);
}

DRIVER get_driver_by_id(DRIVERS_CATALOG catalog, int id) {
  return g_hash_table_lookup(catalog->drivers, GINT_TO_POINTER(id));
}

DRIVER get_driver_by_code(DRIVERS_CATALOG catalog, gpointer driver_code) {
  return g_hash_table_lookup(catalog->drivers, driver_code);
}

void free_drivers_catalog(DRIVERS_CATALOG catalog) {
  g_hash_table_destroy(catalog->drivers);
  free(catalog);
}
