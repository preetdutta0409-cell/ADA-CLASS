#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
}

void selection_sort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

int main(){
    srand(time(NULL)); 
    for(int i = 1000; i < 50000; i += 5000){
        int *arr = malloc(i * sizeof(int));
        generate_random_array(arr, i);
        clock_t start = clock();
        selection_sort(arr, i);
        clock_t end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d, %f\n", i, time_taken);
        free(arr);
    }
    return 0;
}