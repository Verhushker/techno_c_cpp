#ifndef parallel_array_h_
#define parallel_array_h_


#include <stdlib.h>
#include <stdio.h>

typedef struct Array {
    int * arr;
    size_t amount;
    size_t size;
}Array; 


Array* create_arr(size_t size);
Array* create_arr_from_stream(FILE* stream);
int print_array(FILE* ostream, const Array* array);
Array* copy_array(const Array* src, size_t begin, size_t end);
void free_array(Array* array);

void merge(Array* array, size_t left, size_t middle, size_t right);


#endif  // parallel_array_h_