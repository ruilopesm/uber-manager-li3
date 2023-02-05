#include "catalogs/join_catalog.h"

struct join_catalog {
  USERS_CATALOG users_catalog;
  DRIVERS_CATALOG drivers_catalog;
  RIDES_CATALOG rides_catalog;
};

JOIN_CATALOG create_join_catalog(USERS_CATALOG users_catalog,
                                 DRIVERS_CATALOG drivers_catalog,
                                 RIDES_CATALOG rides_catalog) {
  JOIN_CATALOG new_catalog = malloc(sizeof(struct join_catalog));

  new_catalog->users_catalog = users_catalog;
  new_catalog->drivers_catalog = drivers_catalog;
  new_catalog->rides_catalog = rides_catalog;

  return new_catalog;
}

USERS_CATALOG get_users_catalog(JOIN_CATALOG catalog) {
  return catalog->users_catalog;
}

DRIVERS_CATALOG get_drivers_catalog(JOIN_CATALOG catalog) {
  return catalog->drivers_catalog;
}

RIDES_CATALOG get_rides_catalog(JOIN_CATALOG catalog) {
  return catalog->rides_catalog;
}

void free_join_catalog(JOIN_CATALOG catalog) { free(catalog); }
