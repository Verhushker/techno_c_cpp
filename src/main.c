#include "naive_sort.h"
#include "parallel_sort.h"
#include "utils.h"
#include <string.h>

int main(int argc, char** argv) {
    FILE *fp_in = NULL;

    switch (argc)
    {
    case 1:
        fp_in = stdin;
        break;
    case 2:
    case 3:
        fp_in = fopen(argv[1], "r");
        if (fp_in == NULL) {
            handle_errors(INVALID_FILE);
            return FAILURE;
        }
        break;
    default:
        break;
    }

    int error_catcher = SUCCESS;
    Array* arr = create_arr(&error_catcher, fp_in);
    if (error_catcher) {
        handle_errors(error_catcher);

        if (fclose(fp_in)) {
            handle_errors(CLOSE_FAILURE);
            return FAILURE;
        }
        
        return FAILURE;
    }

    if (arr == NULL) {
        free_array(arr);
        if (fclose(fp_in)) {
            handle_errors(CLOSE_FAILURE);
            return FAILURE;
        }
        return FAILURE;
    }

    if (fclose(fp_in)) {
            handle_errors(CLOSE_FAILURE);
            return FAILURE;
    }
    
    error_catcher = merge_sort(arr, 0, arr->amount - 1);
    if (error_catcher) {
        handle_errors(error_catcher);

        return FAILURE;
    }

    FILE *fp_out = NULL;

    switch (argc)
    {
    case 1:
    case 2:
        fp_out = stdout;
        break;
    case 3:
        fp_out = fopen(argv[2], "w");
        if (fp_out == NULL) {
            fclose(fp_in);
            return INVALID_FILE;
        }
        break;
    default:
        break;
    }

    if (print_array(fp_out, arr)){
        free_array(arr);
        
        if (fclose(fp_out)) {
            handle_errors(CLOSE_FAILURE);
            return FAILURE;
        }
        return FAILURE;
    }

    free_array(arr);
    
    if (fclose(fp_out)) {
        handle_errors(CLOSE_FAILURE);
        return FAILURE;
    }
    return 0;
}
