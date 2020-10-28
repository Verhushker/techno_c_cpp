//#include <naive_sort.h>
#include "parallel_sort.h"
#include <string.h>

int main(int argc, char** argv) {
    FILE *fp_in = NULL, *fp_out = NULL;

    switch (argc)
    {
    case 1:
        fp_in = stdin;
        fp_out = stdout;
        break;
    case 2:
        fp_in = fopen(argv[1], "r");
        if (fp_in == NULL) {
            return 1;
        }
        break;
    case 3:
        fp_in = fopen(argv[1], "r");
        if (fp_in == NULL) {
            return 1;
        }
        fp_out = fopen(argv[2], "w");
        if (fp_out == NULL) {
            return 1;
        }
    default:
        break;
    }

    Array* arr = create_arr_from_stream(fp_in);
    if (arr == NULL) {
        free_array(arr);
        fclose(fp_in);
        fclose(fp_out);
        return 1;
    }


    pmerge_sort(arr, 0, arr->amount - 1);

    if (print_array(fp_out, arr)){
        free_array(arr);
        fclose(fp_in);
        fclose(fp_out);
        return 1;
    }


    free_array(arr);
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
