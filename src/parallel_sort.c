#include "parallel_sort.h"
#include "naive_sort.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/wait.h>



static int naive_merge_sort(Array* array, size_t left, size_t right) {
    if (left >= right) {
        return SUCCESS;
    }
    if(array == NULL || array->arr == NULL) {
        return INVALID_INPUT_ARRAY;
    }

    size_t middle = (left + right) / 2;

    int error_catcher = SUCCESS;
    if (error_catcher = naive_merge_sort(array, left, middle)) {
        return error_catcher;
    }
    if (error_catcher = naive_merge_sort(array, middle + 1, right)) {
        return error_catcher;
    }

    merge(array, left, middle, right);
    return SUCCESS;
}


int par_merge_sort(Array* array, size_t left, size_t right, int* nproc) {
    if (left >= right) {
        return SUCCESS;
    }
    if (array == NULL || array->arr == NULL) {
        return INVALID_INPUT_ARRAY;
    }
    
    int error_catcher = SUCCESS;

    if (*nproc >= get_nprocs()) {
        error_catcher = naive_merge_sort(array, left, right);
        if (error_catcher) {
            return error_catcher;
        }
        return SUCCESS;
    }

    int lpipefd[2];
    if(pipe(lpipefd) == -1) {
        return PIPE_FAILED;
        //exit(EXIT_FAILURE);
    }
    int rpipefd[2];
    if(pipe(rpipefd) == -1) {
        return PIPE_FAILED;
        //exit(EXIT_FAILURE);
    }


    size_t middle = (left + right) / 2;

    pid_t left_pid = 0, right_pid = 0;

    left_pid = fork();
    if (left_pid == -1) {
        fprintf(stderr, "Fork error");
        exit(EXIT_FAILURE);
    }  else if (left_pid == 0) {
        (*nproc) += 2;

        error_catcher = par_merge_sort(array, left, middle, nproc);
        if (error_catcher) {
            return error_catcher;
        }
        
        Array* left_arr = create_copy_array(array, &error_catcher, left, middle);
        if (error_catcher) {
            return error_catcher;
        }
        
        close(lpipefd[0]);
        write(lpipefd[1], left_arr->arr, (middle - left + 1) * sizeof(int));

        free_array(left_arr);
        free_array(array);
        exit(EXIT_SUCCESS);
    } else {
        right_pid = fork();
        if (right_pid == -1) {
            fprintf(stderr, "Fork error");
            exit(EXIT_FAILURE);
        } else if (right_pid == 0) {
            (*nproc) += 2;

            error_catcher = par_merge_sort(array, middle + 1, right, nproc);
            if (error_catcher) {
                return error_catcher;
            }
            
            Array* right_arr = create_copy_array(array, &error_catcher, middle + 1, right);
            if (error_catcher) {
                return error_catcher;
            }

            close(rpipefd[0]);
            write(rpipefd[1], right_arr->arr, (right - middle) * sizeof(int));

            free_array(right_arr);
            free_array(array);
            exit(EXIT_SUCCESS);
        }

    }

    int status = 0;
    waitpid(left_pid, &status, 0);
    waitpid(right_pid, &status, 0);


    Array* tmp_left_arr = create_empty_arr(&error_catcher, middle - left + 1);
    if (error_catcher) {
        return error_catcher;
    }

    Array* tmp_right_arr = create_empty_arr(&error_catcher, right - middle);
    if (error_catcher) {
        return error_catcher;
    }

    if(close(lpipefd[1])) {
        return CLOSE_FAILURE;
    }
    if (close(rpipefd[1])) {
        return CLOSE_FAILURE;
    }
    
    if (read(lpipefd[0], tmp_left_arr->arr, (middle - left + 1) * sizeof(int)) < 0) {
        return READ_FAILURE;
    }
    for(size_t i = 0; i <= middle - left; ++i) {
        array->arr[left + i] = tmp_left_arr->arr[i];
    }
    
    if (read(rpipefd[0], tmp_right_arr->arr, (right - middle) * sizeof(int)) < 0) {
        return READ_FAILURE;
    }

    for(size_t i = 0; i < right - middle; ++i) {
        array->arr[middle + 1 + i] = tmp_right_arr->arr[i];
    }
    

    error_catcher = merge(array, left, middle, right);
    if (error_catcher) {
        return error_catcher;
    }


    free_array(tmp_left_arr);
    free_array(tmp_right_arr);
    return SUCCESS;
}


int pmerge_sort(Array* array, size_t left, size_t right) {
    int* nproc = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *nproc = 1;
    
    int error_catcher = 0;
    error_catcher = par_merge_sort(array, left, right, nproc);
    if (error_catcher) {
        return error_catcher;
    }
    munmap(nproc, sizeof(int));
}