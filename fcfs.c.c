#include<stdio.h>

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

int main(){

    int n;
    float avg_tat=0, avg_wt=0;

    printf("Enter the number of processes:\n");
    scanf("%d",&n);

    int p[10],AT[10],BT[10],TAT[10],CT[10],WT[10];

    for(int i=0;i<n;i++){
        p[i]=i+1;

        printf("Enter the arrival time of P%d: ",p[i]);
        scanf("%d",&AT[i]);

        printf("Enter the burst time of P%d: ",p[i]);
        scanf("%d",&BT[i]);
    }

    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(AT[i]>AT[j]){
                swap(&AT[i],&AT[j]);
                swap(&p[i],&p[j]);
                swap(&BT[i],&BT[j]);
            }
        }
    }

    CT[0]=AT[0]+BT[0];

    for(int i=1;i<n;i++){
        if(CT[i-1]<AT[i])
            CT[i]=AT[i]+BT[i];
        else
            CT[i]=CT[i-1]+BT[i];
    }

    for(int i=0;i<n;i++){
        TAT[i]=CT[i]-AT[i];
        WT[i]=TAT[i]-BT[i];

        avg_tat+=TAT[i];
        avg_wt+=WT[i];
    }

    avg_tat/=n;
    avg_wt/=n;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i],AT[i],BT[i],CT[i],TAT[i],WT[i]);
    }

    printf("\nAverage TAT = %.2f\n",avg_tat);
    printf("Average WT = %.2f\n",avg_wt);

    return 0;
}
