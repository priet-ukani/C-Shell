#include "fg_bg.h"

void bg(char *command)
{
    char **Command = separate_by_delimeter(command, " ");
    int number_of_arguments = 0;
    while (Command[number_of_arguments] != NULL)
    {
        number_of_arguments++;
    }
    if (number_of_arguments == 2)
    {
        int val_pid = atoi(Command[1]);
        int val=-1;
        for (int iterator = 0; iterator < num_of_bg_jobs; iterator++)
        {
            if (BJobs[iterator].pid == val_pid)
            {
                val = iterator + 1;
                break;
            }
        }
        if (val > 0 && val <= num_of_bg_jobs)
        {
            kill(BJobs[val - 1].pid, SIGCONT);
        }
        else
        {
            fprintf(stderr, "Invalid job PID\n");
        }
    }
    else
    {
        fprintf(stderr, "Invalid number of arguments\n");
    }
}

void fg(char *command)
{
    char **Command = separate_by_delimeter(command, " ");
    int number_of_arguments = 0;
    while (Command[number_of_arguments] != NULL)
    {
        number_of_arguments++;
    }
    if (number_of_arguments == 2)
    {
        int val_pid = atoi(Command[1]);
        int val=-1;
        for (int iterator = 0; iterator < num_of_bg_jobs; iterator++)
        {
            if (BJobs[iterator].pid == val_pid)
            {
                val = iterator + 1;
                break;
            }
        }
        if(val==-1)
        {
            sprintf(stderr, "Invallid job PID");
            return;
        }

        if (val > 0 && val <= num_of_bg_jobs)
        {
            int pid = BJobs[val - 1].pid;
            char *name_of_process;
            name_of_process = (char *)malloc(1024);
            strcpy(name_of_process, BJobs[val - 1].p_name);
            int i = val;
            
            if (BJobs[i].pid == pid)
            {
                int j = i + 1;
                while (j < num_of_bg_jobs)
                {
                    strcpy(BJobs[j - 1].p_name, BJobs[j].p_name);
                    BJobs[j - 1].pid = BJobs[j].pid;
                    j++;
                }
                BJobs[num_of_bg_jobs - 1].pid = -1;
                num_of_bg_jobs--;
            }

            int current_status;
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(STDIN_FILENO, pid);
            kill(pid, SIGCONT);
            waitpid(pid, &current_status, WUNTRACED);
            tcsetpgrp(STDIN_FILENO, getpgrp());
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            if (WIFSTOPPED(current_status))
            {
                printf("Process with pid: %d is stopped\n", pid);
                BJobs[num_of_bg_jobs].pid = pid;
                strcpy(BJobs[num_of_bg_jobs].p_name, name_of_process);
                num_of_bg_jobs++;
            }
        }
        else
        {
            fprintf(stderr, "Invalid job number\n");
        }
    }
    else
    {
        fprintf(stderr, "Invalid number of arguments\n");
    }
}