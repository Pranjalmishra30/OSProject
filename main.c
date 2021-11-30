#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "SJF/SJF.c"
#include "FCFS/fcfs.c"


int main(){
    int n;
    printf("\n-----------------------------\n");
    printf("\tOS Project\n");
    printf("-----------------------------\n");
    while(1){
        printf("\nScheduling algorithms\n");
        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. Round Robin\n");
        printf("Choose option: ");
        scanf("%d",&n);

        switch (n){
            case 1:
                printf("\nExecuting FCFS\n");
                solveFCFS();
                break;
            
            case 2:
                printf("\nExecuting SJF....\n\n");
                solveSJF();
                break;

            case 3:
                printf("\nExecuting Round Robin\n");
                // execlp("","",NULL) // complete when file is ready

            case -1:
                printf("Exiting...\n");
                exit(0);

            default:
            printf("Wrong option....\n");
        }
    }
    
}