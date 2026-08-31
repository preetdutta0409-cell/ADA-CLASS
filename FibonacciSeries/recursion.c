#include <stdio.h>

int Fib(int n){
    if (n <=1) return n;

    return Fib(n-1) + Fib(n-2);
}

int main()
{
    int n = 10;

    for(int i = 0; i<=n; i++) printf("%d ",Fib(i));

    return 0;
}