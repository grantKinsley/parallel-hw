#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
    
int main(int argc, char **argv){
    //help message
    if(argc != 4){
        printf("USAGE: %s n t verb\n",argv[0]);
        printf("n       : Size of the square matrix\n");
        printf("t       : Number of threads used by the multi-thread multiplier.\n");
        printf("verb    : 0=prints only execution time.\n");
        printf("          1=also print matrices.\n");
        exit(1);
    }

    //get the command line arguments
    unsigned int n, t, verb;
    n=atoi(argv[1]);
    t=atoi(argv[2]);
    verb=atoi(argv[3]);
    if(n < 2 || 10000 < n){
        printf("The size of the matrix 'n' (%d) must be >= 2 and <= 10,000.\n", n);
        exit(1);
    }
    if(t < 1){
        printf("The number of threads 't' (%d) must be >= 1.\n", t);
        exit(1);
    }

    //create and fill 3 matrices
    Mat mats[3];
    mat_init(&mats[0], n, n);
    mat_init(&mats[1], n, n);
    mat_init(&mats[2], n, n);

    // WARNING: these are just examples on what numbers the matrices could have.
    // While grading, these matrices could be filled with any other valid values.
    mat_fill(&mats[0]);
    mat_diag(&mats[1], 2.0);

    //print original matrices
    if(verb){
        printf("A:\n");
        mat_print(&mats[0]);
        printf("B:\n");
        mat_print(&mats[1]);
	
    }

    //run and measure time taken
    double start = stopwatch();
    mat_multiply(&mats[0], &mats[1], &mats[2], t);
    double end = stopwatch();

    //print results
    if(verb){
        printf("\nC = A x B:\n");
        mat_print(&mats[2]);
    }

    //print execution time
    printf("%.8f\n", end - start);
    
    return 0;
}
