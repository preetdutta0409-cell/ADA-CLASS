#include <stdio.h>

#define MAX 20

struct Activity
{
    int start;
    int finish;
};

struct Activity activities[MAX];

int n;
int maxCount = 0;
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
            {
                bestSet[i] = selected[i];
            }
        }

        return;
    }

    bruteForce(index + 1, selected, count);

    selected[count] = index;
    bruteForce(index + 1, selected, count + 1);
}

int main()
{
    int selected[MAX];

    printf("Enter number of activities: ");
    scanf("%d", &n);

    printf("\nEnter start and finish time:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Activity %d: ", i + 1);
        scanf("%d %d", &activities[i].start,
                       &activities[i].finish);
    }

    bruteForce(0, selected, 0);

    printf("\nMaximum number of activities = %d\n", maxCount);

    printf("Selected activities:\n");

    for (int i = 0; i < maxCount; i++)
    {
        int index = bestSet[i];

        printf("Activity %d: (%d, %d)\n",
               index + 1,
               activities[index].start,
               activities[index].finish);
    }

    return 0;
}