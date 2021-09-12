CC=gcc

runalg : cpuscheduling.o
	$(CC) -pthread -o runalg cpuscheduling.o

cpuscheduling.o : cpuscheduling.c
	$(CC) -c cpuscheduling.c