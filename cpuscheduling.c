#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define PROCESS_COUNT 5
#define TIME_QUANTUM 10

void *fcfs(void *arg);
void *sjf(void *arg);
void *rr(void *arg);
void *prio(void *arg);
void print(int ps[][3], int totalElements);
int emptyQueue(int psCpy[PROCESS_COUNT][3]);

int back = -1, front = -1;
int robinSize = 0;
int queue[PROCESS_COUNT];

//predefined set of processes for program to test cpu algorithms
	int processSet[PROCESS_COUNT][3] = {
		{1, 20, 4},
		{2, 25, 2},
		{3, 25, 3},
		{4, 15, 3},
		{5, 10, 10}
	};

int fcfsArr[PROCESS_COUNT][3];
int sjfArr[PROCESS_COUNT][3];
int rrArr[100][3];
int prioArr[PROCESS_COUNT][3];

int main()
{
	//create a thread for each cpu scheduling algorithm
	pthread_t fcfsThread, sjfThread, rrThread, prioThread;

    pthread_create(&fcfsThread, NULL, fcfs, NULL);
    pthread_create(&sjfThread, NULL, sjf, NULL);
    pthread_create(&rrThread, NULL, rr, NULL);
	pthread_create(&prioThread, NULL, prio, NULL);
    pthread_join(fcfsThread, NULL); 
    pthread_join(sjfThread, NULL);
    pthread_join(rrThread, NULL);
	pthread_join(prioThread, NULL);

	printf("\n\n----------FCFS ALGORITHM----------\n\n");
	print(processSet, PROCESS_COUNT);
	printf("\n\n----------SJF ALGORITHM----------\n\n");
	print(sjfArr, PROCESS_COUNT);
	printf("\n\n----------ROUND ROBIN ALGORITHM----------\n\n");
	print(rrArr, robinSize);
	printf("\n\n----------PRIORITY SCHEDULING (NON-PREEMPTIVE) ALGORITHM----------\n\n");
	print(prioArr, PROCESS_COUNT);
	
	

	return 0;
}

void print(int ps[][3], int totalElements) //print gantt chart for each algorithm
{
	int totalBurst = 0;
	float waitTimeTotal = 0;
	float turnAroundTotal = 0;
	float waitTimeArr[5] = { 0 };
	float turnAroundArr[5] = { 0 };

	for (int i = 0; i < totalElements; i++)
	{
		waitTimeArr[ps[i][0] - 1] += totalBurst - turnAroundArr[ps[i][0] - 1];

		printf("  ");
		for (int j = 0; j <= ps[i][1] + 3; j++)
		{
			printf("-");
		}

		printf("\n |");

		for (int j = 0; j <= ps[i][1] / 2; j++)
		{
			printf(" ");
		}

		printf("P%i", ps[i][0]);

		for (int j = (ps[i][1] / 2) + 1; j <= ps[i][1]; j++)
		{
			printf(" ");
		}
		printf("|\n ");
		printf("%i ", totalBurst);
		for (int j = 0; j <= ps[i][1]; j++)
		{
			printf("-");
		}
		totalBurst += ps[i][1];
		printf(" %i\n", totalBurst);
		if (i < totalElements - 1)
		{
			printf("         ||    \n");
			printf("        \\  /    \n");
			printf("         \\/    \n");
		}

		turnAroundArr[ps[i][0] - 1] += totalBurst - turnAroundArr[ps[i][0] - 1];
	}

	for (int i = 0; i < PROCESS_COUNT; i++)
	{
		waitTimeTotal += waitTimeArr[i];
		turnAroundTotal += turnAroundArr[i];
	}


	float avgWaitTime = waitTimeTotal / PROCESS_COUNT;
	float avgTurnAroundTime = turnAroundTotal / PROCESS_COUNT;

	printf("\nThe total wait time is: %.2f\n", waitTimeTotal);
	printf("The average wait time is: %.2f\n", avgWaitTime);
	printf("The total turnaround time is: %.2f\n", turnAroundTotal);
	printf("The average turnaround time is: %.2f\n\n", avgTurnAroundTime);
}

void *fcfs(void *arg) //first come first serve algorithm
{
	
}

void *sjf(void *arg) //shortest job first algorithm
{
	

	int smallestBurst = 0;
	int smallestBurstIndex = 0;

	int psCpy[PROCESS_COUNT][3] = { 0 };
	memcpy(psCpy, processSet, sizeof(psCpy));


	
	for (int i = 0; i < PROCESS_COUNT; i++) //sort by cpu burst time
	{
		for (int j = 0; j < PROCESS_COUNT; j++)
		{
			if ((psCpy[j][1] < sjfArr[i][1] || sjfArr[i][1] == 0) && psCpy[j][1] != -1)
			{
				smallestBurstIndex = j;
				sjfArr[i][0] = psCpy[j][0];
				sjfArr[i][1] = psCpy[j][1];
				sjfArr[i][2] = psCpy[j][2];
			}
		}

		psCpy[smallestBurstIndex][1] = -1;
	}

}

void *rr(void *arg) //round robin algorithm
{
	
	int i = 0, j = 0, k = 0;

	int psCpy[PROCESS_COUNT][3] = { 0 };

	memcpy(psCpy, processSet, sizeof(psCpy));

	for (int it = 0; emptyQueue(psCpy) == 1; it++) //execute processes for the time quantum allowed until all processes are done
	{
		i = it % 5;
		if (psCpy[i][1] > 0)
		{
			for (j = 0, k = psCpy[i][1]; j < TIME_QUANTUM && k - j > 0; j++) {}

			psCpy[i][1] -= j;

			rrArr[robinSize][0] = psCpy[i][0];
			rrArr[robinSize][1] = j;
			rrArr[robinSize][2] = psCpy[i][2];
			robinSize++;
		}
	}

}

int emptyQueue(int psCpy[PROCESS_COUNT][3])
{
	for (int i = 0; i < PROCESS_COUNT; i++)
	{
		if (psCpy[i][1] != 0)
		{
			return 1;
			break;
		}
	}

}

void *prio(void *arg) //priority scheduling algorithm
{
	

	int psCpy[PROCESS_COUNT][3] = { 0 };
	memcpy(psCpy, processSet, sizeof(psCpy));

	int highestPriorityIndex = 0;

	//sort by priority
	for (int i = 0; i < PROCESS_COUNT; i++) //sort the processes by priority 
	{
		for (int j = 0; j < PROCESS_COUNT; j++)
		{
			if ((psCpy[j][2] < prioArr[i][2] || prioArr[i][2] == 0) && psCpy[j][2] != -1)
			{
				highestPriorityIndex = j;
				prioArr[i][0] = psCpy[j][0];
				prioArr[i][1] = psCpy[j][1];
				prioArr[i][2] = psCpy[j][2];
			}
		}

		psCpy[highestPriorityIndex][2] = -1;
	}
	
}
