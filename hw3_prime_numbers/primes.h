#ifndef _PRIMES_H_ //include guard
#define _PRIMES_H_

#include "carr_d.h"

/**
 * @brief Finds and stores all prime numbers beween 2 and max using
 *        a sequential approach.
 * @param[out] array list in which to store the primes found.
 * @param[in]  max maximum number for which to check.
 */
extern void primes_sequential(carr_d_t *primes_list, unsigned int max);

/**
 * @brief Finds and stores all prime numbers beween 2 and max using
 *        many threads.
 * @param[out] array list in which to store the primes found.
 * @param[in]  max maximum number for which to check.
 * @param[in]  thr number of threads that will work together.
 */
extern void primes_parallel(carr_d_t *primes_list, unsigned int max, \
                            unsigned int thr);

#endif //include guard
