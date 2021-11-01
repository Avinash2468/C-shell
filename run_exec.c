#include "headers.h"

void run_exec(char **tokens)
{
    pid_t pid;
    int f;
    fflush(stdout);
    pid = fork(); // Forking to create a child process
    if (pid<0)
    {
        printf("Error: Fork failed for some reason. \n");
    }
    else if (pid == 0)
    {
        
        int f = execvp(tokens[0], tokens); //executing
        if (f < 0)
        {
            perror("Error: exec failed for some reason\n");
            printf("avinash_shell: command not found: %s\n", tokens[0]);
        }
        exit(0);
    }
    else
    {
        child_pid = pid;
        int status;
        waitpid(pid,&status,WUNTRACED);
    }
}