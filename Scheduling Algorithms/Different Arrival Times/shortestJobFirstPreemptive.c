#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

typedef struct Process{
    int pid;
    int burst;
    int initialBurst;
    int wait;
    int turn;
    int arrival;
    bool runStatus;
}Process;

int main(){
    printf("Shortest Job First Algorithm - Preemptive\n===============================\n");
    printf("Enter n (No. of processes)\n");
    int n;
    scanf("%d", &n);
    Process p[n];
    int i, j;
    printf("Enter burst time, arrival time for processes\n");
    for(i=0; i<n; ++i){
        printf("Process %d : ",i);
        scanf("%d", &p[i].burst);
        scanf("%d", &p[i].arrival);
        p[i].initialBurst = p[i].burst;
        p[i].pid = i;
        p[i].runStatus = true;
        p[i].wait = 0;
        p[i].turn = 0;  
    }
    float avgWait=0.0;
    float avgTurn=0.0;

    int processLeft = n;
    int currTime=0;
    int minBurst,minPid;
    while(processLeft){
        minBurst = INT_MAX;
        minPid = -1;
        for(i=0;i<n;++i)
            if(p[i].runStatus && p[i].arrival <= currTime && p[i].burst < minBurst){
                minBurst = p[i].burst;
                minPid = p[i].pid;
            }
        
        currTime++;
        if(minPid==-1)
            continue;

        p[minPid].burst--;
        if(p[minPid].burst == 0){
            p[minPid].runStatus = false;
            p[minPid].turn = currTime - p[minPid].arrival;
            p[minPid].wait = p[minPid].turn - p[minPid].initialBurst;
            avgTurn += p[minPid].turn;
            avgWait += p[minPid].wait;
            processLeft--;            
        }        
    }
    
    avgWait /= n;
    avgTurn /= n;
    printf("\n========================================================================================================================");
    printf("\nProcess No.\t\tArrival Time\t\tBurst Time\t\tWait Time\t\tTurnaround Time\n");
    printf("========================================================================================================================\n");
    for(i=0;i<n;++i){
        printf("Process %d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", p[i].pid,p[i].arrival, p[i].initialBurst,p[i].wait,p[i].turn);
    }
    printf("=========================================================================================================================\n");    
    printf("\nAverage Wait Time = %f\n",avgWait);
    printf("Average Turnaround Time = %f\n",avgTurn);
    printf("======================================================================================================================\n");
    

    return 0;
}
