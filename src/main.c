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
    while (1)
    {

        // read all the commands from the pastevents;
        FILE* fp = fopen("pastevents", "r");
        if (fp == NULL)
        {
            perror("Error");
            exit(0);
        }
        char *line = NULL;
        char **past_events=(char**)malloc(sizeof(char*)*15);
        for (int i = 0; i < 15; i++)
        {
            past_events[i]=(char*)malloc(sizeof(char)*1024);
        }
        // read all 15 commands from pastevents.txt 
        for (int i = 0; i < 15; i++)
        {
            fgets(past_events[i], 1024, fp);
        }
        fclose(fp);
        
        display_user_prompt_function(parent_directory);

        char *input=(char*)malloc(4096*sizeof(char));
        fgets(input,4096,stdin);
        // This takes the input from the user
        input=remove_extra_spaces_and_tabs(input);
        struct commands*ok=split_commands(input);
        int i=0;
        while(ok[i].command!=NULL)
        {
            ok[i].command=remove_extra_spaces_and_tabs(ok[i].command);
            // printf("%s %d\n", ok[i].command, ok[i].print_pid_and_background);
            execute_function(ok[i]);
            i++;
        }
        
        for (int i = 14; i >= 0; i++)
        {
            
        }
        
    }
    return 0;
}

