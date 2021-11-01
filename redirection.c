#include "headers.h"

void redirection(char  *split_by_pipe_or_redirect[10000])
{   
    char* file_name[10000];
    strcpy(file_name, split_by_pipe_or_redirect[1]);
    remove_spaces(file_name);
    int file_desc = open(file_name,O_TRUNC | O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
    int oldout = dup(STDOUT_FILENO); // storing file descriptor of terminal
    dup2(file_desc, 1) ; // making stdout go to custom file

    char  **command_to_run;
    char  line[10000];
    strcpy (line,split_by_pipe_or_redirect[0]);
    strcat (line,"\n");
    command_to_run = tokenize(line);
    run_exec(command_to_run);
    child_pid = -1;
    dup2(oldout, 1) ; // making stdout go to terminal
}