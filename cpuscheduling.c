#include <stdio.h>
#include <stdlib.h>

#define PROCESS_COUNT 5
#define QUANTAM
void fcfs(int ps[PROCESS_COUNT][3]);
void sjf(int ps[PROCESS_COUNT][3]);
void rr(int ps[PROCESS_COUNT][3]);
void prio(int ps[PROCESS_COUNT][3]);
void print(int ps[PROCESS_COUNT][3], int i);
void push(int x);
void pop();

int back = -1, front = -1;
int queue[PROCESS_COUNT];

int main()
{
	int processSet[PROCESS_COUNT][3] = {
		{1, 20, 4},
		{2, 25, 2},
		{3, 25, 3},
		{4, 15, 3},
		{5, 10, 10} };

	printf("----------FCFS ALGORITHM----------\n\n");
	fcfs(processSet);
	printf("\n\n----------SJF ALGORITHM----------\n\n");
	sjf(processSet);
	printf("\n\n----------PRIORITY SCHEDULING (NON-PREEMPTIVE) ALGORITHM----------\n\n");
	prio(processSet);

	return 0;
}

void print(int ps[PROCESS_COUNT][3], int i)
{
	int totalBurst = 0;
	float waitTimeTotal = 0;
	float turnAroundTotal = 0;

	waitTimeTotal += totalBurst;
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
	if (i < 4)
	{
		printf("         ||    \n");
		printf("        \\  /    \n");
		printf("         \\/    \n");
	}

	turnAroundTotal += totalBurst;

	if (i == PROCESS_COUNT)
	{
		float avgWaitTime = waitTimeTotal / PROCESS_COUNT;
		float avgTurnAroundTime = turnAroundTotal / PROCESS_COUNT;

		printf("\nThe total wait time is: %.2f\n", waitTimeTotal);
		printf("The average wait time is: %.2f\n", avgWaitTime);
		printf("The total turnaround time is: %.2f\n", turnAroundTotal);
		printf("The average turnaround time is: %.2f\n", avgTurnAroundTime);
	}

}

void fcfs(int ps[PROCESS_COUNT][3])
{
	int totalBurst = 0;
	float waitTimeTotal = 0;
	float turnAroundTotal = 0;

	for (int i = 0; i < PROCESS_COUNT; i++)
	{
		waitTimeTotal += totalBurst;
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
		if (i < 4)
		{
			printf("         ||    \n");
			printf("        \\  /    \n");
			printf("         \\/    \n");
		}

		turnAroundTotal += totalBurst;
	}

	float avgWaitTime = waitTimeTotal / PROCESS_COUNT;
	float avgTurnAroundTime = turnAroundTotal / PROCESS_COUNT;

	printf("\nThe total wait time is: %.2f\n", waitTimeTotal);
	printf("The average wait time is: %.2f\n", avgWaitTime);
	printf("The total turnaround time is: %.2f\n", turnAroundTotal);
	printf("The average turnaround time is: %.2f\n", avgTurnAroundTime);
}

void sjf(int ps[PROCESS_COUNT][3])
{
	int psCpy[PROCESS_COUNT][3] = { 0 };
	memcpy(psCpy, ps, sizeof(psCpy));
	int tempPS[PROCESS_COUNT][3] = { 0 };

	int smallestBurst = 0;
	int smallestBurstIndex = 0;

	//sort by cpu burst time
	for (int i = 0; i < PROCESS_COUNT; i++)
	{
		for (int j = 0; j < PROCESS_COUNT; j++)
		{
			if ((psCpy[j][1] < tempPS[i][1] || tempPS[i][1] == 0) && psCpy[j][1] != -1)
			{
				smallestBurstIndex = j;
				tempPS[i][0] = psCpy[j][0];
				tempPS[i][1] = psCpy[j][1];
				tempPS[i][2] = psCpy[j][2];
			}
		}

		psCpy[smallestBurstIndex][1] = -1;
	}

	fcfs(tempPS);

}

void rr(int ps[PROCESS_COUNT][3])
{

}

void push(int x)
{
	if (front == -1)
		front = 0;
	back += 1;					//pushes the next value into the queue
	queue[back] = x;
}

void pop()
{
	front += 1;					//moves to the next value in the queue
}

void prio(int ps[PROCESS_COUNT][3])
{
	int psCpy[PROCESS_COUNT][3] = { 0 };
	memcpy(psCpy, ps, sizeof(psCpy));
	int tempPS[PROCESS_COUNT][3] = { 0 };

	int highestPriorityIndex = 0;

	//sort by priority
	for (int i = 0; i < PROCESS_COUNT; i++)
	{
		for (int j = 0; j < PROCESS_COUNT; j++)
		{
			if ((psCpy[j][2] < tempPS[i][2] || tempPS[i][2] == 0) && psCpy[j][2] != -1)
			{
				highestPriorityIndex = j;
				tempPS[i][0] = psCpy[j][0];
				tempPS[i][1] = psCpy[j][1];
				tempPS[i][2] = psCpy[j][2];
			}
		}

		psCpy[highestPriorityIndex][2] = -1;
	}

	fcfs(tempPS);
}

void print(int ps[PROCESS_COUNT][3], int i)
{
}
