#include <stdio.h>

int main() {
    int choice;

    printf("CPU Scheduling - SJF\n");
    printf("1. Non Preemptive SJF\n");
    printf("2. Preemptive SJF (SRTF)\n");
    printf("Enter choice: ");
    scanf("%d",&choice);

    switch(choice) {

    case 1: {
        int n,i,j;
        int bt[20],wt[20],tat[20],p[20];
        float avg_wt=0,avg_tat=0;

        printf("Enter number of processes: ");
        scanf("%d",&n);

        printf("Enter Burst Time:\n");
        for(i=0;i<n;i++){
            printf("P%d: ",i+1);
            scanf("%d",&bt[i]);
            p[i]=i+1;
        }

        for(i=0;i<n;i++){
            for(j=i+1;j<n;j++){
                if(bt[i]>bt[j]){
                    int temp=bt[i];
                    bt[i]=bt[j];
                    bt[j]=temp;

                    temp=p[i];
                    p[i]=p[j];
                    p[j]=temp;
                }
            }
        }

        wt[0]=0;

        for(i=1;i<n;i++)
            wt[i]=wt[i-1]+bt[i-1];

        for(i=0;i<n;i++)
            tat[i]=wt[i]+bt[i];

        printf("\nProcess\tBT\tWT\tTAT\n");

        for(i=0;i<n;i++){
            avg_wt+=wt[i];
            avg_tat+=tat[i];
            printf("P%d\t%d\t%d\t%d\n",p[i],bt[i],wt[i],tat[i]);
        }

        printf("\nAverage WT = %.2f",avg_wt/n);
        printf("\nAverage TAT = %.2f",avg_tat/n);
        break;
    }

    case 2: {
        int n,i,time=0,smallest;
        int bt[10],rt[10],at[10];
        int complete=0;
        int wt[10],tat[10];
        float avg_wt=0,avg_tat=0;

        printf("Enter number of processes: ");
        scanf("%d",&n);

        for(i=0;i<n;i++){
            printf("Arrival Time of P%d: ",i+1);
            scanf("%d",&at[i]);

            printf("Burst Time of P%d: ",i+1);
            scanf("%d",&bt[i]);

            rt[i]=bt[i];
        }

        while(complete!=n){
            smallest=-1;

            for(i=0;i<n;i++){
                if(at[i]<=time && rt[i]>0){
                    if(smallest==-1 || rt[i]<rt[smallest])
                        smallest=i;
                }
            }

            if(smallest==-1){
                time++;
                continue;
            }

            rt[smallest]--;
            time++;

            if(rt[smallest]==0){
                complete++;

                tat[smallest]=time-at[smallest];
                wt[smallest]=tat[smallest]-bt[smallest];

                avg_wt+=wt[smallest];
                avg_tat+=tat[smallest];
            }
        }

        printf("\nProcess\tWT\tTAT\n");

        for(i=0;i<n;i++)
            printf("P%d\t%d\t%d\n",i+1,wt[i],tat[i]);

        printf("\nAverage WT = %.2f",avg_wt/n);
        printf("\nAverage TAT = %.2f",avg_tat/n);
        break;
    }

    default:
        printf("Invalid choice");
    }

    return 0;
}
