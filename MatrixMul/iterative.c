#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// C = A * B for n x n matrices stored as flat row-major arrays
void multiply(const double *A, const double *B, double *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}

int main(void) {
    int sizes[] = {50, 100, 200, 300, 400, 500, 600, 800, 1000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *fp = fopen("matrixMultIterative.csv", "w");
    if (!fp) {
        perror("Could not open matrixMultIterative.csv");
        return 1;
    }
    fprintf(fp, "size,time_seconds\n");

    srand(42);

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];

        double *A = malloc((size_t)n * n * sizeof(double));
        double *B = malloc((size_t)n * n * sizeof(double));
        double *C = malloc((size_t)n * n * sizeof(double));
        if (!A || !B || !C) {
            fprintf(stderr, "Memory allocation failed for n=%d\n", n);
            return 1;
        }

        for (int i = 0; i < n * n; i++) {
            A[i] = (double)rand() / RAND_MAX;
            B[i] = (double)rand() / RAND_MAX;
        }

        clock_t start = clock();
        multiply(A, B, C, n);
        clock_t end = clock();

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

        printf("n = %4d  ->  %.6f s\n", n, elapsed);
        fprintf(fp, "%d,%.6f\n", n, elapsed);

        free(A);
        free(B);
        free(C);
    }

    fclose(fp);
    printf("Results saved to times.csv\n");
    return 0;
}