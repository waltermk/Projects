
//Walter Mkpanam

 

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 5     // Mav shell only supports five arguments

// the history function accepts an array
// and the current value and prints out
// the history of commands entered by
// the user
int history(char *history[],int num)
{
    int i = 0;
    int list = 0;
    
    while(i != num)
    {
        printf("%d: %s",list,history[i]);
        list++;
    
        i = (i+1) % 15;
    }
    
    return 0;
}

// the executeCommands function accepts
// a double pointer to the string
// gotten from the user as a command
void executeCommands(char **command)
{
    pid_t pid = fork();
    int status;
    
    if((pid < 0))
    {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }
    else if( pid == 0)
    {
        if(execvp(*command,command) < 0)
        {
            printf("%s:Command not found.\n", *command);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}

// this sigintCatch function
// is essentially put in place
// to block the SIGINT signal
void sigintCatch(int sig)
{
    signal(SIGINT,sigintCatch);
}

// this sigintCatch function
// is essentially put in place
// to block the SIGTSTP signal
void sigtstpCatch(int num) // handling sigtstp
{
    signal(SIGTSTP, sigtstpCatch);
}

int main()
{

  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );

  struct sigaction act;
  
  memset(&act, '\0',sizeof(act));
  act.sa_handler = &sigintCatch;
  
  signal(SIGTSTP,sigtstpCatch);
  signal(SIGINT, sigintCatch);
    
  char *commands[15]; // create an array that can hold history for 15
    
  int i, idx = 0;
  
  for (i = 0; i < 15; i++)
  {
      commands[i] = NULL; // setting all indexes to null
                        // for initialization
  }
    
  
  while( 1 )
  {
    // Print out the msh prompt
    printf ("msh> ");

    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *arg_ptr;                                         
                                                           
    char *working_str  = strdup( cmd_str );                

    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;

    // Tokenize the input strings with whitespace used as the delimiter
    while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    commands[idx] = strdup(cmd_str); // copying commands from user into array
    idx = (idx + 1) % 15; // setting index
    
    if(strcmp(cmd_str,"exit\n")== 0 || strcmp(cmd_str,"quit\n") == 0) // exit or quit shell
    {
        break;
    }
    else if(strcmp(cmd_str,"history\n") == 0)// implementing history command
    {
        history(commands,idx);
    }
    else if(strcmp(&cmd_str[0],"cd") == 0) //implementing cd command
    {
        char *dir = strtok(cmd_str," ");
        
        if(!(dir == NULL))
        {
            chdir(dir);
            getcwd(dir, sizeof(dir));
        }
    }
    else if (strcmp(&cmd_str[0], "mkdir") == 0)
    {
        printf("Couldn't implement properly\n");
    }
    else if (strcmp(cmd_str,"listpids\n") == 0) //implementing
                                               //listpids command
    {
        pid_t pid = getpid();

        int *pids = (int*) malloc(15);
    
        pids = &pid;
        
        int j = 0;
        int curr = 0;
        
        while(j != idx)
        {
            printf("%d: %d\n",curr,pids[j]);
            curr++;
            j = (j+1) % 15;
        }
     
    }
    else if( strcmp(cmd_str,"ls\n") == 0) // implementing the ls command
    {
        pid_t pid = fork();
        if(!pid)
        {
           execlp("ls","ls",NULL);
        }
       
    }
    else if (strcmp(cmd_str, "\n") == 0)
    {
        // do nothing as this eliminates the new line
        // character going to the exec function
    }
    else
    {
        executeCommands(&cmd_str);
    }
      
    free( working_root );

  }
  return 0;
  
}
