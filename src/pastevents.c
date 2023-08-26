#include "pastevents.h"
#include "main.h"

// char **past_events;
// char* file_open_path;
// char *given_input; extern from another file
char *pastevents_execute_prev_command;
int pastevents_execute_function_called=0;
void write_to_file(int success,char* given_input)
{
    pastevents_execute_function_called=0;
    FILE* f = fopen(file_open_path, "w");
    // fopen("/home/prietukani/Desktop/Codes/Coding/Sem 3/OSN/C Shell/C-Shell/src/pastevents.txt", "w");
    bool already_exists=false;
    if(given_input[strlen(given_input)-1]!='\n')
        strcat(given_input,"\n");
    for (int i = 0; i < 1; i++)
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

    // // printf("%s, %d", split_words[0], i); // check
    for (int it = 0; it < i; it++)
    {
        split_words[it]=remove_extra_spaces_and_tabs(split_words[it]);
        if((strcmp(split_words[it], "pastevents")==0 ))
        {
            if(it<i-1)
            {
                if(strcmp(split_words[it+1], "execute")==0)
                {
                    if(it<i-2)
                    {
                        char* num=split_words[it+2];
                        int num_1=atoi(num);
                        if(num_1<1 || num_1>15)
                        {
                            // puts("Out of Bounds index");
                            return;
                        }
                        // printf("index: %d\n", num_1);
                        char* prev_command=past_events[num_1-1];
                        // printf("%s, %s, %d, %d\n", prev_command, past_events[0], strlen(prev_command), strlen(past_events[0]));
                        
                        if(prev_command[strlen(prev_command)-1]=='\n')prev_command[strlen(prev_command)-1]='\0';
                        if(past_events[0][strlen(past_events[0])-1]=='\n')past_events[0][strlen(past_events[0])-1]='\0';
                        prev_command=remove_extra_spaces_and_tabs(prev_command);
                        past_events[0]=remove_extra_spaces_and_tabs(past_events[0]);
                        
                        if(strcmp(prev_command, past_events[0])==0)
                        {
                            // printf("Hi bro not possible bro");
                            check_not_pastevents_commands=false;
                            break;
                        }
                        else
                        {
                            pastevents_execute_function_called=1;
                            check_not_pastevents_commands=true;
                            strcpy(pastevents_execute_prev_command,prev_command);
                        }
                    }
                    else
                    {
                        check_not_pastevents_commands=false;
                        break;
                    }
                }
                else
                {
                    check_not_pastevents_commands=false;
                    break;
                }
            }
            else
            {
                check_not_pastevents_commands=false;
                break;
            }
        }
        // else if ((strcmp(split_words[it], "pastevents")==0 )&&(it-1<i)&& (strcmp(split_words[it+1], "execute")==0))
        // {
        //     char* num=split_words[it+2];
        //     int num_1=num[0]-'0';
        //     printf("index: %d\n", num_1);
        //     char* prev_command=past_events[num_1-1];
        //     printf("%s, %s, %d, %d\n", prev_command, past_events[0], strlen(prev_command), strlen(past_events[0]));
        //     if(strcmp(prev_command, past_events[0])==0)
        //     {
        //         check_not_pastevents_commands=false;
        //         break;
        //     }
        //     else
        //     {
        //         check_not_pastevents_commands=true;
        //     }
        // }
        // else if ((strcmp(split_words[it], "pastevents")==0 ))
        // {
        //     check_not_pastevents_commands=false;
        //     break;
        // }
    }
    
    // puts(given_input);   
    if(pastevents_execute_function_called)
    {
        strcpy(given_input, pastevents_execute_prev_command);
    }
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
    pastevents_execute_prev_command=(char*)malloc(sizeof(char)*1024);
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
        for (int jj = 0; jj < 15; jj++)
        {
            if (past_events[jj]!=NULL && past_events[jj][0] != ' ' && past_events[jj][0]!='\n')
            {
                printf("%s", past_events[jj]);
            }
        }
    }
    else if (i==3)
    {
        // pastevents execute x 
        if (strcmp(args[1], "execute") == 0)
        {
            int z = atoi(args[2]);
            if (z >= 1 && z <= 15)
            {
                // execute the command
                if(past_events[z-1]!=NULL && past_events[z-1][0] != ' ' && past_events[z-1][0]!='\n')
                {
                    execute_multi_commands(past_events[z-1]);
                }
            }
            else
            {
                puts("Out of bounds index!");
            }
            
        }
    }
}
