#include "execute.h"
#include "extra_functions.h"
#include "warp.h"
#include "peek.h"


char*substr(char*str,int start,int len)
{
    char*substr=(char*)malloc((len+1)*sizeof(char));
    int i=0;
    while(i<len)
    {
        substr[i]=str[start+i];
        i++;
    }
    substr[i]='\0';
    return substr;
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

void execute_function(struct commands command1)
{
    char* command=command1.command;
    bool print_pid_and_background=command1.print_pid_and_background;
    if(print_pid_and_background)
    {
        // this should print the pid of the command and then execute it
        // get the pid of the current process 
        pid_t pid = getpid();
        printf("%s[%d]%s\n",BLUE,pid,RESET);
    }
    if (strcmp("exit",command)==0 || strcmp("quit",command)==0)
    {
        exit(0); // this terminates the program.
    }
    char* check_first_4=substr(command,0,4);
    // warp workes as cd 
    // puts(check_warp);
    if(strcmp(check_first_4,"warp")==0)
    {
        warp_warp(command);
    }
    else if (strcmp(check_first_4, "peek")==0)
    {
        peek_peek(command);
    }
    
}