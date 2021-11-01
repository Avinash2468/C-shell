#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

int original_pid;
int child_pid;

/*Printing Prompt */ void print_prompt(int check);
/*reading the token file*/ char **tokenize(char *line);
/*forking and running a process*/ void run_exec(char **tokens);
/*Handling signals */ void signal_handler(int signal_number);
/*Piping */ void piping(char *tokens[], int num_pipe);
/*Removing Character */ void remove_spaces(char* s);
