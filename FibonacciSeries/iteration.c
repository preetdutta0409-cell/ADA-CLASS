#include <stdio.h>

void printFib(int n){
    if (n<1)
    {
        printf("Invalid input");
        return;
    }
    int prev2 = 0;
    int prev1 = 1;

    printf("%d ", prev2);
    if (n==1){
        return;
    }
    printf("%d ", prev1);

    for (int i=3; i<=n; i++){
        int curr = prev1 + prev2;
        printf("%d ", curr);
        prev2 = prev1;
        prev1 = curr;

    }

}

int main()
{
    int n = 15;

    printFib(n);

    return 0;
}