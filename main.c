#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_kernels/c_kernels.h"
#include "common/time.h"

int run_microbenchmark(int argc, char** argv) {
  char* ub_id = argv[0];

  if (strcmp(ub_id, "agg") == 0) {
    if (argc != 3) {
      printf("Agg benchmark id requires 2 parameters. Usage:"
             " dbkeys ub agg input_size #unique_groups\n");
      return -1;
    }
    aggregation_kernel(atoi(argv[1]), atoi(argv[2]));
  }

  return 0;
}

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("No benchmark id. Usage: dbkeys <benchmark_id> <params>\n");
    return -1;
  }

  if (strcmp(argv[1], "ub") == 0) {
    run_microbenchmark(argc - 2, argv + 2);
  } else {
    printf("Wrong benchmark id. Usage: dbkeys <benchmark_id> <params>\n");
  }

  return 0;
}