#include "system_commands.h"

int number_of_background_jobs = 0;
int begin=0;
int endtime=0;

BackgroundJobs Store_BackgroundJobs[1024];


void Insert_Process(char* command_bro, int pid)
{
    strcpy(Store_BackgroundJobs[number_of_background_jobs].Job_name, command_bro);
    Store_BackgroundJobs[number_of_background_jobs].pid=pid;
    number_of_background_jobs++;
}

void other_system_commands(char* command_bro, int Is_Background)
{
    int pid=fork();
    if(pid>0)
    {
        if(Is_Background==1)
        {
            Insert_Process(command_bro,pid);
            printf("[%d] %d\n",number_of_background_jobs,pid);
        }
        else
        {
            signal(SIGTTIN,SIG_IGN);
            signal(SIGTTOU,SIG_IGN);
            tcsetpgrp(STDIN_FILENO,pid); 

            int current_status;
            begin=endtime=0;
            begin=time(NULL);
            waitpid(pid, &current_status, WUNTRACED);
            endtime=time(NULL);
            if(current_status>=255 && current_status<2*255)

            tcsetpgrp(STDIN_FILENO,getpgrp()); 
            signal(SIGTTOU,SIG_DFL); 
            signal(SIGTTIN,SIG_DFL);
            
            if(WIFSTOPPED(current_status))
            {   
                printf("Process with pid: %d is stopped\n",pid);
                Insert_Process(command_bro,pid);
            }
        }
    }
    else if(pid==0)
    {
        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
        setpgid(0,0);
        char **Command=separate_by_delimeter(command_bro, " ");
        if(execvp(Command[0],Command)>=0)
        {
            printf("Process done successfully\n");
            exit(EXIT_SUCCESS);
            return;
        }
        else
        {
            perror("Invalid Command");
            exit(EXIT_FAILURE);
            return;
        }
    }
    else
    {
        perror("Unable to Fork correctly");
        exit(EXIT_FAILURE);
    }
}

