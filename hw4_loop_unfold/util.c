#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h" //implementing

double stopwatch(void){
    struct timespec ts;
    //timespec_get(&ts, TIME_UTC); //-std=c11
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double) ts.tv_sec + ts.tv_nsec/1000000000.0;
}

void mat_init(Mat *mat, unsigned int m, unsigned int n){
    if(m == 0 || n == 0){
	printf("mat_init: Matrix size invalid.\n");
	exit(1);
    }
    mat->ptr = (double*) calloc(m*n, sizeof(double));
    if(mat->ptr == NULL){
	printf("mat_init: Couldn't allocate memory for matrix.\n");
	exit(1);
    }
    mat->m = m;
    mat->n = n;
    return;
}

void mat_fill(Mat *mat){
    for(int i=0; i < mat->m*mat->n; i++){
	mat->ptr[i] = (double)i;
    }
    return;
}

void mat_diag(Mat *mat, double diag){
    if(mat == NULL){
	printf("mat_diag: The matrix is NULL.\n");
	exit(1);
    }
    if(mat->ptr == NULL && mat->m > 0 && mat->n > 0){
	printf("mat_diag: The matrix is not initialized.\n");
	exit(1);
    }
    unsigned int off = 0, max_off= mat->m * mat->n;
    while(off < max_off){
	mat->ptr[off] = diag;
	off += mat->n + 1;
    }
    return;
}

void mat_copy(Mat *to, Mat *from){
    if(from == NULL || to == NULL){
	printf("mat_copy: one of the matrices is NULL.\n");
	exit(1);
    }
    if(from->ptr == NULL || to->ptr == NULL){
	printf("mat_copy: one of the matrices is not initialized.\n");
	exit(1);
    }
    
    if(from->m != to->m || from->n != to->n){
	printf("mat_copy: matrices size does not match.\n");
	exit(1);
    }
    
    for(int i=0; i < from->m*from->n; i++){
	to->ptr[i] = from->ptr[i];
    }
    return;
}

void mat_print(Mat *mat){
    unsigned int i, j, m = mat->m, n = mat->n;
    for(i=0; i < m; i++){
	for(j=0; j < n; j++){
	    printf("  %5.1f", mat->ptr[i*n + j]);
	}
	printf("\n");
    }
    return;
}
