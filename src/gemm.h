#ifndef GEMM_H
#define GEMM_H
#include "activations.h"
#include <stdint.h>
#include <stddef.h>

static inline void set_bit(unsigned char *const dst, size_t index) {
    size_t dst_i = index / 8;
    int dst_shift = index % 8;
    dst[dst_i] |= 1 << dst_shift;
}

static inline unsigned char get_bit(unsigned char const*const src, size_t index) {
    size_t src_i = index / 8;
    int src_shift = index % 8;
    unsigned char val = (src[src_i] & (1 << src_shift)) > 0;
    return val;
}

void float_to_bit(float *src, unsigned char *dst, size_t size);

void transpose_block_SSE4x4(float *A, float *B, const int n, const int m,
    const int lda, const int ldb, const int block_size);

void gemm_nn_custom_bin_mean_transposed(int M, int N, int K, float ALPHA_UNUSED,
    unsigned char *A, int lda,
    unsigned char *B, int ldb,
    float *C, int ldc, float *mean_arr);

void im2col_cpu_custom(float* data_im,
    int channels, int height, int width,
    int ksize, int stride, int pad, float* data_col);

void activate_array_cpu_custom(float *x, const int n, const ACTIVATION a);


void gemm_bin(int M, int N, int K, float ALPHA,
        char  *A, int lda,
        float *B, int ldb,
        float *C, int ldc);

void gemm(int TA, int TB, int M, int N, int K, float ALPHA,
                    float *A, int lda,
                    float *B, int ldb,
                    float BETA,
                    float *C, int ldc);

void gemm_cpu(int TA, int TB, int M, int N, int K, float ALPHA,
        float *A, int lda,
        float *B, int ldb,
        float BETA,
        float *C, int ldc);

#ifdef GPU
void gemm_ongpu(int TA, int TB, int M, int N, int K, float ALPHA,
        float *A_gpu, int lda,
        float *B_gpu, int ldb,
        float BETA,
        float *C_gpu, int ldc);

void gemm_gpu(int TA, int TB, int M, int N, int K, float ALPHA,
        float *A, int lda,
        float *B, int ldb,
        float BETA,
        float *C, int ldc);
#endif
#endif
