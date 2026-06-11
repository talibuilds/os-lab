#include<stdio.h>

#define MAX 100
struct process{
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};


void round_robin(struct process p[], int n, int tq){

    int completed = 0, t = 0;
    int queue[MAX], rear =0, front=0, visited[MAX] ={0};
    visited[0] = 1;
    queue[rear++] = 0;

    float awt = 0.0, atat = 0.0;
    while(completed <n){
        int idx = queue[front++];

        if(p[idx].rt >0){
            if(p[idx].rt >tq){
                t += tq;
                p[idx].rt -=tq;
            }
            else{
                t+= p[idx].rt;
                p[idx].rt = 0;

                p[idx].ct = t;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;

            }
        }

        // Us execeution ke time par how many process have arrivied recive them
        for(int i=0; i<n; i++){
            if(!visited[i] && i!=idx && p[i].at <=t){
                queue[rear++] = i;
                visited[i] = 1;

            }
        }
        // Re-enque the current process if it is not done
        if(p[idx].rt >0){
            queue[rear++] = idx;
        }
        
        // If queue becomes empty but still all process not completed

        if(completed <n && front ==rear){
            for(int i=0;i<n; i++){

                if(!visited[i]){
                    queue[rear++] = i;
                    visited[i] =1;
                    t = (p[i].at >t) ? p[i].at : t;
                    break;
                }
            }
        }
    }
    printf("PID\tAT\tBT\tWT\tCT\tTAT\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].wt, p[i].ct, p[i].tat);
        atat = p[i].tat;
        awt = p[i].wt;

    }


    printf("AWT: %0.2f \nATAT: %0.2f", awt/n, atat/n);

}

int main(){

    int n;
    struct process p[MAX];
    printf("Enter Number of prcoess: ");
    scanf("%d", &n);
    printf("Enter AT BT\n");
    for(int i=0; i<n; i++){
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }
    printf("Enter Quantum time: ");
    int tq;
    scanf("%d", &tq);
    round_robin(p, n, tq);
    return 0;
}