#include "naive_sort.h"


void merge_sort(Array* array, size_t left, size_t right) {
    if (left >= right) {
        return;
    }

    size_t middle = (left + right) / 2;

    merge_sort(array, left, middle);
    merge_sort(array, middle + 1, right);

    merge(array, left, middle, right);
}