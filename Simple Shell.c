#include<stdio.h>
#include<stdlib.h>
#include<string.h> // used for strtok()
#include<signal.h>
#include<sys/wait.h> // used for wait()
#include<sys/resource.h>// used for pid_t
#include<unistd.h>

#define TRUE 1
#define SIZE 100

void split(char *input, char **arguments); // prototype for splitting the command function
void handle();
int main()
{
    char *args[SIZE];   // pointer to array of splitted command
    char command[SIZE]; // Array for the command that will be inputted by user
    pid_t Parent_id;    // signal type to represent parent ID
    int child_state;

    while(TRUE)
    {
        signal(SIGCHLD,handle);
        printf(" Enter the command : \n");
        gets(command);
        split(command,args);

        if (strcmp(command, "exit") == 0)

        {
            break;
        }
        else if (strcmp(command, "\n") == 0)
        {
            continue;
        }


        Parent_id= fork();

        if(Parent_id==0) // created new child
        {
            child_state=execvp(*args,args);
            if(child_state<0) //error in executing child process
            {
                printf("Error !! \n");
            }
            exit(0);



        }
        else if (Parent_id>0)
        {
            if(args[1]&&(strcmp(args[1],"&")==0)) // checking if & found
            {
// start background
            }
            else
            {
                wait(NULL); // start foreground and wait
            }

        }
        else //error in the command
        {
            printf("Invalid !! \n");
        }
    }

}


void handle ()
{
FILE *fp;
fp = fopen("log.txt","a");
fprintf(fp,"Child proccess was terminated \n");
fclose(fp);

}

void split(char *input, char **arguments)
{
    char *splitted;
    splitted = strtok(input, " ");
    while(splitted != NULL)
    {
        *arguments++  = splitted;
        splitted = strtok(NULL, " ");
    }

    *arguments = NULL;
}
