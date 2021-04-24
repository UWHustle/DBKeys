#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "../common/time.h"
#include "../common/structs.h"
#include "../common/macros.h"

#define INT32_T_MAX 2147483647
#define min(a,b) (((a)<(b))?(a):(b))

void init_rando_gen() {
  srand(42 /* magic constant */);
}

int uar_gen() {
  return (rand() % (INT32_T_MAX));
}

int uar_gen_range(int min, int max) {
  return (rand() % (max + 1 - min) + min);
}

void generate_agg_date(int input_size, int no_unique_groups,
                       vector_int *group_column, vector_int *sum_column) {

  init_rando_gen();

  vector_int *groups = newVectorInt(no_unique_groups);
  map *m_groups = newMap(no_unique_groups);

  for (int i = 0; i < no_unique_groups; ++i) {
    int val = uar_gen_range(1, 10 * no_unique_groups);
    while (map_search(m_groups, val) != -1) {
      val = uar_gen_range(1, 10 * no_unique_groups);
    }
    map_insert(m_groups, val, 1);
    vector_int_insert(groups, val);
  }

  for (int i = 0; i < min(input_size, no_unique_groups); ++i) {
    vector_int_insert(sum_column, uar_gen_range(1, 1000000));
    vector_int_insert(group_column, groups->data[i]);
  }

  for (int i = 0; i < input_size - no_unique_groups; ++i) {
    vector_int_insert(sum_column, uar_gen_range(1, 1000000));
    int index = uar_gen_range(0, no_unique_groups - 1);
    vector_int_insert(group_column, groups->data[index]);
  }

}

int aggregation_kernel(int input_size,
                       int no_unique_groups) {

  // Input Data
  vector_int *group_column = newVectorInt(input_size);
  vector_int *sum_column = newVectorInt(input_size);

  generate_agg_date(input_size, no_unique_groups, group_column, sum_column);

  ////////////////////////

  debug_printf("## Running  aggregation_kernel "
               "(input_size, no_unique_groups) : (%d, %d)\n",
               input_size, no_unique_groups);
  timerstart("aggregation_kernel");

  // Output
  vector_int *groups = newVectorInt(no_unique_groups);
  vector_int *sums = newVectorInt(no_unique_groups);

  // Helpers
  int next_group_id = 0;
  map* hashmap = newMap(no_unique_groups);

  for (int i = 0; i < input_size; i++) {
    int g_val = group_column->data[i];
    int s_val = sum_column->data[i];
    int group_id = -1;
    if ((group_id = map_search(hashmap, g_val)) == -1) {
      group_id = next_group_id++;
      map_insert(hashmap, g_val, group_id);
      vector_int_insert(groups, g_val);
      vector_int_insert(sums, s_val);
    } else {
      sums->data[group_id] += s_val;
    }
  }

  timerstop("aggregation_kernel");

  ////////////////////////

  long sum_sums = 0;
  long sum_groups = 0;
  for (int i = 0; i < groups->size; ++i) {
    sum_sums += sum_column->data[i];
    sum_groups += groups->data[i];
  }
//
//  printf("Groups\n");
//  vector_int_print(groups);
//
//  printf("Sums\n");
//  vector_int_print(sums);

  printf("Aggregation Kernel data stats (Σsums, Σgroups) : (%ld, %ld)\n",
         sum_sums, sum_groups);

  return 0;
}
