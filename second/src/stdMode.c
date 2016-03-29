#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "first.h"


void RunInStdMode() {
	printf("current pid=%i\n", getpid());

	struct sigaction sigUsr1;
	sigUsr1.sa_sigaction = &HandleSigUsr1;
	sigUsr1.sa_flags = SA_SIGINFO;

	sigfillset(&sigUsr1.sa_mask);

	if (sigaction(SIGUSR1, &sigUsr1, NULL) == -1) {
		perror("sigusr1 registration error");
	}

	struct sigaction sigUsr2;
	sigUsr2.sa_sigaction = &HandleSigUsr2;
	sigUsr2.sa_flags = SA_SIGINFO;

	sigfillset(&sigUsr2.sa_mask);

	if (sigaction(SIGUSR2, &sigUsr2, NULL) == -1) {
		perror("sigusr2 registration error");
	}

	struct sigaction sigHup;
	sigHup.sa_sigaction = &HandleSigHup;
	sigHup.sa_flags = SA_SIGINFO;

	sigfillset(&sigHup.sa_mask);

	if (sigaction(SIGHUP, &sigHup, NULL) == -1) {
		perror("sighup registration error");
	}	

	printf("waiting for signals\n");
	while(1) sleep(1);
} 

void PrintSignalInfo(int signal, siginfo_t *siginfo){
	pid_t signalId = siginfo->si_pid;
	fprintf( stdout, "catch %d.process info: PID=%i, GID=%i\n", signal, signalId, getpgid(signalId));
}


void HandleSigUsr1(int signal, siginfo_t *siginfo, void *context){
	PrintSignalInfo(signal, siginfo);
}
void HandleSigUsr2(int signal, siginfo_t *siginfo, void *context){
	PrintSignalInfo(signal, siginfo);
}
void HandleSigHup(int signal, siginfo_t *siginfo, void *context){
	PrintSignalInfo(signal, siginfo);
}