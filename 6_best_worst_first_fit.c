#include<stdio.h>
#include<string.h>


#define N 100


void resetBlocks(int org[], int copy[], int n){
    for(int i=0; i<n; i++){
        copy[i] = org[i];
    }
}


void firstfit(int blocksize[], int m, int processsize[], int n){
    int allocation[N];
    memset(allocation, -1, sizeof(allocation));

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(blocksize[j] >= processsize[i]){
            allocation[i] = j;
            blocksize[j] -=processsize[i];
            break;
        }}
    
        }

    printf("\nProcess No\tProcess Size\tBlock No\n");
    for(int i=0; i<n; i++){
        printf("%d\t\t%d\t\t", i+1, processsize[i]);
        if(allocation[i] !=-1){
            printf("%d\n", allocation[i] +1 );
        }
        else{
            printf("Not Allocated\n");
        }
    }
    
}

void bestfit(int blocksize[], int m, int processsize[], int n){
    int allocation[N];
    memset(allocation, -1, sizeof(allocation));

    for(int i=0; i<n; i++){
        int bestindex = -1;
        for(int j=0; j<m; j++){
            if(blocksize[j] >= processsize[i]){
            if(bestindex ==-1 || blocksize[j] < blocksize[bestindex]){
                bestindex = j;
            }
            }
        }
        if (bestindex !=-1){
               allocation[i] = bestindex;
               blocksize[bestindex] -=processsize[i];
       }   
        }

    printf("\nProcess No\tProcess Size\tBlock No\n");
    for(int i=0; i<n; i++){
        printf("%d\t\t%d\t\t", i+1, processsize[i]);
        if(allocation[i] !=-1){
            printf("%d\n", allocation[i] +1 );
        }
        else{
            printf("Not Allocated\n");
        }
    }
    
}

void worstfit(int blocksize[], int m, int processsize[], int n){
    int allocation[N];
    memset(allocation, -1, sizeof(allocation));

    for(int i=0; i<n; i++){
        int worstindex = -1;
        for(int j=0; j<m; j++){
            if(blocksize[j] >= processsize[i]){
            if(worstindex ==-1 || blocksize[j] > blocksize[worstindex]){
                worstindex = j;

            }}
        }
        if (worstindex !=-1){
            allocation[i] = worstindex;
            blocksize[worstindex] -=processsize[i];
    }
        }

    printf("\nProcess No\tProcess Size\tBlock No\n");
    for(int i=0; i<n; i++){
        printf("%d\t\t%d\t\t", i+1, processsize[i]);
        if(allocation[i] !=-1){
            printf("%d\n", allocation[i] +1 );
        }
        else{
            printf("Not Allocated\n");
        }
    }
    
}

int main() 
   {  
    int m, n;  
    int originalBlockSize[N], blockSize[N], processSize[N];  
  
    printf("Enter number of memory blocks: ");  
    scanf("%d", &m);  
    printf("Enter sizes of %d memory blocks:\n", m);  
    for (int i = 0; i < m; i++)  
        scanf("%d", &originalBlockSize[i]);  
  
    printf("Enter number of processes: ");  
    scanf("%d", &n);  
    printf("Enter sizes of %d processes:\n", n);  
    for (int i = 0; i < n; i++)  
        scanf("%d", &processSize[i]);

        // First Fit  
    resetBlocks(originalBlockSize, blockSize, m);  
    firstfit(blockSize, m, processSize, n);  
  
    // Best Fit  
    resetBlocks(originalBlockSize, blockSize, m);  
    bestfit(blockSize, m, processSize, n);  
    
    // Worst Fit  
    resetBlocks(originalBlockSize, blockSize, m);  
    worstfit(blockSize, m, processSize, n);  
    return 0;  

   }