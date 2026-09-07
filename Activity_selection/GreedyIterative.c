#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

struct Activity
{
    int start;
    int finish;
};

struct Activity activities[MAX];

int compare(const void *a, const void *b)
{
    struct Activity *x = (struct Activity *)a;
    struct Activity *y = (struct Activity *)b;

    return x->finish - y->finish;
}

int activitySelection(int n)
{
    int count = 1;
    int lastFinish = activities[0].finish;

    for (int i = 1; i < n; i++)
    {
        if (activities[i].start >= lastFinish)
        {
            count++;
            lastFinish = activities[i].finish;
        }
    }

    return count;
}

void generateActivities(int n)
{
    for (int i = 0; i < n; i++)
    {
        activities[i].start = rand() % 100000;
        activities[i].finish =
            activities[i].start + 1 + rand() % 100;
    }
}

int main()
{
    int testSizes[] = {100, 1000, 5000, 10000, 50000, 100000};
    int tests = 6;

    srand(time(NULL));

    printf("Greedy Iterative Activity Selection\n\n");
    printf("Activities\tTime (seconds)\n");

    for (int t = 0; t < tests; t++)
    {
        int n = testSizes[t];

        generateActivities(n);

        clock_t start = clock();

        qsort(activities, n, sizeof(struct Activity), compare);

        int result = activitySelection(n);

        clock_t end = clock();

        double time_taken =
            (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t\t%.8f\n", n, time_taken);
    }

    return 0;
}