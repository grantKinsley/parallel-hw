/* SUBMIT ONLY THIS FILE */
/* NAME: ....... */
/* UCI ID: .......*/

#include <pthread.h>
#include "util_common.h"
#include "primes.h"//implementing



//>>>>>>>> DELETE CODE FROM THIS POINT
#ifdef DEBUG
/**
 * This is just a demo code to show the use of the concurrent
 * array type and its functions (carr_d_xxxx). For more info,
 * read the comments in carr_d.h
 **/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void demo_code(carr_d_t *my_array, unsigned int max){
    unsigned int x=0;
    srand((unsigned) time(NULL));
    printf("Empty array:\n");
    carr_d_print(my_array);

    unsigned int i;
    for(i=0; i<10; i++){
        x = rand() % max;
        printf("Pushing %d.\n", x);
        carr_d_push(my_array, x);
        carr_d_print(my_array);
    }
}
#endif
//<<<<<<<< DELETE UP TO THIS POINT

// Return 1 if num is prime
// Else return 0
int isPrime(unsigned int num) {
    if (num <= 1) {
        return 0;
    }
    for (unsigned int i = 2; i <= num/2; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

void primes_sequential(carr_d_t *primes_list, unsigned int max){
    for (unsigned int i = 1; i <= max; i++) {
        if(isPrime(i)) {
            carr_d_push(primes_list, i);
        }
    }
    // carr_d_print(primes_list);
    return;
}

void primes_parallel(carr_d_t *primes_list, unsigned int max, \
                     unsigned int thr){
        
    // YOUR CODE GOES HERE

    //>>>>>>>> DELETE CODE FROM THIS POINT
#ifdef DEBUG
    printf("## DEMO CODE. DELETE BEFORE SUBMITTING!! ##\n");
    printf("primes_parallel(carr_d_t=[pointer], max=%u, thr=%u);\n", \
           max, thr);
    demo_code(primes_list, max);
    printf("## DEMO CODE. DELETE BEFORE SUBMITTING!! ##\n");
#endif
    //<<<<<<<< DELETE UP TO THIS POINT
    return;
}