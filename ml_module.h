#ifndef ML_MODULE_H
#define ML_MODULE_H

/* #include "common.h" */
/* #include <linux/init.h> */
/* #include <linux/module.h> */
/* #include <linux/kernel.h> */
/* #include <linux/random.h> */
/* /1* #include <asm/fpu/api.h> *1/ */
/* #include <linux/slab.h> */
/* #include <math.h> */


/* #define m(i, j) (m)->data[i * m->ncol + j] */

/* typedef struct matrix_t { */
/*     int nrows; */
/*     int ncols; */
/*     REAL *data; */
/* } matrix; */

/* typedef struct vector_t { */
/*     int nrows; */
/*     int ncols; */
/*     REAL *data; */
/* } vector; */

/* matrix W1; */
/* matrix b1; */
/* matrix W2; */
/* matrix b2; */
/* matrix W3; */
/* matrix b3; */


/* // Fast sqrt function taken from: https://github.com/sbu-fsl/kernel-ml/blob/main/src/math/math.c */
/* /1* REAL _sqrt(REAL x) { *1/ */
/* /1*   REAL r; *1/ */
/* /1*   int i = *(int *)&x; *1/ */
/* /1*   i = 0x5f3759df - (i >> 1); *1/ */
/* /1*   r = *(REAL *)&i; *1/ */
/* /1*   r = r * (1.5f - 0.5f * x * r * r); *1/ */
/* /1*   r = r * (1.5f - 0.5f * x * r * r); *1/ */
/* /1*   r = r * (1.5f - 0.5f * x * r * r); *1/ */
/* /1*   return r * x; *1/ */
/* /1* } *1/ */

/* inline int random(void) { */
/*   int rand = 0; */
/*   get_random_bytes(&rand, sizeof(int) - 1); */
/*   printk(KERN_ALERT "HELLO: %d", rand); */
/*   return rand % 256; */
/* } */

/* /1* inline REAL normal_dist(void) { return ((REAL) (random()) + 1.0) / ((REAL)(RAND_MAX) + 1.0); } *1/ */

/* inline void create_matrix(matrix *mat, int nrows, int ncols, int value) { */
/*     /1* if(value == RAND) { *1/ */
/*     /1*     srand(time(NULL)); *1/ */
/*     /1* } *1/ */
/*     mat->nrows = nrows; */
/*     mat->ncols = ncols; */
/*     mat->data = (REAL *)kmalloc(mat->nrows * mat->ncols * sizeof(REAL), GFP_KERNEL); */
/*     if(!mat->data) { */
/*         printk(KERN_ALERT "HELLO: malloc failed\n"); */
/*         return; */
/*     } */
/*     for(int i = 0; i < mat->nrows; i++) { */
/*         for(int j = 0; j < mat->ncols; j++) { */
/*             mat->data[i * mat->ncols + j] = value == RAND ? 1 : value; */
/*         } */
/*     } */
/* } */

/* inline void destroy_matrix(matrix *mat) { */
/*   kfree(mat->data); */
/* } */

#endif
