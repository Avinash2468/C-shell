#include "headers.h"

int main(){

    signal(SIGINT, signal_handler);
    char  line[MAX_INPUT_SIZE];            
    char  **tokens;      
    char  *split_by_semicolon[10000];        
    int i;
    original_pid = getpid();
    child_pid = -1;

    while (1) {           
        
        print_prompt(1);   
        bzero(line, MAX_INPUT_SIZE);
        gets(line);       
        // printf("the lines is: %s\n", line);

        if(strlen(line) > 0)  
        {
            int exit_check = 0;
            int num = splitter(split_by_semicolon, line, ";;");
            for (i=0; i<num; i++)
            {   
                char  *split_by_pipe_or_redirect[10000];
                printf("Executing Command:%s\n",split_by_semicolon[i]);
                int num_pipe = splitter(split_by_pipe_or_redirect, split_by_semicolon[i], "|");
                
                if (num_pipe>1) // If pipe is there
                {
                    piping(split_by_pipe_or_redirect, num_pipe);
                }

                memset(split_by_pipe_or_redirect, 0, 10000);
                int num_redirect = splitter(split_by_pipe_or_redirect, split_by_semicolon[i], ">");

                if (num_redirect>1) // If redirection is there
                {
                    redirection(split_by_pipe_or_redirect);
                }

                if (num_pipe == 1 && num_redirect == 1) // normal cases
                {
                    char  **command_to_run;
                    char  line[10000];
                    strcpy (line,split_by_semicolon[i]);
                    strcat (line,"\n");
                    command_to_run = tokenize(line);

                    if(!strcmp(command_to_run[0], "exit")) // exit code
                    {
                        exit_check = 1;
                        break;
                    }
                    else if (!strcmp(command_to_run[0], "cd"))
                    {
                        char cwd[10000];
                        int check;

                        if (command_to_run[1]==NULL || command_to_run[2]!=NULL)
                        {
                            perror("Error, incorrect number of arguments");
                        }
                        else
                        {
                            check = chdir(command_to_run[1]);
                            if(check!=0)
                            {
                                perror("Error, directory does not exist");
                            }
                            else
                            {
                                getcwd(cwd,sizeof(cwd));
                                printf("%s\n",cwd);
                            }
                        }
                    }
                    else
                    {
                        run_exec(command_to_run);
                    }
                }
            }
            if (exit_check)
            {
                break;
            }
        }

    // for(i=0;tokens[i]!=NULL;i++){
    //     free(tokens[i]);
    // }
    // free(tokens);

    }
}
