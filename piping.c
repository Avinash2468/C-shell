#include "headers.h"

void piping(char *tokens[], int num_pipe)
{
    int in = 0, out = 1;    

    for (int i = 0; i<num_pipe; i++)
    {
        char  **command_to_run;
        char  line[10000];
        strcpy (line,tokens[i]);
        strcat (line,"\n");
        command_to_run = tokenize(line);

        int pipefd[2];
        pipe(pipefd);
        pid_t c_pid = fork();

        if (c_pid<0)
        {
            printf("Fork failed!\n");
        }
        else if (c_pid==0)
        {
            dup2(in,0); // Take input from the previous command
            close(pipefd[0]);
            if (i!=(num_pipe-1))
            {
                dup2(pipefd[1],1); // Print this command's output to p[1]
                run_exec(command_to_run);
                child_pid = -1;
            }
            else // checking if redirect exists
            {
                char  *split_by_redirect[10000];
                int num_redirect = splitter(split_by_redirect, tokens[i], ">");
                if (num_redirect>1)
                {
                    redirection(split_by_redirect);
                }
                else
                {
                    run_exec(command_to_run);
                    child_pid = -1;
                }
            }

            exit(0);
        }
        else
        {
            int status;
            waitpid(c_pid,&status,WUNTRACED);
            close(pipefd[1]);
            in = pipefd[0];
        }
    }
}