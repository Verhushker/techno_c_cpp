#ifndef naive_sort_h_
#define naive_sort_h_

#include "array.h"

#include <stdlib.h>

void merge(Array* array, size_t left, size_t middle, size_t right);
void merge_sort(Array* array, size_t left, size_t right);

#endif  // naive_sort_h_