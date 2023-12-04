#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const unsigned int MIN_INTERVAL = 100;
const unsigned int MAX_INTERVAL = 1000;
const unsigned int MIN_LOAD = 10;
const unsigned int MAX_LOAD = 1000;

struct ProcInterval {
    unsigned int currentInterval;
    unsigned int fixedInterval;
    unsigned int proc;
}p;

typedef struct ProcInterval procInterval;

unsigned int randNum(unsigned int min, unsigned int max) {
    return (rand() % (max-min+1)) + min; 
}

void print_loads(unsigned int* procLoads, unsigned int numProcessors) {
    for (unsigned int i = 0; i < numProcessors; i++) {
        printf("%d ", procLoads[i]);
    }
    printf("\n");
}

int stop_condition(unsigned int lastChange, unsigned int curIteration) {
    if (curIteration - lastChange > MAX_INTERVAL) {
        return 1;
    }
    return 0;
}

int compare(const void* p, const void* q) {  
    procInterval *a = (procInterval *)p;  
    procInterval *b = (procInterval *)q;  
    return (a -> currentInterval) - (b -> currentInterval);  
}  

void sort(procInterval* procIntervals, unsigned int numProcessors) {
    qsort((void *) procIntervals, numProcessors, sizeof(p), compare);  
}

void initialize(unsigned int* procLoads, procInterval* procIntervals, unsigned int numProcessors) {
    srand(time(NULL));
    for (int i = 0; i < numProcessors; i++) {
        procIntervals[i].fixedInterval = randNum(MIN_INTERVAL, MAX_INTERVAL);
        procIntervals[i].currentInterval = procIntervals[i].fixedInterval;
        procIntervals[i].proc = i;
        procLoads[i] = randNum(MIN_LOAD, MAX_LOAD);
    }
    sort(procIntervals, numProcessors);
}

int redistribute(unsigned int* procLoads, unsigned int numProcessors, unsigned int givingProc) {
    const unsigned int left = givingProc > 0 ? givingProc - 1 : numProcessors-1;
    const unsigned int right = (givingProc + 1) % numProcessors;
    unsigned int smallest = procLoads[left] <= procLoads[right] ? left : right;

    if (procLoads[smallest] + 1 >= procLoads[givingProc]) return 0;

    while (procLoads[smallest] + 1 < procLoads[givingProc]) {
        procLoads[givingProc]--;
        procLoads[smallest]++;
        smallest = procLoads[left] <= procLoads[right] ? left : right;
    }

    return 1;
}

void load_balance_sim(unsigned int numProcessors) {
    unsigned int procLoads[numProcessors];
    procInterval procIntervals[numProcessors];
    initialize(procLoads, procIntervals, numProcessors);

    printf("\n-----NUM PROCESSORS: %d-----\n", numProcessors);
    printf("Initial loads:\n");
    print_loads(procLoads, numProcessors);

    unsigned int lastChange = 0;
    for (unsigned int i = 0; i < UINT32_MAX - MAX_INTERVAL - 1; i++) {
        int doesRedistribute = redistribute(procLoads, numProcessors, procIntervals[0].proc);
        procIntervals[0].currentInterval += procIntervals[0].fixedInterval;
        sort(procIntervals, numProcessors);
        if (doesRedistribute) {
            lastChange = i;
        }
        if (stop_condition(lastChange, i)) {
            break;
        }
    }

    printf("End loads:\n");
    print_loads(procLoads, numProcessors);
    printf("Total number of cycles to reach steady balanced state: %d\n", lastChange);
}

int main() {
    load_balance_sim(5);
    load_balance_sim(10);
    load_balance_sim(100);
    printf("\n");
    return 0;
}