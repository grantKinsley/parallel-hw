#ifndef _UTIL_H_ //include guard
#define _UTIL_H_

typedef enum Concurrency {
    CONC_=0,
    CONC_SEQUENTIAL=1,
    CONC_MULTITHREAD=2
} Concurrency;

/**
 * @brief Prime Numbers parameters.
 */
struct ProgramArgs{
    long int max;     ///< maximum number to test
    long int threads; ///< number of threads to use
    Concurrency conc; ///< Sequential or Multi-threaded
};

#endif  //include guard
