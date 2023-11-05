#include <stdio.h> //remove if not using.
#include "util.h"//implementing
#include <pthread.h>
#include <stdlib.h>

// Functions defined with the modifier 'static' are only visible to other
// functions in this file. They cannot be called from outside (for example,
// from main.c). Use them to organize your code. Remember that in C, you cannot
// use a function until you declare it, so declare all your utility functions
// above the point where you use them.
//
// Maintain the mat_multiply function as lean as possible because we are
// measuring their speed. Unless you are debugging, do not print anything on
// them, that consumes precious time.

typedef struct {
    unsigned int Arow;
    unsigned int Bcol;
} MatEntry;

typedef struct {
    pthread_mutex_t *pmtx;
    unsigned int *entryCounter;
    unsigned int size;
    MatEntry *entry_data_list;
    Mat *A, *B, *C;
} Args;

int dot_product(unsigned int size, unsigned int row, unsigned int col, Mat *A, Mat *B) {
    unsigned int entry_res = 0;
    for (int position = 0; position < size; position++) {
        entry_res += (A->ptr[row*size + position]) * (B->ptr[size*position + col]);
    }
    return entry_res;
}

void* generateMatrixC(void *args) {
    Args *a = (Args *) args;
    while(1) {
        pthread_mutex_lock(a->pmtx);
        unsigned int curEntry = *(a->entryCounter);
        *(a->entryCounter) = *(a->entryCounter) + 1;
        pthread_mutex_unlock(a->pmtx);

        // unsigned int size = a->size;
        if (curEntry > (a->size * a->size)-1) {
            pthread_exit(NULL);
        }

        MatEntry data = a->entry_data_list[curEntry];
        int res = dot_product(a->size, data.Arow, data.Bcol, a->A, a->B);
        a->C->ptr[curEntry]= res;
    }
    pthread_exit(NULL);
}

void mat_multiply(Mat *A, Mat *B, Mat *C, unsigned int threads){
    // Put your code here.
    // Remember to set the correct values for C->m, and C->n after doing the
    // multiplication (this matters if the matrices are not square)

    // hw spec says we assume square matrices
    unsigned int size = A->m;

    unsigned int entryCounter = 0;
    pthread_t thread_arr[threads];
    pthread_mutex_t pmtx;
    pthread_mutex_init(&pmtx, NULL);

    int total_entries = size * size;
    MatEntry entry_data_list[total_entries];

    // each spot of thread_data is responsible for an entry of C
    // we split the data so entry knows what parts of A and B to access
    int thread_num = 0;
    for (unsigned int row = 0; row < size; row++) {
        for (unsigned int col = 0; col < size; col++) {
            entry_data_list[thread_num].Arow = row;
            entry_data_list[thread_num].Bcol = col;
            thread_num++;
        }
    }

    Args arg_thr = { &pmtx, &entryCounter, size, entry_data_list, A, B, C };
 
    for (unsigned int i = 0; i < threads; i++) {
        int ret = pthread_create(&thread_arr[i], NULL, &generateMatrixC, (void*) &arg_thr);
        if (ret) {
            printf("Error creating thread\n");
            exit(-1);
        }
    }

    C->m = size;
    C->n = size;

    for (unsigned int i = 0; i < threads; i++) {
        pthread_join(thread_arr[i], NULL);
    }
    return;
}
