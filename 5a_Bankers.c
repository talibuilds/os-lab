#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESS 10
#define MAX_RES 10

int main()
{
    int allocation[MAX_PROCESS][MAX_RES];
    int need[MAX_PROCESS][MAX_RES];
    int max[MAX_PROCESS][MAX_RES];
    int safeseq[MAX_PROCESS];
    int work[MAX_RES];
    int available[MAX_RES];
    bool finish[MAX_PROCESS] = {false};

    int n, m;
    printf("Enter num of Process and Resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter the allocation matrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Enter the Max Demand matrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter available resources\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    int count = 0;

    while (count < n)
    {

        bool found = false;
        for (int i = 0; i < n; i++)
        {

            if (!finish[i])
            {
                bool canFinish = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canFinish = false;
                        break;
                        ;
                    }
                }

                if (canFinish)
                {
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    found = true;
                    safeseq[count++] = i;
                    finish[i] = true;
                }
            }
        }
        if (!found)
        {
            break;
        }
    }

    bool safe = true;
    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            safe = false;
        }
    }

    if (safe)
    {
        printf("No deadlock occur, Safe seq are:\n");

        for (int i = 0; i < n; i++)
        {
            printf("P%d", safeseq[i]);
            if (i != n - 1)
                printf("->");
        }
    }

    else
    {
        printf("Not safe");
    }
}

