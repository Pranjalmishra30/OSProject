#include<stdio.h>
#include<stdlib.h>
#define N 1000

int myMin(int a,int b){
	return a < b ? a : b;
}
void sortByArrival(int arrivalTime[],int sortedProcesses[],int numProcesses){
	//for(int i = 0;i < numProcesses;i++)
	//	sortedProcesses[i] = i;
	int minProcessIndex,tmp;
	//Implementing selection Sort on sortedProcesses
	for(int i = 0;i < (numProcesses - 1);i++){
		minProcessIndex = i;
		for(int j = i + 1; j < numProcesses;j++){
			if(arrivalTime[sortedProcesses[j]] < arrivalTime[sortedProcesses[minProcessIndex]])
				minProcessIndex = j;
		}
		tmp = sortedProcesses[i];
		sortedProcesses[i] = sortedProcesses[minProcessIndex];
		sortedProcesses[minProcessIndex] = tmp;
	}

}

typedef struct readyQueue{
	int processNum;
	struct readyQueue *next;
}RQ;

RQ* newNode(int k)
{
    RQ* temp = (RQ*)malloc(sizeof(RQ));
    temp->processNum = k;
    temp->next = NULL;
    return temp;
}

RQ *readyQueueFront = NULL,*readyQueueRear = NULL;

void enqueue(int processNum){
	RQ* temp = newNode(processNum);
	if(readyQueueFront == NULL || readyQueueRear == NULL){
		//front = (struct readyQueue *)malloc(sizeof(struct readyQueue));
		//rear = (struct readyQueue *)malloc(sizeof(struct readyQueue));
		readyQueueFront = readyQueueRear = temp;
	}
	else{
		readyQueueRear->next = temp;
		readyQueueRear = readyQueueRear->next;
	}
}

int dequeue(){
	int val;
	if(readyQueueRear == NULL || readyQueueFront == NULL){
		printf("Queue empty can't dequeue\n");
		return -1;
	}
	val = readyQueueFront->processNum;
	RQ *temp = readyQueueFront;

	if(readyQueueRear == readyQueueFront){
		readyQueueFront = readyQueueRear = NULL;
	}
	else{
		readyQueueFront = readyQueueFront->next;
	}
	free(temp);
	return val;
}


void RoundRobin(int BurstTime[],int completionTime[],int arrivalTime[], int timeQuantum,int numProcesses){
	int sortedProcesses[N],remainingBurstTime[N],readyQueue[N],waitingTime[N],turnAroundTime[N];
	int currentTime = 0,numComplete = 0,readyQueueIndex = -1,prevProcess = -1;

	for(int i =0;i < numProcesses;i++){
		sortedProcesses[i] = i;
		remainingBurstTime[i] = BurstTime[i];
	}

	sortByArrival(arrivalTime,sortedProcesses,numProcesses);
	int arrivalIndex = 0;
	
	bool isComplete = false;
	int prevExecutedProcess = -1,currentProcess = -1,executionTime;

	while(isComplete == false){
		if(arrivalTime[sortedProcesses[arrivalIndex]] > currentTime && readyQueueFront == NULL){
			currentTime++;
			continue;
		}
		
		while(arrivalTime[sortedProcesses[arrivalIndex]] <= currentTime && arrivalIndex < numProcesses){
			enqueue(sortedProcesses[arrivalIndex]);
			//printf("Adding process %d to queue at %ds\n",sortedProcesses[arrivalIndex],currentTime);
			arrivalIndex++;
		}
		if(prevExecutedProcess != -1 && remainingBurstTime[prevExecutedProcess] > 0){
			enqueue(prevExecutedProcess);
			//printf("Adding process %d to queue at %ds\n",prevExecutedProcess,currentTime);
		}

		currentProcess = dequeue();
		//printf("Dequeueing process %d and executing\n",currentProcess);

		executionTime = myMin(remainingBurstTime[currentProcess],timeQuantum);
		printf("Process P%d is being executed for %d seconds from %ds to %ds\n",currentProcess, executionTime,currentTime,currentTime + executionTime);


		remainingBurstTime[currentProcess] = remainingBurstTime[currentProcess] - executionTime;
		currentTime += executionTime;
		prevExecutedProcess = currentProcess;


		if(remainingBurstTime[currentProcess] == 0){
			completionTime[currentProcess] = currentTime;
			numComplete++;
		}

		if(numComplete == numProcesses)
			isComplete = true;

	}
	printf("-----------------------\n");

	printf("PNo\tAT\tCT\tTAT\tWT\n");
	for(int i = 0;i < numProcesses;i++){
		turnAroundTime[i] = completionTime[i] - arrivalTime[i];
		waitingTime[i] = turnAroundTime[i] - BurstTime[i];
		printf("%d\t%d\t%d\t%d\t%d\n",i,arrivalTime[i],completionTime[i],turnAroundTime[i],waitingTime[i]);
	}

	float avgWaitTime = 0,avgTurnAroundTime = 0;
	for(int i = 0; i < numProcesses;i++){
		avgWaitTime += waitingTime[i];
		avgTurnAroundTime += turnAroundTime[i];
	}
	avgWaitTime = avgWaitTime/numProcesses;
	avgTurnAroundTime = avgTurnAroundTime/numProcesses;
	printf("\n");
	printf("Average waiting time : %f\n",avgWaitTime);
	printf("Average turnaround time : %f\n",avgTurnAroundTime);

}