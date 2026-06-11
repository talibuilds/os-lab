#include<stdio.h>

struct process
{
   int at;
   int bt;
   int wt;
   int tat;
   int ct;
};


void sort(struct process p[], int n){

    for(int i=0;i<n-1; i++){
        for(int j=0; j<n-i-1; j++){

            if(p[j].at >= p[j+1].at){
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void fcfs(struct process p[], int n){
    int t= 0;

    for(int i=0; i<n; i++){
        if(t <p[i].at){
            t = p[i].at;
        }

        p[i].wt = t - p[i].at;
        p[i].ct = t + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;

        t +=p[i].bt;
    }

    printf("PID\tAT\tBT\tWT\tCT\tTAT\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].wt, p[i].ct, p[i].tat);
    }

    float awt = 0.0, atat = 0.0;
    for(int i=0; i<n; i++){
        awt += p[i].wt;;
        atat +=p[i].tat;
    }
    awt = awt/n;
    atat = atat/n;

    printf("AWT: %0.2f \nATAT: %0.2f", awt, atat);

}

int main(){

    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];

    printf("\nEnter AT and BT for %d prcocesses\n", n);
    for(int i=0 ;i<n; i++){
        scanf("%d %d", &p[i].at, &p[i].bt);

    }
    sort(p, n);
    fcfs(p, n);

    return 0;
}