#ifndef DBKEYS_COMMON_DATA_GENERATORS_H_
#define DBKEYS_COMMON_DATA_GENERATORS_H_

#include "limits.h"

#define INT32_T_MAX 2147483647
#define min(a, b) (((a)<(b))?(a):(b))

void init_rando_gen();

int uar_gen();

int uar_gen_range(int min, int max);


#endif //DBKEYS_COMMON_DATA_GENERATORS_H_
