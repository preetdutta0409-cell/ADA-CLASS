#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
void generate_random_numbers(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;
}
int main()
{
    srand(time(NULL));
    printf("N  Time(seconds)\n");

    for (int i = 100000; i <= 1000000; i += 100000)
    {
        int n = i;
        int *arr = (int *)malloc(n * sizeof(int));
        generate_random_numbers(arr, n);
        clock_t start_time = clock();
        mergeSort(arr, 0, n - 1);
        clock_t end_time = clock();

        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("%d %f\n", n, time_taken);
        FILE *fp = fopen("merge_sort.csv", "a");
        if (fp != NULL)
        {
            fprintf(fp, "%d,%f\n", n, time_taken);
            fclose(fp);
        }

        free(arr);
    }
    return 0;
}