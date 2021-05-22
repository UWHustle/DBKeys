#ifndef DBKEYS_C_KERNELS_H_
#define DBKEYS_C_KERNELS_H_

int aggregation_kernel(int input_size,
                       int no_unique_groups);

int join_kernel(int size_fact, int size_dim);

#endif //DBKEYS_C_KERNELS_H_
