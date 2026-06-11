#include <stdio.h>

#define MAX 100

struct Process
{
    int id;
    int bt;
    int deadline; // EDF
    int period;   // RMS
    int share;    // Proportional Share
    int ct, wt, tat;
};

void resetProcesses(struct Process p[], int n)
{
    for (int i = 0; i < n; i++)
        p[i].ct = p[i].wt = p[i].tat = 0;
}

// ---------- EDF ----------
void EDF(struct Process p[], int n)
{
    printf("\n===== Earliest Deadline First (EDF) =====\n");

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].deadline > p[j + 1].deadline)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

    int time = 0;

    for (int i = 0; i < n; i++)
    {
        p[i].wt = time;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
    }

    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
}

// ---------- RMS ----------
void RMS(struct Process p[], int n)
{
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].period > p[j + 1].period)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

    int time = 0;

    for (int i = 0; i < n; i++)
    {
        p[i].wt = time;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
    }

    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
}

// ---------- Proportional Share ----------
void ProportionalShare(struct Process p[], int n)
{
    printf("\n===== Proportional Share Scheduling =====\n");

    int remaining[MAX];

    for (int i = 0; i < n; i++)
        remaining[i] = p[i].bt;

    int time = 0, done = 0;

    while (done < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0)
            {
                int timeSlice = 1;

                if (remaining[i] < timeSlice)
                    timeSlice = remaining[i];

                time += timeSlice;
                remaining[i] -= timeSlice;

                if (remaining[i] == 0)
                {
                    p[i].ct = time;
                    p[i].tat = p[i].ct;
                    p[i].wt = p[i].tat - p[i].bt;
                    done++;
                }
            }
        }
    }

    printf("ID\tBT\tShare\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].bt, p[i].share,
               p[i].ct, p[i].wt, p[i].tat);
}

// ---------- Main ----------
int main()
{
    int n;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Deadline (EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (RMS): ");
        scanf("%d", &p[i].period);

        printf("Share (Proportional): ");
        scanf("%d", &p[i].share);
    }

    resetProcesses(p, n);
    EDF(p, n);

    resetProcesses(p, n);
    RMS(p, n);

    resetProcesses(p, n);
    ProportionalShare(p, n);

    return 0;
}
