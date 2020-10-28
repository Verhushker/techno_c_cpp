#ifndef parallel_sort_h_
#define parallel_sort_h_

#include "utils.h"

#include <stdlib.h>

int par_merge_sort(Array* array, size_t left, size_t right, int* nproc);
int pmerge_sort(Array* array, size_t left, size_t right);


#endif  // parallel_sort_h_