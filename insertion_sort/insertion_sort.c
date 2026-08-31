#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
}

void insertion_sort(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    srand(time(NULL)); 
    for(int i = 1000; i < 50000; i += 5000){
        int *arr = malloc(i * sizeof(int));
        generate_random_array(arr, i);
        clock_t start = clock();
        insertion_sort(arr, i);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d, %f\n", i, time_taken);
        free(arr);
    }
    return 0;
}