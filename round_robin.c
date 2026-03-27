#include <stdio.h>

struct process{
    int pid, at, bt, ct, tat, wt, ret;
};

int main(){
    struct process p[20];
    int queue[100];
    int front = 0, rear = 0;
    int time = 0, completed = 0;
    int visited[20] = {0};
    float avgwt = 0, avgtat = 0;
    int tq, n;

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    printf("Enter no of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);

        p[i].pid = i + 1;
        p[i].ret = p[i].bt;
    }

    // Sort by arrival time
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (p[i].at > p[j].at){
                struct process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Start from first arrival time
    time = p[0].at;

    // Add first process to queue
    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n){

        if (front == rear){
            time++;
            for (int i = 0; i < n; i++){
                if (p[i].at <= time && visited[i] == 0){
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];

        // Case 1: Process runs for full time quantum
        if (p[idx].ret > tq){
            p[idx].ret -= tq;
            time += tq;

            // Add newly arrived processes
            for (int i = 0; i < n; i++){
                if (p[i].at <= time && visited[i] == 0){
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            // Push current process back to queue
            queue[rear++] = idx;
        }
        // Case 2: Process finishes
        else{
            time += p[idx].ret;
            p[idx].ret = 0;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            avgwt += p[idx].wt;
            avgtat += p[idx].tat;
            completed++;

            // Add newly arrived processes
            for (int i = 0; i < n; i++){
                if (p[i].at <= time && visited[i] == 0){
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }
    }

    printf("\n--- Round Robin Scheduling ---\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", avgtat / n);
    printf("\nAverage WT = %.2f\n", avgwt / n);

    return 0;
}
