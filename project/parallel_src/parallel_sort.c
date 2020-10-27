#include "parallel_sort.h"
#include "naive_sort.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>

#define __USE_MISC
#include <sys/mman.h>


void par_merge_sort(Array* array, size_t left, size_t right, int* nproc) {
    if (*nproc >= get_nprocs()) {
        merge_sort(array, left, right);
        return;
    }
    
    
    if (left >= right) {
        return;
    }


    int lpipefd[2];
    if(pipe(lpipefd) == -1) {
        exit(-1);
    }
    int rpipefd[2];
    if(pipe(rpipefd) == -1) {
        exit(-1);
    }


    size_t middle = (left + right) / 2;

    pid_t left_pid = 0, right_pid = 0;

    left_pid = fork();
    if (left_pid == -1) {
        fprintf(stderr, "Fork error");
        exit(-1);
    }  else if (left_pid == 0) {
        (*nproc) += 2;
        par_merge_sort(array, left, middle, nproc);
        
        Array* left_arr = copy_array(array, left, middle);

        close(lpipefd[0]);
        write(lpipefd[1], left_arr->arr, (middle - left + 1) * sizeof(int));

        free_array(left_arr);
        free_array(array);
        exit(0);
    } else {

        right_pid = fork();
        if (right_pid == -1) {
            fprintf(stderr, "Fork error");
            exit(-1);
        } else if (right_pid == 0) {
            (*nproc) += 2;
            par_merge_sort(array, middle + 1, right, nproc);

            Array* right_arr = copy_array(array, middle + 1, right);

            close(rpipefd[0]);
            write(rpipefd[1], right_arr->arr, (right - middle) * sizeof(int));

            free_array(right_arr);
            free_array(array);
            exit(0);
        }

    }

    int status = 0;
    waitpid(left_pid, &status, 0);
    waitpid(right_pid, &status, 0);


    Array* tmp_left_arr = create_arr(middle - left + 1);
    Array* tmp_right_arr = create_arr(right - middle);

    close(lpipefd[1]);
    close(rpipefd[1]);
    read(lpipefd[0], tmp_left_arr->arr, (middle - left + 1) * sizeof(int));
    for(size_t i = 0; i <= middle - left; ++i) {
        array->arr[left + i] = tmp_left_arr->arr[i];
    }
    
    read(rpipefd[0], tmp_right_arr->arr, (right - middle) * sizeof(int));
    for(size_t i = 0; i < right - middle; ++i) {
        array->arr[middle + 1 + i] = tmp_right_arr->arr[i];
    }
    
    merge(array, left, middle, right);


    free_array(tmp_left_arr);
    free_array(tmp_right_arr);
    return;
}


void pmerge_sort(Array* array, size_t left, size_t right) {
    puts ("\n****\n");
    int* nproc = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *nproc = 1;
    par_merge_sort(array, left, right, nproc);
    munmap(nproc, sizeof(int));
}