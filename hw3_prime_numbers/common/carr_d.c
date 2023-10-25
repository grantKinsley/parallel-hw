#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "carr_d.h" //implementing


void carr_d_init(carr_d_t *a, unsigned int capacity){
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

void carr_d_destroy(carr_d_t *a){
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

void carr_d_push(carr_d_t *a, unsigned int val){
    pthread_mutex_lock(a->lock);
    if(!a->arr || !a->capacity){
        fprintf(stderr, "Error carr_d_push: Using NULL array. Uninitialized or destroyed perhaps?\n");
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

void carr_d_pop(carr_d_t *a, unsigned int *val){
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

void carr_d_print(carr_d_t *a){
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
    
