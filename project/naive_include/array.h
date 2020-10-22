#ifndef array_h_
#define array_h_

#include <stdlib.h>
#include <stdio.h>

typedef struct Array {
    int * arr;
    size_t amount;
    size_t size;
}Array; 


Array* create_arr(size_t size);
int fill_arr(FILE* stream, Array* array);
int print_array(FILE* ostream, const Array* array);
int copy_arrays(Array* dst, const Array* src);
void free_array(Array* array);


#endif  // array_h_