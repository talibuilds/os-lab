#include<stdio.h>

#define MAX 10
struct process {
    int at;
    int bt;
    int pr;
    int ct;
    int tat;
    int wt;
    int done;  //only for non preemitve
    int rt;  // only for preemptive
};


void priority(struct process p[], int n){

    int t = 0, completed = 0;
    float awt=0.0, atat =0.0;

    while(completed <n){

        int max_priority = 9999;
        int idx = -1;

        for(int i=0; i<n; i++){
            if(p[i].at <= t && p[i].done==0){
                if(p[i].pr < max_priority){
                    max_priority = p[i].pr;
                    idx = i;
                }

                else if(max_priority == p[i].pr){
                    if(p[i].at <p[idx].at){
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1){
            p[idx].wt = t - p[idx].at;
            p[idx].ct = t + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;

            awt +=p[idx].wt;
            atat +=p[idx].tat;

            t = p[idx].ct;
            p[idx].done = 1;
            completed++;

        }
        else{
            t++;
        }
    }

    printf("PID\tAT\tPR\tBT\tWT\tCT\tTAT\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].pr, p[i].bt, p[i].wt, p[i].ct, p[i].tat);
    }

    awt = awt/n;
    atat = atat/n;

    printf("AWT: %0.2f \nATAT: %0.2f", awt, atat);
}






// Prerpmtive priority

void preepmtive_priortity(struct process p[], int n){
    int t=0, completed = 0;
    float awt = 0.0, atat = 0.0;

    while(completed <n){
        int max_priority = 9999;
        int idx = -1;

        for(int i=0; i<n; i++){
            if(p[i].at <=t && p[i].rt >0){
                if(p[i].pr < max_priority){
                    max_priority = p[i].pr;
                    idx = i;
                }

                else if(p[i].pr == max_priority){
                    if(p[i].at <p[idx].at){
                        idx = i;
                    }
                }
            }
        }

        if (idx ==-1){
            t++;
            continue;;
        }
        p[idx].rt --;
        t++;

        if(p[idx].rt ==0){

            p[idx].ct = t;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;


            awt +=p[idx].wt;
            atat +=p[idx].tat;

            completed++;
        }

    }
    printf("PID\tAT\tPR\tBT\tWT\tCT\tTAT\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].pr, p[i].bt, p[i].wt, p[i].ct, p[i].tat);
    }

    awt = awt/n;
    atat = atat/n;

    printf("AWT: %0.2f \nATAT: %0.2f", awt, atat);


}







int main(){
    int n;
    struct process p[MAX];

    printf("Enter the number of process: ");
    scanf("%d", &n);

    printf("\nEnter AT  BT PRIORITY\n");
    for(int i=0 ;i<n; i++ ){
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        // p[i].done = 0;    // only for non preemitve
        p[i].rt = p[i].bt;  // only for preemtive

    }

    // priority(p, n);

    preepmtive_priortity(p, n);


    return 0;
}