#include "pastevents.h"
#include "main.h"

// char **past_events;
// char* file_open_path;
// char *given_input; extern from another file

void write_to_file(int success,char* given_input)
{
    FILE* f = fopen(file_open_path, "w");
    // fopen("/home/prietukani/Desktop/Codes/Coding/Sem 3/OSN/C Shell/C-Shell/src/pastevents.txt", "w");
    bool already_exists=false;
    if(given_input[strlen(given_input)-1]!='\n')
        strcat(given_input,"\n");
    for (int i = 0; i < 15; i++)
    {
        given_input=remove_extra_spaces_and_tabs(given_input);
        past_events[i]=remove_extra_spaces_and_tabs(past_events[i]);
        if(strcmp(given_input,past_events[i])==0)
        {
            already_exists=!already_exists;
            break;
        }
    }
    // printf("%d\n", already_exists);
    bool check_not_pastevents_commands=true;
    char *cpy=(char*)malloc(sizeof(char)*1024);
    if(given_input[strlen(given_input)-1]=='\n')
    {
        given_input[strlen(given_input)-1]='\0';
    }
    strcpy(cpy,given_input);
    char **split_words=separate_by_delimeter(cpy, " ");
    int i=0;
    while(split_words[i]!=NULL)
    {
        i++;
    }

    // printf("%s, %d", split_words[0], i); // check
    if((strcmp((split_words[0]), "pastevents")==0 && i==1) || ( strcmp(split_words[0], "pastevents")==0 && strcmp(split_words[1], "purge")==0))
    {
        check_not_pastevents_commands=false;
    }
    if((i==3) && (strcmp(split_words[0], "pastevents")==0 )&& (strcmp(split_words[1], "execute")==0) && (strcmp(split_words[2], "1")==0))
    {
        check_not_pastevents_commands=false;
    }
    // puts(given_input);
    if(!already_exists && success && check_not_pastevents_commands)
    {
        for (int k = 13; k >= 0; k--)
        {
            // past_events[k+1]=past_events[k];
            strcpy(past_events[k+1],past_events[k]);
        }
        // past_events[0]=given_input;
        strcpy(past_events[0],given_input);
    }
    for (int i = 0; i < 15; i++)
    {
        fprintf(f, "%s", past_events[i]);
        if(past_events[i][strlen(past_events[i])-1]!='\n')
        {
            fprintf(f, "\n");
        }
    }
    fclose(f);
}

void pastevents_function(char *command)
{
    // separate command by spaces
    // char **args = split_line(command);
    // split line doesnst work 
    char **args = separate_by_delimeter(command, " ");

    int i = 0;
    while (args[i] != NULL)
    {
        i++;
    }
    if (i == 2)
    {
        // pastevents purge
        if (strcmp(args[1], "purge") == 0)
        {
            // delete file
            past_events=(char**) malloc(sizeof(char *) * 17);
            for (int i = 0; i < 17; i++)
            {
                past_events[i]=(char*) malloc(sizeof(char) * 1024);
                past_events[i][0]=' ';
            }

            printf("All pastevents deleted\n");
        }
        else
        {
            printf("Invalid command!\n");
        }
    }
    else if (i == 1)
    {
        // pastevents
        // print all past events
        for (int i = 0; i < 15; i++)
        {
            if (past_events[i][0] != ' ')
            {
                printf("%s", past_events[i]);
            }
        }
    }
    else if (i==3)
    {
        // pastevents execute x 
        if (strcmp(args[1], "execute") == 0)
        {
            int x = atoi(args[2]);
            if (x >= 1 && x <= 15)
            {
                // execute the command
                execute_multi_commands(past_events[x-1]);
            }
        }
    }
    
}
