#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "conc_darray.h" //implementing


void carr_init(CArr *a, unsigned int capacity){
    if(capacity < 1)
        capacity = 1;
    a->arr = calloc(capacity, sizeof(unsigned int));
    a->lock = calloc(1, sizeof(pthread_mutex_t));
    if(!a->arr){
        fprintf(stderr, "Error: Couldn't initialize Concurrent Array\n");
        exit(1);
    }
    a->size = 0;
    a->capacity = capacity;
    if(pthread_mutex_init(a->lock, NULL)){
        fprintf(stderr, "Error: Couldn't initialize Concurrent Array's Mutex\n");
        exit(1);
    }
}

void carr_destroy(CArr *a){
    pthread_mutex_lock(a->lock);
    if(a->arr)
        free(a->arr);
    a->size = 0;
    a->capacity = 0;
    a->arr = NULL;
    pthread_mutex_unlock(a->lock);
    if(a->lock){
        pthread_mutex_destroy(a->lock);
        free(a->lock);
    }
}

void carr_push(CArr *a, unsigned int val){
    pthread_mutex_lock(a->lock);
    if(!a->arr || !a->capacity){
        fprintf(stderr, "Error carr_push: Using NULL array. Uninitialized or destroyed perhaps?\n");
        pthread_mutex_unlock(a->lock);
        exit(1);
    }
    while(a->capacity <= a->size){
        a->arr = realloc(a->arr, 2*a->capacity*sizeof(unsigned int));
        if(!a->arr){
            fprintf(stderr, "Error: Couldn't grow Concurrent Array\n");
            pthread_mutex_unlock(a->lock);
            exit(1);
        }
        a->capacity *= 2;
    }
    a->arr[a->size] = val;
    a->size += 1;
    pthread_mutex_unlock(a->lock);
}

void carr_pop(CArr *a, unsigned int *val){
    pthread_mutex_lock(a->lock);
    if(!a->arr || !a->capacity){
        fprintf(stderr, "Error: Popping from NULL array. Uninitialized or destroyed perhaps?\n");
        pthread_mutex_unlock(a->lock);
        exit(1);
    }
    if(!a->size){
        fprintf(stderr, "Error: Popping from empty array\n");
        pthread_mutex_unlock(a->lock);
        exit(1);
    }
    a->size -= 1;
    *val = a->arr[a->size];
    pthread_mutex_unlock(a->lock);
}
    
static inline void swap(unsigned int *a, unsigned int *b){
    unsigned int t;
    t = *a;
    *a = *b;
    *b = t;
}

static unsigned int part(unsigned int *arr, unsigned int left, unsigned int right){
    if(left == right)
        return left;
    swap(arr+left/2+right/2, arr+right); //swap center with last
    unsigned piv = arr[right]; //piv kind of median
    unsigned int lp=left, rp=right-1;
    while(1){
        while(lp<rp){
            if(piv < arr[lp])
                break;
            lp +=1;
        }
        while(lp<rp){
            if(arr[rp] < piv)
                break;
            rp -= 1;
        }
        if(!(lp<rp))
            break;
        swap(arr+lp, arr+rp);
    }
    if(arr[rp] > arr[right])
        swap(arr+rp, arr+right);
    return rp;
}

static void quick_sort(unsigned int *arr, unsigned int left, unsigned int right){
    unsigned int piv_index;
    if(left>=right){
        return;
    }else{
        piv_index = part(arr, left, right);
        if(0 < piv_index)
            quick_sort(arr, left, piv_index-1);
        if(piv_index < UINT_MAX)
            quick_sort(arr, piv_index+1, right);
    }        
}

void carr_sort(CArr *a){
    pthread_mutex_lock(a->lock);
    quick_sort(a->arr, 0, a->size-1);
    pthread_mutex_unlock(a->lock);
}

void carr_print(CArr *a){
    pthread_mutex_lock(a->lock);
    printf("[");
    if(a->size > 0){
        printf("%3u", a->arr[0]);
        for(unsigned int i=1; i<a->size; i++){
            printf(",%3u", a->arr[i]);
        }
    }
    printf(" ]\n");
    pthread_mutex_unlock(a->lock);
}
    
