#include "extra_functions.h"
#include "colours.h"
#include "main.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>

// struct commands{
//     char *command;
//     bool print_pid_and_background;
// };

// char* remove_extra_spaces_and_tabs(char * input_str);

// struct commands *split_commands(char *input_str);

int mini(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

char** separate_by_delimeter(char*str, char* delimeter)
{
    char **ans=(char**)malloc(sizeof(char*)*1024);
    int index=0;
    char *token;
    for (int i = 0; i < 1024; i++)
    {
        ans[i]=(char*)malloc(sizeof(char)*1024);
    }
    token = strtok(str, delimeter);
    ans[index++]=token;
    while( token != NULL ) 
    {
        token = strtok(NULL, delimeter);
        ans[index++]=token;
    }
    return ans;

}

char *replace_home(char *path)
{
    // replace ~ by home apth 
    char *abs_path = malloc(sizeof(char) * (strlen(path) + strlen(shell_open_path)));
    if (path[0] == '~' && (strlen(path) == 1 || path[1] == '/'))
    {
        if (strlen(path) == 1)
        {
            strcpy(abs_path, shell_open_path);
        }
        else
        {
            sprintf(abs_path, "%s%s", shell_open_path, path + 1);
        }
    }
    else
    {
        strcpy(abs_path, path);
    }

    return abs_path;
}

char *remove_extra_spaces_and_tabs(char *input_str)
{
    // This functions cleans the input string to remove extra spaces and tabs to only keep 1 space in between
    // and remove spaces and tabs from the beginning and end of the string
    int i = 0;
    int j = 0;
    int flag = 0;
    while (input_str[i] != '\0')
    {
        if (input_str[i] == ' ' || input_str[i] == '\t')
        {
            if (flag == 0)
            {
                input_str[j] = input_str[i];
                j++;
                flag = 1;
            }
        }
        else
        {
            input_str[j] = input_str[i];
            j++;
            flag = 0;
        }
        i++;
    }
    input_str[j] = '\0';
    // now replace tabs with single space
    i = 0;
    while (input_str[i] != '\0')
    {
        if (input_str[i] == '\t')
        {
            input_str[i] = ' ';
        }
        i++;
    }
    // now remove spaces from beginning and end of string
    i = 0;
    while (input_str[i] == ' ')
    {
        i++;
    }
    j = 0;
    while (input_str[i] != '\0')
    {
        input_str[j] = input_str[i];
        i++;
        j++;
    }
    input_str[j] = '\0';
    i = strlen(input_str) - 1;
    while (input_str[i] == ' ')
    {
        input_str[i] = '\0';
        i--;
    }
    return input_str;
}

// struct commands{
//     char *command;
//     bool print_pid_and_background;
// };

struct commands *split_commands(char *input_str)
{
    // This function splits and separates multiple commands separated by ";" or by "&" also
    // and returns a char** of all the commands
    input_str[strlen(input_str)-1]=' ';
    struct commands *commands_buffer = (struct commands*)malloc(1024 * sizeof(struct commands));
    for (int it = 0; it < 1024; it++)
    {
        commands_buffer[it].command = (char*)malloc(1024 * sizeof(char));
    }
    
    int i = 0;
    int j = 0;
    int k = 0;
    int flag = 0;
    while (input_str[i] != '\0')
    {
        if (input_str[i] == ';' || input_str[i] == '&')
        {
            if (flag == 0)
            {
                k = 0;
                j++;
                if (j != 0)
                {
                    if (input_str[i] == '&')
                    {
                        commands_buffer[j - 1].print_pid_and_background = 1;
                    }
                    else
                    {
                        commands_buffer[j - 1].print_pid_and_background = 0;
                    }
                }
                flag = 1;
            }
        }
        else
        {
            commands_buffer[j].command[k] = input_str[i];
            k++;
            flag = 0;
        }
        i++;
    }
    commands_buffer[j].command[k] = '\0';
    commands_buffer[j+1].command = NULL;
    return commands_buffer;
}

int check_and_throw_error(int return_code, int errno_code, char* message)
{
    if (return_code == errno_code)
    {
        if (message != NULL)
        {
            perror(message);
        }
        else perror(RED"Sad"RESET);
    }
    return return_code;
}



// int main()
// {
//     char *input_str=malloc(1024*sizeof(char));
//     fgets(input_str, 1024, stdin);
//     input_str[strlen(input_str)-1]=' '; // this removes the '\n' at the end
//     struct commands*ok=split_commands(input_str);
//     int i=0;
//     while(ok[i].command!=NULL)
//     {
//         ok[i].command=remove_extra_spaces_and_tabs(ok[i].command);
//         printf("%s %d\n", ok[i].command, ok[i].print_pid_and_background);
//         i++;
//     }
//     free (input_str);
//     return 0;
// }