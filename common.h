#ifndef COMMON_H
#define COMMON_H
/* #include <stdlib.h> */
/* #include <linux/random.h> */

typedef int REAL;
#define RAND_MAX 2147483647
#define RAND -1
#define NR_FEAT     10
#define NR_OUT      10
#define HIDDEN_SIZE 128
#define MAX(a, b) (a < b ? b : a)

typedef struct matrix_t {
    int nrows;
    int ncols;
    REAL *data;
} matrix;

typedef struct vector_t {
    int nrows;
    int ncols;
    REAL *data;
} vector;

/* extern matrix W1; */
/* extern matrix b1; */
/* extern matrix W2; */
/* extern matrix b2; */
/* extern matrix W3; */
/* extern matrix b3; */


// Fast sqrt function taken from: https://github.com/sbu-fsl/kernel-ml/blob/main/src/math/math.c
/* REAL _sqrt(REAL x) { */
/*   REAL r; */
/*   int i = *(int *)&x; */
/*   i = 0x5f3759df - (i >> 1); */
/*   r = *(REAL *)&i; */
/*   r = r * (1.5f - 0.5f * x * r * r); */
/*   r = r * (1.5f - 0.5f * x * r * r); */
/*   r = r * (1.5f - 0.5f * x * r * r); */
/*   return r * x; */
/* } */

/* inline static int random(void) { */
/*   int rand = 0; */
/*   get_random_bytes(&rand, sizeof(int) - 1); */
/*   return rand % 256; */
/* } */

/* inline REAL normal_dist(void) { return ((REAL) (random()) + 1) / ((REAL)(RAND_MAX) + 1); } */

inline static void init_matrix(matrix *mat, int value) {
    for(int i = 0; i < mat->nrows; i++) {
        for(int j = 0; j < mat->ncols; j++) {
            mat->data[i * mat->ncols + j] = value == RAND ? 1 : value;
        }
    }
}

inline static void destroy_matrix(matrix *mat) {
}

#endif
