#include<stdio.h>

struct process{
    int id;
    int bt;
    int deadline;
    int share;
    int period;
    int ct, wt, tat;
};


void reset(struct process p[], int n){
    for(int i=0; i<n; i++){
        p[i].tat = p[i].ct = p[i].wt =0;
    }
}


// EDF
void edf(struct process p[], int n){
    // sort by deadline

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (p[j].deadline > p[j+1].deadline){
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }

    }

    int time = 0;
    for(int i=0; i<n; i++){
        p[i].wt = time;;
        time +=p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
    }

    printf("ID Deadline WT BT CT TAT"); //loop chalao
}



// RMS - rate monotonic scheduling

void edf(struct process p[], int n){
    // sort by period

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (p[j].period > p[j+1].period){
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }

    }

    int time = 0;
    for(int i=0; i<n; i++){
        p[i].wt = time;;
        time +=p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
    }

    printf("ID Period WT BT CT TAT"); //loop chalao
}

// Proportional sharing
 void proportional(struct process p[], int n){
    int total_bt = 0, total_share=0;

    for(int i=0; i<n; i++){
        total_bt +=p[i].bt;
        total_share = p[i].share;
    }

    int time =0, rem[20];

    int completed = 0;
    while(completed <n){

        for(int i=0; i<n; i++){
            if(rem[i] >0){
                int timeslice = 0;
                timeslice = (p[i].share >0) ? 1: 0;
                if(rem[i] <timeslice) timeslice = rem[i];
                time +=timeslice;
                rem[i] -=timeslice;

                if (rem[i] ==0){
                    p[i].ct = time;
                    p[i].tat = p[i].ct;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                }
            }
        }
    }
 }