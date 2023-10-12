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

double calculate_average_access_time(int cycle, int num_accesses) {
    return num_accesses > 0 ? (double)(cycle) / num_accesses : -1.0;
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

double test_stop_condition(int cycle, double* average_accesses_by_cycle) {
    if (cycle == 0) {
        return 0;
    }
    double cur = average_accesses_by_cycle[cycle];
    double prev = average_accesses_by_cycle[cycle-1];
    if (cur > 0 && prev > 0 && fabs(1-(prev/cur)) < VAR_EPSILON) {
        return cur;
    }
    return 0;
}

void generate_normal_means(int* normal_means, int len, int num_mems) {
    for (int i = 0; i < len; i++) {
        normal_means[i] = rand_uniform(num_mems);
    }
}

int allocate_memory(int* memory, int len, char dist, int* normal_means, int proc) {
    int mem_index = 0;
    if (dist == 'u') {
        mem_index = rand_uniform(len);
    } else if (dist == 'n') {
        int mean = normal_means[proc];
        int dev = 5;
        mem_index = rand_normal_wrap(mean, dev, len);
    } 
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

    int normal_means[num_procs];
    if (dist == 'n') {
        generate_normal_means(normal_means, num_procs, num_mems);
    }

    reset_array(access_times, num_procs);
    reset_array(memory, num_mems);

    for (int i = 0; i < MAX_CYCLES; i++) {
        int new_start_point = -1;
        int cur_point = start_point;

        // Allocate memory to each process
        for (int j = 0; j < num_procs; j++) {
            int allocation_success = allocate_memory(memory, num_mems, dist, normal_means, j);
            if (allocation_success) {
                access_times[cur_point]++;
            }
            else if(new_start_point < 0) {
                new_start_point = cur_point;
            }
            time_cumulitive_averages[cur_point] = calculate_average_access_time(i+1, access_times[cur_point]);
            cur_point = cur_point < num_procs - 1 ? cur_point + 1 : 0;
        }

        start_point = new_start_point >= 0 ? new_start_point : start_point;
        
        average_accesses_by_cycle[i] = average_array(time_cumulitive_averages, num_procs);
        if (test_stop_condition(i, average_accesses_by_cycle)) {
            return average_accesses_by_cycle[i];
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

    for (int i = 0; i < avg_access_time_len; i++) {
        avg_access_time[i] = run_cycles(procs, i+1, dist);
    }
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
