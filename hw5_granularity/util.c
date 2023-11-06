#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "util.h"

#include "util_common.h" //implements

void print_help(char *bin_name){
    fprintf \
        (stderr,"\n"
         "Square Matrix Transposer\n"
         "    Given a nxn matrix, this program obtains its transposed\n"
         "    using O(1) extra memory.\n"
         "\n"
         "Usage:\n"
         "    %s size s\n"
         "    %s size m threads grain\n"
         "    %s (--help|-h|help)\n"
         "\n"
         "  size    : Integer. Size of one side of the square matrix.\n"
         "  s|m     : Character. Use the sequential or multi-threaded "
         "transposer.\n"
         "  threads : Integer. Threads to use in the multi-threaded "
         "transposer.\n"
         "  grain   : Integer. Granularity of the threads' workload.\n"
         "  help    : Show this information.\n"
         "\n"
         "Examples:\n"
         "  Transpose a 300x300 matrix using the sequential algorithm:\n"
         "      %s 300 s\n"
         "\n"
         "  Transpose a 500x500 matrix using 4 threads and a grain of 25\n"
         "  elements:\n"
         "      %s 500 m 4 25\n",
         bin_name, bin_name, bin_name, bin_name, bin_name);
}
void parse_cmd_line(int argc, char **argv, ProgramArgs *args){

    /**
     * NEEDS TO BE CLEANED AND STANDARIZED
     */
    char *p;
    // check number of args
    if(argc != 3 && argc != 5){
        fprintf(stderr,"Incorrect number of arguments\n");
        goto error;
    }
    
    // check matrix size is a number.
    args->size = strtoul(argv[1], &p, 10);
    if(*p != '\0' || args->size == 0){
        fprintf(stderr,"Incorrect matrix size.\n");
        goto error;
    }
    
    // check alg. selection value.
    args->conc = CONC_;
    if(argv[2][1] == '\0'){
        switch(argv[2][0]){
        case 's': args->conc = CONC_SEQUENTIAL; break;
        case 'm': args->conc = CONC_MULTITHREAD; break;
        default: args->conc = CONC_;
        }
    }
    if(args->conc == CONC_){
        fprintf(stderr,"Incorrect algorithm selection, use single character 's' or 'm'\n");
        goto error;
    }
    
    if(args->conc == CONC_MULTITHREAD){
        // check number of args for multi-thread
        if(argc != 5){
            fprintf(stderr,"If multi-thread, then provide only size and threads.\n");
            goto error;
        }
        
        // check # of threads.
        args->threads = strtoul(argv[3], &p, 10);
        if(*p != '\0' || args->threads == 0){
            fprintf(stderr,"Incorrect number of threads.\n");
            goto error;
        }
        // check grain size.
        args->grain = strtoul(argv[4], &p, 10);
        if(*p != '\0' || args->grain == 0){
            fprintf(stderr,"Incorrect number of threads.\n");
            goto error;
        }
    }else{
        // check number of args for sequential
        if(argc != 3){
            fprintf(stderr,"If sequential, then provide only matrix size.\n");
            goto error;
        }
    }
    
    return;
 error:
    print_help(argv[0]);
    exit(1);
}


void print_arguments(ProgramArgs *a){
    printf("Matrix size : %d x %d\n"
           "Threads     : %d\n"
           "Grain       : %d\n",
           a->size, a->size, a->threads, a->grain);
    char *conc;
    switch(a->conc){
    case CONC_: conc="CONC_"; break;
    case CONC_SEQUENTIAL: conc="CONC_SEQUENTIAL"; break;
    case CONC_MULTITHREAD: conc="CONC_MULTITHREAD"; break;
    default: conc="?????";
    }
    printf("Concurrency : %s\n", conc);
}


void create_filename(char *fname, const ProgramArgs *a, long int /*id*/){
    char *conc;
    switch(a->conc){
    case CONC_SEQUENTIAL: conc= "s"; break;
    case CONC_MULTITHREAD: conc="m"; break;
    default: conc="X";
    }
    sprintf(fname, "%s_%03d_%08d_%08d.log",
            conc, a->threads, a->grain, a->size);
}
   

