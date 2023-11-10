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
    unsigned int grain;
    Mat *mat;
    unsigned int *rowCounter;
    unsigned int *colCounter;
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

// static void* transpose_mat(void *args) {
//     // printf("swap entries\n");
//     Args *a = (Args *) args;
//     unsigned int size = a->mat->m;
    
//     while(1) {
//         // get the entry of mat to work on
//         pthread_mutex_lock(a->pmtx);
//         unsigned int curCounter = *(a->counter);
//         *(a->counter) = *(a->counter) + a->grain;
//         pthread_mutex_unlock(a->pmtx);

//         if (curCounter >= (size*(size-1))/2) {
//             pthread_exit(NULL);
//         }

//         for (unsigned int k = 0; k < a->grain; k++) {
//             unsigned int curEntry = a->entriesToSwap->arr[curCounter];
//             unsigned int row = curEntry / size;
//             unsigned int col = curEntry % size;
//             swap_entries(a->mat, row, col);
            
//             curCounter++;
//             if (curCounter >= (size*(size-1))/2) {
//                 break;
//             }
//         }
//     }
//     printf("end thread\n");
//     pthread_exit(NULL);
// }

static void* transpose_mat(void *args) {
    Args *a = (Args *) args;
    unsigned int size = a->mat->m;
    
    while(1) {
        pthread_mutex_lock(a->pmtx);

        // get current row and col for this thread to work on
        unsigned int curCol = *(a->colCounter);
        unsigned int curRow = *(a->rowCounter);
        
        // set row and col counters for next thread to work on
        *(a->colCounter) += a->grain;
        while (*(a->colCounter) >= size) {
            
            ++*(a->rowCounter);
            if (*(a->rowCounter) >= size-1) {
                break;
            }
            unsigned int remainder = (*(a->colCounter)+1) - size;
            *(a->colCounter) = *(a->rowCounter) + remainder;
            // printf("counter: %d %d\n", *(a->rowCounter), *(a->colCounter));
        }
        // printf("current: %d %d\n", curRow, curCol);
        // printf("counter: %d %d\n", *(a->rowCounter), *(a->colCounter));

        pthread_mutex_unlock(a->pmtx);

        // if at last row, done with transposition
        if (curRow >= size-1) {
            pthread_exit(NULL);
        }

        // do grain number of swaps
        for (unsigned int k = 0; k < a->grain; k++) {
            // printf("swap %d %d\n", curRow, curCol);
            swap_entries(a->mat, curRow, curCol);
            ++curCol;
            if (curCol >= size) {
                ++curRow;
                curCol = curRow;
                ++curCol;
            }
            if (curRow >= size-1) {
                break;
            }
        }
        // printf("\n");
    }
    pthread_exit(NULL);
}

void mat_squaretransp_parallel(Mat *mat, unsigned int grain, unsigned int thr){
    unsigned int size = mat->m;
    pthread_t threads[thr];

    pthread_mutex_t pmtx;
    pthread_mutex_init(&pmtx, NULL);
    unsigned int rowCounter = 0;
    unsigned int colCounter = 1;

    // unsigned int counter = 0;
    // carr_d_t entriesToSwap; // holds the entries of upper triangle of mat
    // carr_d_init(&entriesToSwap, (size*(size-1))/2);

    // for (unsigned int i = 0; i < size; i++) {
    //     for (unsigned int j = i+1; j < size; j++) {
    //         carr_d_push(&entriesToSwap, i*size+j);
    //     }
    // }

    Args arg_thr = { &pmtx, grain, mat, &rowCounter, &colCounter};

    // Args arg_thr = { &pmtx, grain, &counter, &entriesToSwap, mat };

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
