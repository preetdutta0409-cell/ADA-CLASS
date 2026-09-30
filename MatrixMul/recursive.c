#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BASE_SIZE 1
 
// C += A * B for n x n blocks inside larger matrices with row stride ld
void rec_multiply(const double *A, const double *B, double *C, int n, int ld) {
    if (n <= BASE_SIZE) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    C[i * ld + j] += A[i * ld + k] * B[k * ld + j];
        return;
    }
 
    int h = n / 2;
 
    // Top-left corner of each quadrant
    const double *A11 = A,              *A12 = A + h;
    const double *A21 = A + h * ld,     *A22 = A + h * ld + h;
    const double *B11 = B,              *B12 = B + h;
    const double *B21 = B + h * ld,     *B22 = B + h * ld + h;
    double *C11 = C,                    *C12 = C + h;
    double *C21 = C + h * ld,           *C22 = C + h * ld + h;
 
    rec_multiply(A11, B11, C11, h, ld);
    rec_multiply(A12, B21, C11, h, ld);
 
    rec_multiply(A11, B12, C12, h, ld);
    rec_multiply(A12, B22, C12, h, ld);
 
    rec_multiply(A21, B11, C21, h, ld);
    rec_multiply(A22, B21, C21, h, ld);
 
    rec_multiply(A21, B12, C22, h, ld);
    rec_multiply(A22, B22, C22, h, ld);
}
 
int main(void) {
    int sizes[] = {16, 32, 64, 128, 256, 512};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
 
    FILE *fp = fopen("times_recursive.csv", "w");
    if (!fp) {
        perror("Could not open times_recursive.csv");
        return 1;
    }
    fprintf(fp, "size,time_seconds\n");
 
    srand(42);
 
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
 
        double *A = malloc((size_t)n * n * sizeof(double));
        double *B = malloc((size_t)n * n * sizeof(double));
        double *C = calloc((size_t)n * n, sizeof(double));  // zero-initialised
        if (!A || !B || !C) {
            fprintf(stderr, "Memory allocation failed for n=%d\n", n);
            return 1;
        }
 
        for (int i = 0; i < n * n; i++) {
            A[i] = (double)rand() / RAND_MAX;
            B[i] = (double)rand() / RAND_MAX;
        }
 
        clock_t start = clock();
        rec_multiply(A, B, C, n, n);
        clock_t end = clock();
 
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
 
        printf("n = %4d  ->  %.6f s\n", n, elapsed);
        fprintf(fp, "%d,%.6f\n", n, elapsed);
 
        free(A);
        free(B);
        free(C);
    }
 
    fclose(fp);
    printf("Results saved to times_recursive.csv\n");
    return 0;
}