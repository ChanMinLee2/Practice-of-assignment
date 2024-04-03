#include <stdio.h>

void matrix_multiply(int size, double *a, double *b, double *result) {
    int i, j, k;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            result[i*size + j] = 0.0;
            for (k = 0; k < size; k++) {
                result[i*size + j] += a[i*size + k] * b[k*size + j];
            }
        }
    }
}