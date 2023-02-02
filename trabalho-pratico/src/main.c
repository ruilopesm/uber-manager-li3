#include <stdio.h>

#include "batch.h"
#include "interactive.h"
#include "utils.h"

int main(int argc, char **argv) {
  if (argc == 3) {
    int ret = batch(argv);

    if (ret != 0) {
      printf("%s\n", get_error_as_string(ret));
      return 1;
    }
  } else if (argc == 1) {
    interactive();
  } else {
    printf("Batch mode: %s\n", argv[0]);
    printf("Interactive mode: %s <folder> <queries-file>\n", argv[0]);
    return 1;
  }

  return 0;
}
