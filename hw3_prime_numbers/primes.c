/* NAME: Ethan Duong, Grant Kinsley */
/* UCI ID: 16765837, */

#include <pthread.h>
#include "util_common.h"
#include "primes.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pthread_mutex_t *pmtx;
    unsigned int *counter;
    carr_d_t *primes_list;
    unsigned int max;
} Args;

int isPrime(unsigned int num) {
    if (num <= 1) 
        return 0;

    for (unsigned int i = 2; i <= num/2; i++) {
        if (num % i == 0) 
            return 0;
    }

    return 1;
}

void primes_sequential(carr_d_t *primes_list, unsigned int max){
    for (unsigned int i = 1; i <= max; i++) {
        if(isPrime(i)) 
            carr_d_push(primes_list, i);
    }
}

void* generatePrimes(void *args) {
    Args *a = (Args *) args;
    while (1) {
        pthread_mutex_lock(a->pmtx);
        unsigned int curNum = *(a->counter);
        *(a->counter) = *(a->counter) + 1;
        pthread_mutex_unlock(a->pmtx);

        if (curNum > a->max) 
            pthread_exit(NULL);

        if(isPrime(curNum)) 
            carr_d_push(a->primes_list, curNum);
    }
    pthread_exit(NULL);
}

void primes_parallel(carr_d_t *primes_list, unsigned int max, unsigned int thr) {
    unsigned int counter = 1;
    pthread_t threads[thr];
    pthread_mutex_t pmtx;
    pthread_mutex_init(&pmtx, NULL);

    Args arg_thr = { &pmtx, &counter, primes_list, max };
    
    for (unsigned int i = 0; i < thr; i++) {
        int ret = pthread_create(&threads[i], NULL, &generatePrimes, (void*) &arg_thr);
        if(ret) {
            printf("Error creating thread\n");
            exit(-1);
        }
    }

    for (unsigned int i = 0; i < thr; i++) {
        pthread_join(threads[i], NULL);
    }
}
