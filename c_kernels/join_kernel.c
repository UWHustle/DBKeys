#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../common/time.h"
#include "../common/structs.h"
#include "../common/macros.h"
#include "../common/data_generators.h"

void generate_join_data(int size_fact,
                        int size_dim,
                        vector_int *column_fact,
                        vector_int *column_dim) {
  init_rando_gen();
  for (int i = 0; i < size_dim; ++i) {
    vector_int_insert(column_dim, i);
  }

  for (int i = 0; i < size_fact; ++i) {
    vector_int_insert(column_fact, uar_gen_range(0, size_dim));
  }
}

int join_kernel(int size_fact, int size_dim) {

  // Input Data
  vector_int *column_fact = newVectorInt(size_fact);
  vector_int *column_dim = newVectorInt(size_dim);

  generate_join_data(size_fact, size_dim, column_fact, column_dim);

  int cnt;

  cnt = 0;
  ////////////////////////

  debug_printf("## Running join kernel "
               "(size fact, size dim) : (%d, %d)\n",
               size_fact, size_dim);

  timerstart("join kernel");

  vector_int *mask = newVectorInt(size_fact);
  map *m = newMap(size_dim);

  for (int i = 0; i < size_dim; i++) {
    map_insert(m, column_dim->data[i], 0);
  }

  for (int i = 0; i < size_fact; i++) {
    int res = map_search(m, column_fact->data[i]);
    vector_int_insert(mask, res);
    if (res != -1) { cnt++; }
  }

  timerstop("join kernel");

////////////////////////

  printf("Join Kernel stats (Σres) : (%d)\n", cnt);

  return 0;
}
