


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RUNS 100000

void generateRandomNumbers(int arr[], int n){
    for(int i = 0; i < n; i++)
    {
        arr[i] = rand() %100000;
    }
}

int linearSearch(int arr[], int n, int key){
    for(int i =0; i < n; i++)
    {
        if(arr[i] == key){
            return i;
        }
    }
    return -1;
}

int main(){
    srand(time(NULL));

    for(int n=10000;n<=500000;n+=10000)
    {
        int *arr = malloc(n*sizeof(int));
        if(arr == NULL)
        {
            printf("Memory not allocated\n");
            return -1;
        }

        generateRandomNumbers(arr,n);

        volatile int result;

        clock_t start = clock();

        for(int i=0;i<RUNS;i++)
        {
            result = linearSearch(arr,n,100001); // always absent
        }

        clock_t end = clock();

        double avg = (double)(end-start)/CLOCKS_PER_SEC/RUNS;

        printf("%d,%lf\n",n,avg);

    free(arr);
}
return 0;
}