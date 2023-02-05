#include <stdio.h>

#include "base/batch.h"
#include "base/interactive.h"
#include "utils/utils.h"

int main(int argc, char **argv) {
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  if (argc == 3) {
    int ret = batch(argv);

    if (ret != 0) {
      printf("%s\n", get_error_as_string(ret));
      return 1;
    }
  } else if (argc == 1) {
    interactive();
  } else {
    printf("Batch mode: %s <dataset> <queries-file>\n", argv[0]);
    printf("Interactive mode: %s\n", argv[0]);
    return 1;
  }
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU Time:%f\n", cpu_time_used);

  return 0;
}
