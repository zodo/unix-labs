#include "first.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void RunInChildMode() {
	struct sigaction sigChld;
	sigChld.sa_flags = SA_SIGINFO;
	sigChld.sa_sigaction = &HandleSigchld;
	pid_t pid = fork();
	if (pid == 0) {
		srand(time(NULL));
		int r = rand() % 10;
		printf("child PID=%d, GID=%d sleepTime=%d\n", getpid(), getpgid(getpid()), r);
		sleep(r);
	} else if(pid > 0) {
		printf("parent PID=%d, GID=%d\n", getpid(), getpgid(getpid()));
		if (sigaction(SIGCHLD, &sigChld, NULL) == -1) {
			perror("SIGCHLD registration error");
		}	
		int status;
		if (wait(&status) > 0) {
			exit( EXIT_SUCCESS );
		} else {
			perror("fail");
			exit( EXIT_FAILURE );
		}
	}
}

void HandleSigchld(int signal, siginfo_t *siginfo, void *context) {
	
	printf("child info. PID=%i, UID=%i, status=%i, code=%i\n", siginfo->si_pid, siginfo->si_uid, siginfo->si_status, siginfo->si_code);	
	exit( EXIT_SUCCESS );				
}