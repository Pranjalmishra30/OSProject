#include<stdio.h>
#include<stdlib.h>
#define MAX 10

int mat[MAX][6];

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void arrangeArrival(int num){
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num - i - 1; j++) {
			if (mat[j][1] > mat[j + 1][1]) {
				for (int k = 0; k < 5; k++) {
					swap(&mat[j][k], &mat[j + 1][k]);
				}
			}
		}
	}
}

void completionTime(int num){
	int temp, val;
	mat[0][3] = mat[0][1] + mat[0][2]; // completion 
	mat[0][5] = mat[0][3] - mat[0][1]; // Turnaround 
	mat[0][4] = mat[0][5] - mat[0][2]; // Waiting

	for (int i = 1; i < num; i++) {
		temp = mat[i - 1][3];
		int low = mat[i][2];
		for (int j = i; j < num; j++) {
			if (temp >= mat[j][1] && low >= mat[j][2]) {
				low = mat[j][2];
				val = j;
			}
		}
		mat[val][3] = temp + mat[val][2];
		mat[val][5] = mat[val][3] - mat[val][1];
		mat[val][4] = mat[val][5] - mat[val][2];
		for (int k = 0; k < 6; k++) {
			swap(&mat[val][k], &mat[i][k]);
		}
	}
}

void AverageTimes(int num){
    float avgWait=0.0,avgTurn=0.0;
    for(int i=0;i<num;i++){
        avgWait+=mat[i][4];
        avgTurn+=mat[i][5];
    }
    printf("\nAverage Waiting time:    %.3f\n",avgWait/num);
	printf("Average Turnaround time: %.3f\n",avgTurn/num);

}

void displayInput(int num){
	printf("Input:\n\n");
	printf("PID\tArrival Time\tBurst Time\n");
	for(int i=0;i<num;i++){
		printf("%d\t\t%d\t\t%d\n",mat[i][0],mat[i][1],mat[i][2]);
	}
	printf("\n");

}

void solveSJF(){

	int num;
	printf("Enter number of Process: \n");
	scanf("%d",&num);

	for (int i = 0; i < num; i++) {
		printf("...Process %d ...\n",i + 1);
		mat[i][0] = i+1; // process id
		printf("Enter Arrival Time: ");
		scanf("%d",&mat[i][1]);
		printf("Enter Burst Time: ");
		scanf("%d",&mat[i][2]);
	}

	displayInput(num);
	arrangeArrival(num);
	completionTime(num);
	printf("Result:\n\n");
	printf("PID\tArrival Time\tBurst Time\tCompletion Time\t\tWaiting "
			"Time\tTurnaround Time\n");
	for(int i = 0; i < num; i++){
		printf("%d\t%d\t\t%d\t\t%d\t\t\t%d\t\t%d\n",mat[i][0],mat[i][1],mat[i][2],mat[i][3],mat[i][4],mat[i][5]);
	}
    AverageTimes(num);
}

// int main(){
// 	solveSJF();
// }
