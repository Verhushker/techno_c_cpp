#include "array.h" 


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

int fill_arr(FILE* stream, Array* array) {
    if (array == NULL) {
        return 1;
    }
    while(fscanf(stream, "%d", &array->arr[array->amount]) != EOF) {
        ++array->amount;
        if (array->amount >= array->size - 1) {
            array->arr = (int*)realloc(array->arr, sizeof(int) * array->size * 2);
            if (array->arr == NULL) {
                free(array);
                return 1;
            }
            array->size *= 2;
        } 
    }
    return 0;

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


int copy_arrays(Array* dst, const Array* src) {

}


void free_array(Array* array) {
    free(array->arr);
    free(array);
    return;
}