#include <time.h>

#include "util_common.h" //implements


double stopwatch(void){
    struct timespec ts;
    //timespec_get(&ts, TIME_UTC); //-std=c11
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double) ts.tv_sec + ts.tv_nsec/1000000000.0;
}


void seed_rng(long int /*seed*/){
    // not implemented yet
}

int mod(int n, int div){
    if(n%div < 0)
        return div+n%div;
    else
        return n%div;
}
