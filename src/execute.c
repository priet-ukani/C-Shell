#include "execute.h"
#include "extra_functions.h"
#include "warp.h"
#include "peek.h"
#include "pastevents.h" 
#include "system_commands.h"
#include "proclore.h"
#include "seek.h"
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

int execute_multi_commands(char*input)
{
    input=remove_extra_spaces_and_tabs(input);
    char *cppy=input;
    struct commands*ok=split_commands(cppy);
    
    int i=0;
    int success=0;
    while(ok[i].command!=NULL)
    {
        ok[i].command=remove_extra_spaces_and_tabs(ok[i].command);
        // printf("%s %d\n", ok[i].command, ok[i].print_pid_and_background);
        success |= execute_function(ok[i]);
        i++;
    }
    return success;
}

int execute_function(struct commands command1)
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
    char* check_first_10=substr(command,0,10);
    char* cppy=(char*)malloc(sizeof(char)*1024);
    strcpy(cppy, command);
    char**Command=separate_by_delimeter(cppy, " ");
    // warp workes as cd 
    // puts(check_warp);
    if(strcmp(Command[0],"warp")==0)
    {
        warp_warp(command);
    }
    else if (strcmp(Command[0], "peek")==0)
    {
        peek_peek(command);
    }
    else if (strcmp(Command[0], "pastevents")==0)
    {
        pastevents_function(command);
    }
    else if (strcmp(Command[0], "proclore")==0)
    {
        pinfo(command);
    }
    else if (strcmp(Command[0], "seek")==0)
    {
        seek_seek(command);
    }
    
    else
    {
        other_system_commands(command, command1.print_pid_and_background);
    }
}