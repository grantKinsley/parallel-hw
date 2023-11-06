#ifndef _COMMON_CARR_D_H_ //include guard
#define _COMMON_CARR_D_H_

#include <pthread.h>

/**
 ** Concurrent Array of integers.
 ** Thread safe array implementation.
 **
 ** Functions:
 ** Initialize array with some initial capacity.
 ** Destroy array and free resources.
 ** Push new value at the end of the array
 ** Pop value from the end of the array
 ** Print array in a pretty manner
 **/

typedef struct carr_d_t{
    unsigned int *arr;
    unsigned int size;
    unsigned int capacity;
    pthread_mutex_t *lock;
} carr_d_t;

extern void carr_d_init(carr_d_t *a, unsigned int capacity);
extern void carr_d_destroy(carr_d_t *a);
extern void carr_d_push(carr_d_t *a, unsigned int val);
extern void carr_d_pop(carr_d_t *a, unsigned int *val);
extern void carr_d_print(carr_d_t *a);

#endif //include guard
