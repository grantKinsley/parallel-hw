#ifndef _UTIL_H_ //include guard
#define _UTIL_H_

typedef enum Concurrency {
    CONC_=0,
    CONC_SEQUENTIAL=1,
    CONC_MULTITHREAD=2
} Concurrency;

/**
 * @brief Granularity parameters.
 */
struct ProgramArgs{
    unsigned int size;    ///< size of the matrix (size * size elements)
    unsigned int threads; ///< number of threads to use
    unsigned int grain;   ///< granularity of the work-unit
    Concurrency conc;     ///< Sequential or Multi-threaded
};

#endif //include guard
