#include<stdio.h>

#define MAX 10

struct process{
    int at;
    int bt;
    int wt;
    int ct;
    int tat;
    int done; // for non preemtive only
    int rt; // remaining time - for preemtive use only.
};

// Non preemptive SJF

void sjf_np(struct process p[], int n){

    int t = 0;
    int completed = 0;
    float awt = 0.0, atat = 0.0;
    
    while(completed <n){

        int min_bt = 99999;
        int idx = -1;

        // choose min bt
        for(int i=0; i<n; i++){
            if(p[i].at <=t && p[i].done==0){

                if(p[i].bt < min_bt){
                    min_bt = p[i].bt;
                    idx = i;
                }

                // If same bt
                else if(p[i].bt== min_bt){
                    if(p[i].at < p[idx].at){
                        idx = i;
                    }
                }

            }
        }

        if(idx !=-1){


            p[idx].wt = t - p[idx].at;   
            p[idx].ct = t + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;

            awt +=p[idx].wt;
            atat +=p[idx].tat;
            p[idx].done = 1;
            t = p[idx].ct;
            completed++;
        
        
        }else{
            t++;
        }
    }

    printf("PID\tAT\tBT\tWT\tCT\tTAT\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].wt, p[i].ct, p[i].tat);
    }

    awt = awt/n;
    atat = atat/n;

    printf("AWT: %0.2f \nATAT: %0.2f", awt, atat);

}








// PREEMPTIVE SJF (SRTF)

void srtf(struct process p[], int n){
    int completed = 0;
    int t= 0;
    float awt = 0.0, atat = 0.0;

    while(completed <n){
        int min_rt = 9999;
        int idx = -1;

        // select the min remaining time wala process
        for(int i=0; i<n; i++){
            if(p[i].at <=t && p[i].rt >0){
                if(p[i].rt <min_rt){
                    min_rt = p[i].rt;
                    idx = i;
                }

                else if(p[i].rt ==min_rt){
                    if(p[i].at <p[idx].at){
                        idx = i;
                    }
                }
            }
        }
        // If no process available
        if(idx ==-1){
            t++;
            continue;
        }
        p[idx].rt--;
        t++;

        if(p[idx].rt==0){
            
            p[idx].ct = t ;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt =p[idx].tat -p[idx].bt;

            awt +=p[idx].wt;
            atat +=p[idx].tat;
            completed++;
        }
    }

    printf("PID\tAT\tBT\tWT\tCT\tTAT\tRT\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].wt, p[i].ct, p[i].tat, p[i].rt);
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

    printf("\nEnter AT and BT\n");
    for(int i=0 ;i<n; i++ ){
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].done = 0;    // only for non preemptive
        p[i].rt = p[i].bt;  //Only for preepmtive

    }

    // sjf_np(p, n);
    srtf(p, n);
    return 0;
}