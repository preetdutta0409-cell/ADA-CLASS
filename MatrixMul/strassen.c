#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
 
// Both recursive methods stop at blocks of this size and multiply them
// with the plain triple loop. (Recursing down to 1x1 makes Strassen slow
// because of the extra additions and memory allocation.)
#define BASE_SIZE 64
 
// ---------- 1. Iterative: C = A * B (contiguous n x n) ----------
void iter_multiply(const double *A, const double *B, double *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++)
                sum += A[i * n + k] * B[k * n + j];
            C[i * n + j] = sum;
        }
    }
}
 
// ---------- 2. Recursive, 8 multiplications: C += A * B ----------
// Works on blocks inside larger matrices with row stride ld.
void rec_multiply(const double *A, const double *B, double *C, int n, int ld) {
    if (n <= BASE_SIZE) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    C[i * ld + j] += A[i * ld + k] * B[k * ld + j];
        return;
    }
 
    int h = n / 2;
    const double *A11 = A,          *A12 = A + h;
    const double *A21 = A + h * ld, *A22 = A + h * ld + h;
    const double *B11 = B,          *B12 = B + h;
    const double *B21 = B + h * ld, *B22 = B + h * ld + h;
    double *C11 = C,                *C12 = C + h;
    double *C21 = C + h * ld,       *C22 = C + h * ld + h;
 
    rec_multiply(A11, B11, C11, h, ld);
    rec_multiply(A12, B21, C11, h, ld);
    rec_multiply(A11, B12, C12, h, ld);
    rec_multiply(A12, B22, C12, h, ld);
    rec_multiply(A21, B11, C21, h, ld);
    rec_multiply(A22, B21, C21, h, ld);
    rec_multiply(A21, B12, C22, h, ld);
    rec_multiply(A22, B22, C22, h, ld);
}
 
// ---------- 3. Strassen: C = A * B (contiguous n x n) ----------
static void add(const double *X, const double *Y, double *Z, int m) {
    for (int i = 0; i < m * m; i++) Z[i] = X[i] + Y[i];
}
 
static void sub(const double *X, const double *Y, double *Z, int m) {
    for (int i = 0; i < m * m; i++) Z[i] = X[i] - Y[i];
}
 
void strassen(const double *A, const double *B, double *C, int n) {
    if (n <= BASE_SIZE) {
        iter_multiply(A, B, C, n);
        return;
    }
 
    int h = n / 2;
    size_t sz = (size_t)h * h;
 
    // One allocation: 8 quadrants + 7 products (M1..M7) + 2 temporaries
    double *mem = malloc(17 * sz * sizeof(double));
    if (!mem) {
        fprintf(stderr, "Memory allocation failed in strassen (n=%d)\n", n);
        exit(1);
    }
    double *A11 = mem,      *A12 = A11 + sz, *A21 = A12 + sz, *A22 = A21 + sz;
    double *B11 = A22 + sz, *B12 = B11 + sz, *B21 = B12 + sz, *B22 = B21 + sz;
    double *M1 = B22 + sz,  *M2 = M1 + sz,   *M3 = M2 + sz,   *M4 = M3 + sz;
    double *M5 = M4 + sz,   *M6 = M5 + sz,   *M7 = M6 + sz;
    double *T1 = M7 + sz,   *T2 = T1 + sz;
 
    // Split A and B into quadrants
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < h; j++) {
            A11[i * h + j] = A[i * n + j];
            A12[i * h + j] = A[i * n + j + h];
            A21[i * h + j] = A[(i + h) * n + j];
            A22[i * h + j] = A[(i + h) * n + j + h];
            B11[i * h + j] = B[i * n + j];
            B12[i * h + j] = B[i * n + j + h];
            B21[i * h + j] = B[(i + h) * n + j];
            B22[i * h + j] = B[(i + h) * n + j + h];
        }
    }
 
    // The 7 recursive products
    add(A11, A22, T1, h); add(B11, B22, T2, h); strassen(T1, T2, M1, h);
    add(A21, A22, T1, h);                       strassen(T1, B11, M2, h);
                          sub(B12, B22, T2, h); strassen(A11, T2, M3, h);
                          sub(B21, B11, T2, h); strassen(A22, T2, M4, h);
    add(A11, A12, T1, h);                       strassen(T1, B22, M5, h);
    sub(A21, A11, T1, h); add(B11, B12, T2, h); strassen(T1, T2, M6, h);
    sub(A12, A22, T1, h); add(B21, B22, T2, h); strassen(T1, T2, M7, h);
 
    // Combine into C
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < h; j++) {
            int p = i * h + j;
            C[i * n + j]             = M1[p] + M4[p] - M5[p] + M7[p];
            C[i * n + j + h]         = M3[p] + M5[p];
            C[(i + h) * n + j]       = M2[p] + M4[p];
            C[(i + h) * n + j + h]   = M1[p] - M2[p] + M3[p] + M6[p];
        }
    }
 
    free(mem);
}
 
// Largest absolute difference between two n x n matrices
double max_diff(const double *X, const double *Y, int n) {
    double d = 0.0;
    for (int i = 0; i < n * n; i++) {
        double e = fabs(X[i] - Y[i]);
        if (e > d) d = e;
    }
    return d;
}
 
int main(void) {
    int sizes[] = {64, 128, 256, 512, 1024};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
 
    FILE *fp = fopen("times_strassen.csv", "w");
    if (!fp) {
        perror("Could not open times_strassen.csv");
        return 1;
    }
    fprintf(fp, "size,iterative,recursive,strassen\n");
 
    srand(42);
 
    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        size_t bytes = (size_t)n * n * sizeof(double);
 
        double *A  = malloc(bytes);
        double *B  = malloc(bytes);
        double *C1 = malloc(bytes);
        double *C2 = calloc((size_t)n * n, sizeof(double));  // rec_multiply accumulates
        double *C3 = malloc(bytes);
        if (!A || !B || !C1 || !C2 || !C3) {
            fprintf(stderr, "Memory allocation failed for n=%d\n", n);
            return 1;
        }
 
        for (int i = 0; i < n * n; i++) {
            A[i] = (double)rand() / RAND_MAX;
            B[i] = (double)rand() / RAND_MAX;
        }
 
        clock_t t0 = clock();
        iter_multiply(A, B, C1, n);
        clock_t t1 = clock();
        rec_multiply(A, B, C2, n, n);
        clock_t t2 = clock();
        strassen(A, B, C3, n);
        clock_t t3 = clock();
 
        double t_iter = (double)(t1 - t0) / CLOCKS_PER_SEC;
        double t_rec  = (double)(t2 - t1) / CLOCKS_PER_SEC;
        double t_str  = (double)(t3 - t2) / CLOCKS_PER_SEC;
 
        printf("n = %4d | iterative %.6f s | recursive %.6f s | strassen %.6f s"
               " | max diff vs iterative: rec %.1e, strassen %.1e\n",
               n, t_iter, t_rec, t_str, max_diff(C1, C2, n), max_diff(C1, C3, n));
        fprintf(fp, "%d,%.6f,%.6f,%.6f\n", n, t_iter, t_rec, t_str);
 
        free(A); free(B); free(C1); free(C2); free(C3);
    }
 
    fclose(fp);
    printf("Results saved to times_strassen.csv\n");
    return 0;
}