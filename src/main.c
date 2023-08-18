#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "display_user_prompt.h"
#include "extra_functions.h"
#include "colours.h"
#include "execute.h"


int main()
{
    char *parent_directory = getcwd(NULL, 0); 
    // This gets the current working directory
    
    char *line = NULL;
    char **past_events=(char**)malloc(sizeof(char*)*17);
    for (int i = 0; i < 17; i++)
    {
        past_events[i]=(char*)malloc(sizeof(char)*1024);
    }

    while (1)
    {
        // // read all the commands from the pastevents;
        FILE* fp;
        char* file_open_path=(char*)malloc(sizeof(char)*1024);
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

        char *input=(char*)malloc(4096*sizeof(char));
        fgets(input,4096,stdin);
        // // This takes the input from the user
        input=remove_extra_spaces_and_tabs(input);
        struct commands*ok=split_commands(input);
        

        fopen(file_open_path, "w");
        // fopen("/home/prietukani/Desktop/Codes/Coding/Sem 3/OSN/C Shell/C-Shell/src/pastevents.txt", "w");
        
        bool already_exists=false;
        for (int i = 0; i < 15; i++)
        {
            strcat(input,"\n");
            if(strcmp(input,past_events[i])==0)
            {
                already_exists=!already_exists;
                break;
            }
        }
        printf("%d\n", already_exists);
        if(!already_exists)
        {
            for (int k = 13; k >= 0; k--)
            {
                // past_events[k+1]=past_events[k];
                strcpy(past_events[k+1],past_events[k]);
            }
            // past_events[0]=input;
            strcpy(past_events[0],input);
        }
        for (int i = 0; i < 15; i++)
        {
            fprintf(fp, "%s", past_events[i]);
            if(past_events[i][strlen(past_events[i])-1]!='\n')
            {
                fprintf(fp, "\n");
            }
        }
        fclose(fp);
        int i=0;
        while(ok[i].command!=NULL)
        {
            ok[i].command=remove_extra_spaces_and_tabs(ok[i].command);
            // printf("%s %d\n", ok[i].command, ok[i].print_pid_and_background);
            execute_function(ok[i]);
            i++;
        }
    }
    return 0;
}

