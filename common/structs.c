#include "structs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "../common/macros.h"

listNode *newListNode() {
  listNode *ln = (listNode *) malloc(sizeof(listNode));
  for (int i = 0; i < 10; ++i) {
    ln->keys[i] = -1;
    ln->next_free = 0;
    ln->next = NULL;
  }
  return ln;
}

int32_t nextPowerOf2(int32_t v) {
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

map *newMap(int head_size) {
  map *m = (map *) malloc(sizeof(map));
  if (head_size < 1) {
    m->head_size = nextPowerOf2(MAPSIZE);
  } else {
    m->head_size = nextPowerOf2(head_size);
  }
  m->head_size_log2 = log2(m->head_size);
  m->head =
      (struct listNode **) malloc(m->head_size * sizeof(struct listNode *));
  for (int i = 0; i < m->head_size; ++i) {
    m->head[i] = newListNode();
  }
  m->size = 0;
  return m;
}

int32_t inline __attribute__((always_inline))
map_hash(int buckets_no, int32_t key) {
  return key % buckets_no;
//  printf("MH - %d %d %d %d %d\n", key, 2^32*key, 32-M);
//  int32_t h =  (2^10 * key) >> (32-M);
//  printf("%d %d\n", key, h);
//  return h;
}

void list_insert(listNode *ln, int k, int v) {
  if (ln->next_free < LISTNODESIZE) {
    ln->keys[ln->next_free] = k;
    ln->row_ids[ln->next_free] = v;
    ln->next_free++;
  } else {
    if (ln->next == NULL) {
      ln->next = newListNode();
    }
    list_insert(ln->next, k, v);
  }
}

// does not check for duplicate keys
void map_insert(map *m, int k, int v) {
  int h = map_hash(m->head_size, k);
  list_insert(m->head[h], k, v);
  m->size++;
}

int list_search(listNode *ln, int k) {
  if (ln == NULL) { return -1; }

  for (int i = 0; i < ln->next_free; ++i) {
    if (ln->keys[i] == k) {
      return ln->row_ids[i];
    }
  }
  return list_search(ln->next, k);
}

//int list_update_or_insert(listNode *ln, int k, int v) {
//  for (int i = 0; i < ln->next_free; ++i) {
//    if (ln->keys[i] == k) {
//       ln->row_ids[i] += v;
//       return ln->row_ids[i];
//    }
//  return list_insert(ln, k, v);
//}
//
//int map_update_or_insert(map *m, int k, int v) {
//  int h = map_hash(m->head_size, k);
//  return list_update_or_insert(m->head[h], k, v);
//}

int map_search(map *m, int k) {
  int h = map_hash(m->head_size, k);
  return list_search(m->head[h], k);
}

void list_delete(listNode *ln) {
  if (ln == NULL) { return; }
  listNode *n = ln->next;
  free(ln);
  list_delete(n);
}

int list_count(listNode *ln) {
  int c = 0;
  if (ln != NULL) {
    c += list_count(ln->next);
    c += ln->next_free;
  }
  return c;
}

void map_delete(map *m) {
  int min = 400000000;
  int max = 0;
  float avg = 0;
  float cnt = 0;
  for (int i = 0; i < m->head_size; ++i) {
    int c = list_count(m->head[i]);
    avg += c;
    cnt++;
    if (max < c) { max = c; }
    if (min > c) { min = c; }
  }
  avg = avg / cnt;
  printf("map stats(min, max, avg): %d %d %f\n", min, max, avg);
  printf("map size %d head size %d log2size %d\n",
         m->size,
         m->head_size,
         m->head_size_log2);

  for (int i = 0; i < m->head_size; ++i) {
    free(m->head[i]);
  }
  free(m);
}

void list_print(listNode *ln) {
  if (ln == NULL) {
    printf("\n");
    return;
  }
  printf("|free_next:%d", ln->next_free);
  for (int i = 0; i < ln->next_free; ++i) {
    printf("|%d,%d,%d", i, ln->keys[i], ln->row_ids[i]);
  }
  printf(" -> ");
  list_print(ln->next);
}

void map_print(map *m) {
  printf("----- print map ---- \n");
  for (int i = 0; i < m->head_size; i++) {
    list_print(m->head[i]);
  }
  printf("----- print map end -- \n");
}

vector *newVector(int initial_size) {
  vector *v = (vector *) malloc(sizeof(vector));
  v->data = malloc(sizeof(void *) * initial_size);
  v->size = 0;
  v->allocated_size = initial_size;
  return v;
}

void vector_insert(vector *v, void *item) {
  if (v->size == v->allocated_size) {
    debug_printf("Vector is reallocating memory from %d to %d capacity\n",
                 v->allocated_size,
                 2 * v->allocated_size);
    v->data = realloc(v->data, 2 * v->allocated_size * sizeof(void *));
    v->allocated_size = 2 * v->allocated_size;
  }
  v->data[v->size] = item;
  v->size++;
}

void *vector_get(vector *v, int index) {
  return v->data[index];
}

void vector_set(vector *v, int index, void *item) {
  v->data[index] = item;
}

void vector_delete(vector *v) {
  free(v->data);
  free(v);
}

vector_int *newVectorInt(int initial_size) {
  vector_int *v = (vector_int *) malloc(sizeof(vector_int));
  v->data = malloc(sizeof(int *) * initial_size);
  v->size = 0;
  v->allocated_size = initial_size;
  return v;
}

void vector_int_insert(vector_int *v, int item) {
  if (v->size == v->allocated_size) {
    debug_printf("Vector Int is reallocating memory from %d to %d capacity\n",
                 v->allocated_size,
                 2 * v->allocated_size);
    v->data = realloc(v->data, 2 * v->allocated_size * sizeof(int *));
    v->allocated_size = 2 * v->allocated_size;
  }
  v->data[v->size] = item;
  v->size++;
}

int vector_int_get(vector_int *v, int index) {
  return v->data[index];
}

void vector_int_set(vector_int *v, int index, int item) {
  v->data[index] = item;
}

void vector_int_print(vector_int *v) {
  for (int i = 0; i < v->size; i++) {
    printf("%d - %d\n", i, v->data[i]);
  }
}

void vector_int_debug_print(vector_int *v) {
  for (int i = 0; i < v->size; i++) {
    debug_printf("%d - %d\n", i, v->data[i]);
  }
}

void vector_int_delete(vector_int *v) {
  free(v->data);
  free(v);
}

void vector_int_stats_debug(vector_int *v, char *name) {
  long long sum = 0;
  for (int i = 0; i < v->size; ++i) {
    sum += v->data[i];
  }
  debug_printf("%s size: %d -- sum: %lld \n", name, v->size, sum);
}

/////////////////////////////
// Works with vector_int elements
vector_vector_int *newVectorVectorInt(int initial_size) {
  vector_vector_int
      *v = (vector_vector_int *) malloc(sizeof(vector_vector_int));
  v->data = (vector_int **) malloc(sizeof(vector_int *) * initial_size);
  v->size = 0;
  v->allocated_size = initial_size;
  return v;
}

void vector_vector_int_insert(vector_vector_int *v, vector_int *item) {
  if (v->size == v->allocated_size) {
    debug_printf(
        "Vector Vector Int is reallocating memory from %d to %d capacity\n",
        v->allocated_size,
        2 * v->allocated_size);
    v->data = realloc(v->data, 2 * v->allocated_size * sizeof(vector_int *));
    v->allocated_size = 2 * v->allocated_size;
  }
  v->data[v->size] = item;
  v->size++;
}

vector_int *vector_vector_int_get(vector_vector_int *v, int index) {
  return v->data[index];
}

void vector_vector_int_set(vector_vector_int *v, int index, vector_int *item) {
  v->data[index] = item;
}

void vector_vector_int_print(vector_vector_int *v) {
  for (int i = 0; i < v->size; i++) {
    vector_int_print(v->data[i]);
  }
}

void vector_vector_int_debug_print(vector_vector_int *v) {
  for (int i = 0; i < v->size; i++) {
    vector_int_debug_print(v->data[i]);
  }
}

void vector_vector_int_delete(vector_vector_int *v) {
  free(v->data);
  free(v);
}
void vector_vector_int_stats_debug(vector_vector_int *v, char *name) {
  long long sum = 0;
  int size = 0;
  for (int i = 0; i < v->size; ++i) {
    size += v->data[i]->size;
    printf("%d: %d\n", i, v->data[i]->size);
    for (int j = 0; j < v->data[i]->size; ++j) {
      sum += v->data[i]->data[j];
    }
  }
  debug_printf("%s size: %d -- sum: %lld -- #elements: %d \n",
               name,
               v->size,
               sum,
               size);
}

int vector_vector_int_count_joinkeys(vector_vector_int *v) {
  int size = 0;
  for (int i = 0; i < v->size; ++i) {
    size += v->data[i]->size;
  }
  return size;
}

/////////////////////////////

group_joinkeys *newGroupJoinkeys(int initial_size, int vvi_initial_size) {
  group_joinkeys *g = (group_joinkeys *) malloc(sizeof(group_joinkeys));
  g->m = newMap(-1);
  g->v = newVectorInt(initial_size);
  g->vv = newVectorVectorInt(initial_size);
  g->vvi_initial_size = vvi_initial_size;
  return g;
}

vector_int *group_joinkeys_access(group_joinkeys *g, int key) {
  int current_g_id = map_search(g->m, key);
  if (current_g_id == -1) {
    current_g_id = g->v->size;
    map_insert(g->m, key, current_g_id);
    vector_int_insert(g->v, key);
    vector_vector_int_insert(g->vv, newVectorInt(g->vvi_initial_size));
  }
  return g->vv->data[current_g_id];
}

void group_joinkeys_delete(group_joinkeys *g) {
  map_delete(g->m);
  vector_int_delete(g->v);
  vector_vector_int_delete(g->vv);
}

void copy_string(char *s, char **d) {
  int len = 1 + strlen(s);
  *d = (char *) malloc(sizeof(char) * len);
  strncpy(*d, s, len);
}
