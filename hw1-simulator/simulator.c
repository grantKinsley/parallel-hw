/* SUBMIT ONLY THIS FILE */
/* NAME: ....... */
/* UCI ID: .......*/

// only include standard libraries.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simulator.h" // implements

double PI_VAL = 3.14159265358979323846;
int MAX_CYCLES = 1000000;
double VAR_EPSILON = 0.02;

void reset_array(int* arr, int len) {
    for(int i = 0; i < len; i++) {
        arr[i] = 0;
    } 
}

// Calculate average function
// Setup memory array (boolean array)
// Track start point (integer, first element to fail)
// iterate PROCS number of times ring pattern starting from start point
// end when start point is -1

double calculate_access_time(int cycle, int num_accesses) {
    return (double)(cycle+1) / num_accesses;
}

double average_array(double* arr, int len) {
    double sum = 0.0;
    for (int i = 0; i < len; i++) {
        if (arr[i] < 0.0) {
            return -1.0;
        }
        sum += arr[i];
    }
    return sum / len;
}

double evaluate_stop_condition(int cycle, double* average_accesses_by_cycle) {
    if (cycle == 0) {
        return -1.0;
    }
    double cur = average_accesses_by_cycle[cycle];
    double prev = average_accesses_by_cycle[cycle-1];
    if (cur > 0 && prev > 0 && fabs(1-(prev/cur)) < VAR_EPSILON) {
        return cur;
    }
    return -1.0;
}

int allocate_memory(int* memory, int len, char dist) {
    int mem_index = 0;
    if (dist == 'u') {
        mem_index = rand_uniform(len);
    } else if (dist == 'n') {
        // TODO
        return 0;
    } else {
        return 0;
    }
    // printf("MEM_INDEX %d\n" , mem_index);
    if (memory[mem_index]) {

        return 0;
    }
    memory[mem_index] = 1;
    return 1;
}

double run_cycles(int num_procs, int num_mems, char dist) {
    int memory[num_mems];
    int access_times[num_procs];
    double average_accesses_by_cycle[MAX_CYCLES];
    double time_cumulitive_averages[num_procs];
    int start_point = 0;

    reset_array(access_times, num_procs);
    reset_array(memory, num_mems);

    for (int i = 0; i < MAX_CYCLES; i++) {
        int new_start_point = -1;
        int cur_point = start_point;
        for (int i = 0; i < num_procs; i++, cur_point = cur_point < num_procs - 1 ? cur_point + 1 : 0) {
            // printf("ALLOCATING PROCESS %d\n", cur_point);
            int allocation_success = allocate_memory(memory, num_mems, dist);
            if (allocation_success) {
                access_times[cur_point]++;
                // printf("ALLOCATION SUCCESS\n");
            }
            else if(new_start_point < 0) {
                new_start_point = cur_point;
            }
            if (!allocation_success) {
                // printf("ALLOCATION FAIL\n");
            }
            time_cumulitive_averages[cur_point] = access_times[cur_point] > 0 ? (double)(i+1) / access_times[cur_point] : -1.0;
        }
        if (new_start_point >= 0) {
            // printf("OLD START POINT: %d. NEW START POINT: %d\n", start_point, new_start_point);

            start_point = new_start_point;
        }
        average_accesses_by_cycle[i] = average_array(time_cumulitive_averages,num_procs);
        double res = evaluate_stop_condition(i, average_accesses_by_cycle);
        if (res > 0) {
            return res;
        }
        reset_array(memory, num_mems);
    }

    printf("FAILURE: STALLING OCCURED\n");

    return -1.0;
}

void simulate(double *avg_access_time,
              int avg_access_time_len,
              int procs,
              char dist){

    for (int i = 0; i < NUM_MEMS; i++) {
        avg_access_time[i] = run_cycles(procs, i+1, dist);
    }
    
    //////////////////////////////////////////////////////
    // YOUR CODE GOES HERE.
    // start of useless code. Just delete it.
    // for(int i=0; i<avg_access_time_len; i++) {
    //     avg_access_time[i] = rand_normal_wrap(75,5,100);
    // }
    // printf("procs: %d\ndist: %c\n", procs, dist);
    // end of useless code
    //////////////////////////////////////////////////////
}


int rand_uniform(int max){
    return rand() % max;
}

int rand_normal_wrap(int mean, int dev, int max){
    static double U, V;
    static int phase = 0;
    double Z;
    if(phase == 0){
        U = (rand() + 1.) / (RAND_MAX + 2.);
        V = rand() / (RAND_MAX + 1.);
        Z = sqrt(-2 *log(U)) * sin(2 * PI_VAL * V);
    }else{
        Z = sqrt(-2 * log(U)) * cos(2 * PI_VAL * V);
    }
    phase = 1 - phase;
    double res = dev*Z + mean;

    // round result up or down depending on whether
    // it is even or odd. This compensates some bias.
    int res_int;
    // if even, round up. If odd, round down.
    if ((int)res % 2 == 0)
        res_int = (int)(res+1);
    else
        res_int = (int)(res);

    // wrap result around max
    int res_wrapped = res_int % max;
    // deal with % of a negative number in C
    if(res_wrapped < 0)
        res_wrapped += max;
    return res_wrapped;
}
