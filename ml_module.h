#ifndef ML_MODULE_H
#define ML_MODULE_H

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/random.h>
#include <asm/fpu/api.h>
#include <linux/slab.h>
/* #include <math.h> */

typedef float REAL;
#define RAND_MAX 2147483647
#define RAND -1

/* #define m(i, j) (m)->data[i * m->ncol + j] */

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

matrix *W1;
matrix *b1;
matrix *W2;
matrix *b2;

// Fast sqrt function taken from: https://github.com/sbu-fsl/kernel-ml/blob/main/src/math/math.c
REAL _sqrt(REAL x) {
  REAL r;
  int i = *(int *)&x;
  i = 0x5f3759df - (i >> 1);
  r = *(REAL *)&i;
  r = r * (1.5f - 0.5f * x * r * r);
  r = r * (1.5f - 0.5f * x * r * r);
  r = r * (1.5f - 0.5f * x * r * r);
  return r * x;
}

inline int random(void) {
  int rand = 0;
  get_random_bytes(&rand, sizeof(int) - 1);
  printk(KERN_ALERT "HELLO: %d", rand);
  return rand % 256;
}

inline REAL normal_dist(void) { return ((REAL) (random()) + 1.0) / ((REAL)(RAND_MAX) + 1.0); }

inline void create_matrix(matrix *mat, int nrows, int ncols, int value) {
    /* if(value == RAND) { */
    /*     srand(time(NULL)); */
    /* } */
    mat->nrows = nrows;
    mat->ncols = ncols;
    mat->data = (REAL *)kmalloc(mat->nrows * mat->ncols * sizeof(REAL), GFP_KERNEL);
    if(!mat->data) {
        printk(KERN_ALERT "HELLO: malloc failed\n");
        return;
    }
    for(int i = 0; i < mat->nrows; i++) {
        for(int j = 0; j < mat->ncols; j++) {
            mat->data[i * mat->ncols + j] = value == RAND ? normal_dist() : value;
        }
    }
}

inline void destroy_matrix(matrix *mat) {
  kfree(mat->data);
}

#endif
