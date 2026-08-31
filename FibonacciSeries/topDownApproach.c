#include <stdio.h>

#define MAX 100

int dp[MAX];

int fib(int n) {
    if (n <= 1)
        return n;

    if (dp[n] != -1)
        return dp[n];

    dp[n] = fib(n - 1) + fib(n - 2);

    return dp[n];
}

int main() {
    int n;

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < MAX; i++)
        dp[i] = -1;

    printf("Fibonacci Series:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", fib(i));
    }

    printf("\n");

    return 0;
}