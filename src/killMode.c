#include "first.h"
#include <signal.h>


void RunInKillMode(pid_t k_pid, int signal_no) {
	kill(k_pid, signal_no);
}