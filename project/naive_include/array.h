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
Array* create_arr_from_stream(FILE* stream);
int print_array(FILE* ostream, const Array* arr);
int copy_arrays(Array* dst, const Array* src);
void free_array(Array* arr);


#endif  // array_h_