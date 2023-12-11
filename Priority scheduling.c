#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;       
    int bt;        
    int priority;  
};

int comparison(const void *a, const void *b) {
    return (((struct Process *)b)->priority - ((struct Process *)a)->priority);
}

void findWaitingTime(struct Process proc[], int n, int wt[]) {
    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = proc[i - 1].bt + wt[i - 1];
}


void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

void findavgTime(struct Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);

    printf("\nProcesses   Burst time   Waiting time   Turn around time\n");

    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" %d\t\t\t%d\t\t\t%d\t\t\t\t%d\t\t\n", proc[i].pid, proc[i].bt, wt[i], tat[i]);
    }

    printf("\nAverage waiting time = %f", (float)total_wt / (float)n);
    printf("\nAverage turn around time = %f", (float)total_tat / (float)n);
}

void priorityScheduling(struct Process proc[], int n) {
    qsort(proc, n, sizeof(struct Process), comparison);

    printf("Order in which processes get executed \n");
    for (int i = 0; i < n; i++)
        printf("%d ", proc[i].pid);

    findavgTime(proc, n);
}

int main() {
    struct Process proc[] = {{1, 10, 2}, {2, 5, 0}, {3, 8, 1}};
    int n = sizeof(proc) / sizeof(proc[0]);
    priorityScheduling(proc, n);
    return 0;
}
