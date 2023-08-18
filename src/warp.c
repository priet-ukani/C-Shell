#include "execute.h"
#include "extra_functions.h"
#include "warp.h"

char* shell_call_path;
char *previous_shell_path;
bool first_time_warp=true;

int tilda()
{
    // this moves the cwd to the default path from where shell is executed 
    previous_shell_path=getcwd(NULL, 0);
    puts(shell_call_path);
    int return_code=chdir(shell_call_path);
    if(return_code==-1)
    {
        perror(RED"Error"RESET);
        return 0;
    }
    return 1;
}

int minus()
{
    // this moves the cwd to the previous path 
    char *temp=getcwd(NULL,0);
    puts(previous_shell_path);
    int return_code=chdir(previous_shell_path);
    previous_shell_path=temp;
    if (return_code==-1)
    {
        perror(RED"Error"RESET);
        return 0;
    }
    return 1;
}


int warp_warp(char *command)
{
    if(first_time_warp)
    {
        first_time_warp=!first_time_warp;
        shell_call_path=getcwd(NULL, 0); 
        previous_shell_path=shell_call_path;
    }
    char* warp_to=substr(command,5,strlen(command)-5);

    // separate multiple arguments by space then warp in left to right order
    char ** tokens=separate_by_delimeter(warp_to, " ");
    int i=0;
    if(tokens[0]==NULL || tokens[0]=="")
    {
        tilda();
    }
    while(tokens[i]!=NULL)
    {
        printf("%s", tokens[i]);
        if(strcmp(tokens[i], "~" ) == 0)
        {
            tilda();
            i++;
            continue;
        }
        else if (strcmp(tokens[i], "-")==0)
        {
            minus();
            i++;
            continue;
        }
        previous_shell_path=getcwd(NULL, 0);
        int return_code=chdir(tokens[i]);
        puts(getcwd(NULL,0));
        if(return_code==-1)
        {
            perror(RED"Error"RESET);
        }
        i++;
    }
    return;
}