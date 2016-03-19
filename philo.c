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


int main(){
	srand((unsigned)time(NULL));
	int lefty = rand() % 5;
	pid_t pid;
//somebody's gonna be a lefty
//to prevent the edge case of everyone grabbing a chopstick
//with their right hand all at once creating a deadlock



	int semID = semget(IPC_PRIVATE, 5, S_IRUSR | S_IWUSR);
	int vals[5] = {1,1,1,1,1};
	union semun init;
	init.array = vals;
	int semctl(semID, 0, SETALL, init);
	//initially all chopsticks are on the table


    /* fork child processes */
    int i;
    for (i = 0; i < n; i++){
        pid = fork ();		
        if (pid < 0)              /* check for error      */
            printf ("Fork error.\n");
        else if (pid == 0){
        	//determine who's the lefty
        	if(i == lefty){
        		lefty = 1; 
        	}else lefty = 0;
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
    else if(pid == lefty)
    else{


    	//to-do
    	exit(0);
    }
}