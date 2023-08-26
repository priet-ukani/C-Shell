#include "system_commands.h"
#include "bg.h"


void set_signal_handlers()
{
    num_of_bg_jobs=0;  
    signal(SIGTSTP,SIG_IGN);
    signal(SIGINT,SIG_IGN);
    signal(SIGCHLD,child_signal);
}

void child_signal()
{
    int status;
    int pid = waitpid(-1,&status, WNOHANG);// WNOHANG is this is just a check, we don't want to wait for child process to terminate.

    // printf("%d %d, ", pid, num_of_bg_jobs); check
    if(pid > 0)
    {
        char p_name[1024];
        int idx=0;

        for(int i=0;i<num_of_bg_jobs;i++)
        {
            if(BJobs[i].pid == pid)
            {
                strcpy(p_name,BJobs[i].p_name);
                idx=i;
                for(int j=i+1;j<num_of_bg_jobs;j++)
                {
                    strcpy(BJobs[j-1].p_name,BJobs[j].p_name);
                    BJobs[j-1].pid = BJobs[j].pid;
                }
                BJobs[num_of_bg_jobs-1].pid = -1;
                num_of_bg_jobs--;
                break;
            }
        }
        // give a message.
        if(WIFEXITED(status) && WEXITSTATUS(status)==EXIT_SUCCESS)
        {
            print_bg_output_flag=1;
            strcpy(print_bg_output, "ok");
            fprintf(stderr,"\033[1;31m\n%s with pid %d exited normally.\n\033[0m",p_name,pid);
            // fprintf(print_bg_output,"\033[1;31m\n%s with pid %d exited normally.\n\033[0m",p_name,pid);
            // fprintf(stdin, "\n");
        }
        else
        {
            print_bg_output_flag=1;
            strcpy(print_bg_output, "ok");
            // fprintf(print_bg_output,"\033[1;31m\n%s with pid %d failed to exit normally.\033[0m\n",p_name,pid);
            fprintf(stderr,"\033[1;31m\n%s with pid %d failed to exit normally.\033[0m\n",p_name,pid);
            // fprintf(stdin, "\n");
        }
        // display_user_prompt_function(parent_directory);
        puts("");
        printf(GREEN "[%s@%s " RESET "%s" GREEN "]$ " RESET, previous_prompt_username, previous_prompt_system_name, previous_prompt_cwd);
        fflush(stdout);
        // fflush(stderr);
    }
    return;
}




void add_process(char** name,int pid)
{
    strcpy(BJobs[num_of_bg_jobs].p_name,name[0]);
    int idx=1;
    while(name[idx]!=NULL)
    {
        strcat(BJobs[num_of_bg_jobs].p_name," ");
        strcat(BJobs[num_of_bg_jobs].p_name,name[idx]);
        idx++;
    }
    BJobs[num_of_bg_jobs].pid = pid;
    num_of_bg_jobs++;
}

void other_commands(char*cmmd, int is_bg)
{
    char **command=separate_by_delimeter(cmmd, " ");
    int status;

    int pid = fork();
    if(pid<0)
    {
        perror("forking error");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0) // child
    {
        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
        
        setpgid(0,0);
    
        if(execvp(command[0],command)<0)
        {
            perror("Command Not Found");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        if(!is_bg)
        {
            signal(SIGTTIN,SIG_IGN); signal(SIGTTOU,SIG_IGN);
 
            tcsetpgrp(STDIN_FILENO,pid); // child process ko terminal cantrol

            begin=0;
            begin=time(NULL);
            waitpid(pid, &status, WUNTRACED);
            endtime=0;
            endtime=time(NULL);

            tcsetpgrp(STDIN_FILENO,getpgrp()); 

            signal(SIGTTIN,SIG_DFL); signal(SIGTTOU,SIG_DFL); // This is necessary as without this tcsetgrp() will not be able to resume control to child as sigttin will 
            
            if(WIFSTOPPED(status))
            {
                printf("Process with id: %d stopped\n",pid);
                add_process(command, pid);
            }
        }
        else
        {
            add_process(command, pid);
            printf("[%d] %d\n", num_of_bg_jobs, pid);
        }
    }
}