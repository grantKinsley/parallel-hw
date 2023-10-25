#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util_common.h"
#include "carr_d.h"
#include "util.h"
#include "primes.h"

int main(int argc, char **argv){
    ProgramArgs args;
    parse_cmd_line(argc, argv, &args);

    //open file to store list of primes
    char filename_list_primes[128];
    memset(filename_list_primes, 0, 128);
    create_filename(filename_list_primes, &args, 0);
    FILE *file_list_primes = fopen(filename_list_primes, "w");
    
    //run and measure time taken
    double end, start;
    carr_d_t primes_arr;
    carr_d_init(&primes_arr, 128);
    if(args.conc == CONC_SEQUENTIAL){
        start = stopwatch();
        primes_sequential(&primes_arr, args.max);
        end = stopwatch();
    }else if(args.conc == CONC_MULTITHREAD){
        start = stopwatch();
        primes_parallel(&primes_arr, args.max, args.threads);
        end = stopwatch();
    }

    for(unsigned int i=0; i<primes_arr.size; i++){
        fprintf(file_list_primes, "%d\n", primes_arr.arr[i]);
    }
    fclose(file_list_primes);
    carr_d_destroy(&primes_arr);
    
    //print time taken
    printf("%.8f [s]\n", end - start);
    
    return 0;
}
