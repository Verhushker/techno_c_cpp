#include "array.h" 


#define DEFAULT_SIZE 10

Array* create_arr(size_t size) {
    Array* new_arr = (Array*)malloc(sizeof(Array));
    if (new_arr == NULL) {
        return NULL;
    }
    new_arr->arr = (int*)malloc(sizeof(int) * size);
    if (new_arr->arr == NULL) {
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
                return NULL;
            }
            new_arr->size *= 2;
        } 
    }
    return new_arr;

}

int print_array(FILE* ostream, const Array* arr) {
    if (arr == NULL) {
        return 1;
    }
    for (size_t i = 0; i < arr->amount; ++i) {
        fprintf(ostream, "%d ", arr->arr[i]);
    }
    return 0;
}


int copy_arrays(Array* dst, const Array* src) {

}


void free_array(Array* arr) {
    free(arr->arr);
    free(arr);
    return;
}