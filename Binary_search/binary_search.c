#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RUNS 5000000

void generateRandomNumbers(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 100000;
}

void selectionSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int min = i;

        for(int j = i + 1; j < n; j++)
        {
            if(arr[j] < arr[min])
                min = j;
        }

        if(min != i)
        {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

int BinarySearch(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;

    while(low <= high)
    {
        int mid = low + (high - low) / 2;

        if(arr[mid] == key)
            return mid;

        if(arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main()
{
    srand((unsigned)time(NULL));

    printf("N,Average_Time(ns)\n");

    for(int n = 1000; n <= 30000; n += 1000)
    {
        int *arr = (int *)malloc(n * sizeof(int));

        if(arr == NULL)
        {
            printf("Memory allocation failed\n");
            return 1;
        }

        generateRandomNumbers(arr, n);

        selectionSort(arr, n);

        volatile int result = 0;

        clock_t start = clock();

        for(int i = 0; i < RUNS; i++)
        {
            result = BinarySearch(arr, n, 100001);
        }

        clock_t end = clock();

        double total =
            (double)(end - start) / CLOCKS_PER_SEC / RUNS;

        printf("%d,%lf\n", n, total * 1e9);

        free(arr);
    }

    return 0;
}