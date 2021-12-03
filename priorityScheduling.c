#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
 
#define totalprocess 3
 
struct process{
    int at,bt,pr,pno;
};
 
struct process proc[50];
 
bool comp(struct process a,struct process b)
{
    if(a.at == b.at){
        return a.pr<b.pr;
    }
    else{
        return a.at<b.at;
    }
}
 
void get_wt_time(int wt[])
{
    int service[50];
    service[0] = proc[0].at;
    wt[0]=0;
    for(int i=1;i<totalprocess;i++)
    {
        service[i]=proc[i-1].bt+service[i-1];
        wt[i]=service[i]-proc[i].at;
 
        if(wt[i]<0)
        {
            wt[i]=0;
        }
    }
 
}
 
void get_tat_time(int tat[],int wt[])
{
    for(int i=0;i<totalprocess;i++)
    {
        tat[i]=proc[i].bt+wt[i];
    }
 
}
 
void findgc()
{
    int wt[50],tat[50];
    double wavg=0,tavg=0;
 
    get_wt_time(wt);
    get_tat_time(tat,wt);
    int stime[50],ctime[50];
    stime[0] = proc[0].at;
    ctime[0]=stime[0]+tat[0];
 
    for(int i=1;i<totalprocess;i++)
    {
        stime[i]=ctime[i-1];
        ctime[i]=stime[i]+tat[i]-wt[i];
    }
 
    printf("Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time\n");
 
    for(int i=0;i<totalprocess;i++)
    {
        wavg += wt[i];
        tavg += tat[i];
 
        printf("%d\t\t",proc[i].pno);
        printf("%d\t\t%d\t\t",stime[i],ctime[i]);
        printf("%d\t\t\t%d\n",tat[i],wt[i]);
    }
 
    printf("Average waiting time is : ");
    printf("%f\n",wavg/(float)totalprocess);
    printf("average turnaround time : ");
    printf("%f\n",tavg/(float)totalprocess);
 
}

void solvePri(){
    int arrivaltime[] = {3,0,1};
    int bursttime[] = {2,4,3};
    int priority[] = {1,2,3};
 
    for(int i=0;i<totalprocess;i++)
    {
        proc[i].at=arrivaltime[i];
        proc[i].bt=bursttime[i];
        proc[i].pr=priority[i];
        proc[i].pno=i+1;
    }
 
    // sort(proc,proc+totalprocess,comp);

    for(int i = 0;i < (totalprocess - 1);i++){
		int minProcessIndex = i;
		for(int j = i + 1; j < totalprocess;j++){
			if(proc[j].at < proc[minProcessIndex].at)
				minProcessIndex = j;
		}
		struct process temp = proc[i];
		proc[i] = proc[minProcessIndex];
		proc[minProcessIndex] = temp;
	}
 
    findgc();
 

}
// int main()
// {
//     solvePri();
// }
