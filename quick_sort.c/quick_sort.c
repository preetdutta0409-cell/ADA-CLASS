#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j < high; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        QuickSort(arr, low, i);
        QuickSort(arr, i + 2, high);
    }
}
int generate_random_numbers(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;
}
int main()
{
    srand(time(NULL));
    printf("N  Time(seconds)\n");

    int choice[] = {10, 50, 100, 300, 500, 700, 1000, 3000, 5000, 7000, 10000, 30000, 50000, 70000, 100000, 300000, 500000, 700000, 1000000};
    int numc = sizeof(choice) / sizeof(choice[0]);

    for (int i = 0; i < numc; i++)
    {
        int n = choice[i];
        int *arr = (int *)malloc(n * sizeof(int));
        generate_random_numbers(arr, n);

        clock_t start_time = clock();
        QuickSort(arr, 0, n - 1);
        clock_t end_time = clock();

        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("%d %f\n", n, time_taken);
        FILE *fp = fopen("quicksortN.csv", "a");
        if (fp != NULL)
        {
            fprintf(fp, "%d,%f\n", n, time_taken);
            fclose(fp);
        }
        free(arr);
    }

    return 0;
}