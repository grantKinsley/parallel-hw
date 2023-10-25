#ifndef _COMMON_CONC_DARRAY_H_ //include guard
#define _COMMON_CONC_DARRAY_H_

#include <pthread.h>

/**
 ** Concurrent Array of integers.
 ** Thread safe array implementation
 **/
typedef struct CArr{
    unsigned int *arr;
    unsigned int size;
    unsigned int capacity;
    pthread_mutex_t *lock;
} CArr;

extern void carr_init(CArr *a, unsigned int capacity);

extern void carr_destroy(CArr *a);

extern void carr_push(CArr *a, unsigned int val);

extern void carr_pop(CArr *a, unsigned int *val);

extern void carr_sort(CArr *a);

extern void carr_print(CArr *a);

#endif //include guard
