#include "ml_module.h"

#define NR_FEAT     15
#define NR_OUT      10
#define MAX(a, b) (a < b ? b : a)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rubens Lacouture");
MODULE_DESCRIPTION("Simple kernel module");
MODULE_VERSION("0.01");

void matmul(matrix *C, matrix *A, matrix *B) {
  int M = A->nrows;
  int N = B->ncols;
  int K = A->ncols;
  int sum;
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < N; j++) {
      sum = 0;
      for(int k = 0; k < K; k++) {
        sum += A->data[i * A->ncols + k] * B->data[j * A->ncols + k];
      }
      C->data[i * C->ncols + j] += sum;
    }
  }
}

int matadd(matrix *C, matrix *A, matrix *B)
{
    for (int i = 0; i < A->nrows * A->ncols; i++) {
        C->data[i] = A->data[i] + B->data[i];
    }
    return 0;
}

void ReLU(matrix *C)
{
    for (int i = 0; i < C->nrows * C->ncols; i++) {
        C->data[i] = MAX(0, C->data[i]);
    }
}

int forward_pass(matrix *input){
    REAL output;

    /* REAL out1_data[NR_OUT], out2_data[1]; */
    matrix out1, out2;

    create_matrix(W1, NR_FEAT, NR_OUT, RAND);
    create_matrix(b1, 1, NR_OUT, RAND);
    create_matrix(W2, NR_OUT, 1, RAND);
    create_matrix(b2, 1, 1, RAND);
    create_matrix(&out1, 1, NR_OUT, 0);
    create_matrix(&out2, 1, 1, 0);

    matmul(&out1, input, W1);

    matadd(&out1, b1, &out1);

    ReLU(&out1);

    matmul(&out2, W2, &out1);

    matadd(&out2, b2, &out2);

    output = out2.data[0];

    printk("output: %f\n", output);
    destroy_matrix(W1);
    destroy_matrix(b1);
    destroy_matrix(W2);
    destroy_matrix(b2);
    return output > 0.5 ? 1 : 0;
}

/* static int ml_main(void) { */
/*     REAL in[NR_FEAT] = {0}; */
/*     matrix input = {1, NR_FEAT, in}; */
/*     int output; */

/*     output = forward_pass(&input); */
/*     printk("pred: %d", output); */

/*     return 0; */
/* } */

static int __init ml_module_init(void) {
    printk(KERN_INFO "Hello");

    kernel_fpu_begin();

    REAL in[NR_FEAT] = {0};
    matrix input = {1, NR_FEAT, in};
    int output;

    output = forward_pass(&input);
    printk(KERN_INFO "pred: %d", output);

    kernel_fpu_end();

    return 0;
}

static void __exit ml_module_exit(void) {
    printk(KERN_INFO "Done");
}

module_init(ml_module_init);
module_exit(ml_module_exit);

/* #include <linux/module.h>       /\* Needed by all modules *\/ */
/* #include <linux/kernel.h>       /\* Needed for KERN_INFO *\/ */
/* #include <linux/init.h>         /\* Needed for the macros *\/ */

/* MODULE_LICENSE("GPL"); */
/* MODULE_AUTHOR("Rubens Lacouture"); */
/* MODULE_DESCRIPTION("Simple kernel module"); */
/* MODULE_VERSION("0.01"); */

/* static int __init hello_start(void) */
/* { */
/* printk(KERN_INFO "Loading hello module...\n"); */
/* printk(KERN_INFO "Hello world\n"); */
/* return 0; */
/* } */

/* static void __exit hello_end(void) */
/* { */
/* printk(KERN_INFO "Goodbye Mr.\n"); */
/* } */

/* module_init(hello_start); */
/* module_exit(hello_end); */
