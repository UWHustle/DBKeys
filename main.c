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
             " dbkeys agg input_size #unique_groups\n");
      return -1;
    }
    aggregation_kernel(atoi(argv[1]), atoi(argv[2]));
  } else if (strcmp(ub_id, "join") == 0) {
    if (argc != 3) {
      printf("Join benchmark id requires 2 parameters. Usage:"
             " dbkeys join fact_relation_size dimension_relation_size\n");
      return -1;
    }
    join_kernel(atoi(argv[1]), atoi(argv[2]));
  }

  return 0;
}

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("No benchmark id. Usage: dbkeys <benchmark_id> <params>\n");
    return -1;
  }

  run_microbenchmark(argc - 1, argv + 1);
  return 0;
}