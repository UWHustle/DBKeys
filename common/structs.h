#ifndef DBKEYS_COMMON_STRUCTS_H_
#define DBKEYS_COMMON_STRUCTS_H_

#define MAPSIZE 4096
#define LISTNODESIZE 12

typedef struct listNode {
  int keys[LISTNODESIZE];
  int row_ids[LISTNODESIZE];
  int next_free;
  struct listNode *next;
} listNode;

typedef struct {
  listNode **head;
  int size;
  int head_size;
  int head_size_log2;
} map;

typedef struct {
  void **data;
  int size;
  int allocated_size;
} vector;

typedef struct {
  int *data;
  int size;
  int allocated_size;
} vector_int;

typedef struct {
  vector_int **data;
  int size;
  int allocated_size;
} vector_vector_int;

typedef struct {
  map *m;
  vector_int *v;
  vector_vector_int *vv;
  int vvi_initial_size;
} group_joinkeys;

////////////////////////////

listNode *newListNode();

void list_insert(listNode *ln, int k, int v);

int list_search(listNode *ln, int k);

void list_print(listNode *ln);

void list_delete(listNode *ln);

int list_count(listNode *ln);

//int list_update_or_insert(listNode *ln, int k, int v);

////////////////////////////

map *newMap(int head_size);

int __attribute__((always_inline)) map_hash(int buckets_no,
                                            int key);

// does not check for duplicate keys
void map_insert(map *m, int k, int v);

int map_search(map *m, int k);

void map_print(map *m);

void map_delete(map *m);

//int map_update_or_insert(map *m, int k, int v);

////////////////////////////
// Does not own the elements inserted to the vector
// Works with void* elements
vector *newVector(int initial_size);

void vector_insert(vector *v, void *item);

void *vector_get(vector *v, int index);

void vector_set(vector *v, int index, void *item);

void vector_delete(vector *v);

/////////////////////////////
// Works with int elements
vector_int *newVectorInt(int initial_size);

void vector_int_insert(vector_int *v, int item);

int vector_int_get(vector_int *v, int index);

void vector_int_set(vector_int *v, int index, int item);

void vector_int_print(vector_int *v);

void vector_int_debug_print(vector_int *v);

void vector_int_delete(vector_int *v);

void vector_int_stats_debug(vector_int *v, char *name);

/////////////////////////////
// Works with vector_int elements
vector_vector_int *newVectorVectorInt(int initial_size);

void vector_vector_int_insert(vector_vector_int *v, vector_int *item);

vector_int *vector_vector_int_get(vector_vector_int *v, int index);

void vector_vector_int_set(vector_vector_int *v, int index, vector_int *item);

void vector_vector_int_print(vector_vector_int *v);

void vector_vector_int_debug_print(vector_vector_int *v);

void vector_vector_int_delete(vector_vector_int *v);

void vector_vector_int_stats_debug(vector_vector_int *v, char *name);

int vector_vector_int_count_joinkeys(vector_vector_int *v);

/////////////////////////////

group_joinkeys *newGroupJoinkeys(int initial_size, int vvi_initial_size);

vector_int *group_joinkeys_access(group_joinkeys *g, int key);

void group_joinkeys_delete(group_joinkeys *g);

/////////////////////////////

void copy_string(char *s, char **d);

#endif //DBKEYS_COMMON_STRUCTS_H_
