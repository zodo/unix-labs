#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "first.h"

void RunInPipeMode() {
	int fd[2];
	int bytesRead;
	struct sigaction sigpipe;
	sigpipe.sa_flags = SA_SIGINFO;
	sigpipe.sa_sigaction = &HandleSigpipe;

	if (pipe(fd) < 0) {
		fprintf(stderr, "pipe error\n" );
		exit( EXIT_FAILURE );
	}

	if(sigaction(SIGPIPE, &sigpipe, NULL) == -1){
		perror("sigpipe registration error");
		exit( EXIT_FAILURE );
	}

	pid_t pid = fork();
	if (pid == 0) {
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	} else if(pid > 0) {
		close(fd[0]);
		sleep(1);
		char * somedata = "somedate";
		int len = strlen(somedata);
		printf("str %s len %d\n", somedata, len);
		size_t stat = write(fd[1], somedata, len);
		if (stat < 0)
		{
			perrror("write");
		}
		if (stat != len)
		{
			fprintf(stderr, "write error\n" );
		}	
		printf("%d\n", stat);

		int status;
		if (wait(&status) > 0) {
			exit( EXIT_SUCCESS );
		} else {
			perror("fail");
			exit( EXIT_FAILURE );
		}
	}

	while(1) sleep(1);
}

void HandleSigpipe(int signal, siginfo_t *siginfo, void *context) {	
	printf("sigpipe!\n");			
}
