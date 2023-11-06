#ifndef _TRANSPOSE_H_ //include guard
#define _TRANSPOSE_H_

#include "matrix.h"
/**
 * @brief Sequential in-place square matrix
 *        transposer.
 * @param mat   Data Structure with the matrix to
 *              transpose.
 */
void mat_squaretransp_sequential(Mat *mat);

/**
 * @brief Multi-threaded in-place square matrix
 *        transposer.
 * @param mat   Data Structure with the matrix to
 *              transpose. It is shared among all
 *              working threads.
 * @param grain Grain size that defines the work-unit.
 *              Normally "the number of exchanges"
 *              to perform.
 * @param thr   Number of threads that will work 
 *              togeter to transpose the matrix.
 */
void mat_squaretransp_parallel(Mat *mat, unsigned int grain, unsigned int thr);

#endif
