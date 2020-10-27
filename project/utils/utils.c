#include "utils.h" 


#define DEFAULT_SIZE 10


Array* create_arr(size_t size) {
    Array* new_arr = (Array*)malloc(sizeof(Array));
    if (new_arr == NULL) {
        return NULL;
    }

    new_arr->arr = (int*)malloc(sizeof(int) * size);
    if (new_arr->arr == NULL) {
        free(new_arr);
        
        return NULL;
    }
    new_arr->amount = 0;
    new_arr->size = size;
}

Array* create_arr_from_stream(FILE* stream) {
    Array* new_arr = create_arr(DEFAULT_SIZE);
    if (new_arr == NULL) {
        return NULL;
    }

    while(fscanf(stream, "%d", &new_arr->arr[new_arr->amount]) != EOF) {
        ++new_arr->amount;
        if (new_arr->amount >= new_arr->size - 1) {
            new_arr->arr = (int*)realloc(new_arr->arr, sizeof(int) * new_arr->size * 2);
            if (new_arr->arr == NULL) {
                free(new_arr);
                return NULL;
            }
            new_arr->size *= 2;
        } 
    }
    return new_arr;

}

int print_array(FILE* ostream, const Array* array) {
    if (array == NULL) {
        return 1;
    }
    for (size_t i = 0; i < array->amount; ++i) {
        fprintf(ostream, "%d ", array->arr[i]);
    }
    fprintf(ostream, "\n");
    return 0;
}


Array* copy_array(const Array* src, size_t begin, size_t end) {
    if(src == NULL || src->arr == NULL) {
        return NULL;
    }
    Array* copy = create_arr(end - begin + 1);
    for(size_t i = 0; i <= end - begin; ++i) {
            copy->arr[i] = src->arr[begin + i];
            ++copy->amount;
    }
    return copy;
}


void free_array(Array* array) {
    free(array->arr);
    free(array);
    return;
}


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