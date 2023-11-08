/**
 ** SUBMIT ONLY THIS FILE
 ** NAME: Grant Kinsley, Ethan Duong
 ** UCI ID: gkinsley, dounget
 **
 ** Use only standard libraries.
 ** See description in header file.
 **/

#include "util_common.h"
#include "transpose.h" //implementing
#include <stdlib.h>
#include <pthread.h>

#ifdef DEBUG
#include <stdio.h> //remove if not using.
#endif

typedef struct {
    pthread_mutex_t *pmtx;
    unsigned int *row;
    unsigned int *col;
    unsigned int grain;
    Mat *mat;
} Args;

void mat_squaretransp_sequential(Mat *mat){
    unsigned int size = mat->m;
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = i+1; j < size; j++) {
            double temp = mat->ptr[i*size+j];
            mat->ptr[i*size+j] = mat->ptr[j*size+i];
            mat->ptr[j*size+i] = temp;
        }
    }
    return;
}

static void swap_entries(Mat *mat, unsigned int row, unsigned int col) {
    unsigned int size = mat->m;
    double temp = mat->ptr[row*size+col];
    mat->ptr[row*size+col] = mat->ptr[col*size+row];
    mat->ptr[col*size+row] = temp;
}

static void* transpose_mat(void *args) {
    // printf("swap entries\n");
    Args *a = (Args *) args;
    unsigned int size = a->mat->m;
    
    while(1) {
        // get the entry of mat to work on
        pthread_mutex_lock(a->pmtx);
        unsigned int row = *(a->row);
        unsigned int col = *(a->col);
        if (col + a->grain >= size) {
            // loop around to next row
            *(a->row) = *(a->row) + 1;
            *(a->col) = 1 + ((col + a->grain) % size) + *(a->row);
        }
        else {
            // stay in same row
            *(a->col) = ((col + a->grain));
        }
        pthread_mutex_unlock(a->pmtx);

        if (row >= size-1) {
            // done transposing once we get to last row
            pthread_exit(NULL);
        }

        for (unsigned int k = 0; k < a->grain; k++) {
            swap_entries(a->mat, row, col);
            // printf("swap %d %d\n", row, col);
            col++;
            if (col >= size) {
                row = row + 1;
                col = row + 1;
            }
            if (row >= size-1) {
                break;
            }
        }
    }
    printf("end thread\n");
    pthread_exit(NULL);
}

void mat_squaretransp_parallel(Mat *mat, unsigned int grain, unsigned int thr){
    unsigned int size = mat->m;
    pthread_t threads[thr];

    pthread_mutex_t pmtx;
    pthread_mutex_init(&pmtx, NULL);
    unsigned int row = 0;
    unsigned int col = 1;

    Args arg_thr = { &pmtx, &row, &col, grain, mat };

    for (unsigned int i = 0; i < thr; i++) {
        int ret = pthread_create(&threads[i], NULL, &transpose_mat, (void*) &arg_thr);
        if (ret) {
            printf("Error creating thread\n");
            exit(-1);
        }
    }

    for (unsigned int i = 0; i < thr; i++) {
        pthread_join(threads[i], NULL);
    }
    return;
}
