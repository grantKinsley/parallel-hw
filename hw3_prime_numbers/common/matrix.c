#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "matrix.h" //implementing

Mat MAT_DEFAULT = {.ptr=NULL, .m=0, .n=0};

void mat_init(Mat *mat, unsigned int m, unsigned int n){
    if(m == 0 || n == 0){
        fprintf(stderr,"mat_init: Matrix size invalid.\n");
        exit(1);
    }
    mat->ptr = (double*) calloc(m*n, sizeof(double));
    if(mat->ptr == NULL){
        fprintf(stderr,"mat_init: Couldn't allocate memory for "
                "matrix.\n");
        exit(1);
    }
    mat->m = m;
    mat->n = n;
    return;
}

/// Check wheter the matrix is initialized.
static void mat_is_inited(Mat *mat, char *fn){
    if(mat == NULL){
        fprintf(stderr,"%s: The matrix is NULL.\n", fn);
        exit(1);
    }
    if(mat->ptr == NULL || mat->m < 1 || mat->n < 1){
        fprintf(stderr,"%s: The matrix is not "
                "initialized.\n", fn);
        exit(1);
    }
}

void mat_fill_incr(Mat *mat, double val){
    mat_is_inited(mat, "mat_fill_incr");
    for(unsigned int i=0; i < mat->m*mat->n; i++){
        mat->ptr[i] = val + i;
    }
    return;
}

void mat_fill_rand(Mat *mat){
    mat_is_inited(mat, "mat_fill_rand");
    int n;
    for(unsigned int i=0; i < mat->m*mat->n; i++){
        n=rand();
        mat->ptr[i] = ((double)n/RAND_MAX)*100;
    }
    return;
}

void mat_fill_diag(Mat *mat, double val){
    mat_is_inited(mat, "mat_fill_diag");
    unsigned int off = 0, max_off= mat->m * mat->n;
    while(off < max_off){
        mat->ptr[off] = val;
        off += mat->n + 1;
    }
    return;
}

void mat_fill_copy(Mat *to, Mat *from){
    mat_is_inited(to, "mat_fill_copy: Mat *to");
    mat_is_inited(from, "mat_fill_copy: Mat *from");
    if(from->m != to->m || from->n != to->n){
        fprintf(stderr,"mat_fill_copy: matrices size does not "
                "match.\n");
        exit(1);
    }
    for(unsigned int i=0; i < from->m*from->n; i++){
        to->ptr[i] = from->ptr[i];
    }
    return;
}

void mat_print(Mat *mat){
    mat_is_inited(mat, "mat_print");
    unsigned int i, j, m = mat->m, n = mat->n;
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            printf("  %5.1f", mat->ptr[i*n + j]);
        }
        printf("\n");
    }
    return;
}

int mat_check_transpose(Mat *orig, Mat *tran){
    mat_is_inited(orig, "mat_transp_check: Mat *orig");
    mat_is_inited(tran, "mat_transp_check: Mat *tran");
    unsigned int i, j;
    unsigned int mo = orig->m, no = orig->n;
    unsigned int mt = tran->m, nt = tran->n;
    // check dimensions
    if(mo != nt || no != mt){
        fprintf(stderr,"Mismatching matrix dimensions\n");
        return 1;
    }
    // check elements
    for(i=0; i<mo; i++){
        for(j=0; j<no; j++){
            if(orig->ptr[i*no+j] != tran->ptr[j*nt+i]){
                fprintf(stderr,"Error:\n"
                        "    Orig[%u,%u] = %5.1f\n"
                        "    Tran[%u,%u] = %5.1f\n",
                        i, j, orig->ptr[i*no+j],
                        j, i, tran->ptr[j*nt+i]);
                return 1;
            }
        }
    }
    return 0;
}
