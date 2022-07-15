#include "common.h"

void matmul(matrix *C, matrix *A, matrix *B) {
  int M = A->nrows;
  int N = B->ncols;
  int K = A->ncols;
  REAL sum;
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

void matmul_(matrix *c, matrix *a, matrix *b) {
  int M = a->nrows;
  int N = b->ncols;
  int K = a->ncols;
  REAL sum;
  for(int i = 0; i < M; i++) {
    for(int k = 0; k < K; k++) {
      for(int j = 0; j < N; j++) {
        c->data[i * c->ncols + j] += a->data[i * a->ncols + k] * b->data[k * b->ncols + j];
      }
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

    REAL W1_d[NR_FEAT * HIDDEN_SIZE], b1_d[HIDDEN_SIZE], W2_d[HIDDEN_SIZE * NR_OUT],
         b2_d[NR_OUT], W3_d[NR_OUT], b3_d[1], out1_d[HIDDEN_SIZE], out2_d[NR_OUT], out3_d[1];

    matrix W1 = {NR_FEAT, HIDDEN_SIZE, W1_d};
    matrix b1 = {1, HIDDEN_SIZE, b1_d};
    matrix W2 = {HIDDEN_SIZE, NR_OUT, W2_d};
    matrix b2 = {1, NR_OUT, b2_d};
    matrix W3 = {NR_OUT, 1, W3_d};
    matrix b3 = {1, 1, b3_d};
    matrix out1 = {1, HIDDEN_SIZE, out1_d};
    matrix out2 = {1, NR_OUT, out2_d};
    matrix out3 = {1, 1, out3_d};
    
    init_matrix(&W1, RAND);
    init_matrix(&b1, RAND);
    init_matrix(&W2, RAND);
    init_matrix(&b2, RAND);
    init_matrix(&W3, RAND);
    init_matrix(&b3, RAND);
    init_matrix(&out1, 0);
    init_matrix(&out2, 0);
    init_matrix(&out3, 0);

    matmul(&out1, input, &W1);
    matadd(&out1, &b1, &out1);
    ReLU(&out1);

    matmul(&out2, &W2, &out1);
    matadd(&out2, &b2, &out2);
    ReLU(&out2);

    matmul(&out3, &W3, &out2);
    matadd(&out3, &b3, &out3);
    output = out3.data[0];

    return output > 0.5 ? 1 : 0;
}
