// Square Matrix structure
typedef struct {
    double *ptr; // pointer to the first element
    unsigned int m; //height
    unsigned int n; //width
} Mat;

/**
 ** Takes the current time in seconds
 **/
extern double stopwatch(void);

/**
 ** Allocates @m*@n elements of memory for matrix @mat
 **/
extern void mat_init(Mat *mat, unsigned int m, unsigned int n);

/**
 ** Fill matrix @mat with consecutive values.
 **/
extern void mat_fill(Mat *mat);

/**
 ** Fill diagonal of matrix @mat with @diag.
 **/
extern void mat_diag(Mat *mat, double diag);

/**
 ** Copies matrix @from to matrix @to. Matrix @to has to be
 ** previously initialized.
 **/
extern void mat_copy(Mat *to, Mat *from);

/**
 ** Print @mat in @mat->m rows, @mat->n columns
 **/
extern void mat_print(Mat *mat);

/**
 ** Multi-threaded matrix multiplier
 **/
extern void mat_multiply(Mat *A, Mat *B, Mat *C, unsigned int threads);
