#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "util_common.h"
#include "util.h"
#include "transpose.h"

int main(int argc, char **argv){
    ProgramArgs args;
    parse_cmd_line(argc, argv, &args);

    //filename for the log
    char log_name[128];
    memset(log_name, 0, 128);
    create_filename(log_name, &args, 0);
    FILE *log_file = fopen(log_name, "w");
    
    // create two identical matrices and show it
    Mat m, m_ctl;
    mat_init(&m, args.size, args.size);
    mat_init(&m_ctl, args.size, args.size);
    mat_fill_incr(&m, 1);
    mat_fill_copy(&m_ctl, &m);
    
#ifdef DEBUG
    printf("Original:\n");
    mat_print(&m);
#endif

    // run and measure time taken
    double start, end;
    if(args.conc == CONC_SEQUENTIAL){
        start = stopwatch();
        mat_squaretransp_sequential(&m);
        end = stopwatch();
    }else if(args.conc == CONC_MULTITHREAD){
        start = stopwatch();
        mat_squaretransp_parallel(&m, args.grain, args.threads);
        end = stopwatch();
    }

    // show result
#ifdef DEBUG
    printf("\nTransposed:\n");
    mat_print(&m);
#endif

    //check correctness
    if(mat_check_transpose(&m_ctl, &m))
        exit(1);
    
    //save results
    fprintf(log_file, "%.8f\n",end-start);
    fclose(log_file);
    return 0;
}
