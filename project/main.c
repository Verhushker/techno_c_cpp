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

    Array* arr = create_arr(10);
    if (fill_arr(fp_in, arr)) {
        free_array(arr);
        fclose(fp_in);
        fclose(fp_out);
        return 1;
    }

  /*   int* shared_arr = mmap(NULL, arr->amount * sizeof(int),
                           PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0); */
   // memcpy(arr, arr, arr->amount * sizeof(int));

   // Array* arr = create_arr(3);
   /*  if (print_array(fp_out, arr)){
        return 1;
    }
    printf("\n\n %zu \n%zu\n", arr->amount, arr->size); */

    pmerge_sort(arr, 0, arr->amount - 1);
    //par_merge_sort(arr, 0, arr->amount - 1);
    //merge_sort(arr, 0, arr->amount - 1);

    if (print_array(fp_out, arr)){
        free_array(arr);
        fclose(fp_in);
        fclose(fp_out);
        return 1;
    }

  //  printf("\n\nNumber of processors^%d\nAvailable processors^%d", get_nprocs_conf(), get_nprocs());

    free_array(arr);
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
