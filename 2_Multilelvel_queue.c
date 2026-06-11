#include <stdio.h>
#define MAX 10


struct process{
    int id, at, bt, wt, tat, ct, type;
};

void sort(struct process p[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if (p[j].at > p[j+1].at){
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}


void fcfs(struct process p[], int n, int *time){
    for(int i=0; i<n; i++){
        if(*time <p[i].at){
            *time = p[i].at;
        }

        p[i].wt = *time- p[i].at;
        p[i].ct = *time+ p[i].bt;
        p[i].tat = p[i].ct - p[i].at;

        *time = p[i].ct ;
    }

}


int main() {
    int n, sysCount=0, userCount=0, time=0;
    struct process sysQueue[MAX], userQueue[MAX];
    float awt =0.0, atat = 0.0;

    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter AT BT Type(0=System, 1=User)\n");
    for(int i=0; i<n; i++){
        struct process p;
        p.id = i;
        scanf("%d %d %d", &p.at, &p.bt, &p.type);
        if(p.type==0){
            sysQueue[sysCount++] = p;
        }else{
            userQueue[userCount++] = p;
        }
    }

    sort(sysQueue, sysCount);
    sort(userQueue, userCount);

    fcfs(sysQueue, sysCount, &time);
    fcfs(userQueue, userCount, &time);

    printf("\nID\tType\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<sysCount; i++){

        printf("%d\tS\t%d\t%d\t%d\t%d\t%d\n", sysQueue[i].id, sysQueue[i].at, sysQueue[i].bt, sysQueue[i].ct, sysQueue[i].tat, sysQueue[i].wt);
        atat +=sysQueue[i].tat;
        awt +=sysQueue[i].wt;
    }
    for(int i=0; i<userCount; i++){
        printf("%d\tU\t%d\t%d\t%d\t%d\t%d\n", userQueue[i].id, userQueue[i].at, userQueue[i].bt, userQueue[i].ct, userQueue[i].tat, userQueue[i].wt);
        atat +=userQueue[i].tat;
        awt +=userQueue[i].wt;
    }

    printf("AWT: %.2f\nATAT: %.2f", awt/n, atat/n);

    return 0;
}