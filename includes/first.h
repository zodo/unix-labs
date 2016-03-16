#ifndef __FIRST__
#define __FIRST__
#include <signal.h>

#define MAX_SIGNALS_AMOUNT 20
#define MAX_SIGNAL_STRING_LENGTH 200

typedef struct 
{
	char mode;
	int amount;
	int signalVal;
	pid_t pidVal;
} Arguments;

Arguments GetArguments(int argc, char * const argv[]);

void RunInStdMode();
void HandleSigUsr1(int signal, siginfo_t *siginfo, void *context);
void HandleSigUsr2(int signal, siginfo_t *siginfo, void *context);
void HandleSigHup(int signal, siginfo_t *siginfo, void *context);
void PrintSignalInfo(int signal, siginfo_t *siginfo);
void RunInChildMode();
void HandleSigchld(int signal, siginfo_t *siginfo, void *context);
void RunInPosixMode(int amount);
void HandleCustomSignal(int signal, siginfo_t *siginfo, void *context);
void HandleMySigchld(int signal, siginfo_t *siginfo, void *context);
void RunInKillMode(pid_t k_pid, int signal_no);
void RunInPipeMode();
void HandleSigpipe(int signal, siginfo_t *siginfo, void *context);

#endif