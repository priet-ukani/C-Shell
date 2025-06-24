#include "main.h"
#include <signal.h>
extern char **past_events;
char* file_open_path;
char *input;

char *parent_directory;
char** past_events;
char* file_open_path;
char* input;
char* shell_open_path;
char *parent_directory;
char *print_bg_output;
int print_bg_output_flag;
char* previous_prompt_username;
char* previous_prompt_system_name;
char* previous_prompt_cwd;
void set_signal_handlers()
{
    num_of_bg_jobs=0;  
    signal(SIGTSTP,SIG_IGN);
    // signal(SIGTSTP, kill_all_exit);
    signal(SIGINT,SIG_IGN);
    signal(SIGCHLD,child_signal);
    // signal(SIGQUIT, kill_all_exit);
}

int begin=0, endtime=0;
int main()
{
    system("clear");
    set_signal_handlers();
    // signal(SIGTSTP,SIG_IGN);

     
    parent_directory = getcwd(NULL, 0); 
    shell_open_path=(char*)malloc(1024*(sizeof(char)));
    previous_prompt_username=(char*)malloc(1024*(sizeof(char)));  
    previous_prompt_system_name=(char*)malloc(1024*(sizeof(char)));
    previous_prompt_cwd=(char*)malloc(1024*(sizeof(char)));
    print_bg_output=(char*)malloc(1024*(sizeof(char)));
    print_bg_output_flag=0;
    strcpy(shell_open_path, parent_directory);
    // This gets the current working directory
    past_events=(char**)malloc(sizeof(char*)*17);
    char *line = NULL;
    for (int i = 0; i < 17; i++)
    {
        past_events[i]=(char*)malloc(sizeof(char)*1024);
    }

    while (1)
    {
        // // // read all the commands from the pastevents;
        FILE* fp;
        file_open_path=(char*)malloc(sizeof(char)*1024);
        strcpy(file_open_path, parent_directory);
        strcat(file_open_path, "/pastevents.txt");
        // printf("%s", file_open_path);
        fp = fopen(file_open_path, "r");
        // fp = fopen("/home/prietukani/Desktop/Codes/Coding/Sem 3/OSN/C Shell/C-Shell/src/pastevents.txt", "r");
        if (fp == NULL)
        {
            perror("Error");
            exit(0);
        }
        // read all 15 commands from pastevents.txt 
        for (int i = 0; i < 15; i++)
        {
            fgets(past_events[i], 1024, fp);
            // puts(past_events[i]);
        }
        fclose(fp);
        display_user_prompt_function(parent_directory);
    }
    return 0;
}

