#ifndef _COMMON_MATRIX_H_ //include guard
#define _COMMON_MATRIX_H_
/**
 * @brief Matrix data structure.
 */
typedef struct Mat{
    double *ptr;    ///< pointer to the first element of the matrix
    unsigned int m; ///< height (number of rows)
    unsigned int n; ///< width (number of columns)
} Mat;

/**
 * @brief Default value for structure Mat. Use it when declaring a matrix.
 */
extern Mat MAT_DEFAULT;

/**
 * @brief Allocates memory for a matrix and initialize the size members.
 * Due to calloc(), the matrix is filled with zeroes.
 * The matrix should not have been previously initialized.
 * @param[in] mat uninitialized matrix data structure
 * @param[in] m   number of rows
 * @param[in] n   number of columns
 */
extern void mat_init(Mat *mat, unsigned int m, unsigned int n);


/**
 * @brief Fill matrix with consecutive incremental values. The first 
 * value used is @p val. The matrix shoud have been initialized already.
 * @param[in] val the number to to put in the top left corner
 */
extern void mat_fill_incr(Mat *mat, double val);


/**
 * @brief Fill matrix with random values. The matrix shoud have been
 * initialized already.
 */
extern void mat_fill_rand(Mat *mat);


/**
 * @brief Fill the diagonal of a matrix. The matrix should have been
 * initialized already.
 * @param val[in] value to put in the diagonal
 */
extern void mat_fill_diag(Mat *mat, double val);


/**
 * @brief Copies a matrix into another. The matrix @p to shoud have been
 * initialized already.
 * @param[in]  from matrix to read from
 * @param[in]  to   matrix to write into
 */
extern void mat_fill_copy(Mat *to, Mat *from);


/**
 * @brief Print the matrix to stdout.
 */
extern void mat_print(Mat *mat);


/**
 * @brief Checks whether the transposition of @p tested was correct.
 * @param[in] orig   matrix that contains exactly what @p tested had
 *                   before the transposition.
 * @param[in] tested matrix to be tested against @p original
 * @return           0 if correct.
 *                   1 if incorrect, printing error to stderr.
 */
extern int mat_check_transpose(Mat *original, Mat *tested);

/**
 * @brief Parallel matrix multiplier. The matrix @p C should have
 * been previously initialized.
 * @param[in]  A   input matrix.
 * @param[in]  B   input matrix.
 * @param[out] C   output matrix.
 * @param[in]  thr number of threads in which the task is divided.
 */
extern void mat_multiply(Mat *A, Mat *B, Mat *C, unsigned int thr);

#endif //include guard
