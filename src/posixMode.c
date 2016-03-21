#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "first.h"

const char savedStrings[MAX_SIGNALS_AMOUNT][MAX_SIGNAL_STRING_LENGTH];
int count = 0;

void HandleCustomSignal(int signo, siginfo_t *siginfo, void *context)
{
    if(signo==SIGCHLD)
    {        
        int i;
    	printf("%d\n", count);
		for (i = 0; i < count; ++i)
		{
			// fprintf(stdout, "%s\n", savedStrings[i]);
		}
        exit(EXIT_SUCCESS);
    }
    else
    {
        sprintf(&savedStrings[count], "paren %i|%i|%i|%i|%i", count, siginfo->si_pid, getpid(), signal, siginfo->si_value.sival_int);
		count++;
    }
    return;
}


void RunInPosixMode(int amount) {
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = HandleCustomSignal;
	int i;
    for(i = SIGRTMIN; i<SIGRTMAX; i++)
    {
        if(sigaction(i, &sa, NULL)== -1)  
        {
        	perror("registration error");
    	 	exit(EXIT_FAILURE);
    	}
    }

    if(sigaction(SIGCHLD, &sa, NULL)== -1) {
        	perror("registration error");
    	 	exit(EXIT_FAILURE);
    	}

	pid_t pid = fork();    
	if (pid == 0)
    {	                  
	    srand(time(0));	  
	    int i;  
	    for (i = 0; i < amount; ++i) {
			union sigval value;
			int r_signal = (rand() % (SIGRTMAX + 1 - SIGRTMIN)) + SIGRTMIN;
			value.sival_int = rand();
			sigqueue(getppid(), r_signal, value);
			printf("child %i|%i|%i|%i|%i\n", i, getpid(), getppid(), r_signal, value.sival_int);
		}
	    sleep(1);
	    exit(EXIT_FAILURE);
    }      
    
}
