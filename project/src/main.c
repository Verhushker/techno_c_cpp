//#include <naive_sort.h>
#include "parallel_sort.h"
#include "utils.h"
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
            return INVALID_FILE;
        }
        break;
    case 3:
        fp_in = fopen(argv[1], "r");
        if (fp_in == NULL) {
            return INVALID_FILE;
        }
        fp_out = fopen(argv[2], "w");
        if (fp_out == NULL) {
            fclose(fp_in);
            return INVALID_FILE;
        }
    default:
        break;
    }

    int error_catcher = SUCCESS;
    Array* arr = create_arr(&error_catcher, fp_in);
    if (error_catcher) {
        handle_errors(error_catcher);
        return 1;
    }

    if (arr == NULL) {
        free_array(arr);
        fclose(fp_in);
        fclose(fp_out);
        return 1;
    }
    
    //merge_sort(arr, 0, arr->amount - 1);
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
