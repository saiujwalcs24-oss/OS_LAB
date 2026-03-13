#include <stdio.h>

int main()
{
    printf("Priority Scheduling Algorithm (Preemptive)\n");
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    int at[n], bt[n], pr[n], rt[n];
    int ct[n], tat[n], wt[n];

    for(int i=0;i<n;i++)
    {
        printf("AT P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("BT P%d: ",i+1);
        scanf("%d",&bt[i]);

        printf("Priority P%d: ",i+1);
        scanf("%d",&pr[i]);

        rt[i]=bt[i];
    }

    int time=0,complete=0;

    while(complete<n)
    {
        int highest=999,index=-1;

        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0)
            {
                if(pr[i]<highest)
                {
                    highest=pr[i];
                    index=i;
                }
            }
        }

        if(index==-1)
        {
            time++;
            continue;
        }

        rt[index]--;
        time++;

        if(rt[index]==0)
        {
            ct[index]=time;
            complete++;
        }
    }

    printf("\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);
    }
}