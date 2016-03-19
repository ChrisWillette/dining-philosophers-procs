//chris willette
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include "random.h"

union semun {
	int val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO*/
};



int grabStick(int semID, int stick){
	struct sembuf tmp;
	tmp.sem_num = stick;
	tmp.sem_op = -1;
	tmp.sem_flg = IPC_UNDO; //incase of unexpected exit
	return semop(semID, &tmp, 1);
}

int releaseStick(int semID, int stick){
	struct sembuf tmp;
	tmp.sem_num = stick;
	tmp.sem_op = 1;
	tmp.sem_flg = IPC_UNDO; //incase of unexpected exit
	return semop(semID, &tmp, 1);
}

int eatTime(){
	int interval = randomGaussian(9, 3);
	if(interval < 0) interval = 0;
	return interval;
}

int thinkTime(){
	int interval = randomGaussian(11, 7);
	if(interval < 0) interval = 0;
	return interval;
}

void printing(int semID, int interval, int arg){
	struct sembuf tmp;
	tmp.sem_num = 6; //print lock
	tmp.sem_op = arg;
	tmp.sem_flg = IPC_UNDO;
	semop(semID, &tmp, 1);
}



int main(){
	srand((unsigned)time(NULL));
	int lefty = rand() % 5;
	pid_t pid;
//somebody's gonna be a lefty
//to prevent the edge case of everyone grabbing a chopstick
//with their right hand all at once creating a deadlock


	//5 chopstick sems and one semaphore for prints 
	int semID = semget(IPC_PRIVATE, 6, 0666);
	ushort vals[] = {1,1,1,1,1,1};
	union semun init;
	init.array = vals;
	int semctl(semID, 0, SETALL, init);
	//initially all chopsticks are on the table


    /* fork child processes */
    int i;
    int philoNum;
    for (i = 0; i < n; i++){
        pid = fork ();		
        if (pid < 0)              /* check for error      */
            printf ("Fork error.\n");
        else if (pid == 0){
        	//determine who's the lefty
        	if(i == lefty){
        		lefty = 1; 
        	}else lefty = 0;
        	philoNum = i;
            break;     /* children don't need silverware */
        }
    }

	

    if (pid != 0){
        /* wait for all children to exit */
        while (pid = waitpid (-1, NULL, 0)){
            if (errno == ECHILD) break;
        }
        printf ("\nEveryone's done eating and thinking.\n");

        /*clean up the semaphores*/
        semctl(semid, 0, IPC_RMID);
        return 0;
    }

    /****child stuff****/
    else{

	int totalEatTime = 0;
	int eatClock;
	int thinkClock;
	int rightStick;
	int leftStick;
	while(totalEatime < 100){
		//grab chopsticks
		grabStick(semID, rightStick);
		grabStick(semID, leftStick);

		eatClock = eatTime();
		totalEatTime = totalEatTime + eatClock;
		printing(-1);
    		printf("\nPhilosopher %d now eating for %d seconds.",
			philoNum+1, eatClock);
		printing(1);
		sleep(eatClock);

		thinkClock = thinkTime();
		printing(-1);
    		printf("\nPhilosopher %d now thinking for %d seconds.",
			philoNum+1, thinkClock);
		printing(1);
		sleep(thinkClock);		
		
		//release chopsticks
		releaseStick(semID, rightStick);
		releaseStick(semID, leftStick);
	}

    	exit(0);
    }
}
