#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "RoundRobin_Algorithm.h"
#define N 1000

void solveRR(){
	int arrivalTime[N], BurstTime[N], completionTime[N], timeQuantum, numProcesses = 4;
	
	//sortByArrival(arrivalTime,sortedProcesses,numProcesses);

	printf("Enter number of processes : ");
	scanf("%d",&numProcesses);
	printf("Enter time quantum : ");
	scanf("%d",&timeQuantum);

	for(int i = 0;i < numProcesses;i++){
		printf("Enter details for Process P%d\n",i);
		printf("Arrival Time : ");
		scanf("%d",&arrivalTime[i]);

		printf("Burst Time : ");
		scanf("%d",&BurstTime[i]);
		printf("------------\n");
	}


	//for(int i = 0;i < numProcesses;i++)
	//	printf("%d\t",sortedProcesses[i]);
	RoundRobin(BurstTime,completionTime,arrivalTime,timeQuantum,numProcesses);
	printf("\n");


}
// int main(){
// 	solveRR();

// }