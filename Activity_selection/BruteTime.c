#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 30

struct Activity
{
    int start;
    int finish;
};

struct Activity activities[MAX];

int n;
int maxCount;
int bestSet[MAX];

int isCompatible(int selected[], int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            int a = selected[i];
            int b = selected[j];

            if (!(activities[a].finish <= activities[b].start ||
                  activities[b].finish <= activities[a].start))
            {
                return 0;
            }
        }
    }

    return 1;
}

void bruteForce(int index, int selected[], int count)
{
    if (index == n)
    {
        if (isCompatible(selected, count) && count > maxCount)
        {
            maxCount = count;

            for (int i = 0; i < count; i++)
                bestSet[i] = selected[i];
        }

        return;
    }

    bruteForce(index + 1, selected, count);

    selected[count] = index;
    bruteForce(index + 1, selected, count + 1);
}

void generateActivities(int size)
{
    for (int i = 0; i < size; i++)
    {
        activities[i].start = rand() % 100;
        activities[i].finish =
            activities[i].start + 1 + rand() % 20;
    }
}

int main()
{
    int selected[MAX];

    int testSizes[] = {5, 10, 15, 20, 25, 30};
    int tests = 6;

    printf("Activity Selection - Brute Force\n\n");
    printf("Activities\tTime (seconds)\n");

    srand(time(NULL));

    for (int t = 0; t < tests; t++)
    {
        n = testSizes[t];

        generateActivities(n);

        maxCount = 0;

        clock_t start = clock();

        bruteForce(0, selected, 0);

        clock_t end = clock();

        double time_taken =
            (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t\t%.8f\n", n, time_taken);
    }

    return 0;
}