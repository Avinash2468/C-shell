#include "headers.h"

void signal_handler(int signal_number) {
	
    pid_t p = getpid();

    if (p != original_pid) // if we are in a child process
    {
        fflush(stdout);
        return;
    }

    if (p == original_pid && child_pid == -1) // if we are in the parent process, and there is no child
    {
        print_prompt(0);
        fflush(stdout);
        return;
    }

    if (child_pid != -1) // if there is a child process, kill it
    {
        kill(child_pid, SIGINT);
        fflush(stdout);
        return;
    }
}