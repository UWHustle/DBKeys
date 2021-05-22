#include "data_generators.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void init_rando_gen() {
  srand(42 /* magic constant */);
}

int uar_gen() {
  return (rand() % (INT32_T_MAX));
}

int uar_gen_range(int min, int max) {
  return (rand() % (max + 1 - min) + min);
}