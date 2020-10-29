#include "utils.h"
#include <string.h>

#define DEFAULT_SIZE 10


Array* create_empty_arr(int* error_catcher, size_t size) {
    Array* new_arr = NULL;
    new_arr = (Array*)malloc(sizeof(Array));
    //memset(new_arr, 0, sizeof(Array));
    if (new_arr == NULL) {
        *error_catcher =  ALLOC_ERROR;
        return NULL;
    }

    new_arr->arr = (int*)calloc(sizeof(int), size);
    //memset(new_arr, 0, sizeof(Array));

    if (new_arr->arr == NULL) {
        free(new_arr);
        *error_catcher = ALLOC_ERROR;
        return NULL;
    }

    new_arr->amount = 0;
    new_arr->size = size;
        
    return new_arr;
}

Array* create_arr(int* error_catcher, FILE* stream) {
    if (error_catcher == NULL) {
        return NULL;
    }
    if (stream == NULL) {
        *error_catcher = INVALID_FILE;
        return NULL;
    }

    Array* new_arr = create_empty_arr(error_catcher, DEFAULT_SIZE);
    if (*error_catcher) {
        return NULL;
    }

    while(fscanf(stream, "%d", &new_arr->arr[new_arr->amount]) != EOF) {
        ++new_arr->amount;

        if (new_arr->amount >= new_arr->size - 1) {
            new_arr->arr = (int*)realloc(new_arr->arr, sizeof(int) * new_arr->size * 2);
            if (new_arr->arr == NULL) {
                free(new_arr);
                *error_catcher = ALLOC_ERROR;
                return NULL;
            }
            new_arr->size *= 2;
        } 
    }

    return new_arr;

}

int print_array(FILE* ostream, const Array* array) {
    if (ostream == NULL) {
        return INVALID_FILE;
    }
    if (array == NULL || array->arr == NULL) {
        return INVALID_INPUT_ARRAY;
    }
    for (size_t i = 0; i < array->amount - 1; ++i) {
        if (fprintf(ostream, "%d ", array->arr[i]) == FAILURE) {
            return PRINT_ERROR;
        }
    }
    fprintf(ostream, "\n");
    return SUCCESS;
}


Array* create_copy_array(const Array* src, int* error_catcher, size_t begin, size_t end) {
    if(src == NULL || src->arr == NULL) {
        *error_catcher = INVALID_INPUT_ARRAY;
        return NULL;
    }
    Array* new_arr = NULL;

    //memset(new_arr, 0, sizeof(Array));

    new_arr = create_empty_arr(error_catcher, end - begin + 1);

    //memset(new_arr->arr, 0, sizeof(new_arr->size * sizeof(int)));
    /* memset(new_arr, 0, sizeof(Array)); */

    if (*error_catcher) {
        return NULL;
    }
    for(size_t i = 0; i <= end - begin; ++i) {
            new_arr->arr[i] = src->arr[begin + i];
            ++new_arr->amount;
    }
    
    return new_arr;
}


void free_array(Array* array) {
    free(array->arr);
    free(array);
    return;
}


int merge(Array* array, size_t left, size_t middle, size_t right) {
    size_t i = 0, j = 0, k = left;
    size_t size_left = middle - left + 1;
    size_t size_right = right - middle;


    int error_catcher = SUCCESS;

    Array* left_array = create_empty_arr(&error_catcher, size_left);
    if (error_catcher) {
        return error_catcher;
    }
    Array* right_array = create_empty_arr(&error_catcher, size_right);
    if (error_catcher) {
        return error_catcher;
    }

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
    return SUCCESS;
}

void handle_errors(int error) {
    switch (error)
    {
    case SUCCESS :
        break;
    case INVALID_FILE :
        fprintf(stderr, "\nInvalid file\n");
        break;
    case  INVALID_INPUT_ARRAY:
        fprintf(stderr, "\nInvalid input array\n");
        break;
    case  WRONG_INPUT:
        fprintf(stderr, "\nWrong input\n");
        break;
    case  ALLOC_ERROR:
        fprintf(stderr, "\nAlloc error\n");
        break;
    case  PRINT_ERROR:
        fprintf(stderr, "\nPrint error\n");
        break;
    case  PIPE_FAILED:
        fprintf(stderr, "\nPipe failed\n");
        break;
    case  CLOSE_FAILURE:
        fprintf(stderr, "\nClose failure\n");
        break;
    case  READ_FAILURE:
        fprintf(stderr, "\nRead failure\n");
        break;
    default:
        fprintf(stderr, "\nUnknown error\n");
        break;
    }
}