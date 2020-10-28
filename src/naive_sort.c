#include "naive_sort.h"




int merge_sort(Array* array, size_t left, size_t right) {
    if (left >= right) {
        return SUCCESS;
    }
    if(array == NULL || array->arr == NULL) {
        return INVALID_INPUT_ARRAY;
    }

    size_t middle = (left + right) / 2;

    int error_catcher = SUCCESS;
    if (error_catcher = merge_sort(array, left, middle)) {
        return error_catcher;
    }
    if (error_catcher = merge_sort(array, middle + 1, right)) {
        return error_catcher;
    }

    merge(array, left, middle, right);
    return SUCCESS;
}

