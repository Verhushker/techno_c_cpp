#ifndef parallel_array_h_
#define parallel_array_h_


#include <stdlib.h>
#include <stdio.h>

typedef struct Array {
    int * arr;
    size_t amount;
    size_t size;
} Array;

enum Errors {
    SUCCESS = 0,
    INVALID_FILE,
    INVALID_INPUT_ARRAY,
    WRONG_INPUT,
    ALLOC_ERROR,
    PRINT_ERROR,
    PIPE_FAILED,
    CLOSE_FAILURE,
    READ_FAILURE

};

Array* create_empty_arr(int* error_catcher, size_t size);
Array* create_arr(int* error_catcher, FILE* stream);
int print_array(FILE* ostream, const Array* array);
Array* create_copy_array(const Array* src, int* error_catcher, size_t begin, size_t end);
void free_array(Array* array);

int merge(Array* array, size_t left, size_t middle, size_t right);

void handle_errors(int error);



#endif  // parallel_array_h_