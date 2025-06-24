#include "ping.h"

//  struct BackgroundJobs BJobs[1024];
// int num_of_bg_jobs;

void ping(char *input)
{
    char *Command[1024];
    int number_of_arguments = 0;
    char *token = strtok(input, " ");
    while (token != NULL)
    {
        Command[number_of_arguments++] = token;
        token = strtok(NULL, " ");
    }
    Command[number_of_arguments] = NULL;
    if (number_of_arguments != 3)
    {
        fprintf(stderr, "Invalid number of arguments\n");
        return;
    }
    if (number_of_arguments == 3)
    {
        int pid_number = atoi(Command[1]);
        int signal_number = atoi(Command[2]);
        signal_number %= 32;
        if (pid_number < 0)
        {
            fprintf(stderr, "Invalid job pid\n");
        }
        else if (signal_number < 0)
        {
            fprintf(stderr, "Invalid Signal number\n");
        }
        else
        {
            for (int it = 0; it < num_of_bg_jobs; it++)
            {
                if (BJobs[it].pid == pid_number)
                {
                    kill(BJobs[it].pid, signal_number);
                    fprintf(stderr, "Sent signal %d to process with pid %d.\n", signal_number, pid_number );
                }
            }
        }
    }
}