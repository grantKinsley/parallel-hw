/**
 ** SUBMIT ONLY THIS FILE
 ** NAME: .......
 ** UCI ID: .......
 **
 ** Use only standard libraries.
 ** See description in header file.
 **/

#include "util_common.h"
#include "transpose.h" //implementing

#ifdef DEBUG
#include <stdio.h> //remove if not using.
#endif

void mat_squaretransp_sequential(Mat *mat){
    
    // YOUR CODE GOES HERE

    //>>>>>>>> DELETE THE CODE BELOW
    // this is a useless demo code. Delete it before
    // submittiong your solution.
#ifdef DEBUG
    printf("TO UNDEFINE THE MACRO 'DEBUG', COMMENT common/util_common.c:15\n");
    printf("mat: {%p, %u, %u}\n", mat->ptr, mat->m, mat->n);
#endif
    //<<<<<<<< DELETE UP TO THIS POINT
    return;
}

void mat_squaretransp_parallel(Mat *mat, unsigned int grain, unsigned int thr){
    
    // YOUR CODE GOES HERE

    //>>>>>>>> DELETE THE CODE BELOW
    // this is a useless demo code. Delete it before
    // submittiong your solution.
#ifdef DEBUG
    printf("TO UNDEFINE THE MACRO 'DEBUG', COMMENT common/util_common.c:15\n");
    printf("mat: {%p, %u, %u}\n", mat->ptr, mat->m, mat->n);
    printf("grain: %u\n", grain);
    printf("threads: %u\n", thr);
#endif
    //<<<<<<<< DELETE UP TO THIS POINT
    return;
}
