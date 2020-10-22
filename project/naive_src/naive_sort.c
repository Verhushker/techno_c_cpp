#include "naive_sort.h"


void merge(Array* array, size_t left, size_t middle, size_t right) {
    size_t i = 0, j = 0, k = left;
    size_t size_left = middle - left + 1;
    size_t size_right = right - middle;

    Array* left_array = create_arr(size_left);
    Array* right_array = create_arr(size_right);

    for (size_t i1 = 0; i1 < size_left; ++i1) {
        left_array->arr[i1] = array->arr[left + i1];
        ++left_array->amount;
    }
    for (size_t j1 = 0; j1 < size_right; ++j1) {
        right_array->arr[j1] = array->arr[middle + 1 + j1];
        ++right_array->amount;
    }

    
    while (i < size_left && j < size_right) {
        if (left_array->arr[i] <= right_array->arr[j]) {
            array->arr[k] = left_array->arr[i];
            ++i;
        } else {
            array->arr[k] = right_array->arr[j];
            ++j;
        }
        ++k;
    }

    while (i < size_left) {
        array->arr[k] = left_array->arr[i];
        ++i;
        ++k;
    }
    while (j < size_right) {
        array->arr[k] = right_array->arr[j];
        ++j;
        ++k;
    }

    free_array(left_array);
    free_array(right_array);
}

void merge_sort(Array* array, size_t left, size_t right) {
    if (left >= right) {
        return;
    }
    size_t middle = (left + right) / 2;

    merge_sort(array, left, middle);
    merge_sort(array, middle + 1, right);

    merge(array, left, middle, right);
}