#include <naive_sort.h>
#include <array.h>

int main(/* int argc, char** argv */) {
    Array* arr = create_arr_from_stream(stdin);
    if (print_array(stdout, arr));{
        return 1;
    }


    return 0;
}