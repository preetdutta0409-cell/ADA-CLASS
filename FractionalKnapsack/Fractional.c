#include <stdio.h>

typedef struct {
    int value;
    int weight;
} Item;

void inputItems(Item items[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter value and weight of item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
    }
}

void sortItems(Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            float ratio1 = (float)items[j].value / items[j].weight;
            float ratio2 = (float)items[j + 1].value / items[j + 1].weight;
            if (ratio1 < ratio2) {
                Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

float knapsack(Item items[], int n, int capacity) {
    float profit = 0;
    for (int i = 0; i < n; i++) {

        if (capacity >= items[i].weight) {
            capacity -= items[i].weight;
            profit += items[i].value;
        }
        else {
            float ratio = (float)items[i].value / items[i].weight;
            profit += ratio * capacity;
            break;
        }
    }
    return profit;
}

void display(Item items[], int n) {
    printf("\nSorted Items:\n");
    for (int i = 0; i < n; i++) {
        printf("Value = %d, Weight = %d, Ratio = %.2f\n",
               items[i].value,
               items[i].weight,
               (float)items[i].value / items[i].weight);
    }
}

int main() {
    int n, capacity;
    printf("Enter number of items: ");
    scanf("%d", &n);
    Item items[n];
    inputItems(items, n);
    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);
    sortItems(items, n);
    display(items, n);
    printf("\nMaximum Profit = %.2f\n",knapsack(items, n, capacity));
    return 0;
}