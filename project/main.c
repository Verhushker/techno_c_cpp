#include <naive_sort.h>
#include <array.h>

int main(int argc, char** argv) {
    FILE *fp = NULL;
    if (argc <= 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
    }

    Array* arr = create_arr(10);
    if (fill_arr(fp, arr)) {
        free_array(arr);
        return 1;
    }
   // Array* arr = create_arr(3);
    if (print_array(stdout, arr)){
        return 1;
    }
    printf("\n\n %zu \n%zu\n", arr->amount, arr->size);

    merge_sort(arr, 0, arr->amount - 1);

    if (print_array(stdout, arr)){
        return 1;
    }

    free_array(arr);
    fclose(fp);
    return 0;
}