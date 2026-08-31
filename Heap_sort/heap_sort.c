#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void generate_random_numbers(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}
void heap_sort(int arr[], int n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    srand(time(NULL));
    printf("N  Time(seconds)\n");

    int choice[] = {10, 50, 100, 300, 500, 700, 1000, 3000, 5000, 7000, 10000, 30000, 50000, 70000, 100000};
    int numc = sizeof(choice) / sizeof(choice[0]);

    for (int i = 0; i < numc; i++)
    {
        int n = choice[i];
        int *arr = (int *)malloc(n * sizeof(int));
        generate_random_numbers(arr, n);

        clock_t start_time = clock();
        heap_sort(arr, n);
        clock_t end_time = clock();

        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("%d %f\n", n, time_taken);
        FILE *fp = fopen("heapsortN.csv", "a");
        if (fp != NULL)
        {
            fprintf(fp, "%d,%f\n", n, time_taken);
            fclose(fp);
        }

        free(arr);
    }
}