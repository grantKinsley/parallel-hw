#ifndef SIMULATOR_H
#define SIMULATOR_H

/*
** Max number of memory modules.
*/
extern int NUM_MEMS;

/*
** Runs the simulation of <avg_access_time_len> systems. Each one of them with
** <procs> processors and a memory request probability distribution <dist>.
** The first system has 1 memory module, the second with 2... and so on until
** the last one with <avg_access_time_len - 1> memory modules.
**
** At the end of the simulation with i memory modules, the function writes
** the last time-cumulative average access-time in avg_access_time[i-1]
**
**
** PARAMETERS:
** avg_access_time:     Array to be witten with the last time-cumulative
**                      average access time of each simulation.
** avg_access_time_len: Length of the previous array.
** procs:               Number of processors in this simulated system.
** dist:                Probability distribution used for memory requests.
*/
void simulate(double *avg_access_time,
              int avg_access_time_len,
              int procs,
              char dist);

/*
** Generates a random integer between 0 and max with uniform distribution.
** Max is exclusive (it will never be returned).
*/
int rand_uniform(int max);

/*
** Generates a random integer normally distributed around <mean>, with standard
** deviation <dev>. The result is wrapped around <max> so the result is always
** equal or greater than 0 and less than max. For example:
**   - if the result would have been 12, but max=10,
**     then the returned value is 2.
**   - If the result would have been 10, but max=10,
**     then the retruned value is 0.
*/
int rand_normal_wrap(int mean, int dev, int max);

#endif /* SIMULATOR_H */
