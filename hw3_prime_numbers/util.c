#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "util.h"

#include "util_common.h" //implements


void print_help(char *bin_name){
    fprintf \
        (stderr,"\n"
         "Prime Numbers Finder\n"
         "    This program searches for prime numbers in a given range.\n"
         "    The program generates a log file registering the numbers\n"
         "    found.\n"
         "    The log name has this format (definitions below):\n"
         "        s|m_thr_max.log\n"
         "\n"
         "Usage:\n"
         "    %s s max\n"
         "    %s m thr max\n"
         "    %s (--help|-h|help)\n"
         "\n"
         "  s|m   : Character. Use the sequential or multi-threaded version.\n"
         "  thr   : Number of threads to use in the multi-threaded version.\n"
         "  max   : Maximum number to check for primality.\n"
         "  help  : Show this information.\n"
         "\n"
         "Examples:\n"
         "  Find primes using the sequential implementation up to (and\n"
         "  including) 1000:\n"
         "      %s s 1000\n"
         "  This will produce the log file:\n"
         "      s_1_1000.log\n"
         "\n"
         "  Find primes using the multi-threaded implementation with 24\n"
         "  threads up to (and including) 7890:\n"
         "      %s m 24 7890\n"
         "  This will produce the log file:\n"
         "      m_24_7890.log\n"
         "\n"
         "Author: Claudio Parra (parraca at uci dot edu)\n",
         bin_name, bin_name, bin_name, bin_name, bin_name);
}


void parse_cmd_line(int argc, char **argv, ProgramArgs *args){
    // if asking for help
    if(argc > 1 &&
       (!strcmp(argv[1], "help") ||
        !strcmp(argv[1], "-h") ||
        !strcmp(argv[1], "--help"))
       ){
        print_help(argv[0]);
        exit(0);
    }
       
    // check number of args
    if(argc != 3 && argc != 4){
        fprintf(stderr, "Error: Incorrect number of arguments\n");
        goto error;
    }

    
    // check alg. selection value.
    args->conc = CONC_;
    if(argv[1][1] == '\0'){
        switch(argv[1][0]){
        case 's': args->conc = CONC_SEQUENTIAL; break;
        case 'm': args->conc = CONC_MULTITHREAD; break;
        default: args->conc = CONC_;
        }
    }
    if(args->conc == CONC_){
        fprintf(stderr,"Incorrect algorithm selection, use single "
                "character 's' or 'm'\n");
        goto error;
    }

    if(args->conc == CONC_MULTITHREAD){
        // check number of args for multi-thread
        if(argc != 4){
            fprintf(stderr,"If multi-thread, then provide only "
                    "threads, and max.\n");
            goto error;
        }

        // obtain thr
        char *p = NULL;
        if(get_lint(argv[2], &p, &args->threads,
                    "Could not read the value thr."))
            goto error;

        // obtain max
        if(get_lint(argv[3], &p, &args->max,
                    "Could not read the value max."))
            goto error;
    }else if(args->conc == CONC_SEQUENTIAL){
        // check number of args for sequential
        if(argc != 3){
            fprintf(stderr,"If Sequential, then provide only max value.\n");
            goto error;
        }
        
        args->threads = 1;

        // obtain max
        char *p = NULL;
        if(get_lint(argv[2], &p, &args->max,
                    "Could not read the value max."))
            goto error;
    }
    return;
 error:
    print_help(argv[0]);
    exit(1);
}


void print_arguments(ProgramArgs *a){
    char *conc;
    switch(a->conc){
    case CONC_: conc="CONC_"; break;
    case CONC_SEQUENTIAL: conc="CONC_SEQUENTIAL"; break;
    case CONC_MULTITHREAD: conc="CONC_MULTITHREAD"; break;
    default: conc="?????";
    }
    printf("Concurrency : %s\n", conc);
    if(a->conc == CONC_MULTITHREAD)
        printf("  Threads : %ld\n", a->threads);
    printf("Max     : %ld\n", a->max);
}


void create_filename(char *fname, const ProgramArgs *a, long int /*id*/){
    char *conc;
    switch(a->conc){
    case CONC_SEQUENTIAL: conc= "s"; break;
    case CONC_MULTITHREAD: conc="m"; break;
    default: conc="X";
    }
    sprintf(fname, "%s_%03ld_%08ld.log",
            conc, a->threads, a->max);
}
    
