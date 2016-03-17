#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "first.h"

const char savedStrings[MAX_SIGNALS_AMOUNT][MAX_SIGNAL_STRING_LENGTH];

void RunInPosixMode(int amount) {
	struct sigaction sigChld;
	sigChld.sa_flags = SA_SIGINFO;
	sigChld.sa_sigaction = &HandleMySigchld;

	struct sigaction sigCustom;
	sigCustom.sa_flags = SA_SIGINFO;
	sigCustom.sa_sigaction = &HandleCustomSignal;
	int j;
	for (j = SIGRTMIN; j < SIGRTMAX; j++) {
		if(sigaction(j, &sigCustom, NULL) == -1){
			perror("registration errror");
		}
	}

	if (sigaction(SIGCHLD, &sigChld, NULL) == -1) {
			perror("SIGCHLD registration error");
		}	

	pid_t pid = fork();
	if (pid == 0) {
		srand(time(NULL));	
		int i;	
		for (i = 0; i < amount; ++i) {
			union sigval value;
			int r_signal = (rand() % (SIGRTMAX + 1 - SIGRTMIN)) + SIGRTMIN;
			value.sival_int = rand();
			sigqueue(getppid(), r_signal, value);
			fprintf(stderr, "child %i|%i|%i|%i|%i\n", i, getpid(), getppid(), r_signal, value.sival_int);
		}
	} else if(pid > 0) {
			
		int status;
		if (wait(&status) > 0) {
			exit( EXIT_SUCCESS );
		} else {
			perror("Failed to handle child-zombie");
			exit( EXIT_FAILURE );
		}
		
	}
	// while(1) sleep(1);	
}


int count = 0;
void HandleMySigchld(int signal, siginfo_t *siginfo, void *context) {
	
	fprintf(stdout, "sigchild handler\n");
	int i;
	for (i = 0; i < count; ++i)
	{
		fprintf(stdout, "%s\n", savedStrings[i]);
	}
	exit( EXIT_SUCCESS );				
}

void HandleCustomSignal(int signal, siginfo_t *siginfo, void *context) {
	sprintf(&savedStrings[count], "paren %i|%i|%i|%i|%i", 
		count, siginfo->si_pid, getpid(), signal, siginfo->si_value.sival_int);
	count++;
}