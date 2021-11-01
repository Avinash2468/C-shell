#include "headers.h"

int splitter(char *tokens[], char *line, char *delim)
{
  int num = 0; //num stores number of arguments

  tokens[num] = strtok(line, delim);

  while (tokens[num] != NULL)
  {
    tokens[++num] = strtok(NULL, delim);
  }

  tokens[num] = NULL;

  return num;
}